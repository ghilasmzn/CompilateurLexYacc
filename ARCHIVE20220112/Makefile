prog: lex.yy.o y.tab.o tablelexico.o tabledeclaration.o tablerepresentation.o tableregions.o pile.o arbre.o
	gcc lex.yy.o y.tab.o tablelexico.o tabledeclaration.o tablerepresentation.o tableregions.o pile.o arbre.o -o prog

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -o lex.yy.o

y.tab.o: y.tab.c
	gcc -c y.tab.c -o y.tab.o

lex.yy.c: cpyrr.l y.tab.h
	lex cpyrr.l

y.tab.c y.tab.h: cpyrr.y
	yacc -d -v cpyrr.y

tablelexico.o : TableLexicographique/tablelexico.c TableLexicographique/tablelexico.h
	gcc -Wall -c TableLexicographique/tablelexico.c

tabledeclaration.o : TableDeclarations/tabledeclaration.c TableDeclarations/tabledeclaration.h Pile/pile.h  TableRegions/tableregions.h
	gcc -Wall -c TableDeclarations/tabledeclaration.c

tablerepresentation.o : TableRepresentation/tablerepresentation.c TableRepresentation/tablerepresentation.h Pile/pile.h
	gcc -Wall -c TableRepresentation/tablerepresentation.c

tableregions.o : TableRegions/tableregions.c TableRegions/tableregions.h Pile/pile.h Arbres/arbre.h
	gcc -Wall -c TableRegions/tableregions.c

arbre.o : Arbres/arbre.c Arbres/arbre.h
	gcc -Wall -c Arbres/arbre.c

pile.o : Pile/pile.c Pile/pile.h
	gcc -Wall -c Pile/pile.c

clean:
	rm -f *.o *.yy.c *.tab.c *.tab.h *~ prog
