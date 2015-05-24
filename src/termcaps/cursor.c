/*
** cursor.c for cursor functions in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Tue May 19 15:55:37 2015 Vertigo
** Last update Sun May 24 18:45:36 2015 Vertigo
*/

#include <sys/ioctl.h>
#include <termios.h>
#include <mysh.h>

int			forward_cursor(t_mysh *sh, int pos)
{
  int			nb;
  struct winsize	ws;
  int			i;
  int			less;

  less = 53;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    return (-1);
  if (git_check() != 1)
    less = 28;
  nb = my_strlen(sh->prompt) + pos - less;
  while (nb >= ws.ws_col)
    nb -= ws.ws_col;
  if (nb == ws.ws_col - 1)
    {
      my_putstr("\033[1B");
      i = -1;
      while (++i < ws.ws_col)
	my_putstr("\033[1D");
    }
  else
    my_putstr("\033[1C");
  return (0);
}

int			back_cursor(t_mysh *sh, int pos)
{
  int			nb;
  struct winsize	ws;
  int			i;
  int			less;

  less = 53;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    return (-1);
  if (git_check() != 1)
    less = 28;
  nb = my_strlen(sh->prompt) + pos - less;
  while (nb >= ws.ws_col)
    nb -= ws.ws_col;
  if (nb == 0)
    {
      my_putstr("\033[1A");
      i = -1;
      while (++i < ws.ws_col)
	my_putstr("\033[1C");
    }
  else
    my_putstr("\033[1D");
  return (0);
}
