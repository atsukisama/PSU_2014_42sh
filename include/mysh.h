/*
** mysh.h for mysh functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 09:57:43 2015 Vertigo
** Last update Fri May 15 18:30:13 2015 
*/

#ifndef MYSH_H_
# define MYSH_H_

# define HISTORY_FILE	".42sh_history"

# include "list.h"
# include "parser.h"

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
};


void			set_sig_msg(t_mysh *sh);
void			malloc_error();
int			my_sh(t_mysh *);
int			can_off();
char			*get_line(t_mysh *);
int			my_char_isprintable(char);
int			particular_key(char buf[4], int *, t_mysh *, char **);
void			left_arrow(int *, char **, t_mysh *);
void    		right_arrow(int *, char **, t_mysh *);
void  			up_arrow(int *, char **, t_mysh *);
void    		down_arrow(int *, char **, t_mysh *);
void			display_line(char *, char *, int *, int);
void			clear_screen(t_mysh *);
void			my_exit(t_mysh *, int, char *, int *);
void			list_goto_root_hist(t_mysh *);
int			save_history(t_list *);
struct termios		*can_on();
int			can_set(struct termios *term);
int			exe_cmd(t_ast *ast, t_mysh *sh);
int			exe_and(t_ast *ast, t_mysh *sh);
int			exe_or(t_ast *ast, t_mysh *sh);
int			exe_trm(t_ast *ast, t_mysh *sh);
int			exe_pipe(t_ast *ast, t_mysh *sh);
int			exe_red(t_ast *ast, t_mysh *sh);
int			my_cd(t_mysh *sh, char **tab);
int			my_unsetenv(t_list *list, char **cmd);
int			my_echo(char **cmd);
int		        my_history(t_list *history);
int	                my_seek_history(t_list *history, char *val);
int			my_setenv(t_list *list, char **cmd);
char			*my_strchr(char *, int);
int			my_puterror(char *, int);
int			chk_bult(t_mysh *sh, char **cmd);

#endif /* !MYSH_H_ */
