
CC					:= gcc

RM					:= rm -rf

FLAGS       := -Wall -Wextra -Werror

LDFLAGS			+= -L../ex07 -llinked_list

CFLAGS			+= -Iinclude -I../ex07/include $(FLAGS)

SRCS				:= $(wildcard src/*.c)

OBJS				:= $(SRCS:.c=.o)

NAME				:= hash_test

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

debug:      re
	          valgrind -v --leak-check=full --track-origins=yes ./$(NAME)
						rm $(NAME)
