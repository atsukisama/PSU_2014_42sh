/*
** list_2.c for list 2 functions in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Sun May 17 17:46:58 2015 Vertigo
** Last update Sun May 17 17:48:54 2015 Vertigo
*/

#include <my.h>
#include <project.h>

char		*concat_var(char *key, char *content)
{
  size_t	key_len;
  size_t	content_len;
  char		*var;

  key_len = my_strlen(key);
  content_len = my_strlen(content);
  if (!(var = malloc(sizeof(*var) * (key_len + content_len + 2))))
    return (NULL);
  my_strncpy(var, key, key_len + 1);
  my_strncat(var, "=", 1);
  my_strncat(var, content, content_len + 1);
  return (var);
}

/*
** put chained list content into a null-terminated array of strings
*/
char		**list_to_tab(t_list *lst)
{
  t_list	*tmp;
  size_t	nb_elem;
  char		**tab;

  tmp = lst->next;
  nb_elem = 0;
  while (tmp != lst && ++nb_elem)
    tmp = tmp->next;
  if (!(tab = my_memalloc(sizeof(tab) * (nb_elem + 1))))
    return (NULL);
  nb_elem = 0;
  tmp = lst;
  lst = lst->next;
  while (lst != tmp)
    {
      if (!(tab[nb_elem++] = concat_var(lst->key, lst->content)))
        return (NULL);
      lst = lst->next;
    }
  return (tab);
}
