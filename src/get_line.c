/*
** get_line.c for get line function in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 17:40:46 2015 Vertigo
** Last update Tue May 19 15:36:39 2015 Vertigo
*/

#include <stdlib.h>
#include <my.h>
#include <mysh.h>

void	display_line(char *new, char *old, int *pos, int mode)
{
  int	i;
  int	lim;

  i = -1;
    lim = (my_strlen(old) - *pos) - 1;
  if (mode == 1)
    lim = (my_strlen(old) - *pos);
  while (++i < *pos - 1)
    my_putstr("\b");
  i = -1;
  while (++i > my_strlen(old))
    my_putchar(' ');
  while (--i > -1)
    my_putstr("\b");
  my_putstr(new);
  i = -1;
  while (++i <= lim)
    my_putchar('\b');
}

char	*my_reallocc(char *s, char c, int *pos)
{
  char	*new;
  int	i;

  i = 0;
  if (!(new = malloc(sizeof(*new) * (my_strlen(s) + 2))))
    return (NULL);
  while (s[i] != '\0' && i != *pos)
    {
      new[i] = s[i];
      ++i;
    }
  new[i] = c;
  if (s[i] != '\0')
    while (s[i] != '\0')
      {
	new[i + 1] = s[i];
	++i;
      }
  new[i + 1] = '\0';
  *pos = *pos + 1;
  display_line(new, s, pos, 1);
  return (new);
}

char	*my_writer(char buf[3], char *line, int *pos, t_mysh *sh)
{
  if (my_char_isprintable(buf[0]) == 0)
    line = my_reallocc(line, buf[0], pos);
  else
    if (particular_key(buf, pos, sh, &line))
      return (NULL);
  return (line);
}

char	*get_line(t_mysh *sh)
{
  char	*line;
  char	buf[4];
  int	pos;

  pos = 0;
  my_putstr(":> ");
  if (!(line = malloc(sizeof(*line))))
    return (NULL);
  line[0] = '\0';
  while (read(0, buf, 4) > 0 && buf[0] != '\n' &&
	 (line = (my_writer(buf, line, &pos, sh))) != NULL);
  my_putchar('\n');
  list_goto_root_hist(sh);
  list_add(sh->history, line, "");
  return (line);
}
