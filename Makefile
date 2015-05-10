##
## Makefile for 42sh in /home/cano_c/rendu/UNIX/42sh
## 
## Made by Chloe Cano
## Login   <cano_c@epitech.net>
## 
## Started on  Mon May  4 07:03:45 2015 
## Last update Sun May 10 02:22:30 2015 
##
NAME	= lexer
SRCS	= lexer.c lexer_common.c lexer_red.c lexer_pct.c lexer_lst.c \
	make_binary.c make_leaf.c parse_cmd.c parse_expr.c \
	parse_instr.c parser.c parse_red.c parser_get_token.c
OBJS	= $(addprefix obj/, $(notdir $(SRCS:.c=.o)))

CFLAGS	+= -Wall -Wextra

all: obj/ include/my.h $(NAME)

include/my.h: lib/my/include/my.h
	cp $< $@
	cp lib/my/include/my_err.h include

obj/:
	mkdir obj/

$(NAME): $(OBJS)
	make -C lib/my
	gcc -o $(NAME) $(OBJS) -Llib -lmy

obj/%.o: src/%.c
	gcc $(CFLAGS) -c -o $@ $< -I include

clean:
	make -C lib/my clean
	rm -rf $(OBJS)

fclean: clean
	make -C lib/my fclean
	rm -rf $(NAME)

re: fclean all
	make -C lib/my re
