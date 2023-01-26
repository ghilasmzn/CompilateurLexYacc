gcc = gcc
optn = -Wall

rpz : tablerepresentation.o
	$(gcc) $(optn) tablerepresentation.o -o rpz

tablelexico.o : ./tablerepresentation.c ./tablerepresentation.h
	$(gcc) $(optn) -c ./tablerepresentation.c

clean:
	rm -f *.o *~ rpz

