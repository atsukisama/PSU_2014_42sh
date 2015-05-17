/*
** environement_2.c for environment in /home/king_j/Git/Epitech/king_j/tmp/src/core
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Thu May 14 04:57:45 2015 Jimmy KING
** Last update Sun May 17 17:36:40 2015 Vertigo
*/

#include "project.h"

char    *str_ass(char *dest, char *src, char *src2)
{
  int   n;
  int   i;

  n = 0;
  i = 0;
  while (src[n])
    {
      dest[n] = src[n];
      n++;
    }
  dest[n++] = '=';
  while (src2[i])
    {
      dest[n + i] = src2[i];
      i++;
    }
  dest[n + i] = '\0';
  return (dest);
}

/*
** Generate environment tab
*/
char		**env_to_tab(t_list *list)
{
  int           n;
  t_list        *tmp;
  char          **env;

  if ((env = malloc((list_count(list) + 1) * 8)) == NULL)
    return (NULL);
  n = 0;
  tmp = list->next;
  while (n < list_count(list))
    {
      if ((env[n] = malloc(xlen(tmp->key) + xlen(tmp->content) + 2)) == NULL)
	return (NULL);
      env[n] = str_ass(env[n], tmp->key, tmp->content);
      n++;
      tmp = tmp->next;
    }
  env[n] = NULL;
  return (env);
}

/*
** Replace the first tilde in str
*/
char            *env_replace_tilde(t_list *list, char *str, int *err)
{
  t_list        *tmp;

  if ((tmp = get_node_by_key(list, "HOME")) == NULL)
    {
      *err = 2;
      return (NULL);
    }
  if (str[0] == '~')
    str = xreplace(str, "~", tmp->content);
  return (str);
}
