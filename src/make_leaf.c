/*
** make_leaf.c for 42sh in /home/cano_c/rendu/UNIX/42sh/src
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Tue May  5 11:49:05 2015 
** Last update Tue May  5 11:49:11 2015 
*/
#include <parser.h>

static char	**make_cmd_argv(t_lex **lex, size_t argc)
{
  char		**argv;
  size_t	idx;

  idx = 0;
  if (!(argv = my_memalloc(sizeof(*argv) * (argc + 1))))
    return (NULL);
  while (idx < argc)
    {
      if (!(argv[idx++] = my_memalloc(sizeof(argv[idx]) * ((*lex)->len + 1))))
	return (NULL);
      my_memcpy(argv[idx - 1], (*lex)->s, (*lex)->len);
      *lex = (*lex)->next;
    }
  argv[argc] = NULL;
  return (argv);
}

t_ast		*make_cmd(t_lex **lex)
{
  t_ast		*node;
  size_t	argc;
  t_lex		*tmp;

  tmp = *lex;
  argc = 0;
  if (DEBUG_AST)
    my_putstr("ast -> make CMD\n");
  while (tmp->type == LX_IDT)
    {
      tmp = tmp->next;
      ++argc;
    }
  if (!(node = my_memalloc(sizeof(*node))))
    return (NULL);
  node->type = PA_CMD;
  if (!(node->content.cmd = make_cmd_argv(lex, argc)))
    return (NULL);
  return (node);
}

t_ast		*make_file(t_lex **lex)
{
  t_ast		*leaf;

  if (DEBUG_AST)
    my_putstr("ast -> make FILE\n");
  if (!(leaf = my_memalloc(sizeof(*leaf))))
    return (NULL);
  leaf->type = PA_FILE;
  if (!(leaf->content.file = my_memalloc(sizeof(*leaf->content.file)
					 * ((*lex)->len + 1))))
    return (NULL);
  my_memcpy(leaf->content.file, (*lex)->s, (*lex)->len);
  *(leaf->content.file + (*lex)->len) = 0;
  return (leaf);
}

t_ast		*make_leaf(t_ast **ast, t_lex **lex, int type)
{
  t_ast		*leaf;

  if (DEBUG_AST)
    my_putstr("ast -> make LEAF\n");
  if (type == PA_CMD && (*lex)->type == LX_IDT)
    {
      if (!(leaf = make_cmd(lex)))
	return (NULL);
      return (leaf);
    }
  else if (type == PA_FILE && (*lex)->type == LX_IDT)
    {
      if (!(leaf = make_file(lex)))
	return (NULL);
      return (leaf);
    }
  return (parse_err(ast, lex));
}
