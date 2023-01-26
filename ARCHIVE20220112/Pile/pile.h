#define TAILLE_PILE 500
#include <stdio.h>
#include <stdlib.h>

typedef struct pile
{
    int t_pile[TAILLE_PILE];
    int nb_elem;
} pile;

pile p_region;
pile p_rep;
int  est_vide(pile* p);

void initPile();

void empile_preg(int e);
void empile_prep(int e);

int depile(pile* p);

int tete_pile(pile* p);
void affiche_pile_region();
void affiche_pile_rep();
