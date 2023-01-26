#ifndef ARBRE_H
#define ARBRE_H
#define A_WRITE 1
#define A_FORMAT 2
#define A_LIRE 3
#define A_LISTE 4
#define A_VRAI 5
#define A_FAUX 6
#define A_CORPS 7
#define A_LISTE_DECL 8
#define A_LISTE_INSTR 9
#define A_DECL_TYPE 10
#define A_STRUCT 11
#define A_TAB 12
#define A_DIMENSION 13
#define A_CSTE_ENTIER 14
#define A_RETOURNE 15
#define A_IDF 16
#define A_LISTE_PARAM 17
#define A_APPEL 18
#define A_LISTE_ARGS 19
#define A_ARG 20
#define A_CONDITION 21
#define A_SI 22
#define A_ALORS 23
#define A_SINON 24
#define A_TANT_QUE 25
#define A_AFFECTATION 26
#define A_LISTE_ECRITURE 27
#define A_COMPARAISON 28
#define A_INFERIEUR 29
#define A_SUPERIEUR_OU_EGAL 30
#define A_INFERIEUR_OU_EGAL 31
#define A_EGAL 32
#define A_DIFFERENT 33
#define A_SUPERIEUR 34
#define A_LISTE_CHAMPS 35
#define A_AND 36
#define A_OR 37
#define A_NOT 38
#define A_PLUS 39
#define A_MOINS 40
#define A_DIV 41
#define A_MULT 42
#define A_CSTE_REEL 43
#define A_CSTE_CARACTERE 44
#define A_PARAM 45
#define A_TAB_STRUCT 46
#define A_DECLA_VAR 47
#define A_DECLA_PROC 48
#define A_DECLA_FONCT 49

typedef struct noeud{
        int type;
        int numlexico;
        int entier;
        float reel;
	struct noeud *fils;
	struct noeud *frere;
} noeud;

typedef struct noeud * arbre;


arbre creer_arbre_vide();
int a_est_vide(arbre a);
arbre creer_noeud(int type, int numlexico,int entier, float reel);
arbre creer_noeud_vide(int type);
arbre concat_frere(arbre a1, arbre a2);
arbre concat_fils(arbre a1, arbre a2);
char* afficherNatureArbre(int n);
void afficher_arbre_bis(arbre a, int espace);
void afficher_arbre(arbre a);

#endif
