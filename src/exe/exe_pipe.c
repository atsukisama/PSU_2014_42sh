/*
** exe_pipe.c for 42sh in /home/cano_c/rendu/UNIX/42sh/PSU_2014_42sh/42tmp
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Fri May 15 10:38:48 2015 Chloe Cano
** Last update Mon May 25 01:33:10 2015 Jimmy KING
*/

#include <mysh.h>
#include <sys/types.h>
#include <sys/select.h>
#include <signal.h>
#include <stdio.h>

int		exe_pipe_right(t_ast *ast, t_mysh *sh, int *pfd, t_job *job)
{
  int		fd;

  sh->wait = 1;
  close(pfd[1]);
  if ((fd = dup(0)) != -1)
    {
      if (dup2(pfd[0], 0) < 0)
	return (-1);
      sh->exe_ft[ast->type](ast, sh, job);
      if (dup2(fd, 0) < 0)
	return (-1);
      return (sh->status);
    }
  return (-1);
}

void		exe_pipe_left(t_ast *ast, t_mysh *sh, int *pfd, t_job *job)
{
  close(pfd[0]);
  setpgid(getpid(), job->pgid);
  if (dup2(pfd[1], 1) != -1)
    {
      sh->exe_ft[ast->type](ast, sh, job);
      exit(0);
    }
  write(2, "42sh: error on dup2\n", 20);
  exit(EXIT_FAILURE);
}

int		exe_pipe(t_ast *ast, t_mysh *sh, t_job *job)
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
  if (!pid && (job->pgid || (job->pgid = getpid())))
    exe_pipe_left(ast->left, sh, pfd, job);
  else if (pid && (job->pgid || (job->pgid = pid)))
    exe_pipe_right(ast->right, sh, pfd, job);
  return (sh->status);
}
