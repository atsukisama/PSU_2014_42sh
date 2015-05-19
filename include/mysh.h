/*
** mysh.h for mysh functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 09:57:43 2015 Vertigo
** Last update Mon May 18 21:37:49 2015 
*/

#ifndef MYSH_H_
# define MYSH_H_

# define HISTORY_FILE	".42sh_history"

# include "list.h"
# include "parser.h"

typedef struct s_mysh	t_mysh;
typedef struct s_proc	t_proc;
typedef struct s_job	t_job;

# define SIG_MAX	40

struct			s_proc
{
  int			pid;
  t_proc		*next;
  t_proc		*prev;
  char			**cmd;
};

struct			s_job
{
  int			status;
  size_t       		n;
  int			pgid;
  t_proc		*proc;
  t_job			*next;
};

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
  int			(*exe_ft[PA_TRM + 1])(t_ast *, t_mysh *, t_job *job);
  int			wait;
  int			is_tty;
  int			pgid;
};

void			set_sig_msg(t_mysh *sh);
void			malloc_error();
int			my_sh(t_mysh *);
int			can_off();
char			*get_line(t_mysh *);
int			my_char_isprintable(char);

/*
** TERMCAPS
*/

int			particular_key(char buf[4], int *, t_mysh *, char **);
void			left_arrow(int *, char **, t_mysh *);
void    		right_arrow(int *, char **, t_mysh *);
void  			up_arrow(int *, char **, t_mysh *);
void    		down_arrow(int *, char **, t_mysh *);
void			display_line(char *, char *, int *, int);
void			clear_screen(t_mysh *);
void			list_goto_root_hist(t_mysh *);
int			save_history(t_list *);
struct termios		*can_on(struct termios **term);
int			can_set(struct termios *term);

/*
** EXECUTION
*/

# define JOB_BG		0
# define JOB_FG		1

int			exe_cmd(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_and(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_or(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_trm(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_bg(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_pipe(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_red(t_ast *ast, t_mysh *sh, t_job *job);

/*
** BUILTINS
*/

int			my_cd(t_mysh *sh, char **tab);
int			my_unsetenv(t_list *list, char **cmd);
int			my_echo(char **cmd, t_mysh *sh);
int		        my_history(t_list *history);
int			chk_bult(t_mysh *sh, char **cmd);
int			my_setenv(t_list *list, char **cmd);
void			my_exit(t_mysh *, int, char *, int *);

int	                my_seek_history(t_list *history, char *val);
char			*my_strchr(char *, int);
int			my_puterror(char *, int);


#endif /* !MYSH_H_ */
