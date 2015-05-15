/*
** error.c for error files in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 09:47:05 2015 Vertigo
** Last update Wed May 13 10:24:32 2015 Vertigo
*/

#include <unistd.h>
#include <stdlib.h>

void	malloc_error()
{
  write(2, "42sh : Can't perform malloc.\n", 29);
  exit(-1);
}
