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
#include	"project.h"

char		*get_cur_pwd()
{
  char		pwd[1024];
  char		*res;

  if (getcwd(pwd, sizeof(pwd)) == NULL)
    fprintf(stderr,"getcwd() error");
  res = pwd;
  return (res);
}

void            my_old_cd(t_list *list)
{
  int		i;
  t_list	*tmp;

  tmp = get_node_by_key(list, "OLDPWD");
  printf("%s", tmp->content);
  env_set(list, "OLDPWD", get_cur_pwd());
  chdir(tmp->content);
  env_set(list, "PWD", get_cur_pwd());
}

void            my_home_cd(t_list *list)
{
  int		i;
  t_list	*tmp;

  tmp = get_node_by_key(list, "HOME");
  printf("%s", tmp->content);
  env_set(list, "OLDPWD", get_cur_pwd());
  chdir(tmp->content);
  env_set(list, "PWD", get_cur_pwd());
}

void            my_cd(t_list *list, char **tab)
{
  if ((access(tab[1], F_OK & R_OK) == -1) && tab[1] && tab[1][0] != '-')
    {
      printf("bash: cd: ");
      printf("%s",tab[1]);
      printf(": No such file or directory\n");
    }
  if (tab[1] == '\0')
    my_home_cd(list);
  else if (tab[1][0] == '-')
      my_old_cd(list);
  else
    {
      env_set(list, "OLDPWD", get_cur_pwd());
      chdir(tab[1]);
      env_set(list, "PWD", get_cur_pwd());
    }
}
