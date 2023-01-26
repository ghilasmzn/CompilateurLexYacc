#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"

arbre creer_arbre_vide(){
  return NULL;
}

int a_est_vide(arbre a){
  if(a == creer_arbre_vide())
    return 1;
  return 0;
}

arbre creer_noeud(int type, int numlexico, int entier, float reel){
  arbre a = (arbre) malloc(sizeof(noeud));
  if(a == NULL){
    fprintf(stderr, "erreur creer_noeud\n");
    exit(EXIT_FAILURE);
  }

  a->type=type;
  a->numlexico=numlexico;
  a->entier=entier;
  a->reel=reel;
  a->fils = creer_arbre_vide();
  a->frere = creer_arbre_vide();
  return a;
}

arbre creer_noeud_vide(int type) {
  return creer_noeud(type, -1, -1, -1);
}

arbre concat_frere(arbre a1, arbre a2){
  if(!a_est_vide(a1->frere)){
    a1->frere = concat_frere(a1->frere,a2);
  }
  else{
    a1->frere=a2;
  }
  return a1;
}


arbre concat_fils(arbre a1, arbre a2){
  if(!a_est_vide(a1)){
    a1->fils = a2;
    return a1;
  }
  else
    return a2;
}

char* afficherNatureArbre(int n) {

  switch(n)
    {
    case A_WRITE :
      return("WRITE");
      break;
    case  A_FORMAT :
      return("FORMAT");
      break;
    case  A_LIRE :
      return("LIRE");
      break;
    case  A_LISTE :
      return("LISTE");
      break;
    case  A_VRAI :
      return("VRAI");
      break;
    case  A_FAUX :
      return("FAUX");
      break;
    case  A_CORPS :
      return("CORPS");
      break;
    case  A_LISTE_DECL :
      return("LISTE_DECL");
      break;
    case  A_LISTE_INSTR :
      return("LISTE_INSTR");
      break;
    case A_DECL_TYPE :
      return("DECL_TYPE");
      break;
    case  A_DECLA_FONCT :
        return("DECL_FONCTION");
        break;
    case  A_DECLA_PROC :
        return("DECL_PROCEDURE");
        break;
    case  A_DECLA_VAR :
        return("DECL_VAR");
        break;
    case  A_STRUCT :
      return("STRUCT");
      break;
    case  A_TAB :
      return("TAB");
      break;
    case  A_DIMENSION :
      return("DIMENSION");
      break;
    case  A_CSTE_ENTIER :
      return("CSTE_ENTIER");
      break;
    case  A_RETOURNE :
      return("RETOURNE");
      break;
  case  A_IDF :
    return("IDF");
    break;
  case  A_LISTE_PARAM :
    return("LISTE_PARAM");
    break;
  case  A_APPEL :
    return("APPEL");
    break;
  case  A_LISTE_ARGS :
    return("LISTE_ARGS");
    break;
  case  A_ARG :
    return("ARG");
    break;
  case  A_CONDITION :
    return("CONDITION");
    break;
  case  A_SI :
    return("SI");
    break;
  case  A_ALORS :
    return("ALORS");
    break;
  case  A_SINON :
    return("SINON");
    break;
  case  A_TANT_QUE :
    return("TANT_QUE");
    break;
  case  A_AFFECTATION :
    return("AFFECTATION");
    break;
  case  A_LISTE_ECRITURE :
    return("LISTE_ECRITURE");
    break;
  case  A_COMPARAISON :
    return("COMPARAISON");
    break;
  case  A_INFERIEUR :
    return("INFERIEUR");
    break;
  case  A_SUPERIEUR_OU_EGAL :
    return("SUPERIEUR_OU_EGAL");
    break;
  case  A_INFERIEUR_OU_EGAL :
    return("INFERIEUR_OU_EGAL");
    break;
  case  A_EGAL :
    return("EGAL");
    break;
  case  A_DIFFERENT :
    return("DIFFERENT");
    break;
  case  A_SUPERIEUR :
    return("SUPPERIEUR");
    break;
  case  A_LISTE_CHAMPS :
    return("LISTE_CHAMPS");
    break;
  case  A_AND :
    return("AND");
    break;
  case  A_OR :
    return("OR");
    break;
  case  A_NOT :
    return("NOT");
    break;
  case  A_PLUS :
    return("PLUS");
    break;
  case  A_MOINS :
    return("MOINS");
    break;
  case  A_DIV :
    return("DIV");
    break;
  case  A_MULT :
    return("MULT");
    break;
  case  A_CSTE_REEL :
    return("CSTE_REEL");
    break;
  case  A_CSTE_CARACTERE :
    return("CSTE_CARACTERE");
    break;
  case  A_PARAM :
    return("PARAM");
    break;
  case  A_TAB_STRUCT :
    return("TAB_STRUCT");
    break;
  default:
    return ("erreur_arbre.c");
    break;
  }


}

void afficher_arbre_bis(arbre a, int espace){
    int i;
    if(a != NULL){
        for(i=0;i<espace;i++){
            printf(" ");
        }

        printf("(%s, %d, %d, %f)\n",afficherNatureArbre(a->type), a->numlexico, a->entier, a->reel);

        if (a->fils != NULL)
        afficher_arbre_bis(a->fils, espace+5 );

        if(a->frere != NULL)
        afficher_arbre_bis(a->frere, espace);
      }
}

void afficher_arbre(arbre a){
  afficher_arbre_bis(a,0);
}



/*int main(int argc, char **argv){
  arbre t, t1, t2;
  t = creer_noeud(A_CONDITION,-1,-1);
  t1 = creer_noeud(A_LISTE,-1,-1);
  t2 = creer_noeud(A_WRITE,-1,-1);
  t = concat_fils(t, t1);
  t = concat_frere(t, t2);
  afficher_arbre(t,10);
  return 0;
}*/
