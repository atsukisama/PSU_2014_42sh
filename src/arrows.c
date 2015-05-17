/*
** arrows.c for arrow keys functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 22:06:16 2015 Vertigo
** Last update Fri May 15 20:32:15 2015 Vertigo
*/

#include <stropts.h>
#include <sys/ioctl.h>
#include <string.h>
#include <my.h>
#include <mysh.h>

void	up_arrow(int *pos, char **line, t_mysh *sh)
{
  while (sh->history->prev->key == NULL)
    sh->history = sh->history->prev;
  display_line(sh->history->prev->key, *line, pos, 2);
  *line = strdup(sh->history->prev->key);
  sh->history = sh->history->prev;
  *pos = my_strlen(*line);
}

void    down_arrow(int *pos, char **line, t_mysh *sh)
{
  while (sh->history->next->key == NULL)
    sh->history = sh->history->next;
  display_line(sh->history->next->key, *line, pos, 2);
  *line = strdup(sh->history->next->key);
  sh->history = sh->history->next;
  *pos = my_strlen(*line);
}

void			right_arrow(int *pos, char **line, t_mysh *sh)
{
  struct winsize	ws;

  (void)sh;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  if (*pos >= my_strlen(*line))
    return;
  my_putstr("\033[1C");
  *pos = *pos + 1;
}

void			left_arrow(int *pos, char **line, t_mysh *sh)
{
  struct winsize	ws;

  (void)line;
  (void)sh;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  if (*pos <= 0)
    return;
  *pos = *pos - 1;
  //my_put_nbr(ws.ws_col);
  my_putstr("\033[1D");
}
