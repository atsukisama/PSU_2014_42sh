/*
** parse_cmd.c for 42sh in /home/cano_c/rendu/UNIX/42sh/src
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Tue May  5 11:49:27 2015 
** Last update Tue May  5 11:49:34 2015 
*/
#include <parser.h>

t_ast		*parse_cmd(t_ast **ast, t_lex **lexem)
{
  t_ast		*c_ast;
  t_lex		*next;

  if (DEBUG_PARSER)
    my_putstr("parser -> CMD\n");
  c_ast = NULL;
  if ((next = lexer_next_token(*lexem))
      && next->type >= LX_REDTO && next->type <= LX_REDI)
    {
      if (!(c_ast = parse_red(ast, lexem)))
	return (NULL);
      return (c_ast);
    }
  else if ((*lexem)->type == LX_IDT)
    {
      if (!(c_ast = make_cmd(lexem)))
	return (NULL);
      return (c_ast);
    }
  return (parse_err(ast, lexem));
}
