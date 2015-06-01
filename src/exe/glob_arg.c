/*
** glob_arg.c for glob functions in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Sun May 24 21:41:55 2015 Vertigo
** Last update Sun May 24 22:31:35 2015 Vertigo
*/

#include <mysh.h>

char		**replace_glob(char **tab, int i)
{
  glob_t	gl;
  char		*s;

  s = tab[i];
  memset(&gl, 0, sizeof(gl));
  if (glob(s, 0, NULL, &gl) != 0)
    return (tab);
  while (tab[i] != NULL)
    {
      tab[i] = tab[i + 1];
      ++i;
    }
  i = 0;
  while (gl.gl_pathv[i] != NULL)
    {
      tab = add_line(tab, gl.gl_pathv[i]);
      ++i;
    }
  return (tab);
}

int	is_contain(char *s, char c)
{
  int	i;

  i = 0;
  while (s[i] != '\0')
    {
      if (s[i] == c)
	return (0);
      ++i;
    }
  return (-1);
}

char	**glob_arg(char **cmd, char **tab)
{
  int	i;

  i = 1;
  get_exe(cmd);
  while (tab[i] != NULL)
    {
      if (is_contain(tab[i], '*') == 0 && is_contain(tab[i], '-') != 0)
	tab = replace_glob(tab, i);
      ++i;
    }
  return (tab);
}
