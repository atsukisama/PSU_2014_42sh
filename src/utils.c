/*
** utils.c for utils in /home/king_j/Git/Epitech/king_j/tmp/src/basics
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Wed May 13 21:25:47 2015 Jimmy KING
** Last update Sat May 23 17:03:10 2015 Jimmy KING
*/

#include <stdlib.h>
#include <project.h>

/*
** Find the first match in a string
*/
char	*xstrstr(char *str, char *keyword)
{
  int	n;

  n = 0;
  if (str[n] != '\0')
    {
      while (keyword[n])
	{
	  if (keyword[n] != str[n])
	    return (xstrstr(str + 1, keyword));
	  n++;
	}
      return (str);
    }
  else
    return (0);
}

/*
** Get the lenght of a string
*/
int	xlen(char *str)
{
  int	n;

  n = 0;
  if (str == NULL)
    return (n);
  while (str[n] != '\0')
    n++;
  return (n);
}

/*
** Replace the first match in a string
*/
char	*xreplace(char *src, char *key, char *nkey)
{
  char	*pos;
  char	*pos2;
  char	*ret;
  int	len;


  printf("src: %s | key: %s | nkey: %s\n", src, key, nkey);
  printf("src: %d | key: %d | nkey: %d\n", xlen(src), xlen(key), xlen(nkey));
  if ((ret = malloc(xlen(src) - xlen(key) + xlen(nkey) + 1)) == NULL)
    return (NULL);
  pos = src;
  pos2 = xstrstr(pos, key);
  len = pos2 - pos;
  xstrncat(ret, pos, len);
  xstrncat(ret, nkey, xlen(nkey));
  pos = pos2 + xlen(key);
  xstrcat(ret, pos);
  return (ret);
}
