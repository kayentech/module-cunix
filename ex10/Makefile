
CC					:= gcc

RM					:= rm -rf

FLAGS       := -Wall -Wextra -Werror

LDFLAGS			+= -Llib

CFLAGS			+= -Iinclude $(FLAGS)

SRCS				:= $(wildcard src/*.c)

OBJS				:= $(SRCS:.c=.o)

NAME				:= queens_test

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
