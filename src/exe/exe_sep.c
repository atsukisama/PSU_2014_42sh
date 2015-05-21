/*
** exe_sep.c for 42sh in /home/cano_c/rendu/UNIX/42sh/PSU_2014_42sh/42tmp
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Fri May 15 09:38:50 2015 
** Last update Fri May 15 09:49:11 2015 
*/
#include <mysh.h>

int		exe_and(t_ast *ast, t_mysh *sh)
{
  if (!(sh->status = sh->exe_ft[ast->left->type](ast->left, sh)))
    sh->status = sh->exe_ft[ast->right->type](ast->right, sh);
  return (sh->status);
}

int		exe_or(t_ast *ast, t_mysh *sh)
{
  if ((sh->status = sh->exe_ft[ast->left->type](ast->left, sh)))
    sh->status = sh->exe_ft[ast->right->type](ast->right, sh);
  return (sh->status);
}

int		exe_trm(t_ast *ast, t_mysh *sh)
{
  if (ast->left)
    {
      sh->status = sh->exe_ft[ast->left->type](ast->left, sh);
      if (ast->right)
	sh->status = sh->exe_ft[ast->right->type](ast->right, sh);
    }
  return (sh->status);
}
