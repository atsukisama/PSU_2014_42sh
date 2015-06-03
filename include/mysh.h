/*
** mysh.h for mysh functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 09:57:43 2015 Vertigo
** Last update Wed Jun  3 13:40:18 2015 Jimmy KING
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

# define HISTORY_FILE	"/tmp/.42sh_history"

typedef struct s_mysh	t_mysh;
typedef struct s_job	t_job;

# define SIG_MAX	40

# define JOB_BG		0
# define JOB_FG		2

struct			s_job
{
  int			pgid;
  int			status;
};

struct			s_mysh
{
  char			sig_msg[SIG_MAX][NAME_MAX + 1];
  int			status;
  char			*oldpwd;
  char			*pwd;
  char			*line;
  int			ret_exit;
  int			pos;
  t_list		*env_list;
  t_list		*history;
  t_list		*alias;
  struct termios	*term;
  struct termios	*tsave;
  int			(*exe_ft[PA_TRM + 1])(t_ast *, t_mysh *, t_job *);
  int			wait;
  char			*prompt;
  int			is_tty;
  int			pgid;
};

t_mysh			*g_mysh;

int			my_sh(t_mysh *);

/*
** command line
*/

char			*get_line(t_mysh *);
char			**glob_arg(char **, char **);
int			my_char_isprintable(char);
int			particular_key(char buf[4], int *, t_mysh *, char **);
void			left_arrow(int *, char **, t_mysh *);
void    		right_arrow(int *, char **, t_mysh *);
void  			up_arrow(int *, char **, t_mysh *);
void    		down_arrow(int *, char **, t_mysh *);
void			display_line(char *tab[2], int , int, t_mysh *);
void			clear_screen(t_mysh *, char *);
void			my_exit(t_mysh *, int, char *, int *);
void			list_goto_root_hist(t_mysh *);
t_list			*send_root_hist(t_mysh *);
int			save_history(t_list *);
int			back_cursor(t_mysh *, int);
int			forward_cursor(t_mysh *, int);
void			clear_plus(char **, t_mysh *, int);
void			display_line_hist(char *tab[2], int *, int, t_mysh *);
void			ctrl_c(int);

/*
** termcaps
*/

struct termios		*can_on(struct termios **term);
int			can_set(struct termios *term);

/*
** Execution
*/

int			exe_cmd(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_and(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_or(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_trm(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_bg(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_pipe(t_ast *ast, t_mysh *sh, t_job *job);
int			exe_red(t_ast *ast, t_mysh *sh, t_job *job);

int			do_red(int red_fd[3], t_ast *ast, t_mysh *sh,
			       t_job *job);
int                     exec_parallel(t_ast *ast, t_mysh *sh, int fd[2],
				      t_job *job);
void                    exec_double_dash_left(t_list *list, int fd[2]);
void                    check_dash_line(char *s, char *file, t_list *list);
int			dash_left_check(int red_fd[3], t_ast *ast, t_mysh *sh,
					t_job *job);

int                     open_failure(char *file, int flags);
void			set_sig_msg(t_mysh *sh);
int			exit_status(int status, t_job *job);
int			wait_proc(t_mysh *sh, int pid, t_job *job);
int			init_proc(t_mysh *sh, t_job *job);
int			proc_status(t_mysh *sh, int pid, t_job *job);
int			control_term(t_mysh *sh);

int			is_exe(char *cmd, char err);
int			get_exe(char **cmd);

/*
** Builtins
*/

char			*my_malloc(int len, t_mysh *sh);
int                     chk_bult(t_mysh *sh, char **cmd, t_job *job);
int                     chk_bult_b(char **cmd);
int                     my_cd(t_mysh *sh, char **tab);
int                     my_unsetenv(t_mysh *sh, char **cmd);
int                     my_echo(char **cmd, t_mysh *sh);
int                     my_history(t_list *history, char **, int, int);
int                     my_seek_history(t_mysh *sh, char *val, int nb);
int                     my_setenv(t_mysh *sh, char **cmd);
char                    *histo_neg(int nb, t_mysh *sh);
char                    *histo_str(t_mysh *sh, char *val);
int                     my_history(t_list *history, char **, int, int);
int                     is_num(char *str);
int                     echo_dol(char *s, int *i, t_mysh *sh, int j);
char                    *get_var_env(t_list *list, char *var);
int                     size_histo(t_list *history);
int                     check_cd_error(char **);
char                    *convert_dol(char *str, t_mysh *sh);
int                     check_dol(char *str);
int                     get_dol_size(char *s, int i);
int                     my_histo_c(t_list *history);
int                     my_exit_n(t_mysh *sh, char **cmd);
int                     exe_histo(char *line, t_mysh *sh);
char			**anlyse_b(char **cmd);
int			my_source(t_mysh *sh, char **cmd);
int			my_alias(t_mysh *sh, char **cmd);
int			my_unalias(t_mysh *sh, char **cmd);

/*
** MISC
*/

char			*my_strchr(char *, int);
int			my_puterror(char *, int);
void			malloc_error();
char			*my_strdup2(char *, char *);
int			match(char *, char *);
char			**add_line(char **, char *);
int			count_dab(char **);
void			free_dab(char **);

/*
** PROMPT
*/

char			*get_prompt(t_mysh *sh);
char			*alias_replace(t_list *alias, char *cmd);
int			git_check();
char                    *get_branch_name(t_mysh *sh, char **branch,
					 int *status);

/*
** ALIAS
*/
void			alias_getcontent(t_list *alias, char *str);
void			alias_openfile(t_list *alias, char *file);
char			*alias_get(t_list *alias, char *key);
char			*alias_replace(t_list *alias, char *cmd);

/*
** Autocompletion
*/

int			autocomplet(char *, t_mysh *, char **, int *);
char			*get_last_word(char *);
char			*get_foldername(char *);
char			*get_file_name(char *);

#endif /* !MYSH_H_ */
