%{
  #include <stdio.h>
  #include "Arbres/arbre.h"
  #include "TableLexicographique/tablelexico.h"
  #include "TableDeclarations/tabledeclaration.h"
  #include "TableRepresentation/tablerepresentation.h"
  #include "TableRegions/tableregions.h"
  #include "Pile/pile.h"
  int yylex();
  int yyerror();
  int ligne_erreur;
  int numRegion=1;
  int numchamp=-1;
  int NIS=0;
  int p = 0; /* test paramètre */
  int save_rpz;

  arbre a = NULL;
%}

%union {
    arbre type_arbre;
    char* type_chaine;
    int type_int;
    float type_float;
}

%token PROG DEBUT FIN
%token POINT VIRGULE POINT_VIRGULE DEUX_POINTS CROCHET_OUVRANT CROCHET_FERMANT POINT_POINT PARENTHESE_OUVRANTE PARENTHESE_FERMANTE ACCOLADE_OUVRANTE ACCOLADE_FERMANTE
%token TYPE STRUCT FSTRUCT
%token TABLEAU DE
%token<type_int> IDF ENTIER REEL BOOLEEN CARACTERE CHAINE CSTE_ENTIERE CSTE_CARACTERE
%token VARIABLE
%token<type_float> CSTE_REEL
%token CSTE_BOOLEEN CSTE_CHAINE
%token PROCEDURE FONCTION
%token RETOURNE
%token SI ALORS SINON
%token POUR TANT_QUE FAIRE
%token OPAFF
%token PLUS MOINS DIV MULT AND OR NOT VRAI FAUX
%token SUPERIEUR INFERIEUR SUPERIEUR_OU_EGAL INFERIEUR_OU_EGAL EGAL DIFFERENT
%token LIRE ECRIRE


%type<type_int> nom_type type_simple
%type<type_arbre> corps liste_declarations liste_instructions declaration
%type<type_arbre> declaration_type declaration_variable declaration_procedure declaration_fonction
%type<type_arbre> liste_champs un_champ
%type<type_arbre> dimension liste_dimensions une_dimension
%type<type_arbre> comparaison retourb expression_arith
%type<type_arbre> suite_liste_inst instruction
%type<type_arbre> affectation condition appel tant_que resultat_retourne expression
%type<type_arbre> liste_parametres liste_param un_param
%type<type_arbre> read write liste_formats format suite_ecriture liste_variables variable
%type<type_arbre> liste_arguments liste_args un_arg
%type<type_arbre> expression_booleenne b1 b2 b3 b4
%type<type_arbre> tableau rang e2 e3 e4

%%

 programme             : PROG corps {
                          printf("\nAffichage du corps du programme entier: \n");
                           afficher_arbre($2);
                           inserer_treg(0,$2);
                           printf("\n\n");
                         }
                       ;

 corps                 : liste_declarations liste_instructions{
                          $$ = concat_fils(creer_noeud_vide(A_CORPS), concat_frere(
				concat_fils(creer_noeud_vide(A_LISTE_DECL), $1),concat_fils(creer_noeud_vide(A_LISTE_INSTR),$2)));
                         }
                       | liste_instructions{
                           $$ = concat_fils(creer_noeud_vide(A_CORPS), concat_fils(creer_noeud_vide(A_LISTE_INSTR), $1));
                         }
                       ;


liste_declarations     : declaration POINT_VIRGULE{$$ = $1;}
		    	| liste_declarations declaration POINT_VIRGULE{
		    	     $$ = concat_frere($1, $2);
                          }
                       ;

declaration            : declaration_type      {$$ = $1;}
                       | declaration_variable  {$$ = $1;}
                       | declaration_procedure {$$ = $1;}
                       | declaration_fonction  {$$ = $1;}
                       ;

declaration_type       : TYPE IDF DEUX_POINTS STRUCT liste_champs FSTRUCT{
                           declarer_struct($2,i_rpz); inserer_struct_trep();
                           save_rpz=i_rpz;
                           $$ = concat_fils(creer_noeud(A_DECL_TYPE, $2, -1, -1),
                                            concat_fils(creer_noeud_vide(A_STRUCT), $5));
                         }
                       | TYPE IDF DEUX_POINTS TABLEAU dimension DE nom_type {
                           declarer_tableau($2,i_rpz,$7); inserer_tab_trep($7);
                           $$ = concat_fils(creer_noeud(A_DECL_TYPE, $2, -1, -1),
                                            concat_fils(creer_noeud(A_TAB, -1, $7, -1),$5));
                         }
                       ;

dimension              : CROCHET_OUVRANT liste_dimensions CROCHET_FERMANT{$$ = $2;}
                       ;

liste_dimensions       : une_dimension {$$ = $1;}
                       | liste_dimensions VIRGULE une_dimension {
                           $$ = concat_fils(creer_noeud(A_LISTE, -1, $1->entier + 1, -1), concat_frere($1, $3));
                         }
                       ;

une_dimension         : CSTE_ENTIERE POINT_POINT CSTE_ENTIERE {
                          empile_prep($1); empile_prep($3);
                           $$ = concat_fils(
                                  creer_noeud_vide(A_DIMENSION),
                                  concat_frere(creer_noeud(A_CSTE_ENTIER, -1, $1, -1),creer_noeud(A_CSTE_ENTIER, -1, $3, -1))
);
                        };

liste_instructions     : DEBUT suite_liste_inst FIN {$$ = $2;}
                       | {$$ = creer_arbre_vide();}
                       ;


suite_liste_inst       : instruction POINT_VIRGULE {$$ = $1;}
                       | suite_liste_inst instruction POINT_VIRGULE {
                           $$ = concat_fils(creer_noeud_vide(A_LISTE), concat_frere($2, $1));
                         }
                       ;

instruction            : affectation                {$$ = $1;}
                       | condition                  {$$ = $1;}
                       | tant_que                   {$$ = $1;}
                       | appel                      {$$ = $1;}
                       | RETOURNE resultat_retourne {$$ = concat_fils(creer_noeud_vide(A_RETOURNE),$2);}
                       | read                       {$$ = $1;}
                       | write                      {$$ = $1;}
                       | {$$ = creer_arbre_vide();}
                       ;

liste_champs           : un_champ POINT_VIRGULE {$$ = $1;}
                       | liste_champs un_champ POINT_VIRGULE{
                           $$ = concat_fils(creer_noeud(A_LISTE_CHAMPS, -1, $2->entier + 1, -1), concat_frere($1, $2));
                         }
                       ;

 un_champ              : IDF DEUX_POINTS nom_type{
                           numchamp++;
                           empile_prep($1);
                           empile_prep($3);
                           $$ = creer_noeud(A_IDF, $1, 1, -1);
                         }
                       ;

 nom_type              : type_simple
                       | IDF
                       ;

type_simple            : ENTIER    {$$=0;}
                       | REEL      {$$=1;}
                       | BOOLEEN   {$$=2;}
                       | CARACTERE {$$=3;}
                       | CHAINE CROCHET_OUVRANT CSTE_ENTIERE CROCHET_FERMANT {$$=4;}
                       ;

declaration_variable   : VARIABLE IDF DEUX_POINTS nom_type{
                           if(declarer_var($2,$4,NIS)==-1){
                           printf("ligne de l'erreur : %d \n",ligne_erreur);
                           exit(-1); }
                           $$ = creer_noeud(A_DECLA_VAR, $2, $4, -1);
                         }
                       ;

declaration_procedure  : PROCEDURE {empile_preg(numRegion++); NIS++; } IDF liste_parametres corps{
                           declarer_procedure($3,i_rpz,numRegion);
                           inserer_proc_trep();
                           $$ = concat_fils(creer_noeud(A_DECLA_PROC, $3, -1, -1),concat_frere($4, $5));
                          inserer_treg(NIS,$5);
                          printf("\nAffichage de la région [%d]\n",numRegion-1);

                           NIS--;
                           depile(&p_region);
                         };


declaration_fonction   : FONCTION { empile_preg(numRegion++); NIS++; } IDF  liste_parametres RETOURNE type_simple{
                           declarer_fonction($3,i_rpz,numRegion);
                           inserer_fonc_trep($6);
                         } corps {
                           $$ = concat_fils(creer_noeud(A_DECLA_FONCT, $3, $6, -1), concat_frere($4, $8));
                           inserer_treg(NIS,$8);
                           printf("\nAffichage de la région [%d]\n",numRegion-1);
                           NIS--;
                          depile(&p_region);
                         };

liste_parametres       : PARENTHESE_OUVRANTE PARENTHESE_FERMANTE {
                           $$ = creer_noeud_vide(A_LISTE_PARAM);
                         }
                       | PARENTHESE_OUVRANTE liste_param PARENTHESE_FERMANTE{
                           $$ = concat_fils(creer_noeud_vide(A_LISTE_PARAM), $2);
                         }
                       ;

liste_param            : un_param {$$ = $1;}
                       | liste_param POINT_VIRGULE un_param{
                           $$ = concat_frere($1, $3);
                         }
                       ;

un_param               : IDF DEUX_POINTS type_simple {declarer_param($1,$3,NIS); empile_prep($1); empile_prep($3);
                         $$ = creer_noeud(A_IDF, $1, -1, -1);
                       }
                       ;


resultat_retourne      : {$$ = creer_arbre_vide();}
                       | expression {$$ = $1;}
                       ;

appel                 : IDF liste_arguments{
                           $$ = concat_fils(creer_noeud(A_APPEL, $1, -1, -1), $2);
                         }
                       ;

liste_arguments        : PARENTHESE_OUVRANTE PARENTHESE_FERMANTE {$$ = creer_noeud_vide(A_LISTE_ARGS);}
                       | PARENTHESE_OUVRANTE liste_args PARENTHESE_FERMANTE {$$ = $2;}
                       ;

liste_args             : un_arg {$$ = $1;}
                       | liste_args VIRGULE un_arg {$$ = concat_frere($1, $3);}
                       ;

un_arg                 : expression { $$ = concat_fils(creer_noeud_vide(A_ARG), $1);};;

condition              : SI expression_booleenne
                         ALORS liste_instructions{
		            $$ = concat_fils(
                                   creer_noeud_vide(A_CONDITION),
    			            concat_frere(
                                     concat_fils(creer_noeud_vide(A_SI),$2),
                                     concat_fils(creer_noeud_vide(A_ALORS),$4)
                                   )
                                 );
                           }
                         |
                         SI expression_booleenne
                         ALORS liste_instructions
                         SINON liste_instructions{
		            $$ = concat_fils(
                                   creer_noeud_vide(A_CONDITION),
    			            concat_frere(
    			              concat_fils(creer_noeud_vide(A_SI),$2),
    			              concat_frere(
    		                       concat_fils(creer_noeud_vide(A_ALORS),$4),
    				        concat_fils(creer_noeud_vide(A_SINON),$6)
    			              )
    			            )
		                 );
	                 };

tant_que               : TANT_QUE expression_booleenne FAIRE liste_instructions{
                            $$ = concat_fils(creer_noeud_vide(A_TANT_QUE), concat_frere($2, $4));
                          }
                       ;

affectation            : variable OPAFF expression{
                            $$ = concat_fils(creer_noeud_vide(A_AFFECTATION), concat_frere($1, $3));
                         }
                       ;


variable               : IDF{
                           $$ = creer_noeud(A_IDF, $1, -1, -1);
                         }
                       | IDF tableau{
                           $$ = concat_fils(creer_noeud_vide(A_TAB),concat_frere(creer_noeud(A_IDF, $1, -1, -1), $2));
                         }
                       | IDF POINT variable {
                           $$ = concat_fils(creer_noeud_vide(A_STRUCT), concat_frere(creer_noeud(A_IDF, $1, -1, -1), $3));
                         }
                       | IDF tableau POINT variable{
                           $$ = concat_fils( creer_noeud(A_TAB_STRUCT, $1, -1, -1), $4);
                         }
                       ;


tableau                 : CROCHET_OUVRANT rang CROCHET_FERMANT tableau {
                            $$ = concat_fils(creer_noeud_vide(A_TAB), concat_frere($2, $4));
                          }
                        | CROCHET_OUVRANT rang CROCHET_FERMANT {$$ = $2;}
                        ;

rang                    : expression              {$$ = $1;}
                        | rang VIRGULE expression {$$ = concat_frere($1, $3);}
                        ;


expression              : expression_arith     {$$ = $1;}
                        | expression_booleenne {$$ = $1;}
                        ;

expression_arith        : expression_arith PLUS e2 {
                            $$ = concat_fils(creer_noeud_vide(A_PLUS), concat_frere($1, $3));
                          }
                        | expression_arith MOINS e2{
                            $$ = concat_fils(creer_noeud_vide(A_MOINS), concat_frere($1, $3));
                          }
                        | e2 {$$ = $1;}
			 ;

e2                      : e2 DIV e3{
                            $$ = concat_fils(creer_noeud_vide(A_DIV), concat_frere($1, $3));
                          }
                        | e2 MULT e3{
                            $$ = concat_fils(creer_noeud_vide(A_MULT), concat_frere($1, $3));
                          }
                        | e3 {$$ = $1;}
			 ;

e3                      : PARENTHESE_OUVRANTE expression_arith PARENTHESE_FERMANTE {$$ = $2;}
                        | e4 {$$ = $1;}
                        ;

e4                      : variable       {$$ = $1;}
                        | CSTE_ENTIERE   {$$ = creer_noeud(A_CSTE_ENTIER, -1, $1, -1);}
 			                  | CSTE_REEL      {$$ = creer_noeud(A_CSTE_REEL, -1, -1, $1);}
                        | CSTE_CARACTERE {$$ = creer_noeud(A_CSTE_CARACTERE, -1, $1, -1);}
                        | appel          {$$ = $1;}
                        ;


expression_booleenne    : b1 {$$ = $1;}
                        | PARENTHESE_OUVRANTE b1 PARENTHESE_FERMANTE {$$ = $2;}
                        ;

b1                      : b1 AND b2{
                            $$ = concat_fils(creer_noeud_vide(A_AND), concat_frere($1, $3));
                          }
                        | b2 {$$ = $1;}
                        ;

b2                      : b2 OR b3{
                            $$ = concat_fils(creer_noeud_vide(A_OR), concat_frere($1, $3));
                          }
                        | b3 {$$ = $1;}
                        ;

b3                      : NOT b4{
                            $$ = concat_fils(creer_noeud_vide(A_NOT), $2);
                          }
                        | b4 {$$ = $1;}
                        ;

b4                      : comparaison {$$ = $1;}
                        | retourb     {$$ = $1;}
                        ;

comparaison             : expression_arith SUPERIEUR expression_arith{
                            $$ = concat_fils(creer_noeud_vide(A_SUPERIEUR), concat_frere($1, $3));
                          }
                        | expression_arith INFERIEUR expression_arith{
                            $$ = concat_fils(creer_noeud_vide(A_INFERIEUR), concat_frere($1, $3));
                          }
                        | expression_arith SUPERIEUR_OU_EGAL expression_arith{
                            $$ = concat_fils(creer_noeud_vide(A_SUPERIEUR_OU_EGAL), concat_frere($1, $3));
                          }
                        | expression_arith INFERIEUR_OU_EGAL expression_arith{
                            $$ = concat_fils(creer_noeud_vide(A_INFERIEUR_OU_EGAL), concat_frere($1, $3));
                          }
                        | expression_arith EGAL expression_arith{
                            $$ = concat_fils(creer_noeud_vide(A_EGAL), concat_frere($1, $3));
                          }
                        | expression_arith DIFFERENT expression_arith{
                            $$ = concat_fils(creer_noeud_vide(A_DIFFERENT), concat_frere($1, $3));
                          }
                        ;

retourb                 : VRAI{
                            $$ = creer_noeud(A_VRAI, 1, -1, -1);
                          }
                        | FAUX{
                            $$ = creer_noeud(A_FAUX, 0, -1, -1);
                          }
                        ;

liste_variables         : liste_variables VIRGULE variable{
                            $$ = concat_fils(creer_noeud_vide(A_LISTE), concat_frere($1, $3));
                          }
                        | variable {$$ = $1;}
                        ;


write                   : ECRIRE  PARENTHESE_OUVRANTE liste_formats suite_ecriture PARENTHESE_FERMANTE{
                            $$ = concat_fils(creer_noeud_vide(A_WRITE), concat_frere($3, $4));
                          }
                        ;


liste_formats           : liste_formats format {
                            $$ = concat_fils(creer_noeud_vide(A_LISTE), concat_frere($1, $2));
                          }
                        | format {$$ = $1;}
                        ;

format                  : CHAINE {
                            $$ = creer_noeud(A_FORMAT, $1, -1, -1);
                          }
                        ;

suite_ecriture          :  VIRGULE variable suite_ecriture {
                             $$ = concat_fils(creer_noeud_vide(A_LISTE_ECRITURE), concat_frere($2, $3));
                           }
                        |  VIRGULE variable {$$ = $2;}
                        ;

read                    : LIRE PARENTHESE_OUVRANTE liste_variables PARENTHESE_FERMANTE{
                            $$ = concat_fils(creer_noeud_vide(A_LIRE), $3);
                          }
                        ;



 %%
 int main(void)
{  initTabLexico();
   initTabedeclaration();
   initPile();
   init_trep();
   yyparse();
   afficheTableLexico();
   afficheTableHash();
   affichertabdecl();
   afficher_trep();
   afficher_treg();
   afficher_arbres_regions();
   return 0;
}


int yyerror(){
  printf("Erreur syntaxique en ligne %d \n",ligne_erreur);
  exit(0);
}
