/*
** actions.c for actions in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Sat May 23 09:55:37 2015 Vertigo
** Last update Sat May 23 10:30:40 2015 Vertigo
*/

#include <autocomplet.h>

void		set_active(t_complet *args, int nb)
{
  t_complet	*tmp;
  int		i;

  i = 0;
  tmp = args->next;
  while (tmp != args)
    {
      if (i == nb)
	tmp->is_active = 1;
      else
	tmp->is_active = 0;
      ++i;
      tmp = tmp->next;
    }
}

void		set_selected(t_complet *args, int nb)
{
  t_complet	*tmp;
  int		i;

  i = 0;
  tmp = args->next;
  while (tmp != args)
    {
      if (i == nb)
	tmp->is_selected = ~tmp->is_selected;
      ++i;
      tmp = tmp->next;
    }
}

void		delete_item(t_complet *args, int nb)
{
  t_complet	*tmp;
  int		i;

  i = 0;
  tmp = args->next;
  while (tmp != args)
    {
      if (i == nb)
	{
	  complet_delete(tmp);
	  break;
	}
      ++i;
      tmp = tmp->next;
    }
}
