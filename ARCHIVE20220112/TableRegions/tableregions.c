#include <stdio.h>
#include <stdlib.h>
#include "tableregions.h"
#include "../TableDeclarations/tabledeclaration.h"
#include "../Pile/pile.h"
#include "../Arbres/arbre.h"




void init_tabregion(){
  int i = 0;
  for(i=0;i<MAX_REGION;i++){
    tableregions[i].taille = 0;
    tableregions[i].NIS = -1;
    tableregions[i].a = NULL;
  }
}

int taillereg(int region){
  int i;
  int taille = 0;
  for(i=0; i< MAX_DECLA; i++){
    if(tableDeclaration[i].region == region){
      taille += tableDeclaration[tableDeclaration[i].description].execution;
    }
  }
  return taille;
}

void inserer_treg(int NIS, arbre a){
  int numRegion=tete_pile(&p_region); /*pour récuperer le numéro de la region actuelle */

  tableregions[numRegion].NIS = NIS;
  tableregions[numRegion].a = a;
}

void afficher_treg() {
    printf("---------------------\n");
    printf("index\t|taille\t|nis\n");
    printf("---------------------\n");

    for (int i = 0; i < 10; i++) {
        printf("%d\t|%d\t|%d\n", i, tableregions[i].taille, tableregions[i].NIS);
    }
    printf("---------------------\n");
}

void afficher_arbres_regions(){

  for(int i=0;i<10;i++){
    printf("Arbre de la région [ %d ] \n *----------------------* \n",i);
    afficher_arbre(tableregions[i].a);
    printf("\n");
  }
}



/*int main(){
  init_tabregion();
  ajouter_region(1,NULL);
  affiche_treg();
}*/
