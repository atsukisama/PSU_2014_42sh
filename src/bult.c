/*
** bult.c for  in /home/rusig_n/rendu/minishell2/PSU_2014_minishell2
** 
** Made by nicolas rusig
** Login   <rusig_n@epitech.net>
** 
** Started on  Sun Mar  8 17:54:31 2015 nicolas rusig
** Last update Fri May 15 12:34:45 2015 Vertigo
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"project.h"

int		my_exit(t_list *list, char **tab)
{
  int		ret;

  if (tab[1])
    ret = atoi(tab[1])
  exit(ret);
}

int		chk_bult2(t_list *list, char **cmd)
{
  if (cmd[0] && my_strcmp("cd", cmd[0]) == 0)
    {
      my_cd(list, cmd);
      return (1);
    }
  else if (cmd[0] && my_strcmp("echo", cmd[0]) == 0)
    {
      my_echo(cmd);
      return (1);
    }
  else if (cmd[0] && my_strcmp("exit", cmd[0]) == 0)
    {
      my_exit(list, cmd);
      return (1);
    }
  return (0);
}

int		chk_bult(t_list *list, char **cmd)
{
  int		i;

  if (cmd[0][0] == '\0')
    return (1);
  else if (my_strcmp("env", cmd[0]) == 0)
    {
      env_show(list);
      return (1);
    }
  else if (cmd[0] && my_strcmp("setenv", cmd[0]) == 0)
    {
      my_setenv(list, cmd);
      return (1);
    }
  else if (cmd[0] && my_strcmp("unsetenv", cmd[0]) == 0)
    {
      my_unsetenv(list, cmd);
      return (1);
    }
  return (chk_bult2(list, cmd));
}
