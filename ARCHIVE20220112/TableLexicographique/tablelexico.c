#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablelexico.h"


int ligne=0;


/* retourner le hcode                                   */

int hc(char * lexeme){
  int i=0;
  int somme = 0;
  while(lexeme[i]!='\0'){
    somme += lexeme[i];
    i++;
  }
  return somme%32;
}



void initTabLexico(){
  /* intiialiser la tablelexico                           */
  int i;


  for(i=0;i<MAXlexico;i++){
    tablelexico[i].longueur=0;
    tablelexico[i].suivant=-1;
  }
  for(i=0;i<MAXhc;i++){
    tablehc[i]=-1; /* initialiser la table hash-code*/
  }
  ajouter_lexeme("int");ajouter_lexeme("float");ajouter_lexeme("bool");ajouter_lexeme("char");
}

/* insertion d'un lexème donné dans la table lexicographique */
int ajouter_lexeme(char* lexeme){
  int hcode_lexeme;
  hcode_lexeme=hc(lexeme);
  int hc_premier=tablehc[hcode_lexeme];

  if (hc_premier==-1){ /* c'est le premier lexeme correspondant à ce hashcode
  Nous l'ajoutons tout simplement */
    tablehc[hcode_lexeme]=ligne;
    tablelexico[ligne].longueur=strlen(lexeme);
    strcpy(tablelexico[ligne].lexeme,lexeme);
    ligne++;
    return ligne-1;
  }
  else /* il existe des lexeme ayant le même hashcode */
	{
		while(tablelexico[hc_premier].suivant != -1 && strcmp(tablelexico[hc_premier].lexeme,lexeme)!=0) // on test s'il y a un suivant et si la chaine n'est pas deja dans le tableau et si il existe un suivant dans le tableau
	    	{
	      		hc_premier=tablelexico[hc_premier].suivant;
	    	}

		if(strcmp(tablelexico[hc_premier].lexeme,lexeme)!=0) /* le lexeme n'a jamais été ajouté jusque là */
	  	{ /* on l'ajoute */
		  tablelexico[ligne].longueur=strlen(lexeme);
		  strcpy(tablelexico[ligne].lexeme,lexeme);
      tablelexico[hc_premier].suivant = ligne;
		  tablelexico[ligne].suivant=-1;
		  ligne++;
			return ligne-1;
		}
		else
		{
			return hc_premier; /* le lexeme existe dans la table lexico , on ne fait rien ! */
		}
	}


}

/* insertion dans la table hashcode */

int ajouter_hc(int hc, int i){
  int j = 0;
  if(tablehc[hc]== -1){
    tablehc[hc]=i;
    return 1;
  }
  if(tablehc[hc]!= -1){
    i = tablehc[hc];
    while(tablelexico[j].suivant != -1)
      j = tablelexico[j].suivant;
    tablelexico[j].suivant = i;
    return 0;
  }
  return -1;
}

/* récuperer le numero lexicographique d'un lexeme donné */
/* cette fonction nous servira pour la table des déclarations */
int num_lexico(char * lexeme){
  int num_lexico=0;
  int hash_code = hc(lexeme);
  if(hash_code==-1){
    printf("le lexeme n'existe pas");
    return -1;
  }
  num_lexico=tablehc[hash_code];
  /* on va parcourir la table lexicographique pour chercher le lexème */
  if(!strcmp(lexeme , tablelexico[num_lexico].lexeme)) {
            return num_lexico; /* nous l'avons trouvé */
  }
  else { /* pas encore trouvé , parcourons les suivants */
    while(tablelexico[num_lexico].suivant != -1)  {
      num_lexico = tablelexico[num_lexico].suivant;
        if(!strcmp(tablelexico[num_lexico].lexeme , lexeme))
        {   return num_lexico; /* nous l'avons trouvé */ }
    }
    /* si l'on sort du while c'est que nous l'avons pas trouvé */
  }
  return -1; /* le lexème n'existe pas */
}



/* affichage de la tablelexico */

void afficheTableLexico(){
  int i;
  printf("\n****** TABLE LEXICOGRAPHIQUE ******\n");
  printf("\n\n|indice |lgr\t|lexeme\t\t|suivant|\n");
  printf("-----------------------------------------\n");
  for(i=0;i<ligne;i++){
    printf("|%d\t|%d\t|%s\t\t|%d\t|\n",i,tablelexico[i].longueur,tablelexico[i].lexeme, tablelexico[i].suivant);
  }
  printf("-----------------------------------------");
  printf("\n");
}

void afficheTableHash(){
  int i;
  printf("\n****** TABLE HASHCODE ******\n");
  printf("\n\n|indice |hc\t|\n");
  printf("--------|-------\n");
  for(i=0;i<32;i++){
    printf("|%d\t|%d\t|\n",i,tablehc[i]);
  }
  printf("\n");
}



/*int main(){
  initTabLexico();
 ajouter_lexeme("int");
 ajouter_lexeme("int");
 ajouter_lexeme("float");
 ajouter_lexeme("nti");
 ajouter_lexeme("nit");
 ajouter_lexeme("bonjour");
 ajouter_lexeme("yes");
 ajouter_lexeme("yse");
 ajouter_lexeme("fltoa");
ajouter_lexeme("bonjuor");
 printf("hc('bonjour')=%d ",hc("bonjour"));
afficheTableLexico();
afficheTableHash();
 printf("%d ",tablelexico[1].suivant);
  return 0;
}*/
