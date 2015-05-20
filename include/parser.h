/*
** parser.h for 42sh in /home/cano_c/rendu/UNIX/42sh
** 
** Made by Chloe Cano
** Login   <cano_c@epitech.net>
** 
** Started on  Tue May  5 10:13:00 2015
** Last update Wed May 20 18:38:16 2015 
*/

#ifndef PARSER_H_
# define PARSER_H_

# include <lexer.h>

# define DEBUG_AST	0
# define DEBUG_PARSER	0

typedef struct s_ast	t_ast;
typedef union u_parse	t_parse;

typedef enum	e_parse
  {
    PA_LEAF,
    PA_CMD,
    PA_FILE,
    PA_NODE,
    PA_RED,
    PA_AND,
    PA_OR,
    PA_PIPE,
    PA_TRM
  } t_e_parse;

union		u_parse
{
  char		**cmd;
  char		*file;
  char		red[3];
};

struct		s_ast
{
  int		type;
  t_parse	content;
  t_ast		*right;
  t_ast		*left;
};

t_lex		*lexer_next_token(t_lex *lex);
void		lexer_rm_token(t_lex *lex, t_lex **lexems);

t_ast		*parse_init(t_lex *lex);
t_ast		*parse_expr(t_ast **ast, t_lex **lex);
t_ast		*parse_instr(t_ast **ast, t_lex **lex);
t_ast		*parse_pipeline(t_ast **ast, t_lex **lex);
t_ast		*parse_red(t_ast **ast, t_lex **lex);
t_ast		*parse_cmd(t_ast **ast, t_lex **lex);
t_ast		*parse_end(t_ast **ast, t_lex **lex);
t_ast		*parse_err(t_ast **ast, t_lex **lex);

t_ast		*make_binary(t_ast **ast, t_lex **lexem);
t_ast		*make_red(t_ast **ast, t_lex *lex);
t_ast		*make_leaf(t_ast **ast, t_lex **lexem, int type);
t_ast		*make_cmd(t_lex **lex);

#endif
