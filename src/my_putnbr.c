/*
** my_putnbr.c for put nbr in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Sun May 17 19:43:48 2015 Vertigo
** Last update Sun May 17 19:47:00 2015 Vertigo
*/

#include <unistd.h>

void	my_put_nbr(int nb)
{
  int	tmp;

  if (nb < 0)
    {
      write(1, "-", 1);
      nb = -nb;
    }
  if (nb >= 10)
    {
      my_put_nbr(nb / 10);
      my_put_nbr(nb % 10);
    }
  else
    {
      tmp = nb + 48;
      write(1, &tmp, 1);
    }
}
