/*
** my_memalloc.c for libmy in /home/cano_c/my_select
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Wed Jan  7 16:42:32 2015
** Last update Sun Mar  8 05:38:14 2015 Cano Chloe
*/

#include <my.h>

void		*my_memalloc(size_t len)
{
  void		*new;

  if ((new = malloc(len)))
    my_bzero(new, len);
  else
    errno = E_OOM;
  return (new);
}
