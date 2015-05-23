/*
** exe_red_utils.c for exe_red_utils in /home/kerebel/PSU_2014_42sh/src/exe
** 
** Made by Paul Kerebel
** Login   <kerebe_p@epitech.eu>
** 
** Started on  Sat May 23 17:46:00 2015 Paul Kerebel
** Last update Sat May 23 17:46:00 2015 Paul Kerebel
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <mysh.h>

int             open_failure(char *file, int flags)
{
  struct stat   s_stat;

  if (access(file, F_OK))
    {
      if (flags & O_TRUNC)
	fprintf(stderr, "42sh: %s: cannot create file\n", file);
      else
	fprintf(stderr, "42sh: %s: no such file or directory\n", file);
    }
  else if ((flags & O_WRONLY && access(file, W_OK))
	   || (!flags && access(file, R_OK)))
    fprintf(stderr, "42sh: %s: permission denied\n", file);
  else if (flags && !(stat(file, &s_stat)) && S_ISDIR(s_stat.st_mode))
    fprintf(stderr, "42sh: %s: is a directory\n", file);
  else
    fprintf(stderr, "42sh: %s: undefined error at open\n", file);
  return (-1);
}

int     swap_red(t_ast *ast, int red_fd[2])
{
  ast->content.red[0] = ast->content.red[1];
  ast->content.red[1] = ast->content.red[2];
  ast->content.red[2] = 0;
  red_fd[1] = 2;
  return (0);
}

void     exec_parallel(t_ast *ast, t_mysh *sh, int fd[2])
{
  int   s;

  close(fd[1]);
  s = dup(0);
  dup2(fd[0], 0);
  sh->status = sh->exe_ft[ast->right->type](ast->right, sh);
  dup2(0, fd[0]);
  dup2(s, 0);
}

void             exec_double_dash_left(t_list *list, int fd[2])
{
  t_list        *tmp;

  close(fd[0]);
  dup2(fd[1], 1);
  tmp = list->next;
  while (tmp != list)
    {
      my_putstr(tmp->key);
      my_putchar('\n');
      tmp = tmp->next;
    }
  dup2(1, fd[1]);
  exit(0);
}
