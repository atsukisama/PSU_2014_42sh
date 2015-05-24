/*
** git.c for git_status in /home/king_j/Git/Epitech/kerebe_p/o/p/PSU_2014_42sh/src/prompt
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Sun May 24 03:01:44 2015 Jimmy KING
** Last update Mon May 25 01:07:14 2015 Jimmy KING
*/

#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <get_next_line.h>
#include "project.h"
#include "my.h"

int	check_dir(char *current)
{
  int	n;
  int	i;

  while (current[0] != '\0')
    {
      n = strlen(current);
      current[n] = '/';
      current[n + 1] = '.';
      current[n + 2] = 'g';
      current[n + 3] = 'i';
      current[n + 4] = 't';
      current[n + 5] = '\0';
      if (access(current, F_OK) == 0)
        return (1);
      i = 0;
      while (current[strlen(current) - i] != '/')
	i++;
      current[strlen(current) - i] = '\0';
      i = 0;
      while (current[strlen(current) - i] != '/')
	i++;
      current[strlen(current) - i] = '\0';
    }
  return (0);
}

void	exec_git(t_mysh *sh)
{
  char	*args[3];
  char	**env;
  int	n;

  args[0] = "git";
  args[1] = "status";
  args[2] = NULL;
  env = list_to_tab(sh->env_list);
  execve("/usr/bin/git", args, env);
  n = -1;
  while (env[++n])
    free(env[n]);
  free(env);
}

void	exec_gitparent(char **branch, int *status, int fd)
{
  char	*tmp;

  *branch = get_next_line(fd);
  tmp = get_next_line(fd);
  free(tmp);
  tmp = get_next_line(fd);
  if (strcmp("nothing to commit, working directory clean", tmp) == 0)
    *status = 1;
  else
    *status = 0;
}

char	*get_branch_name(t_mysh *sh, char **branch, int *status)
{
  int	pid;
  int	pipes[2];

  pipe(pipes);
  pid = fork();
  if (pid == -1)
    {
      *branch = NULL;
      *status = -1;
    }
  else if (pid == 0)
    {
      close(pipes[0]);
      dup2(pipes[1], 1);
      close(pipes[1]);
      exec_git(sh);
      exit(0);
    }
  else
    {
      close(pipes[1]);
      exec_gitparent(branch, status, pipes[0]);
      waitpid(pid, NULL, 0);
    }
  return (NULL);
}

int	git_check()
{
  char	current[1042];

  if (getcwd(current, sizeof(current)) != NULL)
    return (check_dir(current));
  return (0);
}
