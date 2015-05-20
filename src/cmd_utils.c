/*
** cmd_utils.c for 42sh in /home/cano_c/rendu/UNIX/PSU_2014_42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Wed May 20 19:05:12 2015 
** Last update Wed May 20 19:13:20 2015 
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

void		set_sig_msg(t_mysh *sh)
{
  size_t	idx;

  idx = 0;
  while (idx < SIG_MAX)
    my_bzero(sh->sig_msg[idx++], NAME_MAX + 1);
  my_strncpy(sh->sig_msg[SIGQUIT], "Quit from keyboard", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGILL], "Illegal instruction", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGABRT], "Abort signal from abort(3)", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGFPE], "Floating point exception", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGSEGV], "Invalid memory reference (SEGV)", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGPIPE], "Broken pipe: write to pipe with no readers",
	     NAME_MAX);
  my_strncpy(sh->sig_msg[SIGBUS], "Bus error (bad memory access)", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGBUS], "Bus error (bad memory access)", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGSYS], "Bad argument to routine", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGTRAP], "It's a trap", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGXCPU], "Cpu time limit exceeded", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGXFSZ], "File size limit exceeded", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGIOT], "It's also a trap", NAME_MAX);
  my_strncpy(sh->sig_msg[SIGUNUSED], "Bad argument to routine", NAME_MAX);
}

int		exit_status(int status, t_mysh *sh)
{
  if (WIFSIGNALED(status) && sh->sig_msg[WTERMSIG(status)])
    {
      fprintf(stderr, "mysh: killed by signal %d: %s\n",
	      WTERMSIG(status), sh->sig_msg[WTERMSIG(status)]);
    }
  else
    status = WEXITSTATUS(status);
  return (status);
}
