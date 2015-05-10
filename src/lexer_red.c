/*
** lexer_red.c for 42sh in /home/cano_c/rendu/UNIX/42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Sun May 10 02:18:43 2015 
** Last update Sun May 10 02:18:49 2015 
*/
#include <parser.h>

int		lex_redo(t_lex *lex, char **line, char UN *types)
{
  ++(*line);
  ++lex->len;
  return (LX_REDO);
}

int		lex_redi(t_lex *lex, char **line, char UN *types)
{
  ++(*line);
  ++lex->len;
  return (LX_REDI);
}

int		lex_redto(t_lex *lex, char **line, char *types)
{
  ++(*line);
  ++lex->len;
  if (LX_XPECT(*line, types, C_GTHAN))
    return (lex_redo(lex, line, types));
  return (LX_REDTO);
}

int		lex_redti(t_lex *lex, char **line, char *types)
{
  ++(*line);
  ++lex->len;
  if (LX_XPECT(*line, types, C_LTHAN))
    return (lex_redi(lex, line, types));
  return (LX_REDTI);
}
