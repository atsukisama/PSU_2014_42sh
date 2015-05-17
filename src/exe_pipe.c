/*
** exe_pipe.c for 42sh in /home/cano_c/rendu/UNIX/42sh/PSU_2014_42sh/42tmp
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Fri May 15 10:38:48 2015 
** Last update Sun May 17 17:38:59 2015 Vertigo
*/
#include <mysh.h>
#include <sys/types.h>
#include <signal.h>

int		exe_pipe_right(t_ast *ast, t_mysh *sh, int *pfd)
{
  int		fd;

  sh->wait = 1;
  close(pfd[1]);
  if ((fd = dup(0)) != -1)
    {
      if (dup2(pfd[0], 0) < 0)
	return (-1);
      sh->exe_ft[ast->type](ast, sh);
      if (dup2(fd, 0) < 0)
	return (-1);
      return (0);
    }
  return (-1);
}

void		exe_pipe_left(t_ast *ast, t_mysh *sh, int *pfd)
{
  close(pfd[0]);
  if (dup2(pfd[1], 1) != -1)
    exit(sh->exe_ft[ast->type](ast, sh));
  write(2, "42sh: error on dup2\n", 20);
  exit(EXIT_FAILURE);
}

int		exe_pipe(t_ast *ast, t_mysh *sh)
{
  int		pfd[2];
  int		pid;

  sh->wait = 0;
  if (pipe(pfd) == -1)
    {
      write(2, "42sh: error on pipe.\n", 21);
      return (-1);
    }
  if ((pid = fork()) == -1)
    {
      write(2, "42sh: error on fork.\n", 22);
      return (-1);
    }
  if (!pid)
    exe_pipe_left(ast->left, sh, pfd);
  else if (exe_pipe_right(ast->right, sh, pfd))
    {
      kill(pid, SIGKILL);
      return (-1);
    }
  return (0);
}
