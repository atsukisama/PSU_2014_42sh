/*
** doublearray.c for double array functions in /home/gascon/Epitech/PSU/PSU_2014_my_ls
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 20 13:12:12 2015 Vertigo
** Last update Sat May 23 20:07:13 2015 Vertigo
*/

#include <string.h>
#include <stdlib.h>
#include <my.h>

void	free_dab(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != NULL)
    {
      free(tab[i]);
      ++i;
    }
}

int	count_dab(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != NULL)
    ++i;
  return (i);
}

char	**add_line(char **tab, char *s)
{
  char	**new;
  int	nb;
  int	i;

  nb = count_dab(tab);
  i = 0;
  if (!(new = malloc(sizeof(*new) * (nb + 2))))
    return (NULL);
  while (i < nb)
    {
      new[i] = my_strdup(tab[i]);
      ++i;
    }
  new[i++] = my_strdup(s);
  new[i] = NULL;
  return (new);
}
