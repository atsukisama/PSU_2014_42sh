/*
** lex_lst.c for 42sh in /home/cano_c/rendu/UNIX/42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Sun May 10 02:15:37 2015 
** Last update Wed Jun  3 03:40:59 2015 Jimmy KING
*/

#include <parser.h>

t_lex		*lex_append_new(t_lex **lex, char *line)
{
  t_lex		*new;
  t_lex		*tmp;

  if (!(new = my_memalloc(sizeof(*new))))
    return (NULL);
  new->s = line;
  if (!*lex)
    *lex = new;
  else
    {
      tmp = *lex;
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = new;
      tmp->next->prev = tmp;
    }
  return (new);
}

void		free_lex(t_lex *lex)
{
  t_lex		*tmp;

  while (lex)
    {
      tmp = lex;
      write(1, lex->s, lex->len);
      write(1, "\n", 1);
      lex = lex->next;
      free(tmp);
    }
}
