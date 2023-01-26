%{
#include "Arbres/arbre.h"
  #include "TableLexicographique/tablelexico.h"
  #include "y.tab.h"

  void yyerror();
  int ligne_erreur=1;
%}

%%
[ \t] ;
"//".*;
\+ {return (PLUS);}
\- {return (MOINS);}
\* {return (MULT);}
\/ {return (DIV);}
\( {return (PARENTHESE_OUVRANTE);}
\) {return (PARENTHESE_FERMANTE);}
:= {return (OPAFF);}
\{ {return (ACCOLADE_OUVRANTE);}
\} {return (ACCOLADE_FERMANTE);}
\[ {return (CROCHET_OUVRANT);}
\] {return (CROCHET_FERMANT);}
\: {return (DEUX_POINTS);}
\.\. {return (POINT_POINT);}
\, {return (VIRGULE);}
\; {return (POINT_VIRGULE);}
\. {return (POINT);}


(prog|programme) {return PROG;}
begin {return (DEBUT);}
end {return (FIN);}
var	 {return(VARIABLE);}
type {return (TYPE);}
int { return (ENTIER);}
float { return (REEL);}
bool { return (BOOLEEN);}
string { return (CHAINE);}
char { return(CARACTERE);}
struct {return (STRUCT);}
struct_end {return(FSTRUCT);}
array {return(TABLEAU);}
of {return(DE);}

read {return(LIRE);}
write {return(ECRIRE);}
if {return(SI);}
then {return(ALORS);}
do {return(FAIRE);}
else {return(SINON);}
for {return(POUR);}
while {return(TANT_QUE);}
return {return(RETOURNE);}
false {return(FAUX);}
true {return(VRAI);}
procedure {return(PROCEDURE);}
function {return(FONCTION);}

\<				{return(INFERIEUR);}
\>				{return(SUPERIEUR);}
==	      {return(EGAL);}
\<=				{return(INFERIEUR_OU_EGAL);}
\>=				{return(SUPERIEUR_OU_EGAL);}
!=				{return(DIFFERENT);}
\!				{return(NOT);}
\&\&				{return(AND);}
\|\|				{return(OR);}


[a-zA-Z][a-zA-Z0-9_]*		{yylval.type_int = ajouter_lexeme(yytext);
  return IDF;}
(0|[1-9][0-9]*) {yylval.type_int=atoi(yytext); return (CSTE_ENTIERE); }
((0|[1-9][0-9]*)\.[0-9]*) {yylval.type_float=atof(yytext); return (CSTE_REEL);}
\'[a-zA-Z]\' {return (CSTE_CARACTERE);}
\"[^\"]+\"			{return(CSTE_CHAINE);}
\n {ligne_erreur++;}

%%
int yywrap(void) {
   return 1;
}
