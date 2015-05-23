/*
** handle_proc.c for 42sh in /home/cano_c/rendu/UNIX/PSU_2014_42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Wed May 20 19:14:07 2015
** Last update Sat May 23 18:35:24 2015 
*/
#include <mysh.h>

int		init_proc(t_mysh *sh, t_job *job)
{
  int		pid;

  if (sh->is_tty)
    {
      can_set(sh->tsave);
      signal(SIGQUIT, SIG_DFL);
      signal(SIGINT, SIG_DFL);
      signal(SIGSTOP, SIG_DFL);
      signal(SIGTTIN, SIG_DFL);
      signal(SIGTTOU, SIG_DFL);
      pid = getpid();
      if (!job->pgid)
	job->pgid = pid;
      if ((setpgid(pid, job->pgid)))
	{
	  job->pgid = pid;
	  setpgid(pid, pid);
	}
      if (job->status == JOB_FG)
	tcsetpgrp(0, job->pgid);
    }
  return (0);
}

int		proc_status(t_mysh *sh, int pid, t_job *job)
{
  if (sh->is_tty)
    {
      if (setpgid(pid, job->pgid))
	{
	  job->pgid = pid;
	  setpgid(pid, job->pgid);
	}
      if (job->status == JOB_FG)
	tcsetpgrp(0, job->pgid);
    }
  sh->status = wait_proc(sh, pid, job);
  if (job->status == JOB_FG)
    while (waitpid(-1, NULL, WNOHANG) > -1)
      ;
  return (sh->status);
}


int	control_term(t_mysh *sh)
{
  int	pgid;

  if ((sh->is_tty = isatty(0)))
    {
      while (tcgetpgrp(0) != (pgid = getpgrp()))
        kill(-pgid, SIGTTIN);
      signal(SIGQUIT, SIG_IGN);
      signal(SIGINT, SIG_IGN);
      signal(SIGSTOP, SIG_IGN);
      signal(SIGTTIN, SIG_IGN);
      signal(SIGTTOU, SIG_IGN);
      sh->pgid = getpid();
      if (setpgid(sh->pgid, sh->pgid))
	{
	  write(2, "42sh: failed to set process group\n", 34);
	  return (-1);
	}
      if (tcsetpgrp(0, sh->pgid))
	{
	  write(2, "42sh: failed to become foreground process\n", 42);
	  return (-1);
       	}
    }
  return (0);
}

int		wait_proc(t_mysh *sh, int pid, t_job *job)
{
  int		status;

  status = 0;
  if (sh->wait && job->status == JOB_FG)
    {
      while (waitpid(-1, &status, 0) != pid)
	{
	  status = exit_status(status, job);
	  if (WIFSIGNALED(status))
	    killpg(job->pgid, SIGKILL);
	}
      status = exit_status(status, job);
      if (WIFSIGNALED(status))
	killpg(job->pgid, SIGKILL);
    }
  return (status);
}
