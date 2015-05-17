/*
** list.h for list in /home/king_j/Git/Epitech/king_j/tmp/includes
**
** Made by Jimmy KING
** Login   <king_j@epitech.net>
**
** Started on  Wed May 13 21:34:19 2015 Jimmy KING
** Last update Sun May 17 17:21:35 2015 Vertigo
*/

#ifndef LIST_H_
# define LIST_H_

typedef struct	s_list
{
  char		*key;
  char		*content;
  struct s_list	*next;
  struct s_list	*prev;
}		t_list;

t_list	*list_create();
t_list	*list_add(t_list *list, char *key, char *content);
void	list_delete_node(t_list *node);
t_list	*get_node_by_key(t_list	*list, char *key);
char	**list_to_tab(t_list *lst);

#endif /* !LIST_H_ */
