/*
** make_binary.c for 42sh in /home/cano_c/rendu/UNIX/42sh/src
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Tue May  5 11:48:42 2015 
** Last update Mon May 18 21:32:28 2015 
*/
#include <parser.h>

t_ast		*make_red(t_ast **ast, t_lex *lexem)
{
  t_ast		*red;

  if (!(red = make_binary(ast, &lexem)))
    return (NULL);
  my_memcpy(red->content.red, lexem->s, lexem->len > 3 ? 3 : lexem->len);
  red->type = PA_RED;
  if (!(red->left = make_leaf(ast, &lexem->next, PA_FILE)))
    {
      free(red);
      return (NULL);
    }
  return (red);
}

t_ast		*make_binary(t_ast **ast, t_lex **lex)
{
  t_ast		*bin;

  if (DEBUG_AST)
    my_putstr("ast -> make BINARY\n");
  if (!(bin = my_memalloc(sizeof(*bin))))
    return (NULL);
  if ((*lex)->type >= LX_BAR && (*lex)->type <= LX_OR)
    {
      bin->type = PA_AND;
      if (*(*lex)->s == '|')
	bin->type = (*lex)->type == LX_BAR ? PA_PIPE : PA_OR;
    }
  else if ((*lex)->type == LX_SEP)
    bin->type = PA_TRM;
  else if ((*lex)->type == LX_AMP)
    bin->type = PA_BG;
  else if ((*lex)->type >= LX_REDTO && (*lex)->type <= LX_REDI)
    bin->type = PA_RED;
  else
    return (parse_err(ast, lex));
  return (bin);
}
