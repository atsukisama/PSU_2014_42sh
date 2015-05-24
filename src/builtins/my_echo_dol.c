/*
** my_echo.c for  in /home/rusign/rendu/42sh/PSU_2014_42sh/bultin
** 
** Made by rusig_n
** Login   <nicolas.rusig@epitech.eu>
** 
** Started on  Thu May 14 11:51:53 2015 rusig_n
** Last update Sun May 17 19:46:48 2015 Vertigo
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "project.h"

int	is_dol_print(char c, t_mysh *sh)
{
  char	*val;

  if ((c >= 'a' && c <= 'z')
      || (c >= 'A' && c <= 'Z')
      || c == '(' || c == ')'
      || c == '?' || c == '*' || c == '0')
    {
      if (c == '0')
	{
	  if ((val = get_var_env(sh->env_list, "SHELL")) == NULL)
	    return (0);
	  else
	    {
	      my_putstr(val);
	      return (0);
	    }
	}
      return (0);
    }
  else
    return (1);
}

int	get_dol_size(char *s, int i)
{
  int	j;

  j = 0;
  while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
    {
      i++;
      j++;
    }
  return (j);
}

int	echo_dol(char *s, int *i, t_mysh *sh, int j)
{
  char	*str;
  char	*val;

  (*i)++;
  if (is_dol_print(s[*i], sh) == 1)
    my_putchar('$');
  if (s[*i] == '?')
    {
      my_put_nbr(sh->status);
      *i += 1;
    }
  else
    {
      str = my_malloc(get_dol_size(s, *i) * sizeof(str), sh);
      j = 0;
      while ((s[*i] >= 'a' && s[*i] <= 'z') || (s[*i] >= 'A' && s[*i] <= 'Z'))
	str[j++] = s[(*i)++];
      str[j] = 0;
      if ((val = get_var_env(sh->env_list, str)) == NULL)
	return (0);
      else
	my_putstr(val);
      free(str);
    }
  return (0);
}
