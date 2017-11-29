test: shell.o parser.o bash_shell.o exec_commands.o
	gcc -g -o test shell.o parser.o bash_shell.o exec_commands.o

shell.o: shell.c shell.h
	gcc -c shell.c

parser.o: ./parser/parser.c ./parser/parser.h
	gcc -c ./parser/parser.c

bash_shell.o: ./bash_shell/bash_shell.c ./bash_shell/bash_shell.h
	gcc -c ./bash_shell/bash_shell.c

exec_commands.o: ./exec_commands/exec_commands.c ./exec_commands/exec_commands.h
	gcc -c ./exec_commands/exec_commands.c

run: test
	./test

clean:
	rm *.o