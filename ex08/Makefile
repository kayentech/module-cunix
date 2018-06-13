
CC					:= gcc

RM					:= rm -rf

FLAGS       := -Wall -Wextra -Werror

LDFLAGS			+= -Llib

CFLAGS			+= -Iinclude $(FLAGS) -g

SRCS				:= $(wildcard src/*.c)

OBJS				:= $(SRCS:.c=.o)

NAME				:= binary_tree

all:				$(NAME)

$(NAME):		$(OBJS)
						$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
						$(RM) $(OBJS)

fclean: 		clean
						$(RM) $(NAME)

re: 				fclean all

test:				re
						@(./$(NAME) && echo "Test success" || echo "Test Fails")

debug:			re
						valgrind -v --leak-check=full --track-origins=yes ./$(NAME)
