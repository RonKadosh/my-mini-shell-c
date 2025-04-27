all: myshell
myshell: myshell.o LineParser.o
	gcc -m32 -g -Wall -o myshell myshell.o LineParser.o
LineParser.o: LineParser.c LineParser.h
	gcc -g -Wall -m32 -c LineParser.c -o LineParser.o
myshell.o: myshell.c LineParser.h 
	gcc -g -Wall -m32 -c myshell.c -o myshell.o

.PHONY: clean
clean:
	rm -f *.o myshell