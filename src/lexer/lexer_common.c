/*
** lex_common.c for 42sh in /home/cano_c/rendu/UNIX/42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Sun May 10 02:12:09 2015 
** Last update Sun May 24 23:26:26 2015 
*/
#include <parser.h>

int		lex_idt(t_lex *lex, char **line, char *types)
{
  int		type;

  type = types[(int)*(*line + lex->len)];
  while (type == C_DFLT || type == C_ESC)
    {
      if (type == C_ESC && *(*line + lex->len + 1))
	++lex->len;
      else if (type && (*line += lex->len))
	return (LX_ERR);
      ++lex->len;
      type = types[(int)*(*line + lex->len)];
    }
  *line += lex->len;
  return (LX_IDT);
}

int		lex_sep(t_lex *lex, char **line, char *types)
{
  while (types[(int)**line] == C_DCOM)
    ++(*line);
  lex->len = 1;
  return (LX_SEP);
}
