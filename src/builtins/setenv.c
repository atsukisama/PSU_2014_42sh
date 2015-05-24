/*
** my_setenv.c for  in /home/rusign/rendu/42sh/PSU_2014_42sh/bultin
** 
** Made by rusig_n
** Login   <nicolas.rusig@epitech.eu>
** 
** Started on  Thu May 14 11:50:32 2015 rusig_n
** Last update Sun May 17 17:42:02 2015 Vertigo
*/

#include <stdlib.h>
#include <unistd.h>
#include "project.h"

int		check_dol(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] == '$')
	return (1);
      i++;
    }
  return (0);
}

char		*dol_to_str(t_mysh *sh, char *str, int *i)
{
  int		len;
  char		*var;
  char		*val;
  int		k;

  k = 0;
  len = get_dol_size(str, ++(*i));
  var = my_malloc(sizeof(char *) * len, sh);
  while (len > 0)
    {
      var[k++] = str[(*i)++];
      len--;
    }
  var[k] = 0;
  if ((val = get_var_env(sh->env_list, var)) == NULL)
    {
      fprintf(stderr, "%s: Undefined variable\n", var);
      return (NULL);
    }
  free(var);
  return (val);
}


char		*convert_dol(char *str, t_mysh *sh)
{
  int		i;
  int		j;
  int		k;
  char		*tmp;
  char		*val;

  i = 0;
  j = 0;
  tmp = my_malloc(sizeof(char *) * my_strlen(str), sh);
  while (str[i])
    {
      k = 0;
      if (str[i] == '$')
	{
	  if ((val = dol_to_str(sh, str, &i)) == NULL)
	    return (NULL);
	  while (val[k])
	    tmp[j++] = val[k++];
	}
      else
	tmp[j++] = str[i++];
    }
  tmp[j] = 0;
  return (tmp);
}

int		my_setenv(t_mysh *sh, char **cmd)
{
  char		*var;
  char		*val;

  if (cmd[1] == NULL)
    {
      env_show(sh->env_list);
      return (1);
    }
  var = cmd[1];
  if (check_dol(var))
    if ((var = (convert_dol(var, sh))) == NULL)
      return (-1);
  if (cmd[2] == NULL)
    env_set(sh->env_list, var, "");
  else
    {
      val = cmd[2];
      if (check_dol(val))
	if ((val = (convert_dol(val, sh))) == NULL)
	  return (-1);
      if (var == NULL)
	return (my_puterror("error var null\n", -1));
      env_set(sh->env_list, var, val);
    }
  return (1);
}
