#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tabledeclaration.h"
#include "../TableLexicographique/tablelexico.h"
#include "../Pile/pile.h"
#include "../TableRegions/tableregions.h"

int taille_tdecla=500;


void initTabedeclaration(){
  int i=0;
  for(i=0;i<4;i++){
    tableDeclaration[i].nature = TYPE_BASE;
    tableDeclaration[i].region = 0;
    tableDeclaration[i].description = -1;
    tableDeclaration[i].execution = 1;
  }

  for(i=4;i<MAX_DECLA;i++){
    tableDeclaration[i].nature = -1;
    tableDeclaration[i].suivant = -1;
    tableDeclaration[i].region = -1;
    tableDeclaration[i].description = -1;
    tableDeclaration[i].execution = -1;
  }
}


int inserer_decl(int i_lex, int nature, int region, int description, int execution){
  int i=0;
  // si aucune déclaration n'existe
  if (tableDeclaration[i_lex].nature==-1) {
    tableDeclaration[i_lex].nature = nature;
    tableDeclaration[i_lex].suivant = -1;
    tableDeclaration[i_lex].region = region;
    tableDeclaration[i_lex].description = description;
    tableDeclaration[i_lex].execution = execution;
    return 0;
  }
  // sinon on va dans la zone de débordement
  else{
    if (tableDeclaration[i_lex].region == region && tableDeclaration[i_lex].nature == nature){
      printf("Erreur de déclaration :\n Vous avez voulu déclarer %s:%s \n",tablelexico[i_lex].lexeme,tablelexico[description].lexeme);
      printf("%s est déjà déclaré: \n %s: %s \n",tablelexico[i_lex].lexeme,tablelexico[i_lex].lexeme,tablelexico[tableDeclaration[i_lex].description].lexeme);
      return(-1);
    }
    while(tableDeclaration[i_lex].suivant!=-1){

      i_lex=tableDeclaration[i_lex].suivant;
    }
    tableDeclaration[i_lex].suivant=taille_tdecla;
    i=taille_tdecla;
    tableDeclaration[i].nature = nature;
    tableDeclaration[i].suivant = -1;
    tableDeclaration[i].region = region;
    tableDeclaration[i].description = description;
    tableDeclaration[i].execution = execution;
    taille_tdecla++;
    return 0;
  }
  return 0;
}

int declarer_var(int i_lex,int i_lex_type,int NIS){
  int i;
  i=inserer_decl(i_lex,TYPE_VAR,tete_pile(&p_region),i_lex_type,NIS+tableregions[tete_pile(&p_region)].taille);
  tableregions[tete_pile(&p_region)].taille += tableDeclaration[i_lex_type].execution;
  return i;
}

int declarer_param(int i_lex,int i_lex_type,int NIS){
  int i;
  i=inserer_decl(i_lex,TYPE_PARAM,tete_pile(&p_region),i_lex_type,NIS+tableregions[tete_pile(&p_region)].taille);
  tableregions[tete_pile(&p_region)].taille += tableDeclaration[i_lex_type].execution;
  return i;
}


int declarer_fonction(int i_lex,int i_rep,int numRegion){
  return inserer_decl(i_lex,TYPE_FONCTION,p_region.t_pile[p_region.nb_elem-2],i_rep,numRegion);
}

int declarer_procedure(int i_lex,int i_rep,int numRegion){
    return inserer_decl(i_lex,TYPE_PROCEDURE,p_region.t_pile[p_region.nb_elem-2],i_rep,numRegion);
}

int declarer_tableau(int i_lex,int i_rep,int i_lex_type){
  int i;
  /*Calculons d'abord la taille du tableau qu'on passera en paramètre de notre fonction
  inserer_decl() */
  int tailleTableau=1;
  /*On parcoure la pile de représentation avec un pas de 2 pour récuperer
  les bornes de chaque dimension et les soustraire */
  for(i=0;i<p_rep.nb_elem-1;i++) {
      tailleTableau*= p_rep.t_pile[i+1]-p_rep.t_pile[i];
      i++;
    }
  return inserer_decl(i_lex,TYPE_TABLE,tete_pile(&p_region),i_rep,tailleTableau*tableDeclaration[i_lex_type].execution);
}

int declarer_struct(int i_lex,int i_rep){
  int exec=0;
  int retour;
  /* on calcule le champ exec en parcourant la pile de représentation avec un pas de 2
  pour accéder aux types des champs qui sont aux indices 1 3 5 ... */
  for (int i = 1; i<p_rep.nb_elem; i++){
    exec += tableDeclaration[p_rep.t_pile[i]].execution;
    i++;
  }
  retour= inserer_decl(i_lex,TYPE_STRUCT,tete_pile(&p_region),i_rep,exec);
  return retour;
}


void affichertabdecl(){
  int i;
  printf("\n****** TABLE DES DECLARATIONS ******\n\n");
  printf("|indice\t|nature\t|suivant|région\t|desc\t|exec\t|\n");
  printf("-------------------------------------------------\n");
  for(i=0;i<MAX_DECLA;i++){
    if(tableDeclaration[i].nature!=-1){
      printf("|%d\t", i);
      switch( tableDeclaration[i].nature ){
      case 1 :
        printf("|TYPE_B\t|");
	break;
      case 2 :
        printf("|TYPE_S\t|");
	break;
      case 3 :
        printf("|VAR\t|");
	break;
      case 4 :
        printf("|PARAM\t|");
	break;
      case 5 :
        printf("|TABLE\t|");
	break;
      case 6 :
        printf("|PROC\t|");
	break;
      case 7 :
        printf("|FONC\t|");
	break;
      case 8 :
        printf("|MAIN\t|");
	break;
      default :
        printf("|TYPE INCONNU\t\t|");
      }

      printf("%d\t|%d\t|%d\t|%d\t|\n", tableDeclaration[i].suivant, tableDeclaration[i].region, tableDeclaration[i].description, tableDeclaration[i].execution);
    }
  }
}
/*int main(){
  initTabedeclaration();
  inserer_decl(5, TYPE_VAR, 0, INT, 33);
  inserer_decl(5, TYPE_VAR, 1, INT, 0);
  affichertabdecl();
  return 0;
}*/
