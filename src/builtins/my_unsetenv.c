/*
** my_unsetenv.c for  in /home/rusign/rendu/42sh/PSU_2014_42sh/bultin
** 
** Made by rusig_n
** Login   <nicolas.rusig@epitech.eu>
** 
** Started on  Thu May 14 11:17:28 2015 rusig_n
** Last update Wed Jun  3 13:26:40 2015 Jimmy KING
*/

#include <my.h>
#include <project.h>

int	chk_var(char *var)
{
  if (var == NULL)
    {
      my_putstr("usage: unsetenv var\n");
      return (-1);
    }
  return (0);
}

int	my_unsetenv(t_mysh *sh, char **cmd)
{
  char	*var;
  int	i;

  i = 0;
  if (chk_var(cmd[1]) == -1)
    return (-1);
  if (cmd[1] == NULL || my_strlen(cmd[1]) == 0
      || my_strchr(cmd[1], '=') != NULL)
    return (my_puterror("usage : usetenv var\n", -1));
  while (cmd[i])
    {
      var = cmd[i];
      if (check_dol(var))
	if ((var = (convert_dol(var, sh))) == NULL)
	  return (-1);
      env_unset(sh->env_list, var);
      i++;
    }
  return (1);
}
