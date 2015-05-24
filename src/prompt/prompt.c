/*
** prompt.c for prompt in /home/king_j/Git/Epitech/kerebe_p/o/PSU_2014_42sh/src/prompt
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Sat May 23 20:28:44 2015 Jimmy KING
** Last update Sun May 24 19:05:24 2015 Jimmy KING
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <get_next_line.h>
#include "project.h"

char	*get_hostname()
{
  int	fd;
  char	*hostname;

  if ((fd = open("/etc/hostname", O_RDONLY)) == -1)
    return (NULL);
  if ((hostname = get_next_line(fd)) == NULL)
    return (NULL);
  return (hostname);
}

char		*prompt_getdir(t_list *env_list)
{
  t_list	*home;
  char		*rdir;
  char		cwd[1024];

  if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
      rdir = words_get(cwd, words_count(cwd, "/"), "/");
      if (rdir[0] == 0)
	return ("/");
      if ((home = get_node_by_key(env_list, "HOME")) != NULL)
	if (strcmp(cwd, home->content) == 0)
	  return ("~");
      return (rdir);
    }
  return (NULL);
}

char	*get_git(t_mysh *sh)
{
  char	*git;
  char	*branch;
  int	status;

  status = 0;
  if (access("/usr/bin/git", F_OK) != -1)
    {
      get_branch_name(sh, &branch, &status);
      branch = words_get(branch, 3, " ");
      git = "\e[33mgit:(\033[01;39m%branch %git_status\e[33m) ";
      git = xreplace(git, "%branch", branch);
      if (status == 1)
	git = xreplace(git, "%git_status", "\e[32m✓");
      else
	git = xreplace(git, "%git_status", "\e[31m✗");
    }
  else
    git = "\e[33mgit:(\033[01;39mGit not installed\e[33m) ";
  return (git);
}

char		*get_prompt(t_mysh *sh)
{
  char		*prompt;

  prompt = strdup("%arrow \033[01;36m%pwd %git\033[00m");
  if (sh->status == 0)
    prompt = xreplace(prompt, "%arrow", strdup("\033[01;32m➜ \033[00m"));
  else
    prompt = xreplace(prompt, "%arrow", strdup("\033[01;31m➜ \033[00m"));
  if (prompt_getdir(sh->env_list) != NULL)
    prompt = xreplace(prompt, "%pwd", prompt_getdir(sh->env_list));
  if (git_check() == 1)
    prompt = xreplace(prompt, "%git", get_git(sh));
  else
    prompt = xreplace(prompt, "%git", "");
  return (prompt);
}
