/*
** char_isprintable.c for my_char_isprintable function in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 21:17:48 2015 Vertigo
** Last update Wed May 13 21:19:10 2015 Vertigo
*/

int	my_char_isprintable(char c)
{
  if (c == '\t' || (c >= 32 && c <= 126))
    return (0);
  return (-1);
}
