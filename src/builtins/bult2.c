/*
** bult.c for  in /home/rusig_n/rendu/minishell2/PSU_2014_minishell2
** 
** Made by nicolas rusig
** Login   <rusig_n@epitech.net>
** 
** Started on  Sun Mar  8 17:54:31 2015 nicolas rusig
** Last update Wed Jun  3 11:33:42 2015 
*/

#include	<termios.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<project.h>
#include	<mysh.h>

int		chk_bult_b2(char **cmd)
{
  if (cmd[0] && my_strcmp("cd", cmd[0]) == 0)
    return (1);
  else if (cmd[0] && my_strcmp("echo", cmd[0]) == 0)
    return (1);
  else if (cmd[0] && my_strcmp("history", cmd[0]) == 0)
    return (1);
  else if (cmd[0] && my_strcmp("alias", cmd[0]) == 0)
    return (1);
  else if (cmd[0] && my_strcmp("unalias", cmd[0]) == 0)
    return (1);
  else if (cmd[0] && my_strcmp("source", cmd[0]) == 0)
    return (1);
  else if (cmd[0] && cmd[0][0] == '!')
    return (1);
  else if (cmd[0] && my_strcmp("exit", cmd[0]) == 0)
    {
      return (1);
    }
  return (0);
}

int		chk_bult_b(char **cmd)
{
  if (cmd[0][0] == '\0')
    return (0);
  else if (my_strcmp("env", cmd[0]) == 0)
    {
      return (1);
    }
  else if (cmd[0] && my_strcmp("setenv", cmd[0]) == 0)
    return (1);
  else if (cmd[0] && my_strcmp("unsetenv", cmd[0]) == 0)
    return (1);
  return (chk_bult_b2(cmd));
}
