/*
** disp.c for disp_history in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 20 11:14:43 2015 Vertigo
** Last update Wed Jun  3 03:53:49 2015 Jimmy KING
*/

#include <mysh.h>

void	display_line_hist(char **str, int *pos, int mode, t_mysh *sh)
{
  int	i;
  int	lim;

  i = -1;
  lim = (my_strlen(str[1]) - *pos) - 1;
  if (mode == 1)
    lim = (my_strlen(str[1]) - *pos);
  while (++i < *pos)
    back_cursor(sh, *pos - i);
  i = -1;
  while (++i < my_strlen(str[1]))
    my_putchar(' ');
  i = -1;
  while (++i < my_strlen(str[1]))
    back_cursor(sh, my_strlen(str[1]) - i);
  my_putstr(str[0]);
  i = -1;
  while (++i <= lim)
    back_cursor(sh, my_strlen(str[0]) - i);
}

void	my_put_blank_from_pos(char *s, int pos, t_mysh *sh)
{
  char	c;
  int	save;

  c = ' ';
  save = pos;
  while (s[pos++] && write(1, &c, 1));
  while (s[save++] && back_cursor(sh,
				  my_strlen(s) - (my_strlen(s) -save)) == 0);
}

void	clear_plus(char **str, t_mysh *sh, int pos)
{
  if (my_strlen(str[0]) > my_strlen(str[1]))
    return ;
  my_put_blank_from_pos(str[1], pos, sh);
}
