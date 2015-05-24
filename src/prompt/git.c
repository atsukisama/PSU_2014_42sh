/*
** git.c for git_status in /home/king_j/Git/Epitech/kerebe_p/o/p/PSU_2014_42sh/src/prompt
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Sun May 24 03:01:44 2015 Jimmy KING
** Last update Sun May 24 17:43:59 2015 Jimmy KING
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <get_next_line.h>
#include "project.h"
#include "my.h"

void	add_dotgit(char *str)
{
  int	n;

  n = strlen(str);
  str[n] = '/';
  str[n + 1] = '.';
  str[n + 2] = 'g';
  str[n + 3] = 'i';
  str[n + 4] = 't';
  str[n + 5] = '\0';
}

void	remove_lastword(char *str)
{
  int	n;

  n = 0;
  while (str[strlen(str) - n] != '/')
    n++;
  str[strlen(str) - n] = '\0';
}

int	check_dir(char *current)
{
  while (current[0] != '\0')
    {
      add_dotgit(current);
      if (access(current, F_OK) == 0)
	return (1);
      remove_lastword(current);
      remove_lastword(current);
    }
  return (0);
}

char	*get_branch_name(t_mysh *sh, char **branch, int *status)
{
  char	*args[3];
  char	**env;
  int	pid;
  int	pipes[2];
  char	*tmp;

  pipe(pipes);
  if ((pid = fork() == 0))
    {
      close(pipes[0]);
      dup2(pipes[1], 1);
      close(pipes[1]);
      args[0] = "git";
      args[1] = "status";
      args[2] = NULL;
      env = list_to_tab(sh->env_list);
      execve("/usr/bin/git", args, env);
      exit(1);
    }
  else
    {
      close(pipes[1]);
      *branch = get_next_line(pipes[0]);
      tmp = get_next_line(pipes[0]);
      tmp = get_next_line(pipes[0]);
      if (strcmp("nothing to commit, working directory clean", tmp) == 0)
	*status = 1;
      else
	*status = 0;
    }
  return (NULL);
}

int	git_check()
{
  char	current[1042];

  if (getcwd(current, sizeof(current)) != NULL)
    return(check_dir(current));
  return (0);
}
