/*
** exit.c for exit function in /home/gascon/Server/PSU/42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Thu May 14 17:20:44 2015 Vertigo
** Last update Fri May 15 09:31:58 2015 Vertigo
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <mysh.h>

void	my_putstr_file(char *s, int fd)
{
  int	i;

  i = 0;
  while (s[i] != '\0')
    {
      write(fd, &s[i], 1);
      ++i;
    }
  write(fd, "\n", 1);
}

int		save_history(t_list *history)
{
  int		fd;
  t_list	*tmp;

  tmp = history->next;
  if ((fd = open(HISTORY_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
    return (-1);
  while (tmp != history)
    {
      if (tmp->key != NULL)
	my_putstr_file(tmp->key, fd);
      tmp = tmp->next;
    }
  close(fd);
  return (1);
}
