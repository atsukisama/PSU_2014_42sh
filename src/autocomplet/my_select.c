/*
** main.c for my_select in /home/fulmine/Git/epitech/PSU/PSU_2014_my_select
**
** Made by KING Jimmy
** Login   <fulmine@epitech.net>
**
** Started on  Mon Jan  5 13:53:34 2015 KING Jimmy
** Last update Sat May 23 10:15:31 2015 Vertigo
*/

#include <autocomplet.h>

/*
** Return the last argument selected of the list
*/
t_complet	*get_lastword(t_complet *args)
{
  t_complet	*tmp;
  t_complet	*last;

  tmp = args->next;
  last = NULL;
  while (tmp != args)
    {
      if (tmp->is_selected)
	last = tmp;
      tmp = tmp->next;
    }
  return (last);
}

/*
** Print the arguments selected on the STDOUT
*/
int		print_final(t_complet *args)
{
  t_complet	*tmp;

  tmp = args->next;
  while (tmp != args)
    {
      if (tmp->is_selected)
        {
          my_putstr(tmp->name);
          if (tmp != get_lastword(args))
            my_putchar(' ');
        }
      tmp = tmp->next;
    }
  return (0);
}
