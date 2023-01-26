gcc = gcc
optn = -Wall

lexico : tablelexico.o
	$(gcc) $(optn) tablelexico.o -o lexico

tablelexico.o : ./tablelexico.c ./tablelexico.h
	$(gcc) $(optn) -c ./tablelexico.c

clean:
	rm -f *.o *~ lexico
