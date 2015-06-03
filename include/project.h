/*
** project.h for project in /home/king_j/Git/Epitech/king_j/tmp
**
** Made by king_j
** Login   <king_j@epitech.eu>
**
** Started on  Thu May 14 01:58:41 2015 king_j
** Last update Wed Jun  3 13:41:21 2015 Jimmy KING
*/

#ifndef PROJECT_H_
# define PROJECT_H_

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "list.h"
# include "mysh.h"

char	*xstrstr(char *str, char *keyword);
int	xlen(char *str);
char	*xreplace(char *src, char *key, char *nkey);
int	is_str(char c, char *seps);
int	words_count(char *str, char *seps);
int	words_lenght(char *str, int word, char *seps);
char	*words_get(char *str, int word, char *seps);
int	we_count(char *str);
int	we_lenght(char *str, int id);
char	*we_get(char *str, int id);
void	env_collect(char **env, t_list *list);
char	**env_to_tab(t_list *list);
void	env_show(t_list *list);
char	*env_replacestr(t_list *list, char *content, int *err);
char	*env_getcontent(t_list *list, char *content);
int	env_set(t_list *list, char *key, char *content);
int	env_unset(t_list *list, char *key);
char	*env_replace_tilde(t_list *list, char *str, int *err);
char	*xstrncat(char *, char *, int);
char	*xstrcat(char *, char *);
int	s_str(char, char *);
int	xstrcmp(char *, char *);
int	list_count(t_list *);
void	alias_initialize(t_list *);
char	*alias_replace(t_list *, char *);
void	alias_getcontent(t_list *alias, char *str);

#endif /* !PROJECT_H_ */
