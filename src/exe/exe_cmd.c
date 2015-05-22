/*
** exe_cmd.c for 42sh in /home/cano_c/rendu/UNIX/42sh/PSU_2014_42sh/42tmp
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Fri May 15 06:14:14 2015 
** Last update Fri May 22 21:16:35 2015 
*/
#include <mysh.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <glob.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

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
	  /*	  init_proc(sh);*/
	  can_set(sh->tsave);
	  execve(cmd, arv, env);
	  write(2, "42sh: failed to execute command\n", 32);
	  exit(126);
	}
      sh->status = wait_proc(sh, pid);
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
  fprintf(stderr, "42sh: %s: command not found\n", cmd[0]);
  return (127);
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
  while (waitpid(-1, NULL, WNOHANG) > -1)
    ;
  if (sh->is_tty && sh->wait)
    {
      /*      tcsetpgrp(0, sh->pgid);*/
      can_set(sh->term);
    }
  return (sh->status);
}
