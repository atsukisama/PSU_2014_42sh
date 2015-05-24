/*
** bult.c for  in /home/rusig_n/rendu/minishell2/PSU_2014_minishell2
** 
** Made by nicolas rusig
** Login   <rusig_n@epitech.net>
** 
** Started on  Sun Mar  8 17:54:31 2015 nicolas rusig
** Last update Sun May 24 21:14:33 2015 Jimmy KING
*/

#include	<termios.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<project.h>
#include	<mysh.h>

int		my_exit_n(t_mysh *sh, char **tab)
{
  int		ret;

  sh->tsave->c_lflag |= ICANON;
  sh->tsave->c_lflag |= ECHO;
  if ((tcsetattr(0, TCSANOW, sh->tsave)) == -1)
    fprintf(stderr, "error : can't set values\n");
  ret = 0;
  save_history(sh->history);
  if (tab && tab[0] && tab[1])
    ret = my_getnbr(tab[1]);
  exit(ret);
}

int		chk_bult_next(t_mysh *sh, char **cmd)
{
  if (cmd[0] && my_strcmp("cd", cmd[0]) == 0)
    return (my_cd(sh, cmd));
  else if (cmd[0] && my_strcmp("echo", cmd[0]) == 0)
    return (my_echo(cmd, sh));
  else if (cmd[0] && my_strcmp("history", cmd[0]) == 0)
    return (my_history(sh->history, cmd, 1, 0));
  else if (cmd[0] && cmd[0][0] == '!')
    return (my_seek_history(sh, cmd[0] + 1, 0));
  else if (cmd[0] && my_strcmp("alias", cmd[0]) == 0)
    return (my_alias(sh, cmd));
  else if (cmd[0] && my_strcmp("source", cmd[0]) == 0)
    return (my_source(sh, cmd));
  else if (cmd[0] && my_strcmp("exit", cmd[0]) == 0)
    {
      my_exit_n(sh, cmd);
      return (1);
    }
  return (0);
}

int		chk_bult(t_mysh *sh, char **cmd)
{
  if (cmd[0][0] == '\0')
    return (0);
  else if (my_strcmp("env", cmd[0]) == 0)
    {
      env_show(sh->env_list);
      return (1);
    }
  else if (cmd[0] && my_strcmp("setenv", cmd[0]) == 0)
    return (my_setenv(sh, cmd));
  else if (cmd[0] && my_strcmp("unsetenv", cmd[0]) == 0)
    return (my_unsetenv(sh, cmd));
  return (chk_bult_next(sh, cmd));
}
