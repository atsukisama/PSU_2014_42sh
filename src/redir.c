/*
** redir.c for redir functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Fri May 15 14:36:48 2015 Vertigo
** Last update Fri May 15 14:55:14 2015 Vertigo
*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <parser.h>
#include <mysh.h>

int	redir_right(t_ast *ast, t_mysh *sh)
{
  int	fd;

  if ((fd = open(ast->left->content.file,
		 O_CREAT | O_WRONLY | O_TRUNC), 0644) < 0)
    return (-1);
  dup2(fd, 1);
  sh->status = sh->exe_ft[ast->right->type](ast, sh);
  dup2(1, fd);
  close(fd);
  return (sh->status);
}

int	redir_left(t_ast *ast, t_mysh *sh)
{
  int	fd;

  if ((fd = open(ast->right->content.file, O_RDONLY)) < 0)
    return (-1);
  dup2(fd, 0);
  sh->status = sh->exe_ft[ast->left->type](ast, sh);
  dup2(0, fd);
  close(fd);
  return (sh->status);
}
