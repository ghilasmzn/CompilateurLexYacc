#define MAX_DECLA 1000

#define TYPE_BASE 1
#define TYPE_STRUCT 2
#define TYPE_VAR 3
#define TYPE_PARAM 4
#define TYPE_TABLE 5
#define TYPE_PROCEDURE 6
#define TYPE_FONCTION 7
#define TYPE_MAIN 8

#define INT 1
#define FLOAT 2
#define BOOL 3
#define CHAR 4

typedef struct declaration {
    int nature;
    int suivant;
    int region;
    int description;
    int execution;
} declaration;

declaration tableDeclaration[MAX_DECLA];

void initTabedeclaration();

int inserer_decl(int i_lex,int nature,int region, int description, int execution);
int declarer_var(int i_lex,int i_lex_type,int NIS);
int declarer_param(int i_lex,int i_lex_type,int NIS);
int declarer_fonction(int i_lex,int i_rep,int numRegion);
int declarer_procedure(int i_lex,int i_rep,int numRegion);
int declarer_tableau(int i_lex,int i_rep,int i_lex_type);
int declarer_struct(int i_lex,int i_rep);


void affichertabdecl();
