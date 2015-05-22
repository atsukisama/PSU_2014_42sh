/*
** mysh.h for mysh functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 09:57:43 2015 Vertigo
** Last update Fri May 22 18:21:39 2015 
*/

#ifndef MYSH_H_
# define MYSH_H_

# include <signal.h>
# include <glob.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

# include "list.h"
# include "parser.h"

# define HISTORY_FILE	".42sh_history"

typedef struct s_mysh	t_mysh;

# define SIG_MAX	40

struct			s_mysh
{
  char			sig_msg[SIG_MAX][NAME_MAX + 1];
  int			status;
  char			*oldpwd;
  char			*pwd;
  t_list		*env_list;
  t_list		*history;
  struct termios	*term;
  struct termios	*tsave;
  int			(*exe_ft[PA_TRM + 1])(t_ast *, t_mysh *);
  int			wait;
  char			*prompt;
  int			is_tty;
  int			pgid;
};

int			my_sh(t_mysh *);

/*
** command line
*/

char			*get_line(t_mysh *);
int			my_char_isprintable(char);
int			particular_key(char buf[4], int *, t_mysh *, char **);
void			left_arrow(int *, char **, t_mysh *);
void    		right_arrow(int *, char **, t_mysh *);
void  			up_arrow(int *, char **, t_mysh *);
void    		down_arrow(int *, char **, t_mysh *);
void			display_line(char *tab[2], int , int, t_mysh *);
void			clear_screen(t_mysh *);
void			my_exit(t_mysh *, int, char *, int *);
void			list_goto_root_hist(t_mysh *);
int			save_history(t_list *);
int			back_cursor(t_mysh *, int);
int			forward_cursor(t_mysh *, int);
void			clear_plus(char **, t_mysh *, int);
void			display_line_hist(char *tab[2], int *, int, t_mysh *);

/*
** termcaps
*/

struct termios		*can_on(struct termios **term);
int			can_set(struct termios *term);

/*
** Execution
*/

int			exe_cmd(t_ast *ast, t_mysh *sh);
int			exe_and(t_ast *ast, t_mysh *sh);
int			exe_or(t_ast *ast, t_mysh *sh);
int			exe_trm(t_ast *ast, t_mysh *sh);
int			exe_pipe(t_ast *ast, t_mysh *sh);
int			exe_red(t_ast *ast, t_mysh *sh);

void			set_sig_msg(t_mysh *sh);
int			exit_status(int status, t_mysh *sh);
int			wait_proc(t_mysh *sh, int pid);
int			init_proc(t_mysh *sh);
int			proc_status(t_mysh *sh, int pid);
int			control_term(t_mysh *sh);

int			is_exe(char *cmd, char err);
int			get_exe(char **cmd);

/*
** Builtins
*/

int			chk_bult(t_mysh *sh, char **cmd);
int			my_cd(t_mysh *sh, char **tab);
int			my_unsetenv(t_list *list, char **cmd);
int			my_echo(char **cmd, t_mysh *sh);
int		        my_history(t_list *history);
int	                my_seek_history(t_list *history, char *val);
int			my_setenv(t_list *list, char **cmd);

/*
** MISC
*/

char			*my_strchr(char *, int);
int			my_puterror(char *, int);
void			malloc_error();

#endif /* !MYSH_H_ */
