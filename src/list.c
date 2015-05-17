/*
** list.c for list in /home/king_j/Git/Epitech/king_j/tmp/src/basics
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Wed May 13 21:14:10 2015 Jimmy KING
** Last update Sun May 17 17:48:18 2015 Vertigo
*/

#include <my.h>
#include <project.h>

/*
** Create and initialize a new linked list (type: t_list)
*/
t_list		*list_create()
{
  t_list	*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->next = new;
  new->prev = new;
  new->key = strdup("\0");
  return (new);
}

/*
** Add an new element to the linked list of type t_list
*/
t_list		*list_add(t_list *list, char *key, char *content)
{
  t_list	*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->key = key;
  new->content = content;
  new->next = list;
  new->prev = list->prev;
  list->prev->next = new;
  list->prev = new;
  return (new);
}

/*
** Delete a node from a linked list of type t_list
*/
void	list_delete_node(t_list *node)
{
  node->prev->next = node->next;
  node->next->prev = node->prev;
  free(node->key);
  free(node->content);
  free(node);
}

/*
** Get node by key
*/
t_list		*get_node_by_key(t_list	*list, char *key)
{
  t_list	*tmp;

  tmp = list->next;
  while (tmp != list)
    {
      if (xstrcmp(key, tmp->key) == 0)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

/*
** Count the number of entry in a linked list of type t_list
*/
int		list_count(t_list *list)
{
  t_list	*tmp;
  int		count;

  count = 0;
  tmp = list->next;
  while (tmp != list)
    {
      count++;
      tmp = tmp->next;
    }
  return (count);
}
