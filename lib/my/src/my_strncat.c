/*
** my_strncat.c for my_strncat.c in /home/k6/rendu/Piscine_C_J07
** 
** Made by Cano Chloe
** Login   <cano_c@epitech.net>
** 
** Started on  Wed Oct  8 10:18:07 2014 Cano Chloe
** Last update Sun Mar  8 05:42:05 2015 Cano Chloe
*/

char		*my_strncat(char *dest, char *src, int nb)
{
  int		n;
  char		*dp;

  n = 0;
  dp = dest;
  while (*dest)
    ++dest;
  while (n < nb && *src)
    dest[n++] = *src++;
  dest[n] = '\0';
  return (dp);
}
