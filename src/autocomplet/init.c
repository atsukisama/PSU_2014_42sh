/*
** init.c for init autocomplet in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Thu May 21 15:30:23 2015 Vertigo
** Last update Sun May 24 14:15:53 2015 Vertigo
*/

#include <mysh.h>
#include <autocomplet.h>

void	collect_args(t_complet *args, char **av)
{
  int	i;

  i = 1;
  while (av[i] != NULL)
    {
      select_add_before(args, av[i]);
      ++i;
    }
}

char	*generate_file_line(char *line, char *file)
{
  char	*new;
  int	i;

  i = my_strlen(line);
  while (i >= 0 && line[i] != ' ')
    --i;
  line[i + 1] = '\0';
  new = my_strdup2(line, file);
  return (new);
}

char		*get_selected(t_complet *args)
{
  t_complet	*tmp;

  tmp = args->next;
  while (tmp != args)
    {
      if (tmp->is_active == 1)
	return (tmp->name);
      tmp = tmp->next;
    }
  return (NULL);
}

int		init_autocomplet(char **args, t_mysh *sh, char **line, int *pos)
{
  if ((g_select.tty = open("/dev/tty", O_RDWR)) < 0)
    return (my_putstr("Error, could not open \"/dev/tty\"\n"));
  if ((tgetent(NULL, get_var_env(sh->env_list, "TERM"))) != 1)
    return (my_putstr("Environment fail, autocomplet terminated.\n"));
  g_select.args = select_create();
  collect_args(g_select.args, args);
  signal(SIGWINCH, terminal_hook);
  if (my_select(g_select.args, sh, line) == 1)
    *line = generate_file_line(*line, get_selected(g_select.args));
  clearscreen(sh, *line);
  *pos = my_strlen(*line);
  return (0);
}
