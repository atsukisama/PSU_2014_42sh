/*
** string.c for strings in /home/king_j/Git/Epitech/king_j/tmp/src/basics
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Thu May 14 00:41:06 2015 Jimmy KING
** Last update Sun May 24 22:24:45 2015 Jimmy KING
*/

#include <stdlib.h>
#include <project.h>

/*
** Compare two strings and return the differance
*/
int	xstrcmp(char *str_1, char *str_2)
{
  int	n;

  n = 0;
  while (str_1[n] && str_2[n] && str_1[n] == str_2[n])
    n++;
  return (str_2[n] - str_1[n]);
}

/*
** Copy a string to the end of a another string
*/
char	*xstrcat(char *dest, char *src)
{
  int	n;
  int	i;

  n = 0;
  i = xlen(dest);
  while (src[n])
    dest[i++] = src[n++];
  dest[i] = '\0';
  return (dest);
}

/*
** Copy 'x' character of  a string to the end of a another string
*/
char	*xstrncat(char *dest, char *src, int len)
{
  int	n;
  int	i;

  n = 0;
  i = xlen(dest);

  while (src[n] && n < len)
    dest[i++] = src[n++];
  dest[i] = '\0';
  return (dest);
}
