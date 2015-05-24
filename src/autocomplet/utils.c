/*
** utils.c for utils functions in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Sat May 23 10:04:05 2015 Vertigo
** Last update Sat May 23 10:09:00 2015 Vertigo
*/

#include <autocomplet.h>

void	my_channelput(char c, int channel)
{
  write(channel, &c, 1);
}

int	putchars(int c)
{
  my_channelput((char)c, g_select.tty);
  return (0);
}
