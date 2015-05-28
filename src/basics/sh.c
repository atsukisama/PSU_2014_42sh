/*
** sh.c for my_sh functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 10:21:40 2015 Vertigo
** Last update Thu May 28 18:51:25 2015 Vertigo
*/

#include <stdio.h>
#include <sys/wait.h>
#include <mysh.h>
#include <get_next_line.h>
#include <project.h>

void		init_ast(t_mysh *sh)
{
  sh->exe_ft[PA_CMD] = exe_cmd;
  sh->exe_ft[PA_AND] = exe_and;
  sh->exe_ft[PA_OR] = exe_or;
  sh->exe_ft[PA_TRM] = exe_trm;
  sh->exe_ft[PA_BG] = exe_bg;
  sh->exe_ft[PA_RED] = exe_red;
  sh->exe_ft[PA_PIPE] = exe_pipe;
}

int	my_sh(t_mysh *sh)
{
  char	*line;

  sh->status = 0;
  sh->wait = 1;
  init_ast(sh);
  while ((sh->is_tty && (line = get_line(sh)))
	 || (!sh->is_tty && (line = get_next_line(0))))
    {
      line = alias_replace(sh->alias, line);
      if (exe_histo(line, sh) == -1)
	return (-1);
      while (waitpid(-1, NULL, WNOHANG) != -1)
	;
      tcsetpgrp(0, sh->pgid);
      if (sh->is_tty)
	can_set(sh->term);
      if (sh->ret_exit != 0)
	break;
    }
  if (sh->is_tty)
    can_set(sh->tsave);
  return (sh->status);
}
