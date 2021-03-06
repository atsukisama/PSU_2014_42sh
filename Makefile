##
## Makefile for 42sh in /home/cano_c/rendu/UNIX/42sh
## 
## Made by Chloe Cano
## Login   <cano_c@epitech.net>
## 
## Started on  Mon May  4 07:03:45 2015 
## Last update Wed Jun  3 11:39:21 2015 
##

NAME	= 42sh

SRCS	= lexer/lexer.c lexer/lexer_common.c lexer/lexer_red.c \
	lexer/lexer_pct.c lexer/lexer_lst.c \
	basics/make_binary.c basics/make_leaf.c basics/cmd_utils.c \
	basics/sh.c basics/basic.c basics/match.c \
	basics/my_strdup2.c basics/doublearray.c \
	parser/parse_cmd.c parser/parse_expr.c \
	parser/parse_instr.c parser/parser.c parser/parse_red.c \
	parser/parser_get_token.c \
	main.c string.c utils.c words.c words_env.c my_putnbr.c \
	termcaps/can.c termcaps/get_line.c termcaps/disp.c termcaps/cursor.c \
	termcaps/char_isprintable.c termcaps/key.c termcaps/clear_screen.c \
	termcaps/arrows.c \
        builtins/environement.c builtins/environement_2.c \
	builtins/my_unsetenv.c \
        builtins/setenv.c builtins/my_cd.c builtins/bult.c builtins/my_echo.c \
        builtins/util_bult.c builtins/my_echo_dol.c builtins/exit.c \
        builtins/historic.c builtins/historic_c.c builtins/alias.c \
	builtins/bult2.c\
	list/list.c list/list_2.c list/list_goto.c \
	exe/exe_cmd.c exe/exe_sep.c exe/exe_pipe.c exe/exe_red.c \
	exe/handle_proc.c exe/exe_red_utils.c exe/glob_arg.c \
	alias/alias.c prompt/prompt.c prompt/git.c \
	autocomplet/autocomplet.c autocomplet/keys.c autocomplet/select.c \
	autocomplet/select_list.c autocomplet/terminal.c \
	autocomplet/get_string.c \
	autocomplet/my_select.c autocomplet/actions.c autocomplet/utils.c \
	autocomplet/init.c autocomplet/free.c

OBJS	= $(addprefix obj/, $(SRCS:.c=.o))

CFLAGS	+= -Wall -Wextra -ggdb

all: obj/ include/my.h $(NAME)

include/my.h: lib/my/include/my.h
	cp $< $@
	cp lib/my/include/my_err.h include

obj/:
	mkdir obj/
	mkdir obj/termcaps/
	mkdir obj/builtins/
	mkdir obj/list/
	mkdir obj/lexer/
	mkdir obj/parser/
	mkdir obj/exe/
	mkdir obj/basics/
	mkdir obj/alias/
	mkdir obj/prompt/
	mkdir obj/autocomplet/

$(NAME): $(OBJS)
	make -C lib/my
	gcc -o $(NAME) $(OBJS) -lncurses -Llib -lmy

obj/%.o: src/%.c
	gcc $(CFLAGS) -c -o $@ $< -I include

clean:
	make -C lib/my clean
	rm -rf obj/
	rm -rf $(OBJS)

fclean: clean
	make -C lib/my fclean
	rm -rf $(NAME)

re: fclean all
	make -C lib/my re
