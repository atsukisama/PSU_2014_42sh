/*
** autocomplet.h for autocomplet header in /home/gascon/Epitech/PSU/PSU_2014_42sh
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Thu May 21 15:19:05 2015 Vertigo
** Last update Sun May 24 09:56:00 2015 Vertigo
*/

#ifndef AUTOCOMPLET_H_
# define AUTOCOMPLET_H_

# include <termios.h>
# include <unistd.h>
# include <termcap.h>
# include <curses.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <mysh.h>

# define MKEY_DEL	2117294875
# define MKEY_UP	4283163
# define MKEY_DOWN	4348699
# define MKEY_ESCAPE	27
# define MKEY_LEFT	4479771
# define MKEY_RIGHT	4414235
# define MKEY_SPACE	32
# define MKEY_BACKSPACE	127

# define MKEY_ENTER	13

typedef struct	s_complet	t_complet;

struct		s_complet
{
  char		*name;
  unsigned int	lenght;
  int		is_selected;
  int		is_active;
  int		pos_x;
  int		pos_y;
  t_complet	*prev;
  t_complet	*next;
};

typedef struct		s_select
{
  int			cols;
  int			rows;
  int			tty;
  t_complet		*args;
}			t_select;

t_select		g_select;

int		select_add_before(t_complet *, char *);
t_complet	*select_create();
int		init_autocomplet(char **, t_mysh *, char **, int *);
void		terminal_hook(int);
void		clearscreen(t_mysh *, char *);
void		terminal_reinitialize();
int		my_select(t_complet *, t_mysh *, char **);
int		print_final(t_complet *);
int		terminal_getsize();
int		terminal_checksize();
void		print_list(t_complet *);
void		delete_item(t_complet *, int);
void		set_selected(t_complet *, int);
void		set_active(t_complet *, int);
int		complet_count(t_complet *);
int		putchars(int);
void		key_space(t_complet *, int *);
int		key_delete(t_complet *, int *, t_mysh *, char *);
void		key_arrows(t_complet *, int *, int);
int		get_colspace();
void		complet_delete(t_complet *);
void		free_select();
char		*generate_file_line(char *, char *);

#endif /* !AUTOCOMPLET_H_ */
