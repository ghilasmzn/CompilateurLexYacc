#define MAX 31
#define MAXlexico 500
#define MAXhc 100

typedef struct tablex{
  int longueur;
  char lexeme[MAX];
  int suivant;
}tablex;

tablex tablelexico[MAXlexico];

int tablehc[MAXhc];

/***********FONCTIONS*************/

int hc(char * lexeme);/* Conversion hcode */
void initTabLexico(); /* Initialise la tablexi et tabhcode */
int ajouter_lexeme(char *lexeme); /* retourne 0 si ajout, -1 sinon */
int ajouter_hc(int hc, int i); /* retourne 0 si ajout, -1 sinon */
int num_lexico(char * lexeme);
void afficheTableLexico(); /* affichage de la tablelexico */
void afficheTableHash(); /* affichage de la table HashCode */
