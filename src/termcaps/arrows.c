/*
** arrows.c for arrow keys functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 22:06:16 2015 Vertigo
** Last update Wed May 20 11:15:58 2015 Vertigo
*/

#include <string.h>
#include <my.h>
#include <mysh.h>

void	up_arrow(int *pos, char **line, t_mysh *sh)
{
  char	*tab[2];

  while (sh->history->prev->key == NULL)
    sh->history = sh->history->prev;
  tab[0] = sh->history->prev->key;
  tab[1] = *line;
  display_line_hist(tab, pos, 2, sh);
  *line = strdup(sh->history->prev->key);
  sh->history = sh->history->prev;
  *pos = my_strlen(*line);
}

void    down_arrow(int *pos, char **line, t_mysh *sh)
{
  char	*tab[2];

  while (sh->history->next->key == NULL)
    sh->history = sh->history->next;
  tab[0] = sh->history->next->key;
  tab[1] = *line;
  display_line_hist(tab, pos, 2, sh);
  *line = strdup(sh->history->next->key);
  sh->history = sh->history->next;
  *pos = my_strlen(*line);
}

void    right_arrow(int *pos, char **line, t_mysh *sh)
{
  if (*pos >= my_strlen(*line))
    return;
  forward_cursor(sh, *pos);
  *pos = *pos + 1;
}

void    left_arrow(int *pos, char **line, t_mysh *sh)
{
  (void)line;
  if (*pos <= 0)
    return;
  back_cursor(sh, *pos);
  *pos = *pos - 1;
}
