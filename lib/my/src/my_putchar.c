/*
** my_putchar.c for my_putchar.c in /home/k6/rendu/Piscine_C_J07
** 
** Made by Cano Chloe
** Login   <cano_c@epitech.net>
** 
** Started on  Wed Oct  8 15:14:22 2014 Cano Chloe
** Last update Sun Mar  8 05:39:15 2015 Cano Chloe
*/

#include <unistd.h>

int			my_putchar(char c)
{
  return (write(1, &c, 1));
}
