#include "../Arbres/arbre.h"

#define MAX_REGION 20
typedef struct region {
  int taille;
  int NIS;
  arbre a;
}region;
region tableregions[MAX_REGION];
void init_tabregion();
int taillereg(int region);
void inserer_treg(int NIS, arbre a);
void afficher_treg();
void afficher_arbres_regions();
