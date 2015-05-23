/*
** alias.c for alias in /home/king_j/Git/Epitech/king_j/tmp2/src/alias
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Tue May 19 01:18:47 2015 Jimmy KING
** Last update Sat May 23 10:25:57 2015 Vertigo
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <get_next_line.h>
#include "project.h"

void		alias_getcontent(t_list *alias, char *str)
{
  char		*key;
  char		*cmd;
  t_list	*tmp;

  if (my_strncmp("alias", str, 5) == 0)
    {
      str = str + 6;
      key = words_get(str, 1, " \t");
      str = str + strlen(key) + 1;
      while (*str == '\t' || *str == ' ')
        str = str + 1;
      if (*str != '\0')
        {
          cmd = my_strdup(str);
	  if ((tmp = get_node_by_key(alias, key)) == NULL)
	    list_add(alias, key, cmd);
	  else
	    tmp->content = cmd;
        }
      else
        free(key);
    }
}

void    alias_openfile(t_list *alias, char *file)
{
  int   fd;
  char  *tmp;

  if ((fd = open(file, O_RDONLY)) == -1)
    printf("Error when oppening file : %s\n", file);
  else
    {
      while ((tmp = get_next_line(fd)) != NULL)
        {
          alias_getcontent(alias, tmp);
          free(tmp);
        }
    }
}

char		*alias_get(t_list *alias, char *key)
{
  t_list        *tmp;

  tmp = alias->next;
  while (tmp != alias)
    {
      if (my_strcmp(tmp->key, key) == 0)
        return (tmp->content);
      tmp = tmp->next;
    }
  return (NULL);
}

void		alias_initialize(t_list *alias)
{
  t_list        *alias_tmp;

  alias_openfile(alias, ".42rc");
  alias_tmp = alias->next;
  while (alias_tmp != alias)
    alias_tmp = alias_tmp->next;
}

char            *alias_replace(t_list *alias, char *cmd)
{
  t_list        *tmp_alias;
  t_list        *test;
  char          *tmp;
  int           n;

  tmp_alias = list_create();
  n = 0;
  while (n < words_count(cmd, "&;|<"))
    {
      tmp = words_get(cmd, n + 1, "&;|<");
      list_add(tmp_alias, tmp, tmp);
      n++;
    }
  test = tmp_alias->next;
  while (test != tmp_alias)
    {
      tmp = words_get(test->content, 1, " \0");
      if (alias_get(alias, tmp) != NULL)
	{
	  test->content = xreplace(test->content, tmp, alias_get(alias, tmp));
	  cmd = xreplace(cmd, test->key, test->content);
	}
      test = test->next;
    }
  return (cmd);
}
