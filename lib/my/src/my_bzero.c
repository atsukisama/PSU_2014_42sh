/*
** my_bzero.c for my_bzero in /home/cano_c/rendu/Piscine_C_J12/lib/my
** 
** Made by
** Login   <cano_c@epitech.net>
** 
** Started on  Tue Oct 21 09:37:35 2014
** Last update Sun May 17 17:30:11 2015 Vertigo
*/

void		my_bzero(void *mem, unsigned int len)
{
  unsigned int	idx;

  idx = 0;
  while (idx < len)
    *((char *)mem + idx++) = 0;
}
