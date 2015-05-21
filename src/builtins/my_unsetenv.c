/*
** my_unsetenv.c for  in /home/rusign/rendu/42sh/PSU_2014_42sh/bultin
** 
** Made by rusig_n
** Login   <nicolas.rusig@epitech.eu>
** 
** Started on  Thu May 14 11:17:28 2015 rusig_n
** Last update Thu May 14 11:17:28 2015 rusig_n
*/

#include <my.h>
#include <project.h>

int		chk_var(char *var)
{
  if (var == NULL)
    {
      my_putstr("usage: unsetenv var\n");
      return (-1);
    }
  return (0);
}

int             my_unsetenv(t_list *list, char **cmd)
{
  if (chk_var(cmd[1]) == 1)
    return (-1);
  if (cmd[1] == NULL || my_strlen(cmd[1]) == 0
      || my_strchr(cmd[1], '=') != NULL)
    return (my_puterror("error : cmd[1] NULL\n", -1));
  env_unset(list, cmd[1]);
  return (1);
}
