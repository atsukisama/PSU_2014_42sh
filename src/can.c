/*
** can.c for can mode in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 10:26:14 2015 Vertigo
** Last update Mon May 18 14:01:23 2015 
*/

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <my.h>

struct termios		*can_on(struct termios **attr)
{
  struct termios	*tsave;

  if (!(*attr = malloc(sizeof(**attr))))
    return (NULL);
  if (!(tsave = malloc(sizeof(*tsave))))
    return (NULL);
  if (tcgetattr(0, tsave) == -1)
    return (NULL);
  my_memcpy(*attr, tsave, sizeof(*attr));
  (*attr)->c_lflag &= ~ICANON;
  (*attr)->c_lflag &= ~ECHO;
  (*attr)->c_cc[VTIME] = 0;
  (*attr)->c_cc[VMIN] = 1;
  if (tcsetattr(0, TCSANOW, *attr) == -1)
    return (NULL);
  return (tsave);
}

int			can_set(struct termios *t_save)
{
  return (tcsetattr(0, TCSANOW, t_save));
}
