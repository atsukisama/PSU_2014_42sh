/*
** cmd_utils.c for 42sh in /home/cano_c/rendu/UNIX/PSU_2014_42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Wed May 20 19:05:12 2015 
** Last update Sun May 24 23:29:39 2015 
*/
#include <mysh.h>

int		is_exe(char *cmd, char err)
{
  struct stat	s_stat;

  if (access(cmd, F_OK | X_OK) || stat(cmd, &s_stat))
    {
      if (access(cmd, F_OK) && err)
	{
	  fprintf(stderr, "42sh: %s: no such file or directory\n", cmd);
	  return (127);
	}
      else if (access(cmd, X_OK) && err)
	fprintf(stderr, "42sh: %s: permission denied\n", cmd);
      return (126);
    }
  else if (stat(cmd, &s_stat) || S_ISDIR(s_stat.st_mode))
    {
      if (err)
	fprintf(stderr, "42sh: %s: is a directory\n", cmd);
      return (126);
    }
  return (0);
}

int		get_exe(char **cmd)
{
  glob_t	s_glob;

  memset(&s_glob, 0, sizeof(s_glob));
  if (!glob(cmd[0], 0, NULL, &s_glob))
    {
      if (s_glob.gl_pathc && *s_glob.gl_pathv[0])
	{
	  cmd[0] = my_strdup(s_glob.gl_pathv[0]);
	  return (0);
	}
    }
  return (-1);
}

int		exit_status(int status, t_job UN *job)
{
  char		*sig_msg;

  if (WIFSIGNALED(status))
    {
      status = WTERMSIG(status);
      if ((sig_msg = strsignal(status)))
	fprintf(stderr, "mysh: killed by signal %d: %s\n",
		status, sig_msg);
      else
	fprintf(stderr, "mysh: killed by signal %d: %s\n",
		status, "unknown");
    }
  else
    status = WEXITSTATUS(status);
  return (status);
}
