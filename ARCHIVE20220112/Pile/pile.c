#include "pile.h"


int  est_vide(pile* p){
  return ((*p).nb_elem==0);
}

void initPile(){
  p_region.nb_elem=0;
  p_rep.nb_elem=0;
}

void empile_preg(int e){
  if (p_region.nb_elem==TAILLE_PILE) { fprintf(stderr,"pile remplie,erreur empiler\n"); }
  else {
    p_region.t_pile[ p_region.nb_elem ]=e;
    p_region.nb_elem++;
  }
}

void empile_prep(int e){
  if (p_rep.nb_elem==TAILLE_PILE) { fprintf(stderr,"pile remplie,erreur empiler\n"); }
  else {
    p_rep.t_pile[ p_rep.nb_elem ]=e;
    p_rep.nb_elem++;
  }
}

int depile(pile* p){
  int depile;
  if ((*p).nb_elem==0) { fprintf(stderr,"pile vide,erreur depiler\n"); return -1; }
  else {
    depile=(*p).t_pile[(*p).nb_elem-1];
    (*p).t_pile[(*p).nb_elem-1]=-1;
    (*p).nb_elem--;
    return depile;
  }
}

int tete_pile(pile* p){
  return (*p).t_pile[(*p).nb_elem-1];
}

void affiche_pile_region(){
  int i;
  printf("Affichage pile_des_regions:\n");
  for(i=0;i<4;i++)
	{
		printf("%d\n",p_region.t_pile[i]);
	}
}

void affiche_pile_rep(){
  int i;
  printf("Affichage pile_des_representations:\n");
  for(i=0;i<10;i++)
	{
		printf(" %d |",p_rep.t_pile[i]);
	}
}

/*int main(int argc, char *argv[])
{
  initPile(&p_region);
  empile(&p_region,2);
  printf("J'empile le 2. nb elements pile: %d \n",p_region.nb_elem);
  printf("Je dépile. l'element dépilé = %d\n",depile(&p_region));
  printf("nb elements pile maintenant: %d\n",p_region.nb_elem);
  return 0;
}
*/
