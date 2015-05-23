/*
** clear_screen.c for clear screen in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Thu May 14 12:22:03 2015 Vertigo
** Last update Sat May 23 12:26:07 2015 Vertigo
*/

#include <my.h>
#include <mysh.h>

void	clear_screen(t_mysh *sh, char *line)
{
  (void)sh;
  my_putstr("\033[2J\033[0;0f");
  my_putstr(sh->prompt);
  my_putstr(line);
}
