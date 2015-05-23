/*
** match.c for match in /home/gascon_n/rendu/Piscine_C_match-nmatch
**
** Made by Nicolas Gascon
** Login   <gascon_n@epitech.net>
**
** Started on  Thu Oct  9 08:27:44 2014 Nicolas Gascon
** Last update Mon Mar  2 06:40:26 2015 GASCON Nicolas
*/

/*
** Check if s1 match with s2
*/

int	match(char *s1, char *s2)
{
  if (*s1 == 0 && *s2 == 0)
    return (1);
  else if (*s1 == *s2 && *s1 != 42)
    return (match(s1 + 1, s2 + 1) > 0 ? 1 : 0);
  else if (*s1 == 42 && *s2 == 42)
    return (match(s1 + 1, s2) > 0 ? 1 : 0);
  else if (*s2 == 42 && *s1 == 0)
    return (match(s1, s2 + 1) > 0 ? 1 : 0);
  else if (*s2 == 42 && *s2 != 0 && *s1 != 0)
    return (match(s1, s2 + 1) + match(s1 + 1, s2) > 0 ? 1 : 0);
  else
    return (0);
}
