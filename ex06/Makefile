
CC					:= gcc

RM					:= rm -rf

FLAGS       := -Wall -Wextra -Werror

LDFLAGS			+= -Llib

CFLAGS			+= -Iinclude $(FLAGS)

SRCS				:= $(wildcard src/*.c)

OBJS				:= $(SRCS:.c=.o)

NAME				:= printf_test

all:				$(NAME)

$(NAME):		$(OBJS)
						$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
						$(RM) $(OBJS)
						$(RM) output.test

fclean: 		clean
						$(RM) $(NAME)

re: 				fclean all

test:				re
						$(shell ./$(NAME) > output.test)
						@(diff -q output.verif output.test && echo "Test success" || echo "Test Fails")
