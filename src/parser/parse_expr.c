/*
** parse_expr.c for 42sh in /home/cano_c/rendu/UNIX/42sh/src
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Tue May  5 11:51:38 2015 
** Last update Sat May 23 13:34:24 2015 
*/
#include <parser.h>

t_ast		*parse_expr(t_ast **ast, t_lex **lexem)
{
  t_lex		*next;
  t_ast		*e_ast;
  t_ast		*tmp;

  if (DEBUG_PARSER)
    my_putstr("parser -> EXPR\n");
  if (*lexem && (*lexem)->type != LX_EOL)
    {
      if (!(e_ast = parse_instr(ast, lexem)))
	return (NULL);
      while ((next = lexer_next_token(*lexem))
	     && (next->type == LX_SEP || next->type == LX_AMP))
	{
	  tmp = e_ast;
	  if (!(e_ast = make_binary(ast, &next)))
	    return (NULL);
	  *lexem = next->next;
	  e_ast->left = tmp;
	  if ((*lexem)->type != LX_EOL)
	    e_ast->right = parse_instr(ast, lexem);
	}
      *ast = e_ast;
    }
  if (*lexem && (*lexem)->type == LX_EOL)
    return (parse_end(ast, lexem));
  return (parse_err(ast, lexem));
}
