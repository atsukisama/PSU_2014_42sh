/*
** lex_common.c for 42sh in /home/cano_c/rendu/UNIX/42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Sun May 10 02:12:09 2015 
** Last update Sun May 10 02:12:14 2015 
*/
#include <parser.h>

int		lex_idt(t_lex *lex, char **line, char *types)
{
  while (types[(int)*(*line + lex->len)] == C_DFLT)
    ++lex->len;
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
