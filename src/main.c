/*
** main.c for main file in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 09:45:35 2015 Vertigo
** Last update Fri May 15 13:49:49 2015 
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <get_next_line.h>
#include <mysh.h>
#include <project.h>

void	load_history(t_list *history)
{
  int	fd;
  char	*s;

  if ((fd = open(HISTORY_FILE, O_RDONLY)) < 0)
    return;
  while ((s = get_next_line(fd)) != NULL)
    list_add(history, s, "");
  close(fd);
}

int	init_sh(t_mysh *sh, char **env)
{
  sh->env_list = list_create();
  sh->history = list_create();
  if (access(HISTORY_FILE, R_OK) == 0)
    load_history(sh->history);
  env_collect(env, sh->env_list);
  if (!(sh->tsave = can_on()))
    return (-1);
  return (0);
}

void	sig(int sign)
{
  sign = sign;
}

void		free_sh(t_mysh *sh)
{
  free(sh->tsave);
  free(sh);
}

int		main(int ac, char **av, char **env)
{
  t_mysh	*sh;
  int		ret;

  (void)ac;
  (void)av;
  if (!(sh = malloc(sizeof(*sh))))
    malloc_error();
  signal(SIGINT, sig);
  if (init_sh(sh, env))
    return (-1);
  ret = my_sh(sh);
  list_goto_root_hist(sh);
  save_history(sh->history);
  free_sh(sh);
  return (ret);
}
