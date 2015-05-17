/*
** exe_cmd.c for 42sh in /home/cano_c/rendu/UNIX/42sh/PSU_2014_42sh/42tmp
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Fri May 15 06:14:14 2015 
** Last update Sun May 17 17:38:05 2015 Vertigo
*/
#include <mysh.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <glob.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

int		is_exe(char *cmd, char err)
{
  struct stat	s_stat;

  if (access(cmd, F_OK | X_OK) || stat(cmd, &s_stat))
    {
      write(2, "mysh: ", 6);
      if (access(cmd, F_OK) && err)
	{
	  write(2, "no such file or directory\n", 26);
	  return (127);
	}
      else if (access(cmd, X_OK) && err)
	write(2, "permission denied\n", 18);
      return (126);
    }
  else if (stat(cmd, &s_stat) || !S_ISREG(s_stat.st_mode))
    {
      if (err)
	write(2, "mysh: is not a regular file\n", 28);
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
      if (s_glob.gl_pathc)
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

int		exe_abs(char *cmd, char **arv, t_mysh *sh)
{
  char		**env;
  int		pid;
  int		status;
  int		ret;

  get_exe(&cmd);
  if ((ret = is_exe(cmd, 1)))
    return (ret);
  if (!(env = list_to_tab(sh->env_list)))
    return (-1);
  if ((pid = fork()) > -1)
    {
      if (!pid)
	{
	  execve(cmd, arv, env);
	  write(2, "failed to execute command\n", 26);
	  exit(126);
	}
      else if (sh->wait)
	{
	  while (waitpid(-1, &status, 0) != pid)
	    status = exit_status(status, sh);
	  status = exit_status(status, sh);
	}
    }
  else
    status = -1;
  free(env);
  return (status);
}

int		exe_path(char **cmd, t_mysh *sh)
{
  char		pathname[NAME_MAX + PATH_MAX + 2];
  t_list       	*path_list;
  char		*path;
  char		*p;
  char		*path_cpy;

  if ((path_list = get_node_by_key(sh->env_list, "PATH")))
    {
      path = path_list->content;
      if (!(path_cpy = strdup(path)))
	return (-1);
      while ((p = strtok(path_cpy, ":")))
	{
	  path_cpy = NULL;
	  strncpy(pathname, p, PATH_MAX + 1);
	  strncat(pathname, "/", 2);
	  strncat(pathname, cmd[0], NAME_MAX);
	  p = cmd[0];
	  cmd[0] = pathname;
	  if (!get_exe(cmd) && !is_exe(cmd[0], 0))
	    return (exe_abs(cmd[0], cmd, sh));
	  cmd[0] = p;
	}
    }
  return (exe_abs(cmd[0], cmd, sh));
}

int		exe_rlt(char **cmd, t_mysh *sh)
{
  char		cwd[PATH_MAX + 1];
  char		pathname[PATH_MAX + NAME_MAX + 2];
  size_t	cmd_len;
  size_t	cwd_len;

  my_bzero(pathname, PATH_MAX + NAME_MAX + 2);
  if ((getcwd(cwd, PATH_MAX + 1)))
    {
      cmd_len = my_strlen(cmd[0]) - 2;
      cwd_len = my_strlen(cwd);
      if (cwd_len + cmd_len <= PATH_MAX + NAME_MAX && *(cmd[0] + 2))
	{
	  my_strncpy(pathname, cwd, cwd_len);
	  my_strncat(pathname, "/", 1);
	  my_strncat(pathname, cmd[0] + 2, cmd_len);
	  get_exe(cmd);
	  return (exe_abs(pathname, cmd, sh));
	}
    }
  return (-1);
}

int		exe_cmd(t_ast *ast, t_mysh *sh)
{
  if (ast->content.cmd[0])
    {
      if (!my_strncmp(ast->content.cmd[0], "./", 2))
	sh->status = exe_rlt(ast->content.cmd, sh);
      else if (chk_bult(sh, ast->content.cmd) != 0)
	sh->status = 0;
      else if (*ast->content.cmd[0] == '/' && sh->status != 9)
	sh->status = exe_abs(ast->content.cmd[0], ast->content.cmd, sh);
      else
	sh->status = exe_path(ast->content.cmd, sh);
    }
  free(ast->content.cmd);
  free(ast);
  return (sh->status);
}
