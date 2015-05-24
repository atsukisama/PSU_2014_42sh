/*
** autocomplet.c for autocomplet in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 20 12:21:18 2015 Vertigo
** Last update Sun May 24 13:08:15 2015 Vertigo
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <my.h>
#include <mysh.h>
#include <autocomplet.h>

int	contain_folder(char *s)
{
  int	i;

  i = 0;
  while (s[i] != '\0')
    {
      if (s[i] == '/')
	return (0);
      ++i;
    }
  return (-1);
}

char		**generate_array(char *s)
{
  char		**tab;
  glob_t	s_glob;
  int		i;

  i = 0;
  memset(&s_glob, 0, sizeof(s_glob));
  if (!(tab = malloc(sizeof(*tab) * 2)))
    return (NULL);
  tab[0] = my_strdup("autocomplet");
  tab[1] = NULL;
  if (glob(my_strdup2(s, "*"), 0, NULL, &s_glob) == 0)
    while (s_glob.gl_pathv[i] != NULL)
      {
	tab = add_line(tab, s_glob.gl_pathv[i]);
	++i;
      }
  return (tab);
}

void			disp_alone(char **line, char *file, int *pos,
				   t_mysh *sh)
{
  int	i;
  struct winsize	ws;

  i = 0;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1)
    while (i++ < ws.ws_col)
      my_putstr("\033[1D");
  *line = generate_file_line(*line, file);
  *pos = my_strlen(*line);
  my_putstr(sh->prompt);
  my_putstr(*line);
}

int	autocomplet(char *s, t_mysh *sh, char **line, int *pos)
{
  char	*last;
  char	**files;

  last = get_last_word(s);
  files = generate_array(last);
  if (count_dab(files) > 2)
    init_autocomplet(files, sh, line, pos);
  else if (count_dab(files) == 2)
    disp_alone(line, files[1], pos, sh);
  free(g_select.args);
  return (0);
}
