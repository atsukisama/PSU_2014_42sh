/*
** my_getenv.c for libmy in /home/k6/epitech/UNIX/my_select
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Mon Jan  5 22:40:58 2015
** Last update Sun Mar  8 05:37:33 2015 Cano Chloe
*/
#include <my.h>

char		*my_getenv(char **environ, char *name)
{
  char		**env;

  env = environ;
  while (*env)
    {
      if (!my_strncmp(*env, name, my_strlen(name)))
	return (*env + my_strlen(name));
      ++env;
    }
  return (*env);
}
