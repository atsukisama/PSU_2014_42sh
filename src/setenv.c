/*
** my_setenv.c for  in /home/rusign/rendu/42sh/PSU_2014_42sh/bultin
** 
** Made by rusig_n
** Login   <nicolas.rusig@epitech.eu>
** 
** Started on  Thu May 14 11:50:32 2015 rusig_n
** Last update Thu May 14 11:50:32 2015 rusig_n
*/

#include <stdlib.h>
#include <unistd.h>
#include "project.h"

char	*add_egale(char *var)
{
  int	size;
  char	*tmp;
  int	i;

  size = my_strlen(var);
  if ((tmp = (char*)malloc(size + 2)) == NULL)
    return (NULL);
  i = 0;
  while (var[i])
  {
    tmp[i] = var[i];
    i = i + 1;
  }
  tmp[i++] = '=';
  tmp[i] = 0;
  return (tmp);
}

int		my_setenv(t_list *list, char **cmd)
{
  if (cmd[1] == NULL)
    return (my_puterror("usage: setenv [key] [content] or setenv [key] \n", -1));
  if (cmd[2] == NULL)
    env_set(list, cmd[1], "");
  else
    {
      if (cmd[1] == NULL || my_strlen(cmd[1]) == 0
	  || my_strchr(cmd[1], '=') != NULL)
	return (my_puterror("error cmd[1] null\n", -1));
      env_set(list, cmd[1], cmd[2]);
    }
  return (1);
}
