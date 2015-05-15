/*
** basic.c for  in /home/rusign/42_env
** 
** Made by rusig_n
** Login   <nicolas.rusig@epitech.eu>
** 
** Started on  Fri May 15 09:45:09 2015 rusig_n
** Last update Fri May 15 09:45:09 2015 rusig_n
*/
#include <stdlib.h>
#include <unistd.h>

char            *my_strchr(char *s, int c)
{
  int           i;

  i = 0;
  while (s[i])
    {
      if (s[i] == c)
	return (s + i);
      i = i + 1;
    }
  return (NULL);
}

int             my_putchar(char c)
{
  return (write(1, &c, 1));
}

int             my_strlen(char *str)
{
  int           i;

  i = 0;
  while (str[i])
    i++;
  return (i);
}
void            my_error(char *str)
{
  int           i;

  i = 0;
  while (str[i])
    {
      my_putchar(str[i]);
      i++;
    }
  exit(1);
}

void            my_putstr(char *str)
{
  int           i;

  i = 0;
  if (str == NULL)
    my_error("error : my_putstr");
  while (str[i])
    {
      my_putchar(str[i]);
      i++;
    }
}

int            my_puterror(char *str, int err)
{
  int           i;

  i = 0;
  if (str == NULL)
    my_error("error : my_putstr");
  while (str[i])
    {
      my_putchar(str[i]);
      i++;
    }
  return (err);
}

int             my_strcmp(char *s1, char *s2)
{
  int           i;

  i = 0;
  while (s1[i] && s2[i])
    {
      if (s1[i] != s2[i])
	return (s1[i] - s2[i]);
      i++;
    }
  if (s1[i] == '\0' && s2[i] == '\0')
    return (0);
  else
    return (-1);
}
