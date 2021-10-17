sijimi: main.o read_line.o split_line.o exec_line.o builtin_cmd.o
	gcc -o sijimi main.o read_line.o split_line.o exec_line.o builtin_cmd.o

main.o: main.c
	gcc -c main.c

read_line.o: read_line.c
	gcc -c read_line.c

split_line.o: split_line.c
	gcc -c split_line.c

exec_line.o: exec_line.c
	gcc -c exec_line.c

builtin_cmd.o: builtin_cmd.c
	gcc -c builtin_cmd.c

run:
	make sijimi
	./sijimi

clean:
	rm *.o