/*
** lexer.h for 42sh in /home/cano_c/rendu/UNIX/42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Mon May  4 06:17:13 2015 
** Last update Fri May 15 13:33:04 2015 
*/

#ifndef LEXER_H_
# define LEXER_H_

# include <unistd.h>
# include <stdlib.h>
# include <my.h>

# define LX_XPECT(line, types, tok)	(types[(int)(*line)] == (tok) ? 1 : 0)

typedef struct s_lex	t_lex;

struct		s_lex
{
  char		*s;
  size_t	len;
  int		type;
  t_lex		*next;
  t_lex		*prev;
};

enum		e_char_type
  {
    C_DFLT,
    C_DCOM,
    C_AMP,
    C_BAR,
    C_LTHAN,
    C_GTHAN,
    C_SPC,
    C_ESC,
    C_EOL
  };

enum		e_lex_type
  {
    LX_INIT,
    LX_IDT,
    LX_TOK,
    LX_SEP,
    LX_AMP,
    LX_BAR,
    LX_AND,
    LX_OR,
    LX_REDTO,
    LX_REDO,
    LX_REDTI,
    LX_REDI,
    LX_EOL,
    LX_ERR
  };

t_lex		*lexer(char *s);

int		lex_idt(t_lex *lex, char **line, char* types);
int		lex_sep(t_lex *lex, char **line, char *types);
int		lex_redti(t_lex *lex, char **line, char *types);
int		lex_redto(t_lex *lex, char **line, char *types);
int		lex_redi(t_lex *lex, char **line, char *types);
int		lex_redo(t_lex *lex, char **line, char *types);
int		lex_and(t_lex *lex, char **line, char *types);
int		lex_amp(t_lex *lex, char **line, char *types);
int		lex_or(t_lex *lex, char **line, char *types);
int		lex_bar(t_lex *lex, char **line, char *types);

t_lex		*lex_append_new(t_lex **lex, char *line);
void		free_lex(t_lex *lex);

#endif
