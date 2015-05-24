/*
** environement.c for environment in /home/king_j/Git/Epitech/king_j/tmp/src/core
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Wed May 13 21:35:35 2015 Jimmy KING
** Last update Wed May 20 19:32:47 2015 Cano Chloe
*/

#include "project.h"

/*
** Collect the environment from a char ** to a t_list linked list
*/
void	env_collect(char **env, t_list *list)
{
  int	n;

  n = 0;
  while (env[n])
    {
      list_add(list, words_get(env[n], 1, "="), words_get(env[n], 2, "="));
      n++;
    }
}

/*
** Display the environment on the terminal
*/
void		env_show(t_list *list)
{
  t_list	*tmp;

  tmp = list->next;
  while (tmp != list)
    {
      my_putstr(tmp->key);
      my_putchar('=');
      my_putstr(tmp->content);
      my_putchar(10);
      tmp = tmp->next;
    }
}

char		*env_replacestr(t_list *list, char *content, int *err)
{
  char		*key;
  t_list	*tmp;

  while (we_count(content) != 0 && *err == 0)
    {
      key = we_get(content, 1);
      if ((tmp = get_node_by_key(list, key + 1)) != NULL)
	content = xreplace(content, key, tmp->content);
      else
	{
	  fprintf(stderr, "%s: Undefined variable.\n", key + 1);
	  *err = 1;
	}
    }
  content = env_replace_tilde(list, content, err);
  if (*err == 2)
    fprintf(stderr, "(~)HOME: Undefined variable.\n");
  return (content);
}

/*
** Add/Edit a environment variabe to/from t_list linked list
*/
int		env_set(t_list *list, char *key, char *content)
{
  t_list	*tmp;
  int		err;
  char		*parsed_content;

  err = 0;
  tmp = get_node_by_key(list, key);
  parsed_content = env_replacestr(list, content, &err);
  if (err == 0)
    {
      if (tmp == NULL)
	list_add(list, key, parsed_content);
      else
	tmp->content = parsed_content;
    }
  return (0);
}

/*
** Remove a environment variabe from t_list linked list
*/
int		env_unset(t_list *list, char *key)
{
  t_list	*tmp;

  tmp = get_node_by_key(list, key);
  if (tmp != NULL)
    list_delete_node(tmp);
  return (0);
}
