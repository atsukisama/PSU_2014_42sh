/*
** my_putstr.c for my_putstr.c in /home/k6/rendu/Piscine_C_J04
** 
** Made by Cano Chloe
** Login   <cano_c@epitech.net>
** 
** Started on  Fri Oct  3 09:22:47 2014 Cano Chloe
** Last update Sun Mar  8 05:40:09 2015 Cano Chloe
*/
#include <my.h>

int		my_putstr(char *str)
{
  char		*s;

  s = str;
  if (str)
    {
      while (*s)
	{
	  my_putchar(*s);
	  ++s;
	}
    }
  return ((int)(s - str));
}
