/*
** words.c for words in /home/king_j/Git/Epitech/king_j/tmp/src/basics
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Wed May 13 21:39:18 2015 Jimmy KING
** Last update Sat May 23 16:46:20 2015 Jimmy KING
*/

#include "project.h"

/*
** Check if a character is a separator or not
*/
int	is_str(char c, char *seps)
{
  int	n;

  n = 0;
  while (seps[n])
    {
      if (c == seps[n])
	return (0);
      n++;
    }
  return (1);
}

/*
** Count the number of words in a string
*/
int	words_count(char *str, char *seps)
{
  int	n;
  int	words;

  n = 0;
  words = 0;
  while (str[n])
    {
      if (is_str(str[n], seps))
	words++;
      while (is_str(str[n], seps) && str[n])
	n++;
      if (str[n] != '\0')
	n++;
    }
  return (words);
}

/*
** Get the lenght of a word in string
*/
int	words_lenght(char *str, int word, char *seps)
{
  int	n;
  int	words;
  int	lenght;

  n = 0;
  words = 0;
  lenght = 0;
  while (str[n])
    {
      if (is_str(str[n], seps))
	words++;
      while (is_str(str[n], seps) && str[n])
	{
	  if (words == word)
	    lenght++;
	  n++;
	}
      if (str[n] != '\0')
	n++;
    }
  return (lenght);
}

/*
** Get a word in a string
*/
char	*words_get(char *str, int word, char *seps)
{
  int	n;
  int	words;
  char	*tmp;
  int	i;

  i = 0;
  n = 0;
  words = 0;
  if ((tmp = malloc(words_lenght(str, word, seps) + 1)) == NULL)
     return (NULL);
  while (str[n])
    {
      if (is_str(str[n], seps))
	words++;
      while (is_str(str[n], seps) && str[n])
	{
	  if (words == word)
	      tmp[i++] = str[n];
	  n++;
	}
      if (str[n] != '\0')
	n++;
    }
  tmp[i] = '\0';
  return (tmp);
}
