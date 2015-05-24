/*
** get_string.c for get string functions in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 20 15:43:36 2015 Vertigo
** Last update Sun May 24 01:46:20 2015 Vertigo
*/

#include <string.h>
#include <my.h>
#include <stdlib.h>

char	*get_last_word(char *s)
{
  char	*new;
  int	nb;
  int	i;
  int	j;

  nb = my_strlen(s);
  i = 0;
  while (nb >= 0 && s[nb] != ' ' && s[nb--] != '\t')
    ++i;
  if (!(new = malloc(sizeof(*new) * (i))))
    return (NULL);
  new[i--] = '\0';
  j = 0;
  while (j < i)
    new[j++] = s[++nb];
  return (new);
}

char	*get_foldername(char *s)
{
  char	*new;
  int	i;
  int	j;

  j = 0;
  i = my_strlen(s) - 1;
  while (s[i] != '/')
    --i;
  if (!(new = malloc(sizeof(*new) * (i + 1))))
    return (NULL);
  while (j != i)
    {
      new[j] = s[j];
      ++j;
    }
  new[j] = '\0';
  return (new);
}

char	*get_file_name(char *s)
{
  char	*new;
  int	nb;
  int	i;

  nb = my_strlen(s) - 1;
  i = 0;
  while (nb >= 0 && s[nb] != ' ' && s[nb--] != '/')
    ++i;
  if (!(new = malloc(sizeof(*new) * (i + 1))))
    return (NULL);
  nb = my_strlen(s);
  new[i--] = '\0';
  while (i > -1)
    new[i--] = s[--nb];
  return (new);
}
