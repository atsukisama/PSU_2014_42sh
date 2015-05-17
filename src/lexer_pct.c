/*
** lex_pct.c for 42sh in /home/cano_c/rendu/UNIX/42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Sun May 10 02:13:58 2015 
** Last update Fri May 15 19:47:24 2015 
*/
#include <parser.h>

int		lex_and(t_lex *lex, char **line, char UN *types)
{
  ++(*line);
  ++lex->len;
  return (LX_AND);
}

int		lex_amp(t_lex *lex, char **line, char *types)
{
  ++(*line);
  ++lex->len;
  if (LX_XPECT(*line, types, C_AMP))
    return (lex_and(lex, line, types));
  if (LX_XPECT(*line, types, C_GTHAN))
    return (lex_redto(lex, line, types));
  return (LX_ERR);
}

int		lex_or(t_lex *lex, char **line, char UN *types)
{
  ++(*line);
  ++lex->len;
  return (LX_OR);
}

int		lex_bar(t_lex *lex, char **line, char *types)
{
  ++(*line);
  ++lex->len;
  if (LX_XPECT(*line, types, C_BAR))
    return (lex_or(lex, line, types));
  return (LX_BAR);
}
