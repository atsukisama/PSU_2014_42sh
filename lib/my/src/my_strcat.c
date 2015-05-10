/*
** my_strcat.c for my_strcat.c in /home/k6/rendu/Piscine_C_J07
** 
** Made by Cano Chloe
** Login   <cano_c@epitech.net>
** 
** Started on  Wed Oct  8 09:53:21 2014 Cano Chloe
** Last update Sun Mar  8 05:41:09 2015 Cano Chloe
*/

char		*my_strcat(char *dest, char *src)
{
  char		*pd;

  pd = dest;
  while (*pd)
    ++pd;
  while ((*pd++ = *src++))
    ;
  return (dest);
}
