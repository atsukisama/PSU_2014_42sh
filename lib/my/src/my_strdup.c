/*
** my_strdup.c for my_strdup.c in /home/k6/rendu/Piscine_C_J08
** 
** Made by Cano Chloe
** Login   <k6@epitech.net>
** 
** Started on  Wed Oct  8 15:37:44 2014 Cano Chloe
** Last update Sun Mar  8 05:41:41 2015 Cano Chloe
*/
#include <my.h>
#include <my_err.h>

char		*my_strdup(char *src)
{
  int		src_len;
  char		*dup;
  char		*pdup;

  src_len = my_strlen(src);
  if (!(dup = malloc(sizeof(*src) * src_len + 1)))
    {
      errno = E_OOM;
      return (NULL);
    }
  pdup = dup;
  while (*src)
    *dup++ = *src++;
  *dup = '\0';
  return (pdup);
}
