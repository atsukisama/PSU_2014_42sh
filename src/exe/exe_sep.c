/*
** exe_sep.c for 42sh in /home/cano_c/rendu/UNIX/42sh/PSU_2014_42sh/42tmp
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Fri May 15 09:38:50 2015 Chloe Cano
** Last update Mon May 25 01:35:00 2015 Jimmy KING
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
      sh->status = sh->exe_ft[ast->left->type](ast->left, sh, job);
      if (ast->right)
	{
	  if (!(job = my_memalloc(sizeof(*job))))
	    return (-1);
	  job->status = JOB_FG;
	  sh->status = sh->exe_ft[ast->right->type](ast->right, sh, job);
	}
    }
  return (sh->status);
}

int		exe_bg(t_ast *ast, t_mysh *sh, t_job *job)
{
  if (ast->left)
    {
      job->status = JOB_BG;
      sh->status = sh->exe_ft[ast->left->type](ast->left, sh, job);
      if (ast->right)
	{
	  if (!(job = my_memalloc(sizeof(*job))))
	    return (-1);
	  job->status = JOB_FG;
	  sh->status = sh->exe_ft[ast->right->type](ast->right, sh, job);
	}
    }
  return (sh->status);
}
