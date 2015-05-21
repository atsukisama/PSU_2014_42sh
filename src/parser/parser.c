/*
** parser.c for 42sh in /home/cano_c/rendu/UNIX/42sh/src
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Tue May  5 11:52:52 2015 
** Last update Sun May 10 02:37:55 2015 
*/
#include <parser.h>

t_ast		*parse_err(t_ast UN **ast, t_lex **lex)
{
  t_lex		*tmp;

  if (DEBUG_PARSER)
    my_putstr("parser -> ERR\n");
  if (*lex && *(*lex)->s)
    {
      write(2, "mysh: parsing error: unexpected token \"", 40);
      write(2, (*lex)->s, (*lex)->len);
      write(2, "\"\n", 2);
    }
  else
    write(2, "mysh: parsing error: unexpected end of line\n", 44);
  while (*lex)
    {
      tmp = *lex;
      *lex = (*lex)->next;
      free(tmp);
    }
  return (NULL);
}

t_ast		*parse_end(t_ast **ast, t_lex **lexem)
{
  t_lex		*tmp;

  while ((*lexem)->prev)
    *lexem = (*lexem)->prev;
  while (*lexem)
    {
      tmp = *lexem;
      *lexem = (*lexem)->next;
      free(tmp);
    }
  if (DEBUG_PARSER)
    my_putstr("parser -> END\n");
  return (*ast);
}

t_ast		*insert_cmd(t_ast **ast, t_ast *cmd)
{
  if (!(*ast))
    *ast = cmd;
  if ((*ast)->type > PA_NODE && insert_cmd(&(*ast)->left, cmd))
    return (*ast);
  if ((*ast)->type > PA_NODE && insert_cmd(&(*ast)->right, cmd))
    return (*ast);
  return (NULL);
}

t_ast		*parse_init(t_lex *lexem)
{
  t_ast		*ast;

  ast = NULL;
  ast = parse_expr(&ast, &lexem);
  return (ast);
}
