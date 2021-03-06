/*
** sh_lexer.c for 42sh in /home/cano_c/rendu/UNIX/42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Mon May  4 06:14:56 2015
** Last update Wed Jun  3 03:40:44 2015 Jimmy KING
*/

#include <parser.h>
#include <stdio.h>

void		set_types(char *types)
{
  size_t	idx;

  idx = 0;
  while (idx < 256)
    {
      if (idx == ';')
	types[idx] = C_DCOM;
      else if (idx == '&')
	types[idx] = C_AMP;
      else if (idx == '|')
	types[idx] = C_BAR;
      else if (idx == '>')
	types[idx] = C_GTHAN;
      else if (idx == '<')
	types[idx] = C_LTHAN;
      else if (idx == '\\')
	types[idx] = C_ESC;
      else if (idx == ' ' || idx == '\t')
	types[idx] = C_SPC;
      else if (!idx)
	types[idx] = C_EOL;
      else
	types[idx] = C_DFLT;
      ++idx;
    }
}

void		lex_init_xpect(char **line, char *types, t_lex *new_lex)
{
  if (!**line)
    new_lex->type = LX_EOL;
  else if (LX_XPECT(*line, types, C_DFLT))
    new_lex->type = lex_idt(new_lex, line, types);
  else if (LX_XPECT(*line, types, C_DCOM))
    new_lex->type = lex_sep(new_lex, line, types);
  else if (LX_XPECT(*line, types, C_AMP))
    new_lex->type = lex_amp(new_lex, line, types);
  else if (LX_XPECT(*line, types, C_BAR))
    new_lex->type = lex_bar(new_lex, line, types);
  else if (LX_XPECT(*line, types, C_GTHAN))
    new_lex->type = lex_redto(new_lex, line, types);
  else if (LX_XPECT(*line, types, C_LTHAN))
    new_lex->type = lex_redti(new_lex, line, types);
  else if (LX_XPECT(*line, types, C_ESC))
    new_lex->type = lex_idt(new_lex, line, types);
  else
    new_lex->type = LX_ERR;
}

int		lex_init(t_lex **lex, char *line, char *types)
{
  int		ret;
  t_lex		*new_lex;

  ret = LX_INIT;
  while (ret != LX_ERR && ret != LX_EOL)
    {
      while (*line && types[(int)*line] == C_SPC)
	++line;
      if (!(new_lex = lex_append_new(lex, line)))
	return (-1);
      lex_init_xpect(&line, types, new_lex);
      ret = new_lex->type;
    }
  if (ret == LX_ERR && *line)
    fprintf(stderr, "mysh: lexing error: unexpected token \'%c\'\n", *line);
  else if (ret == LX_ERR)
    fprintf(stderr, "mysh: lexing error: unexpected end of line\n");
  return (ret);
}

t_lex		*lexer(char *line)
{
  t_lex		*lex;
  char		types[256];

  lex = NULL;
  set_types(types);
  if (lex_init(&lex, line, types) == LX_ERR)
    return (NULL);
  return (lex);
}
