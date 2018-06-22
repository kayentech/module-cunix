#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../include/hash.h"

#define BUFSIZE 512

char *keys_arr[10];
int poss = 0;
hashtable_t *tbl;

char *builtin_str[] = {
  "exit",
  "echo",
  "export",
  "env"
};

int myexit(char **args){
  return 0;
}

int myenv (char ** args){
  for(int i = 0; i < poss; i++)
    printf("%s: %s\n", keys_arr[i], hash_get(tbl, keys_arr[i]));
  return 1;
}

char *no_dollar(char * str){
	for (int i = 0; i <= strlen(str); i++)
		str[i] = str[i + 1];
	return str;
}

int myecho(char ** args){
	int i = 1;
	while (1){
		if (args[i] == NULL)
			break;
		if (args[i][0] == '$')
			printf("%s ", hash_get(tbl, no_dollar(args[i])));
		else printf("%s ", args[i]);
		i++;
	}
	printf("\n");
}

int check_arr(char *val){
  for(int i = 0; i < poss; i++)
    if(strcmp(keys_arr[i], val) == 0)
      return 0;
  return 1;
}

int myexport (char ** args){
  int i = 1;
  while(1){
    if(args[i] == NULL)
      break;
    char *token;
    char s[2] = "=";
    token = strtok(args[i], s);
    if(check_arr(token)){
      keys_arr[poss] = (char *) malloc(sizeof(char) * strlen(token));
      strcpy(keys_arr[poss], token);
      poss++;
    }
    if (tbl == NULL)
	    tbl = hash_create(10);
    char *tok1 = token;
    token = strtok(NULL, s);
    hash_set(tbl, tok1, token);
    i++;
  }
  return 1;
}

int (*builtin_func[]) (char **) = {
  &myexit,
  &myecho,
  &myexport,
  &myenv
};

int num_builtins(){
  return sizeof(builtin_str) / sizeof(char *);
}

char *read_line(){
  int bufsize = BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;
  if (!buffer){
    fprintf(stderr, "minishell: allocation error\n");
    exit(EXIT_FAILURE);
  }
  while (1){
    c = getchar();
    if (c == EOF || c == '\n'){
      buffer[position] = '\0';
      return buffer;
    }
    else
     buffer[position] = c;
    position++;
    if (position >= bufsize){
      bufsize += BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer){
        fprintf(stderr, "minishell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define TOK_BUFSIZE 32
#define TOK_DELIM " \t\r\n\a"

char **parse(char *line){
  int bufsize = TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;
  if (!tokens){
    fprintf(stderr, "minishell: allocation error\n");
    exit(EXIT_FAILURE);
  }
  token = strtok(line, TOK_DELIM);
  while (token != NULL){
    tokens[position] = token;
    position++;
    if (position >= bufsize){
      bufsize += TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens){
        fprintf(stderr, "minishell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

int launch(char **args){
  pid_t pid, wpid;
  int status;
  pid = fork();
  if (pid == 0){
    if (execvp(args[0], args) == -1)
      perror("error");
        exit(EXIT_FAILURE);
  } else if (pid < 0)
        perror("error");
   else {
        do
      wpid = waitpid(pid, &status, WUNTRACED);
     while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}

int execute(char **args){
  int i;
  if (args[0] == NULL)
    return 1;
  for (i = 0; i < num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0)
      return (*builtin_func[i])(args);
      }
  return launch(args);
}

void signalHandler(int sign){
  if (sign == SIGINT){
     puts("");
     write(1, "$_>", 3);
     signal(SIGINT, signalHandler);
   }
}

void rpe_loop(){
  char *line;
  char **args;
  int status;

  do {
    printf("$_>");
    signal(SIGINT, signalHandler);
    line = read_line();
    args = parse(line);
    status = execute(args);

    free(line);
    free(args);
  } while (status);
}

int main(){
  rpe_loop();
  return 0;
}
