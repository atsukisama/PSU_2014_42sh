/*
** parse_instr.c for 42sh in /home/cano_c/rendu/UNIX/42sh/src
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Tue May  5 11:52:28 2015 
** Last update Sun May 10 02:31:17 2015 
*/
#include <parser.h>

t_ast		*parse_instr(t_ast **ast, t_lex **lexem)
{
  t_lex		*next;
  t_ast		*i_ast;
  t_ast		*tmp;

  if (DEBUG_PARSER)
    my_putstr("parser -> INSTR\n");
  if ((next = lexer_next_token(*lexem)) && next->type != LX_EOL)
    {
      if (!(i_ast = parse_cmd(ast, lexem)))
	return (NULL);
      while ((next = lexer_next_token(*lexem))
	     && next->type >= LX_BAR && next->type <= LX_OR)
	{
	  tmp = i_ast;
	  if (!(i_ast = make_binary(ast, &next)))
	    return (NULL);
	  i_ast->left = tmp;
	  *lexem = next->next;
	  if (!(i_ast->right = parse_cmd(ast, lexem)))
	    return (NULL);
	}
    }
  else if ((*lexem)->type != LX_EOL)
    return (parse_cmd(ast, lexem));
  return (i_ast);
}
