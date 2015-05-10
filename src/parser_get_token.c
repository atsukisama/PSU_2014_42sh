/*
** parser_get_token.c for 42sh in /home/cano_c/rendu/UNIX/42sh/src
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Tue May  5 11:48:18 2015 
** Last update Tue May  5 11:48:24 2015 
*/

#include <parser.h>

t_lex		*lexer_next_token(t_lex *lex)
{
  while (lex && lex->type == LX_IDT)
    lex = lex->next;
  return (lex);
}

void		lexer_rm_token(t_lex *tok, t_lex **lexems)
{
  t_lex		*p;
  t_lex		*tmp;

  p = *lexems;
  if (*lexems == tok)
    {
      if ((*lexems = (*lexems)->next))
	(*lexems)->prev = NULL;
      free(p);
    }
  else
    {
      while (p && p->next != tok)
	p = p->next;
      if (p)
	{
	  if (p->next == *lexems)
	    *lexems = (*lexems)->next;
	  tmp = p->next;
	  p->next = p->next->next;
	  p->next->prev = p;
	  free(tmp);
	}
    }
}
