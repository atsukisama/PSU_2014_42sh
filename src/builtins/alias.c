/*
** alias.c for alias in /home/king_j/AZEAZEAZ/PSU_2014_42sh/src/builtins
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Sun May 24 20:48:23 2015 Jimmy KING
** Last update Wed Jun  3 13:12:40 2015 Jimmy KING
*/

#include <mysh.h>

char		*tab_to_str(char **tab)
{
  int		i;
  char		*str;
  int		len;

  i = 0;
  len = 0;
  while (tab[i] != NULL)
    len = len + strlen(tab[i++]) + 1;
  if ((str = malloc(sizeof(char) * len)) == NULL)
    return (NULL);
  i = 0;
  if (str != NULL)
    str[0] = '\0';
  while (tab[i] != NULL)
    {
      strcat(str, tab[i]);
      if (tab[i + 1] != NULL)
	strcat(str, " ");
      i++;
    }
  return (str);
}

int		my_alias(t_mysh *sh, char **cmd)
{
  char		*str;
  t_list	*tmp;

  if (cmd[1] != NULL && cmd[2] != NULL)
    {
      if ((str = tab_to_str(cmd)) != NULL)
	alias_getcontent(sh->alias, str);
    }
  else if (count_dab(cmd) == 1)
    {
      tmp = sh->alias->next;
      while (tmp != sh->alias)
	{
	  printf("%s\t%s\n", tmp->key, tmp->content);
	  tmp = tmp->next;
	}
    }
  else
    return (-1);
  return (1);
}

int		my_unalias(t_mysh *sh, char **cmd)
{
  t_list	*tmp;

  if (cmd[1] != NULL)
    {
      tmp = sh->alias->next;
      while (tmp != sh->alias)
	{
	  if (match(tmp->key, cmd[1]) == 1)
	    list_delete_node(tmp);
	  tmp = tmp->next;
	}
    }
  else
    {
	fprintf(stderr, "unalias: Too few arguments.\n");
      return (-1);
    }
  return (1);
}

int		my_source(t_mysh *sh, char **cmd)
{
  if (cmd[1] != NULL)
    {
      if (access(cmd[1], F_OK) == 0)
	{
	  alias_openfile(sh->alias, cmd[1]);
	  return (1);
	}
      else
	{
	  fprintf(stderr, "%s: No such file or directory.\n", cmd[1]);
	  return (-1);
	}
    }
  else
    {
      fprintf(stderr, "source: Too few arguments.\n");
      return (-1);
    }
  return (0);
}
