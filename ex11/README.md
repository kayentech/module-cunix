## Mini Shell

### Objectives
* Learn about shell
* Implement a series of basic commands: `echo`, `ls`, `env`, `export`, `exit`

### Actions
* Go to the course directory `cd cep/courses/cunix/ex11/`
* Read all files in include/ and the Makefile before starting anything
* Create a file called src/minishell.c. It should implement the functions above
* Use hash table from previous exercise to save your environment variable
##### Example
-----------------------------
| KEY      | VALUE           |
| ---      | ---             |
| PATH     | /usr/local/bin  |
| LANG     | en US.UTF-8     |
------------------------------
* Use `make debug` to test your program for memory leaks and errors
* Enter `make test` and see if your program works properly
* After building the source, run `./minishell` from the project root to run your program
#### Example of minishell
```
$_>export PWD="/home/user"
$_>echo $PWD
/home/user
$_>env
PATH: /usr/local/bin
PWD: /home/user
$_>ls
include src Makefile README.md
$_>exit
```
### Bonus
* Use `|`, `>`,`<` in your own minishell
* Auto completions

### Docs
* [Unix system calls](https://www.youtube.com/watch?v=xHu7qI1gDPA)
* [Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
* [Implementation of redirection and pipe operators in shell](http://www.sarathlakshman.com/2012/09/24/implementation-overview-of-redirection-and-pipe-operators-in-shell)
