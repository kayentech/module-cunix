CC         	      := gcc

RM         		  := rm -rf

LDFLAGS   		  += -Llib

CFLAGS    		  += -Iinclude -Wall -Wextra -Werror -g

GAME_S		  	  := $(wildcard src/*.c)

FUNC_S  	      := $(wildcard src/*.c)

UNIT_S            := $(wildcard  src/exec_player.c src/insert_elem.c src/vm_filler.c test/unit/*.c)

GAME_O			  := $(GAME_S:.c=.o)

FUNC_O            := $(FUNC_S:.c=.o)

UNIT_O            := $(UNIT_S:.c=.o)

GAME		      := start_game

FUNC_TEST         := functional_test

UNIT_TEST		  := unit_test

all:        	  $(GAME)

$(GAME):		  $(GAME_O)
						$(CC) $(CFLAGS) -o $(GAME) $(GAME_O) $(LDFLAGS)

$(FUNC_TEST):	  $(FUNC_O)
						$(CC) $(CFLAGS) -o $(FUNC_TEST) $(FUNC_O) $(LDFLAGS)

$(UNIT_TEST):     $(UNIT_O)
						$(CC) $(CFLAGS) -o $(UNIT_TEST) $(UNIT_O) $(LDFLAGS)

clean:
						$(RM) $(UNIT_O) $(FUNC_O) $(GAME_O)

fclean:     	  clean
						$(RM) $(UNIT_TEST) $(FUNC_TEST) $(GAME)

re:         	  fclean all

test_functional:  re $(FUNC_TEST)
	@(./$(FUNC_TEST) -p ./filler1 -m test/functional/resources/start_map.map )

test_unit:		  re $(UNIT_TEST)
	@(./$(UNIT_TEST) -p Player1_1_./filler -p Player2_2_./filler -m test/functional/resources/start_map.map  && echo "Test success" || echo "Test Fails" )

debug:              $(NAME)
					valgrind -v --leak-check=full --track-origins=yes ./$(NAME)
