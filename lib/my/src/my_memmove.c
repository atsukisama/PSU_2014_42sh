/*
** my_memmove.c for Bistro in /home/cano_c/rendu/ELEM/Bistromathique
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Sun Nov  9 09:13:00 2014
** Last update Sun Mar  8 05:38:50 2015 Cano Chloe
*/

#include <my.h>

void		*my_memmove(void *dest, void *src, size_t len)
{
  char		*pdest;

  pdest = dest;
  if (pdest > (char *)src)
    {
      pdest += len;
      src += len;
      while (pdest >= (char *)dest)
	*(unsigned char *)pdest-- = *(unsigned char *)src--;
    }
  return (dest);
}
