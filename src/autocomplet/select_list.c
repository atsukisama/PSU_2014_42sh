/*
** select.c for select list function in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Thu May 21 17:06:40 2015 Vertigo
** Last update Sat May 23 20:00:11 2015 Vertigo
*/

#include <autocomplet.h>

int		select_add_before(t_complet *list, char *name)
{
  t_complet	*new;

  if (!(new = malloc(sizeof(*new))))
    return (-1);
  new->name = name;
  new->lenght = my_strlen(name);
  new->is_active = 1;
  new->is_selected = 1;
  new->prev = list->prev;
  new->next = list;
  list->prev->next = new;
  list->prev = new;
  return (0);
}

t_complet	*select_create()
{
  t_complet	*new;

  if (!(new = malloc(sizeof(*new))))
    return (NULL);
  new->next = new;
  new->prev = new;
  return (new);
}

int		complet_count(t_complet *list)
{
  int		i;
  t_complet	*tmp;

  i = 0;
  tmp = list->next;
  while (tmp != list)
    {
      tmp = tmp->next;
      ++i;
    }
  return (i);
}

void	complet_delete(t_complet *node)
{
  node->prev->next = node->next;
  node->next->prev = node->prev;
  if (node->name != NULL)
    free(node->name);
  free(node);
}
