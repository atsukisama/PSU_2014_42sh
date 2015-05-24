/*
** historic_c.c for  in /home/rusign/test/PSU_2014_42sh/src/builtins
** 
** Made by rusig_n
** Login   <nicolas.rusig@epitech.eu>
** 
** Started on  Sat May 23 19:09:15 2015 rusig_n
** Last update Sat May 23 19:09:15 2015 rusig_n
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <mysh.h>

int		my_histo_c(t_list *history)
{
  t_list	*tmp;
  int		fd;

  tmp = history->next;
  while (tmp != history)
    {
      tmp->key = NULL;
      tmp = tmp->next;
    }
  if ((fd = open(HISTORY_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
    return (-1);
  close(fd);
  return (0);
}
