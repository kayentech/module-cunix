
CC					:= gcc

RM					:= rm -rf

CFLAGS				+= -Iinclude -Wall -Wextra -Werror -g

SRCS				:= $(wildcard src/*.c)

SRCS_TEST			:= $(wildcard src/input.c src/parse.c src/game_logic.c test/main.c)

SRCS_STR			:= $(wildcard src/my_string.c test/main_str.c)

OBJS				:= $(SRCS:.c=.o)

OBJS_TEST   		:= $(SRCS_TEST:.c=.o)

OBJS_STR    		:= $(SRCS_STR:.c=.o)

NAME				:= filler

NAME_TEST   		:= filler_test

NAME_STR    		:= string_test

all:				$(NAME)

$(NAME):			$(OBJS)
						$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) -lm

$(NAME_TEST):  		$(OBJS_TEST)
						$(CC) $(CFLAGS) -o $(NAME_TEST) $(OBJS_TEST) $(LDFLAGS) -lm

$(NAME_STR):  		$(OBJS_STR)
						$(CC) $(CFLAGS) -o $(NAME_STR) $(OBJS_STR) $(LDFLAGS) -lm

clean:
						$(RM) $(OBJS) $(OBJS_TEST)

fclean: 			clean
						$(RM) $(NAME_TEST)

re: 				fclean $(NAME_TEST)

re_str:    			fclean $(NAME_STR)

test:				re
						@(./$(NAME_TEST) && echo "Test success" || echo "Test Fails")

test_valgrind:		re
						@(valgrind ./$(NAME_TEST) && echo "Test success" || echo "Test Fails")

test_string:    	re_str
								@(./$(NAME_STR) && echo "Test success" || echo "Test Fails")

test_string_valgrind:  re_str
												@(valgrind --track-origins=yes ./$(NAME_STR) && echo "Test success" || echo "Test Fails")

debug:              $(NAME)
					valgrind -v --leak-check=full --track-origins=yes ./$(NAME)
