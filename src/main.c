/*
** main.c for main file in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 09:45:35 2015 Vertigo
** Last update Thu May 28 18:49:24 2015 Vertigo
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

  if ((fd = open(HISTORY_FILE, O_RDONLY)) >= 0)
    {
      while ((s = get_next_line(fd)) != NULL)
	list_add(history, s, "");
      close(fd);
    }
}

int	init_sh(t_mysh *sh, char **env)
{
  if (control_term(sh))
    return (-1);
  if (sh->is_tty && !(sh->tsave = can_on(&sh->term)))
    return (-1);
  sh->oldpwd = NULL;
  sh->pwd = NULL;
  sh->env_list = list_create();
  sh->history = list_create();
  sh->alias = list_create();
  alias_initialize(sh->alias);
  if (access(HISTORY_FILE, R_OK) == 0)
    load_history(sh->history);
  env_collect(env, sh->env_list);
  sh->prompt = get_prompt(sh);
  sh->ret_exit = 0;
  return (0);
}

void	ctrl_c(int sign)
{
  sign = sign;
  write(1, "\n", 1);
  g_mysh->status = 1;
  if (g_mysh->line != NULL)
    g_mysh->line[0] = 0;
  g_mysh->prompt = get_prompt(g_mysh);
  my_putstr(g_mysh->prompt);
  g_mysh->pos = 0;
}

void		free_sh(t_mysh *sh)
{
  free(sh->tsave);
  free(sh);
}

int		main(int ac, char **av, char **env)
{
  int		ret;

  (void)ac;
  (void)av;
  if (!(g_mysh = my_memalloc(sizeof(*g_mysh))))
    return (-1);
  signal(SIGINT, ctrl_c);
  if (init_sh(g_mysh, env))
    return (-1);
  ret = my_sh(g_mysh);
  list_goto_root_hist(g_mysh);
  if (g_mysh->is_tty != 0)
    {
      save_history(g_mysh->history);
      free_sh(g_mysh);
    }
  return (ret);
}
