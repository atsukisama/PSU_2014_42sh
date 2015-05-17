/*
** my_cd.c for  in /home/rusign/rendu/42sh/PSU_2014_42sh/bultin
** 
** Made by rusig_n
** Login   <nicolas.rusig@epitech.eu>
** 
** Started on  Thu May 14 12:29:31 2015 rusig_n
** Last update Thu May 14 12:29:31 2015 rusig_n
*/

# include       <sys/wait.h>
# include       <sys/time.h>
# include       <sys/types.h>
# include       <stdlib.h>
# include       <unistd.h>
# include	"project.h"

char		*get_cur_pwd()
{
  char		pwd[1024];
  char		*res;

  if (getcwd(pwd, sizeof(pwd)) == NULL)
    {
      fprintf(stderr,"getcwd() error");
      return (NULL);
    }
  res = pwd;
  return (res);
}

char		*get_var_env(t_list *list, char *var)
{
  t_list	*tmp;

  if ((tmp = get_node_by_key(list, var)) == NULL)
    return (NULL);
  else
    return (tmp->content);
}

void            my_old_cd(t_mysh *sh)
{
  my_putstr(sh->oldpwd);
  my_putchar(10);
  env_set(sh->env_list, "OLDPWD", sh->pwd);
  chdir(sh->oldpwd);
  sh->oldpwd = my_strdup(sh->pwd);
  sh->pwd = my_strdup(sh->oldpwd);
  env_set(sh->env_list, "PWD", sh->pwd);
}

void            my_home_cd(t_mysh *sh)
{
  char		*str;

  if ((str = get_var_env(sh->env_list, "HOME")) == NULL)
    {
      str = my_strdup("/");
      env_set(sh->env_list, "OLDPWD", str);
    }
  sh->oldpwd = my_strdup(sh->pwd);
  env_set(sh->env_list, "OLDPWD", sh->pwd);
  chdir(str);
  sh->pwd = my_strdup(str);
  env_set(sh->env_list, "PWD", str);
}

int            my_cd(t_mysh *sh, char **tab)
{
  sh->pwd = get_cur_pwd();
  if (sh->oldpwd == NULL)
    sh->oldpwd = sh->pwd;
  if ((access(tab[1], F_OK & R_OK) == -1) && tab[1] && tab[1][0] != '-')
    {
      printf("bash: cd: %s", tab[1]);
      printf(": No such file or directory\n");
      return (-1);
    }
  if (tab[1] == NULL)
    my_home_cd(sh);
  else if (tab[1][0] == '-')
    my_old_cd(sh);
  else
    {
      sh->oldpwd = my_strdup(sh->pwd);
      env_set(sh->env_list, "OLDPWD", sh->pwd);
      chdir(tab[1]);
      sh->pwd = my_strdup(tab[1]);
      env_set(sh->env_list, "PWD", get_cur_pwd());
    }
  return (1);
}
