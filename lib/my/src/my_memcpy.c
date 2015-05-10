/*
** my_memcpy.c for PISC_J14 in /home/cano_c/rendu/Piscine_C_J13/who
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Thu Oct 23 15:06:52 2014
** Last update Sun Mar  8 05:38:39 2015 Cano Chloe
*/

#include <my.h>

void		my_memcpy(void *dst, const void *src, size_t len)
{
  size_t	plen;

  plen = 0;
  while (plen < len)
    {
      *((unsigned char *)dst + plen) = *((unsigned char *)src + plen);
      ++plen;
    }
}
