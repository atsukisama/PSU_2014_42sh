/*
** redir.c for redir functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Fri May 15 14:36:48 2015 Vertigo
** Last update Tue May 19 00:10:25 2015 
*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <parser.h>
#include <mysh.h>
#include <stdio.h>

int	file_perms(char *file, int flags)
{
  if (!(flags & O_CREAT))
    {
      if (access(file, F_OK))
	{
	  fprintf(stderr, "mysh: %s: no such file or directory\n", file);
	  return (-1);
	}
      if (flags & O_WRONLY && access(file, O_WRONLY))
	{
	  fprintf(stderr, "mysh: %s: permission denied\n", file);
	  return (-1);
	}
      if (flags & O_RDONLY && access(file, O_RDONLY))
	{
	  fprintf(stderr, "mysh: %s: permission denied\n", file);
	  return (-1);
	}
    }
  return (0);
}

int	do_red(int red_fd[2], int flags[2], t_ast *ast, t_mysh *sh, t_job *job)
{
  int	fd;
  int	save_fd[2];

  if (file_perms(ast->left->content.file, flags[0]))
    return (-1);
  if ((fd = open(ast->left->content.file, flags[0], flags[1])) < 0)
    return (-1);
  save_fd[0] = dup(red_fd[0]);
  if (red_fd[1] > -1)
    {
      save_fd[1] = dup(red_fd[1]);
      dup2(fd, red_fd[1]);
    }
  dup2(fd, red_fd[0]);
  sh->status = sh->exe_ft[ast->right->type](ast->right, sh, job);
  dup2(save_fd[0], red_fd[0]);
  if (red_fd[1] > -1)
    dup2(save_fd[0], red_fd[1]);
  return (sh->status);
}

int	swap_red(t_ast *ast, int red_fd[2])
{
  ast->content.red[0] = ast->content.red[1];
  ast->content.red[1] = ast->content.red[2];
  ast->content.red[2] = 0;
  red_fd[1] = 2;
  return (0);
}

int	exe_red(t_ast *ast, t_mysh *sh, t_job *job)
{
  int	flags[2];
  int	red_fd[2];
  int	ret;

  flags[0] = 0;
  flags[1] = 0;
  red_fd[1] = -1;
  if (ast->content.red[0] == '&')
    swap_red(ast, red_fd);
  if (ast->content.red[0] == '<')
    {
      flags[1] = 0400;
      flags[0] = O_RDONLY | O_APPEND;
      red_fd[0] = 0;
    }
  else if (ast->content.red[0] == '>')
    {
      flags[1] = 0644;
      flags[0] = O_WRONLY | O_CREAT;
      red_fd[0] = 1;
    }
  if (ast->content.red[1] && (flags[0] & O_WRONLY))
    flags[0] |= O_APPEND;
  else if (flags[0] & O_WRONLY)
    flags[0] |= O_TRUNC;
  ret = do_red(red_fd, flags, ast, sh, job);
  return (ret);
}
