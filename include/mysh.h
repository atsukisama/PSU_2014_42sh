/*
** mysh.h for mysh functions in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Wed May 13 09:57:43 2015 Vertigo
<<<<<<< HEAD
** Last update Fri May 15 11:09:30 2015 
=======
** Last update Fri May 15 07:25:37 2015 
>>>>>>> 8f2a3e921d4ff41392b021e2d9c1b11caaa7225f
*/

#ifndef MYSH_H_
# define MYSH_H_

# define HISTORY_FILE	".42sh_history"

# include "list.h"
# include "parser.h"

typedef struct s_mysh	t_mysh;

struct			s_mysh
{
  int			status;
  t_list		*env_list;
  t_list		*history;
  struct termios	*term;
  struct termios	*tsave;
  int			(*exe_ft[PA_TRM + 1])(t_ast *, t_mysh *);
  int			wait;
};


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
void			save_history(t_list *);
struct termios		*can_on();
int			can_set(struct termios *term);

int			exe_cmd(t_ast *ast, t_mysh *sh);
int			exe_and(t_ast *ast, t_mysh *sh);
int			exe_or(t_ast *ast, t_mysh *sh);
int			exe_trm(t_ast *ast, t_mysh *sh);
int			exe_pipe(t_ast *ast, t_mysh *sh);

#endif /* !MYSH_H_ */
