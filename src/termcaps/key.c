/*
** key.c for particular key functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 21:57:58 2015 Vertigo
** Last update Sat May 23 12:25:20 2015 Vertigo
*/

#include <stdlib.h>
#include <my.h>
#include <mysh.h>

void	remove_letter(char *s, int nb)
{
  while (s[nb] != '\0')
    {
      s[nb] = s[nb + 1];
      ++nb;
    }
}

void	delete_char(char *line, int *pos, char c, t_mysh *sh)
{
  char	*old;
  char	*tab[2];
  int	nb;

  if (c == 127)
    nb = *pos - 1;
  else
    nb = *pos;
  if (nb < 0 || nb >= my_strlen(line))
    return;
  if (!(old = my_strdup(line)))
    return;
  remove_letter(line, nb);
  if (c != 127)
    *pos = *pos + 1;
  else if (c == 127)
    back_cursor(sh, *pos);
  tab[0] = line;
  tab[1] = old;
  display_line(tab, *pos, 2, sh);
  *pos = *pos - 1;
  free(old);
}

void	init_arrows(void  (*arrow[4]) (int *, char **, t_mysh *))
{
  arrow[0] = up_arrow;
  arrow[1] = down_arrow;
  arrow[2] = right_arrow;
  arrow[3] = left_arrow;
}

void	end_key(char *line, int *pos)
{
  while (line[*pos] != '\0')
    {
      my_putchar(line[*pos]);
      *pos = *pos + 1;
    }
}

int	particular_key(char buf[4], int *pos, t_mysh *sh, char **line)
{
  void	(*arrow[4]) (int *, char **, t_mysh *);

  init_arrows(arrow);
  if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 51) || buf[0] == 127)
    delete_char(*line, pos, buf[0], sh);
  else if (buf[0] == 27 && buf[1] == 91 && (buf[2] >= 65 && buf[2] <= 68))
    arrow[buf[2] - 65](pos, line, sh);
  else if (buf[0] == 12)
    clear_screen(sh, *line);
  else if (buf[0] == 27 && buf[1] == 79 && buf[2] == 70)
    end_key(*line, pos);
  else if (buf[0] == 4)
    return (-1);
  return (0);
}
