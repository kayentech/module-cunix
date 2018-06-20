
CC					:= gcc

RM					:= rm -rf

LDFLAGS				+= -L../ex07 -llinked_list

CFLAGS				+= -Iinclude -I../ex07/include -Wall -Wextra -Werror -g

SRCS				:= $(wildcard src/*.c)

OBJS				:= $(SRCS:.c=.o)

NAME				:= hash_test

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

debug:      		$(NAME)
	          		valgrind -v --leak-check=full --track-origins=yes ./$(NAME)
						rm $(NAME)
