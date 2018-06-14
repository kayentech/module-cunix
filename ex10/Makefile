
CC					:= gcc

RM					:= rm -rf

LDFLAGS				+= -Llib

CFLAGS				+= -Iinclude -Wall -Wextra -Werror

SRCS				:= $(wildcard src/*.c)

OBJS				:= $(SRCS:.c=.o)

NAME				:= queens_test

all:				$(NAME)

$(NAME):			$(OBJS)
						$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
						$(RM) $(OBJS)

fclean: 			clean
						$(RM) $(NAME)

re: 				fclean all

test:				re
						@(./$(NAME) && echo "Test success" || echo "Test Fails")
