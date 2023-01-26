#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tablerepresentation.h"
#include "../TableDeclarations/tabledeclaration.h"
#include "../Pile/pile.h"



int init_trep(){
  i_rpz = 0;
  int i;
  for(i=0;i<MAX_RPZ;i++){
    tableRepresentation[i]=-1;
  }
  return 1;
}

int inserer_fonc_trep(int valeur){
  int i;
  tableRepresentation[i_rpz]=valeur; i_rpz++;
  tableRepresentation[i_rpz]=p_rep.nb_elem/2; i_rpz++;
  for(i=0;i<p_rep.nb_elem;i++){
    tableRepresentation[i_rpz]=p_rep.t_pile[i]; i_rpz++;
  }
  p_rep.nb_elem=0;
  return i_rpz;
}

int inserer_proc_trep(){
  int i;
  tableRepresentation[i_rpz]=p_rep.nb_elem/2; i_rpz++;
  for(i=0;i<p_rep.nb_elem;i++){
    tableRepresentation[i_rpz]=p_rep.t_pile[i]; i_rpz++;
  }
  p_rep.nb_elem=0;
  return i_rpz;
}

int inserer_tab_trep(int i_lex_type){
  int i;
  tableRepresentation[i_rpz]=i_lex_type; i_rpz++;
  tableRepresentation[i_rpz]=p_rep.nb_elem/2; i_rpz++;
  for(i=0;i<p_rep.nb_elem;i++){
    tableRepresentation[i_rpz]=p_rep.t_pile[i]; i_rpz++;
  }
  p_rep.nb_elem=0;
  return i_rpz;
}

int inserer_struct_trep(){
  int i=0;
  int j=0;
  int numchamp=-1;
  tableRepresentation[i_rpz]=p_rep.nb_elem/2; i_rpz++;
  //empile_prep( tableRepresentation[i_rpz-3]+tableDeclaration[$3].execution)
  for(j=0;j<p_rep.nb_elem/2;j++){
    tableRepresentation[i_rpz]=p_rep.t_pile[i]; i++; i_rpz++;
    tableRepresentation[i_rpz]=p_rep.t_pile[i]; i++; i_rpz++;
    numchamp++;
    if(numchamp==0){
    tableRepresentation[i_rpz]=0; i_rpz++;
    }
    else{
    tableRepresentation[i_rpz]=tableRepresentation[i_rpz-3]+tableDeclaration[tableRepresentation[i_rpz-4]].execution; i_rpz++;
    
    }
  }
  /*for(i=0;i<p_rep.nb_elem;i++){
    tableRepresentation[i_rpz]=p_rep.t_pile[i]; i_rpz++;
  }*/
  p_rep.nb_elem=0;
  return i_rpz;
}

void afficher_trep(){
  int i;
  printf("\n***********TABLE DES REPRESENTATIONS***********\n");
  for(i=0;i<i_rpz;i++){
    printf("| %d ",tableRepresentation[i]);
  }
  printf("|\n***********************************************\n");
}

/*int main(){
  init_trep();
  inserer_trep(2);
  afficher_trep();

}
*/
