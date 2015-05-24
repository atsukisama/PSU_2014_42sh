/*
** get_line.c for get line function in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 17:40:46 2015 Vertigo
** Last update Sun May 24 13:00:23 2015 Vertigo
*/

#include <stdlib.h>
#include <my.h>
#include <mysh.h>

void	my_put_from_pos(char *s, int pos)
{
  while (s[pos] && write(1, &s[pos++], 1));
}

void	display_line(char **str, int pos, int mode, t_mysh *sh)
{
  int	i;
  int	lim;

  i = -1;
  lim = (my_strlen(str[1]) - pos) - 1;
  if (mode == 1)
    lim = (my_strlen(str[1]) - pos);
  clear_plus(str, sh, pos - 1);
  my_put_from_pos(str[0], pos - 1);
  while (++i <= lim)
    back_cursor(sh, my_strlen(str[0]) - i);
}

char	*my_reallocc(char *s, char c, int *pos, t_mysh *sh)
{
  char	*new;
  char	*tab[2];
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
  tab[0] = new;
  tab[1] = s;
  display_line(tab, *pos, 1, sh);
  return (new);
}

char	*my_writer(char buf[3], char *line, int *pos, t_mysh *sh)
{
  if (my_char_isprintable(buf[0]) == 0)
    line = my_reallocc(line, buf[0], pos, sh);
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
  sh->prompt = get_prompt(sh->env_list);
  my_putstr(sh->prompt);
  if (!(line = malloc(sizeof(*line))))
    return (NULL);
  line[0] = '\0';
  while (read(0, buf, 4) > 0 && buf[0] != '\n' &&
	 (line = (my_writer(buf, line, &pos, sh))) != NULL);
  my_putchar('\n');
  list_goto_root_hist(sh);
  if (line && line[0] != '\0' && match(line, "*!*") != 1)
    list_add(sh->history, line, "");
  return (line);
}
