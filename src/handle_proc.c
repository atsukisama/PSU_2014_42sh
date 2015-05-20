/*
** handle_proc.c for 42sh in /home/cano_c/rendu/UNIX/PSU_2014_42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Wed May 20 19:14:07 2015
** Last update Wed May 20 19:21:43 2015 
*/
#include <mysh.h>

int		wait_proc(t_mysh *sh, int pid)
{
  int		status;

  status = 0;
  if (sh->wait)
    {
      while (waitpid(-1, &status, 0) != pid)
	status = exit_status(status, sh);
      status = exit_status(status, sh);
    }
  return (status);
}
