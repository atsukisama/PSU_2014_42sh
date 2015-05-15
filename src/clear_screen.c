/*
** clear_screen.c for clear screen in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Thu May 14 12:22:03 2015 Vertigo
** Last update Thu May 14 18:10:49 2015 Vertigo
*/

#include <my.h>
#include <mysh.h>

void	clear_screen(t_mysh *sh)
{
  (void)sh;
  my_putstr("\033[2J\033[0;0f");
}
