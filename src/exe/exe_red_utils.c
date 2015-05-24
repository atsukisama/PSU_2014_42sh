/*
** exe_red_utils.c for exe_red_utils in /home/kerebel/PSU_2014_42sh/src/exe
**
** Made by Paul Kerebel
** Login   <kerebe_p@epitech.eu>
**
** Started on  Sat May 23 17:46:00 2015 Paul Kerebel
** Last update Sun May 24 22:26:08 2015 Jimmy KING
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <get_next_line.h>
#include <mysh.h>

void	check_dash_line(char *s, char *file, t_list *list)
{
  if (s != NULL &&
      my_strncmp(s, file, my_strlen(s)) != 0)
    list_add(list, s, "");
  if (s == NULL)
    fprintf(stderr, "42sh: warning: delimited by end-of-file (wanted `%s')\n"
            , file);
}

int	exec_parallel(t_ast *ast, t_mysh *sh, int fd[2], t_job *job)
{
  int	s_fd;
  int	ret;

  close(fd[1]);
  if ((s_fd = dup(0)) == -1)
    return (-1);
  if (dup2(fd[0], 0) == -1)
    return (-1);
  sh->status = sh->exe_ft[ast->right->type](ast->right, sh, job);
  ret = dup2(s_fd, 0);
  if (ret && !sh->status)
    sh->status = -1;
  return (sh->status);
}

void		exec_double_dash_left(t_list *list, int fd[2])
{
  t_list	*tmp;

  close(fd[0]);
  tmp = list->next;
  while (tmp != list)
    {
      write(fd[1], tmp->key, my_strlen(tmp->key));
      write(fd[1], "\n", 1);
      tmp = tmp->next;
    }
  exit(0);
}

int		do_double_red(t_ast *ast, t_mysh *sh, char *s, t_job *job)
{
  int		pid;
  int		fd[2];
  t_list	*list;

  list = list_create();
  can_set(sh->tsave);
  while (s != NULL && my_strcmp(s, ast->left->content.file) != 0)
    {
      if (job->pgid)
        tcsetpgrp(0, job->pgid);
      write(0, "> ", 2);
      s = get_next_line(0);
      check_dash_line(s, ast->left->content.file, list);
    }
  if (pipe(fd))
    return (-1);
  if ((pid = fork()) < 0)
    return (-1);
  if (pid == 0)
    exec_double_dash_left(list, fd);
  can_set(sh->term);
  return (exec_parallel(ast, sh, fd, job));
}

int	dash_left_check(int red_fd[3], t_ast *ast, t_mysh *sh, t_job *job)
{
  int	ret;

  if (ast->content.red[0] == '<' && ast->content.red[1])
    ret = do_double_red(ast, sh, "", job);
  else
    ret = do_red(red_fd, ast, sh, job);
  return (ret);
}
