/*
** exe_sep.c for 42sh in /home/cano_c/rendu/UNIX/42sh/PSU_2014_42sh/42tmp
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Fri May 15 09:38:50 2015 
** Last update Mon May 18 21:35:02 2015 
*/
#include <mysh.h>

int		exe_and(t_ast *ast, t_mysh *sh, t_job *job)
{
  if (!(sh->status = sh->exe_ft[ast->left->type](ast->left, sh, job)))
    sh->status = sh->exe_ft[ast->right->type](ast->right, sh, job);
  return (sh->status);
}

int		exe_or(t_ast *ast, t_mysh *sh, t_job *job)
{
  if ((sh->status = sh->exe_ft[ast->left->type](ast->left, sh, job)))
    sh->status = sh->exe_ft[ast->right->type](ast->right, sh, job);
  return (sh->status);
}

int		exe_trm(t_ast *ast, t_mysh *sh, t_job *job)
{
  if (ast->left)
    {
      if (!(job = my_memalloc(sizeof(*job))))
	return (-2);
      job->status = JOB_FG;
      sh->status = sh->exe_ft[ast->left->type](ast->left, sh, job);
      if (ast->right)
	sh->status = sh->exe_ft[ast->right->type](ast->right, sh, job);
    }
  return (sh->status);
}

int		exe_bg(t_ast *ast, t_mysh *sh, t_job *job)
{
  if (ast->left)
    {
      if (!(job = my_memalloc(sizeof(*job))))
	return (-2);
      job->status = JOB_BG;
      sh->status = sh->exe_ft[ast->left->type](ast->left, sh, job);
      if (ast->right)
	sh->status = sh->exe_ft[ast->right->type](ast->right, sh, job);
    }
  return (sh->status);
}
