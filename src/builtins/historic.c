/*
** historic.c for  in /home/rusign/rendu/PSU_2014_42sh/src
** 
** Made by rusig_n
** Login   <nicolas.rusig@epitech.eu>
** 
** Started on  Mon May 18 14:02:59 2015 rusig_n
** Last update Mon May 18 14:02:59 2015 rusig_n
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <mysh.h>

int		my_history(t_list *history, char **cmd, int i, int max)
{
  t_list	*tmp;
  char		buf_m[255];
  char		buf_i[255];

  if (cmd[1] && (my_strcmp(cmd[1], "-c")) == 0)
    my_histo_c(history);
  else
    {
      tmp = history->next;
      max = size_histo(history);
      sprintf(buf_m, "%d", max);
      while (tmp != history)
	{
	  if (tmp->key != NULL)
	    {
	      sprintf(buf_i, "%d", i);
	      max = my_strlen(buf_m) - my_strlen(buf_i) + 3;
	      while (--max)
		my_putchar(' ');
	      printf("%d %s\n", i++, tmp->key);
	    }
	  tmp = tmp->next;
	}
    }
  return (1);
}

char		*histo_pos(int nb, t_mysh *sh)
{
  t_list	*tmp;

  tmp = sh->history->next;
  while (nb > 1)
    {
      tmp = tmp->next;
      nb--;
    }
  my_putstr(tmp->key);
  my_putchar('\n');
  return (tmp->key);
}

char		*histo_str(t_mysh *sh, char *val)
{
  t_list	*tmp;
  int		i;

  i = 0;
  tmp = sh->history->next;
  while (tmp != sh->history)
    {
      i++;
      tmp = tmp->next;
    }
  while (i >= 0)
    {
      if ((my_strncmp(val, tmp->key, my_strlen(val) - 1)) == 0)
	{
	  printf("%s\n", tmp->key);
	  return (tmp->key);
	}
      tmp = tmp->prev;
      i--;
    }
  fprintf(stderr, "42sh: !%s: event not found\n", val);
  return (NULL);
}

char		*histo_neg(int nb, t_mysh *sh)
{
  t_list	*tmp;

  tmp = sh->history->next;
  while (tmp != sh->history)
    tmp = tmp->next;
  while (nb >= 0)
    {
      tmp = tmp->prev;
      nb--;
    }
  my_putstr(tmp->key);
  my_putchar('\n');
  return (tmp->key);
}

int		my_seek_history(t_mysh *sh, char *val, int nb)
{
  char		*line;

  if (val && (my_strcmp(val, "") == 0 || val[0] == '!'))
    return (1);
  if (is_num(val) == 0)
    {
      if ((nb = my_getnbr(val)) > 0)
	line = histo_pos(nb, sh);
      else
	line = histo_neg(nb * -1, sh);
    }
  else
    line = histo_str(sh, val);
  if (line == NULL)
    return (1);
  line = alias_replace(sh->alias, line);
  if (exe_histo(line, sh) == -1)
    return (-1);
  return (1);
}

