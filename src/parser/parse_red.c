/*
** parse_red.c for 42sh in /home/cano_c/rendu/UNIX/42sh/src
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Tue May  5 11:53:11 2015 
** Last update Sun May 17 17:55:38 2015 Vertigo
*/
#include <parser.h>

static t_ast	*add_cmd(t_ast **ast, t_ast *r_ast, t_lex **lexem, t_ast *tmp)
{
  if ((*lexem)->type == LX_IDT)
    {
      if (!(tmp->right = make_cmd(lexem)))
	return (NULL);
      return (r_ast);
    }
  return (parse_err(ast, lexem));
}

t_ast		*parse_red(t_ast **ast, t_lex **lexem)
{
  t_ast		*r_ast;
  t_lex		*next;
  t_lex		*to_rm;
  t_ast		*tmp;

  if (!(next = lexer_next_token(*lexem)))
    return (NULL);
  if (!(r_ast = make_red(ast, next)))
    return (NULL);
  lexer_rm_token(next->next, lexem);
  to_rm = next;
  tmp = r_ast;
  while ((next = lexer_next_token(next->next))
	 && next->type >= LX_REDTO && next->type <= LX_REDI)
    {
      lexer_rm_token(to_rm, lexem);
      if (!(tmp->right = make_red(ast, next)))
	return (NULL);
      tmp = tmp->right;
      lexer_rm_token(next->next, lexem);
      to_rm = next;
    }
  lexer_rm_token(to_rm, lexem);
  return (add_cmd(ast, r_ast, lexem, tmp));
}
