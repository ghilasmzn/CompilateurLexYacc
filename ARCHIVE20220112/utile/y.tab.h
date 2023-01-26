/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROG = 258,
    DEBUT = 259,
    FIN = 260,
    POINT = 261,
    VIRGULE = 262,
    POINT_VIRGULE = 263,
    DEUX_POINTS = 264,
    CROCHET_OUVRANT = 265,
    CROCHET_FERMANT = 266,
    POINT_POINT = 267,
    PARENTHESE_OUVRANTE = 268,
    PARENTHESE_FERMANTE = 269,
    ACCOLADE_OUVRANTE = 270,
    ACCOLADE_FERMANTE = 271,
    TYPE = 272,
    STRUCT = 273,
    FSTRUCT = 274,
    TABLEAU = 275,
    DE = 276,
    IDF = 277,
    VARIABLE = 278,
    ENTIER = 279,
    REEL = 280,
    BOOLEEN = 281,
    CARACTERE = 282,
    CHAINE = 283,
    CSTE_ENTIERE = 284,
    CSTE_REEL = 285,
    CSTE_BOOLEEN = 286,
    CSTE_CARACTERE = 287,
    CSTE_CHAINE = 288,
    PROCEDURE = 289,
    FONCTION = 290,
    VIDE = 291,
    RETOURNE = 292,
    SI = 293,
    ALORS = 294,
    SINON = 295,
    POUR = 296,
    TANT_QUE = 297,
    FAIRE = 298,
    OPAFF = 299,
    PLUS = 300,
    MOINS = 301,
    DIV = 302,
    MULT = 303,
    AND = 304,
    OR = 305,
    NOT = 306,
    VRAI = 307,
    FAUX = 308,
    SUPERIEUR = 309,
    INFERIEUR = 310,
    SUPERIEUR_OU_EGAL = 311,
    INFERIEUR_OU_EGAL = 312,
    EGAL = 313,
    DIFFERENT = 314,
    LIRE = 315,
    ECRIRE = 316
  };
#endif
/* Tokens.  */
#define PROG 258
#define DEBUT 259
#define FIN 260
#define POINT 261
#define VIRGULE 262
#define POINT_VIRGULE 263
#define DEUX_POINTS 264
#define CROCHET_OUVRANT 265
#define CROCHET_FERMANT 266
#define POINT_POINT 267
#define PARENTHESE_OUVRANTE 268
#define PARENTHESE_FERMANTE 269
#define ACCOLADE_OUVRANTE 270
#define ACCOLADE_FERMANTE 271
#define TYPE 272
#define STRUCT 273
#define FSTRUCT 274
#define TABLEAU 275
#define DE 276
#define IDF 277
#define VARIABLE 278
#define ENTIER 279
#define REEL 280
#define BOOLEEN 281
#define CARACTERE 282
#define CHAINE 283
#define CSTE_ENTIERE 284
#define CSTE_REEL 285
#define CSTE_BOOLEEN 286
#define CSTE_CARACTERE 287
#define CSTE_CHAINE 288
#define PROCEDURE 289
#define FONCTION 290
#define VIDE 291
#define RETOURNE 292
#define SI 293
#define ALORS 294
#define SINON 295
#define POUR 296
#define TANT_QUE 297
#define FAIRE 298
#define OPAFF 299
#define PLUS 300
#define MOINS 301
#define DIV 302
#define MULT 303
#define AND 304
#define OR 305
#define NOT 306
#define VRAI 307
#define FAUX 308
#define SUPERIEUR 309
#define INFERIEUR 310
#define SUPERIEUR_OU_EGAL 311
#define INFERIEUR_OU_EGAL 312
#define EGAL 313
#define DIFFERENT 314
#define LIRE 315
#define ECRIRE 316

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
