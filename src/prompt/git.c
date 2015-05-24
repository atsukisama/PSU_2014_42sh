/*
** git.c for git_status in /home/king_j/Git/Epitech/kerebe_p/o/p/PSU_2014_42sh/src/prompt
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Sun May 24 03:01:44 2015 Jimmy KING
** Last update Sun May 24 03:56:53 2015 Jimmy KING
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <get_next_line.h>
#include "project.h"


int	git_check()
{
  char	current[1042];
  char	tmp[1042];
  int	len;

  if (getcwd(current, sizeof(current)) != NULL)
    {
      len = strlen(current);
      current[len] = '/';
      current[len + 1] = '.';
      current[len + 2] = 'g';
      current[len + 3] = 'i';
      current[len + 4] = 't';
      current[len + 5] = '\0';
      //return (access(current, F_OK));
    }
  //  tmp = current;
  //len = strlen(current);
  /*
  while (current[0] == '/' && current[1] != '\0')
    {
      while (
    }
  */
  return (0);
}
