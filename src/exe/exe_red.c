/*
** redir.c for redir functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Fri May 15 14:36:48 2015 Vertigo
** Last update Sun May 24 22:27:20 2015 Jimmy KING
*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <parser.h>
#include <mysh.h>
#include <stdio.h>

int		open_failure(char *file, int flags)
{
  struct stat	s_stat;

  if (access(file, F_OK))
    {
      if (flags & O_TRUNC)
	fprintf(stderr, "42sh: %s: cannot create file\n", file);
      else
	fprintf(stderr, "42sh: %s: no such file or directory\n", file);
    }
  else if ((flags & O_WRONLY && access(file, W_OK))
	   || (!flags && access(file, R_OK)))
    fprintf(stderr, "42sh: %s: permission denied\n", file);
  else if (flags && !(stat(file, &s_stat)) && S_ISDIR(s_stat.st_mode))
    fprintf(stderr, "42sh: %s: is a directory\n", file);
  else
    fprintf(stderr, "42sh: %s: undefined error at open\n", file);
  return (-1);
}

int	do_red(int red_fd[3], t_ast *ast, t_mysh *sh, t_job *job)
{
  int	fd;
  int	save_fd[2];

  if ((fd = open(ast->left->content.file, red_fd[2], 0644)) < 0)
    return (open_failure(ast->left->content.file, red_fd[2]));
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
  int	red_fd[3];
  int	ret;

  red_fd[2] = 0;
  red_fd[1] = -1;
  if (ast->content.red[0] == '&')
    swap_red(ast, red_fd);
  if (ast->content.red[0] == '<')
    {
      red_fd[2] = O_RDONLY;
      red_fd[0] = 0;
    }
  else if (ast->content.red[0] == '>')
    {
      red_fd[2] = O_WRONLY | O_CREAT;
      red_fd[0] = 1;
    }
  if (ast->content.red[1] && (red_fd[2] & O_WRONLY))
    red_fd[2] |= O_APPEND;
  else if (red_fd[2] & O_WRONLY)
    red_fd[2] |= O_TRUNC;
  ret = dash_left_check(red_fd, ast, sh, job);
  return (ret);
}
