/*
** redir.c for redir functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Fri May 15 14:36:48 2015 Vertigo
** Last update Sun May 17 17:53:22 2015 Vertigo
*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <parser.h>
#include <mysh.h>

int	do_red(int red_fd[2], int flags, t_ast *ast, t_mysh *sh)
{
  int	fd;
  int	save_fd[2];

  if ((fd = open(ast->left->content.file, flags, 0644)) < 0)
    return (-1);
  save_fd[0] = dup(red_fd[0]);
  if (red_fd[1] > -1)
    {
      save_fd[1] = dup(red_fd[1]);
      dup2(fd, red_fd[1]);
    }
  dup2(fd, red_fd[0]);
  sh->status = sh->exe_ft[ast->right->type](ast->right, sh);
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

int	exe_red(t_ast *ast, t_mysh *sh)
{
  int	flags;
  int	red_fd[2];
  int	ret;

  flags = 0;
  red_fd[1] = -1;
  if (ast->content.red[0] == '&')
    swap_red(ast, red_fd);
  if (ast->content.red[0] == '<')
    {
      flags = O_RDONLY | O_APPEND;
      red_fd[0] = 0;
    }
  else if (ast->content.red[0] == '>')
    {
      flags = O_WRONLY | O_CREAT;
      red_fd[0] = 1;
    }
  if (ast->content.red[1] && (flags & O_WRONLY))
    flags |= O_APPEND;
  else if (flags & O_WRONLY)
    flags |= O_TRUNC;
  ret = do_red(red_fd, flags, ast, sh);
  return (ret);
}
