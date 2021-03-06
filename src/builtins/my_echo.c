/*
** my_echo.c for  in /home/rusign/rendu/42sh/PSU_2014_42sh/bultin
** 
** Made by rusig_n
** Login   <nicolas.rusig@epitech.eu>
** 
** Started on  Thu May 14 11:51:53 2015 rusig_n
** Last update Wed Jun  3 11:08:44 2015 
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "project.h"

int	exe_echo_opt_spe(char *str, int i)
{
  i++;
  if (str[i] == 'n')
    my_putchar('\n');
  else if (str[i] == 't')
    my_putchar('\t');
  else if (str[i] == 'f')
    my_putchar('\f');
  else if (str[i] == 'a')
    my_putchar('\a');
  else if (str[i] == 'b')
    my_putchar('\b');
  else if (str[i] == 'f')
    my_putchar('\f');
  else if (str[i] == 'r')
    my_putchar('\r');
  else if (str[i] == 'v')
    my_putchar('\v');
  else if (str[i] == 'c')
    {
      write(1, "\n", 1);
      return (2);
    }
  return (0);
}

int	exe_echo_opt_e(char *str, t_mysh *sh, int i)
{
  while (str[++i] != 0)
    {
      if (str[i] == '\\')
	{
	  if (exe_echo_opt_spe(str, i++) == 2)
	    return (2);
	}
      else if (str[i] == '$')
	{
	  echo_dol(str, &i, sh, 0);
	  if (str[i] != '0')
	    i--;
	}
      else
	my_putchar(str[i]);
    }
  return (0);
}

int	exe_echo(char *str, int opt, t_mysh *sh)
{
  int	i;

  i = -1;
  if (opt == 2)
    {
      if (exe_echo_opt_e(str, sh, -1) == 2)
	return (2);
    }
  else
    {
      while (str[++i] != 0)
	{
	  if (str[i] == '$')
	    {
	      echo_dol(str, &i, sh, 0);
	      if (str[i] != '0')
		i--;
	    }
	  else if (str[i] != '\\')
	    my_putchar(str[i]);
	}
    }
  return (0);
}

int	print_echo(char **cmd, int opt, t_mysh *sh)
{
  int	i;

  i = 1;
  while (cmd[i])
    {
      if ((my_strcmp(cmd[i], "-n")) == 0 ||
	  (my_strcmp(cmd[i], "-e")) == 0 ||
	  (my_strcmp(cmd[i], "-E")) == 0)
	i++;
      else
	{
	  if (exe_echo(cmd[i++], opt, sh) == 2)
	    return (2);
	  if (cmd[i])
	    my_putchar(' ');
	}
    }
  if (opt == 0 || opt == 2 || opt == 3)
    my_putchar(10);
  return (0);
}

int		my_echo(char **cmd, t_mysh *sh)
{
  char		opt;
  int		j;

  j = 0;
  opt = 0;
  tcsetpgrp(0, getpgrp());
  if (cmd[1] && cmd[1][j] == '-')
    {
      while (cmd[1][j])
	j++;
      if (cmd[1][j - 1] == 'n')
	opt = 1;
      if (cmd[1][j - 1] == 'e')
	opt = 2;
      if (cmd[1][j - 1] == 'E')
	opt = 3;
    }
  if (opt == 2)
    cmd = anlyse_b(cmd);
  if (opt != 0)
    print_echo(cmd + 1, opt, sh);
  else
    print_echo(cmd, opt, sh);
  return (1);
}
