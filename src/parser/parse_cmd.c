/*
** parse_cmd.c for 42sh in /home/cano_c/rendu/UNIX/42sh/src
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Tue May  5 11:49:27 2015 
** Last update Tue May 19 19:12:09 2015 
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

t_ast		*parse_pipeline(t_ast **ast, t_lex **lexem)
{
  t_lex		*next;
  t_ast		*i_ast;
  t_ast		*tmp;

  if (DEBUG_PARSER)
    my_putstr("parser -> PIPELINE\n");
  if (!(i_ast = parse_cmd(ast, lexem)))
    return (NULL);
  while ((next = lexer_next_token(*lexem)) && next->type == LX_BAR)
    {
      tmp = i_ast;
      if (!(i_ast = make_binary(ast, &next)))
	return (NULL);
      i_ast->left = tmp;
      *lexem = next->next;
      if (!(i_ast->right = parse_cmd(ast, lexem)))
	return (NULL);
    }
  return (i_ast);
}
