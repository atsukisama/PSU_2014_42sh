/*
** terminal.c for my_select in /home/fulmine/Git/epitech/PSU/PSU_2014_my_select/src
**
** Made by KING Jimmy
** Login   <fulmine@epitech.net>
**
** Started on  Fri Jan  9 21:51:17 2015 KING Jimmy
** Last update Sat May 23 10:12:45 2015 Vertigo
*/

#include <autocomplet.h>

/*
** Initialize the terminal capabilities
*/
void	terminal_initialize()
{
  terminal_getsize();
  tputs(tgetstr("vi", NULL), 0, putchars);
}

/*
** Reinitialize the terminal capabilities
*/
void	terminal_reinitialize()
{
  tputs(tgetstr("ve", NULL), 0, putchars);
}

/*
** Get the size of the terminal
*/
int			terminal_getsize()
{
  struct winsize        term_infos;

  if (ioctl(0, TIOCGWINSZ, &term_infos) == -1)
    return (-1);
  g_select.cols = term_infos.ws_col;
  g_select.rows = term_infos.ws_row;
  return (0);
}

/*
** Check if the size of the terminal is tall in off for display
*/
int		terminal_checksize()
{
  t_complet	*tmp;
  int		n;
  int		cols;

  tmp = g_select.args->next;
  n = 0;
  cols = 0;
  while (tmp != g_select.args)
    {
      if ((n + 2) >= g_select.rows)
        {
          n = 0;
          cols++;
        }
      else
        n++;
      tmp = tmp->next;
    }
  n = (cols + 1) * get_colspace();
  if (n < g_select.cols)
    return (1);
  return (0);
}

/*
** Hook the resize signal
*/
void     terminal_hook(int sig)
{
  sig = sig;
  tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, putchars);
  tputs(tgetstr("cd", NULL), 1, putchars);
  terminal_getsize();
  if (terminal_checksize())
    print_list(g_select.args);
  else
    my_putstr("Terminal size is too small.\n");
}
