gcc = gcc
optn = -Wall

arbre : arbre.o
	$(gcc) $(optn) arbre.o -o arbre

arbre.o : ./arbre.c ./arbre.h
	$(gcc) $(optn) -c ./arbre.c

clean:
	rm -f *.o *~ arbre
