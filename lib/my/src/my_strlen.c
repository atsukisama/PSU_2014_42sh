/*
** my_strlen.c for my_strlen.c in /home/k6/rendu/Piscine_C_J04
** 
** Made by Cano Chloe
** Login   <cano_c@epitech.net>
** 
** Started on  Fri Oct  3 09:23:46 2014 Cano Chloe
** Last update Sun Mar  8 05:41:53 2015 Cano Chloe
*/

int			my_strlen(char *str)
{
  char			*s;

  s = str;
  if (s)
    {
      while (*s)
	++s;
    }
  return (s - str);
}
