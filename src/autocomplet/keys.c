/*
** keys.c for my_select in /home/fulmine/Git/epitech/PSU/PSU_2014_my_select/src
**
** Made by KING Jimmy
** Login   <fulmine@epitech.net>
**
** Started on  Thu Jan  8 22:59:29 2015 KING Jimmy
** Last update Sat May 23 15:45:41 2015 Vertigo
*/

#include <autocomplet.h>

/*
** Event when the key SPACE is pressed
*/
void    key_space(t_complet *args, int *n)
{
  if (terminal_checksize())
    {
      set_selected(args, *n);
      if (*n < complet_count(args) - 1)
        *n += 1;
      else
        *n = 0;
      set_active(args, *n);
      print_list(args);
    }
}

/*
** Event when the key DELETE or BACKSPACE is pressed
*/
int   key_delete(t_complet *args, int *n, t_mysh *sh, char *line)
{
  if (terminal_checksize())
    {
      clearscreen(sh, line);
      delete_item(args, *n);
      if (*n >= complet_count(args))
        *n -= 1;
      set_active(args, *n);
      if (complet_count(args) == 0)
        return (1);
      print_list(args);
      return (0);
    }
  return (1);
}

/*
** Event when left arrow or right arrow is pressed
*/
void    arrows_left_right(t_complet *args, int *n, int key)
{
  if (key == MKEY_RIGHT && (*n + g_select.rows) <= complet_count(args))
    *n = g_select.rows + *n - 1;
  if (key == MKEY_LEFT && (*n - g_select.rows + 1) >= 0)
    *n = *n - g_select.rows + 1;
  set_active(args, *n);
  print_list(args);
}

/*
** Event when an arrow key is pressed
*/
void    key_arrows(t_complet *args, int *n, int key)
{
  if (terminal_checksize())
    {
      if (key == MKEY_UP || key == MKEY_DOWN)
        {
          if (key == MKEY_UP)
            {
              if (*n <= 0)
                *n = complet_count(args) - 1;
              else
                *n -= 1;
            }
          if (key == MKEY_DOWN)
            {
              if (*n >= complet_count(args) - 1)
                *n = 0;
              else
                *n += 1;
            }
          set_active(args, *n);
          print_list(args);
        }
      if (key == MKEY_LEFT || key == MKEY_RIGHT)
        arrows_left_right(args, n, key);
    }
}
