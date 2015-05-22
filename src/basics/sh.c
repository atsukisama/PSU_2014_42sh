/*
** sh.c for my_sh functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 10:21:40 2015 Vertigo
** Last update Fri May 22 21:04:10 2015 
*/

#include <stdio.h>
#include <mysh.h>
#include <sys/wait.h>
#include <get_next_line.h>

void		init_ast(t_mysh *sh)
{
  sh->exe_ft[PA_CMD] = exe_cmd;
  sh->exe_ft[PA_AND] = exe_and;
  sh->exe_ft[PA_OR] = exe_or;
  sh->exe_ft[PA_TRM] = exe_trm;
  sh->exe_ft[PA_RED] = exe_red;
  sh->exe_ft[PA_PIPE] = exe_pipe;
}

int	my_sh(t_mysh *sh)
{
  char	*line;
  t_lex	*lex;
  t_ast	*ast;

  sh->status = 0;
  sh->wait = 1;
  init_ast(sh);
  while ((sh->is_tty && (line = get_line(sh)))
	 || (!sh->is_tty && (line = get_next_line(0))))
    {
      if ((lex = lexer(line)))
	{
	  if ((ast = parse_init(lex)))
	    sh->status = sh->exe_ft[ast->type](ast, sh);
	  else
	    sh->status = 0;
	}
      while (waitpid(-1, NULL, WNOHANG) != -1)
	;
      can_set(sh->term);
    }
  if (sh->is_tty)
    can_set(sh->tsave);
  return (sh->status);
}
