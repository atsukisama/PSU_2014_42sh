/*
** free.c for free function in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Sat May 23 19:49:24 2015 Vertigo
** Last update Sat May 23 19:58:27 2015 Vertigo
*/

#include <autocomplet.h>

void		free_select()
{
  t_complet	*tmp;
  t_complet	*next;

  tmp = g_select.args->next;
  while (tmp != g_select.args)
    {
      next = tmp->next;
      complet_delete(tmp);
      tmp = next;
    }
}
