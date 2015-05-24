/*
** my_strdup2.c for my_strdup2 in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 20 13:10:41 2015 Vertigo
** Last update Wed May 20 15:27:02 2015 Vertigo
*/

#include <stdlib.h>
#include <my.h>

char	*my_strdup2(char *str, char *buf)
{
  char	*s;
  int	i;
  int	j;

  if (!(s = malloc(my_strlen(str) + my_strlen(buf) + 1)))
    return (NULL);
  i = 0;
  j = 0;
  while (str[i] != '\0')
    {
      s[i] = str[i];
      ++i;
    }
  while (buf[j] != '\0')
    {
      s[i] = buf[j];
      ++i;
      ++j;
    }
  s[i] = '\0';
  return (s);
}
