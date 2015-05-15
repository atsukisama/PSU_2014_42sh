/*
** main.c for pipes in /home/gascon/Server/Test/Pipes
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Fri May  8 12:40:15 2015 Vertigo
** Last update Wed May 13 19:40:38 2015 Vertigo
*/

#include <stdlib.h>
#include <unistd.h>

void	pipe_func(char *prg1, char *prg2)
{
  int	pipefd[2];
  int	pid;
  char	buf[512];
  int	len;

  if (pipe(pipefd) == -1)
    {
      write(2, "Error on pipe.\n", 15);
      exit(-1);
    }
  if ((pid = fork()) == -1)
    {
      write(1, "Error on fork.\n", 15);
      exit(-1);
    }
  if (pid == 0)
    {
      close(pipefd[0]);
      dup2(pipefd[1], 1);
      execl("/bin/sh", "sh", "-c", prg1, (char*)0);
      dup2(1, pipefd[1]);
    }
  else
    {
      close(pipefd[1]);
      dup2(pipefd[0], 0);
      execl("/bin/sh", "sh", "-c", prg2, (char*)0);
      dup2(0, pipefd[0]);
    }
}
