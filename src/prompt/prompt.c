/*
** prompt.c for prompt in /home/king_j/Git/Epitech/kerebe_p/o/PSU_2014_42sh/src/prompt
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Sat May 23 20:28:44 2015 Jimmy KING
** Last update Sun May 24 02:10:55 2015 Jimmy KING
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

char	*prompt_getdir(t_list *env_list)
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

char	*get_prompt(t_list *env)
{
  char		*prompt;

  prompt = strdup("%arrow \033[01;36m%pwd \033[00m");
  prompt = xreplace(prompt, "%arrow", strdup("\033[01;32m➜ \033[00m"));
  if (prompt_getdir(env) != NULL)
    prompt = xreplace(prompt, "%pwd", prompt_getdir(env));
  //  if (get_hostname() != NULL && match(prompt, "*%hostname*"))
  // prompt = xreplace(prompt, "%hostname", get_hostname());
  return (prompt);
}
