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
#include <get_next_line.h>
#include <mysh.h>

void    check_dash_line(char *s, char *file, t_list *list)
{
  if (s != NULL &&
      my_strncmp(s, file, my_strlen(s)) != 0)
    list_add(list, s, "");
  if (s == NULL)
    fprintf(stderr, "42sh: warning: delimited by end-of-file (wanted `%s')\n"
	    , file);
}

void     exec_parallel(t_ast *ast, t_mysh *sh, int fd[2], t_job *job)
{
  int   s;

  close(fd[1]);
  s = dup(0);
  dup2(fd[0], 0);
  sh->status = sh->exe_ft[ast->right->type](ast->right, sh, job);
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

int             do_double_red(t_ast *ast, t_mysh *sh, char *s, t_job *job)
{
  int           pid;
  int           fd[2];
  t_list        *list;

  list = list_create();
  can_set(sh->tsave);
  while (s != NULL && my_strcmp(s, ast->left->content.file) != 0)
    {
      write(0, "> ", 2);
      s = get_next_line(0);
      check_dash_line(s, ast->left->content.file, list);
    }
  pipe(fd);
  if ((pid = fork()) < 0)
    return (-1);
  if (pid == 0)
    exec_double_dash_left(list, fd);
  else if (pid > 0)
    exec_parallel(ast, sh, fd, job);
  can_on(&sh->term);
  wait(&pid);
  return (0);
}

int     dash_left_check(int red_fd[2], int flags, t_ast *ast, t_mysh *sh, t_job *job)
{
  int   ret;

  if (ast->content.red[0] == '<' && ast->content.red[1])
    ret = do_double_red(ast, sh, "", job);
  else
    ret = do_red(red_fd, flags, ast, sh, job);
  return (ret);
}
