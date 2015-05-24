/*
** util_bult.c for  in /home/rusign/test/PSU_2014_42sh/src/builtins
** 
** Made by rusig_n
** Login   <nicolas.rusig@epitech.eu>
** 
** Started on  Fri May 22 20:59:53 2015 rusig_n
** Last update Fri May 22 20:59:53 2015 rusig_n
*/

#include <my.h>
#include <mysh.h>
#include <stdlib.h>
#include <unistd.h>

int             size_histo(t_list *history)
{
  t_list        *tmp;
  int           max;

  max = 0;
  tmp = history->next;
  while (tmp != history)
    {
      tmp = tmp->next;
      max++;
    }
  return (max);
}

int		is_num(char *str)
{
  int		i;
  int		j;
  int		len;

  len = my_strlen(str);
  i = 0;
  j = 0;
  if (str != NULL)
    {
      if (str[i] == '-')
	{
	  i++;
	  j++;
	}
      while (str[i])
	{
	  if (str[i] > '0' && str[i] <= '9')
	    j++;
	  i++;
	}
    }
  if (j == len)
    return (0);
  else
    return (1);
}

int		check_cd_error(char **tab)
{
  DIR		*dir;

  if (tab[1] && (access(tab[1], F_OK & R_OK) == -1) && tab[1][0] != '-')
    {
      fprintf(stderr, "42sh: cd: %s : No such file or directory\n", tab[1]);
      return (-1);
    }
  if (tab[1] && tab[1][0] != '-' && (dir = opendir(tab[1])) == NULL)
    {
      fprintf(stderr, "42sh: cd: %s : Not a directory\n", tab[1]);
      return (-1);
    }
  return (0);
}

char		*my_malloc(int len, t_mysh *sh)
{
  char		*tmp;

  if ((tmp = malloc(len)) == NULL)
    {
      my_putstr("malloc error\n");
      my_exit_n(sh, NULL);
    }
  return (tmp);
}
