gcc = gcc
optn = -Wall

decl : tabledeclaration.o
	$(gcc) $(optn) tabledeclaration.o -o decl

tablelexico.o : ./tabledeclaration.c ./tabledeclaration.h
	$(gcc) $(optn) -c ./tabledeclaraton.c

clean:
	rm -f *.o *~ decl
