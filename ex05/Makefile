
# vim: noai:ts=4:sw=4

CC					:= gcc

RM					:= rm -rf

LDFLAGS				+= -Llib

CFLAGS				+= -Iinclude -Wall -Wextra -Werror -g

SRCS				:= $(wildcard src/*.c)

OBJS				:= $(SRCS:.c=.o)

NAME				:= puts_test

all:				$(NAME)

$(NAME):			$(OBJS)
						$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
						$(RM) $(OBJS)
						$(RM) output.test

fclean: 			clean
						$(RM) $(NAME)

re: 				fclean all

test:				re
						$(shell ./$(NAME) > output.test)
						@(diff -q output.verif output.test && echo "Test success" || echo "Test Fails")

debug:              $(NAME)
					valgrind -v --leak-check=full --track-origins=yes ./$(NAME)

