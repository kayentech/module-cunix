
CC					:= gcc

RM					:= rm -rf

LDFLAGS				+= -Llib

CFLAGS				+= -Iinclude -Wall -Wextra -Werror -g

SRCS				:= $(wildcard src/*.c)

OBJS				:= $(SRCS:.c=.o)

TNAME				:= linked_list_test

all:				$(OBJS)

lib: all liblinked_list.a

liblinked_list.a:	src/linked_list.o
								ar rcs $@ $^

$(TNAME):			$(OBJS)
					$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
						$(RM) $(OBJS)

fclean: 			clean
					$(RM) $(TNAME) $(ANAME)

re: 				fclean all

test:				$(TNAME)
					@(./$(TNAME) && echo "Test success" || echo "Test Fails")

debug:				$(TNAME)
					valgrind -v --leak-check=full --track-origins=yes ./$(TNAME)
