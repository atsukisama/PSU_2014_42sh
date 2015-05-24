/*
** select.c for my_select in /home/fulmine/Git/epitech/PSU/PSU_2014_my_select/src
**
** Made by KING Jimmy
** Login   <fulmine@epitech.net>
**
** Started on  Wed Jan  7 19:23:11 2015 KING Jimmy
** Last update Sat May 23 17:40:58 2015 Vertigo
*/

#include <autocomplet.h>

/*
** Clear the screen
*/
void	clearscreen(t_mysh *sh, char *line)
{
  tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, putchars);
  tputs(tgetstr("cd", NULL), 1, putchars);
  my_putstr(sh->prompt);
  my_putstr(line);
}

/*
** Get the number of space for columns
*/
int		get_colspace()
{
  t_complet	*tmp;
  unsigned int	size;

  size = 0;
  tmp = g_select.args->next;
  while (tmp != g_select.args)
    {
      if (tmp->lenght > size)
        size = tmp->lenght;
      tmp = tmp->next;
    }
  return (size);
}

/*
** Print the argument with flags or without flags
*/
void    print_argument(t_complet *arg)
{
  tputs(tgoto(tgetstr("cm", NULL), arg->pos_x, arg->pos_y), 1, putchars);
  if (arg->is_active)
    tputs(tgetstr("us", NULL), 0, putchars);
  if (arg->is_selected)
    tputs(tgetstr("so", NULL), 0, putchars);
  tputs(arg->name, 0, putchars);
  if (arg->is_active)
    tputs(tgetstr("ue", NULL), 0, putchars);
  if (arg->is_selected)
    tputs(tgetstr("se", NULL), 0, putchars);
}

/*
** Print the list of argument
*/
void		print_list(t_complet *args)
{
  int		x;
  int		y;
  t_complet	*tmp;

  x = 0;
  y = 0;
  tmp = args->next;
  while (tmp != args)
    {
      tmp->pos_x = x;
      tmp->pos_y = y;
      print_argument(tmp);
      tmp = tmp->next;
      if ((y + 2) >= g_select.rows)
        {
          y = 0;
          x = x + (get_colspace() + 1);
        }
      else
        y = y + 1;
    }
}

/*
** Hold the program active, and exiting it when ENTER is pressed
*/
int	my_select(t_complet *args, t_mysh *sh, char **line)
{
  int	keycode;
  int	n;

  n = 0;
  clear_screen(sh, *line);
  set_active(args, n);
  print_list(args);
  terminal_hook(0);
  while (42)
    {
      keycode = 0;
      read(0, &keycode, 4);
      if (keycode == MKEY_ENTER || keycode == 10)
        return (1);
      if (keycode == MKEY_ESCAPE)
        return (-1);
      key_arrows(args, &n, keycode);
      terminal_hook(0);
    }
}
