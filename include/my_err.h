/*
** my_err.h for minishell1.h in /home/cano_c/rendu/UNIX/my_select/minishell1
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Fri Jan 30 18:42:39 2015
** Last update Sun Mar  8 05:35:51 2015 Cano Chloe
*/
#ifndef MY_ERR_H_
# define MY_ERR_H_

# include <sys/types.h>
# include <dirent.h>

# define MAX_ERRMSG	200

int			errno;

# define CP(str, msg)			(my_strncpy(str, msg, MAX_ERRMSG))
# define SET_ERRSTR(str, errno, msg)	(CP((str) + (errno) * MAX_ERRMSG, msg))

typedef enum		e_errno_idx
  {
    E_SUCCESS,
    E_OOM,
    E_NSFD,
    E_FILENF,
    E_DIRNF,
    E_NAMETOOLNG,
    E_PERM,
    E_OPEN,
    E_OPENDIR,
    E_NOTDIR,
    E_TERMCAP,
    E_ENV,
    E_FORK,
    E_PIPE,
    E_DUP,
    MAX_ERRNO
  } t_errno_idx;

void		my_perror(int my_errno, char *prog_name, char *msg);

int		my_access(const char *path, int flags);
int		my_open(char *path, int flags);
pid_t		my_fork(void);
void		my_execve(char *pathname, char **av, char **environ);
DIR		*my_opendir(const char *name);

#endif /* !MY_ERR_H_ */
