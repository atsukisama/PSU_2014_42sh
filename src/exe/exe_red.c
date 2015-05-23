/*
** redir.c for redir functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Fri May 15 14:36:48 2015 Vertigo
** Last update Tue May 19 22:19:33 2015 
*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <parser.h>
#include <mysh.h>
#include <stdio.h>
#include <get_next_line.h>

int	do_red(int red_fd[2], int flags, t_ast *ast, t_mysh *sh)
{
  int	fd;
  int	save_fd[2];

  if ((fd = open(ast->left->content.file, flags, 0644)) < 0)
    return (open_failure(ast->left->content.file, flags));
  save_fd[0] = dup(red_fd[0]);
  if (red_fd[1] > -1)
    {
      save_fd[1] = dup(red_fd[1]);
      dup2(fd, red_fd[1]);
    }
  dup2(fd, red_fd[0]);
  sh->status = sh->exe_ft[ast->right->type](ast->right, sh);
  dup2(save_fd[0], red_fd[0]);
  if (red_fd[1] > -1)
    dup2(save_fd[0], red_fd[1]);
  return (sh->status);
}

void	check_dash_line(char *s, char *file, t_list *list)
{
  if (s != NULL &&
      my_strncmp(s, file, my_strlen(s)) != 0)
    list_add(list, s, "");
  if (s == NULL)
    fprintf(stderr, "42sh: warning: delimited by end-of-file (wanted `%s')\n"
	    , file);
}

int             do_double_red(t_ast *ast, t_mysh *sh, char *s)
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
    exec_parallel(ast, sh, fd);
  can_on(&sh->term);
  wait(&pid);
  return (0);
}

int	dash_left_check(int red_fd[2], int flags, t_ast *ast, t_mysh *sh)
{
  int   ret;

  if (ast->content.red[0] == '<' && ast->content.red[1])
    ret = do_double_red(ast, sh, "");
  else
    ret = do_red(red_fd, flags, ast, sh);
  return (ret);
}

int	exe_red(t_ast *ast, t_mysh *sh)
{
  int	flags;
  int	red_fd[2];
  int	ret;

  flags = 0;
  red_fd[1] = -1;
  if (ast->content.red[0] == '&')
    swap_red(ast, red_fd);
  if (ast->content.red[0] == '<')
    {
      flags = O_RDONLY;
      red_fd[0] = 0;
    }
  else if (ast->content.red[0] == '>')
    {
      flags = O_WRONLY | O_CREAT;
      red_fd[0] = 1;
    }
  if (ast->content.red[1] && (flags & O_WRONLY))
    flags |= O_APPEND;
  else if (flags & O_WRONLY)
    flags |= O_TRUNC;
  ret = dash_left_check(red_fd, flags, ast, sh);
  return (ret);
}
