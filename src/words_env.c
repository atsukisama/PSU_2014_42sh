/*
** words_env.c for env_words in /home/king_j/Git/Epitech/king_j/tmp/src/basics
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Wed May 13 23:35:04 2015 Jimmy KING
** Last update Sun May 17 17:38:16 2015 Vertigo
*/

#include <stdlib.h>
#include <project.h>

int	is_str2(char c)
{
  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    return (1);
  return (0);
}

/*
** Count the number of env vars in a string
*/
int	we_count(char *str)
{
  int	n;
  int	count;

  n = -1;
  count = 0;
  while (str[++n])
    {
      if (str[n] == '$' && is_str(str[++n], "/-:%<>."))
	count++;
    }
  return (count);
}

/*
** Get the lenght of a env var in a string
*/
int	we_lenght(char *str, int id)
{
  int	n;
  int	count;
  int	lenght;

  n = -1;
  count = 0;
  lenght = 0;
  while (str[++n])
    {
      if (str[n] == '$' && is_str(str[n + 1], "/-:%<>."))
	{
	  count++;
	  if (count == id)
	    while (str[n + 1] && is_str(str[n++ + 1], "/-:%<>."))
	      lenght++;
	}
    }
  return (lenght);
}

/*
** Get a env var from a string
*/
char	*we_get(char *str, int id)
{
  int	n;
  int	count;
  char	*tmp;
  int	i;

  n = -1;
  count = 0;
  i = 0;
  if ((tmp = malloc(we_lenght(str, id) + 2)) == NULL)
     return (NULL);
  tmp[i++] = '$';
  while (str[++n])
    {
      if (str[n] == '$' && is_str2(str[n + 1]))
	{
	  count++;
	  if (count == id)
	    while (str[n + 1] && is_str2(str[n + 1]))
	      tmp[i++] = str[++n];
	}
    }
  tmp[i] = '\0';
  return (tmp);
}
