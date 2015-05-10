/*
** my_putstr_fd.c for my_putstr.c in /home/k6/rendu/Piscine_C_J04
** 
** Made by Cano Chloe
** Login   <cano_c@epitech.net>
** 
** Started on  Fri Oct  3 09:22:47 2014 Cano Chloe
** Last update Sun Mar  8 05:40:41 2015 Cano Chloe
*/

#include <my.h>

int		my_putstr_fd(char *str, int fd)
{
  char		*s;

  s = str;
  if (str)
    {
      while (*s)
	{
	  write(fd, s, 1);
	  ++s;
	}
    }
  return ((int)(s - str));
}
