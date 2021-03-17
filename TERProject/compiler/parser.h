/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ENTIER = 258,
     FLOAT = 259,
     PLUS = 260,
     IMPLIZE = 261,
     ASSIGN = 262,
     PV = 263,
     V = 264,
     PO = 265,
     PF = 266,
     CO = 267,
     CF = 268,
     IDENT = 269,
     VESICULE = 270,
     ESPECE = 271,
     TAILLE = 272,
     VITESSE = 273,
     INIT = 274
   };
#endif
/* Tokens.  */
#define ENTIER 258
#define FLOAT 259
#define PLUS 260
#define IMPLIZE 261
#define ASSIGN 262
#define PV 263
#define V 264
#define PO 265
#define PF 266
#define CO 267
#define CF 268
#define IDENT 269
#define VESICULE 270
#define ESPECE 271
#define TAILLE 272
#define VITESSE 273
#define INIT 274




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 21 "compiler/parser.y"
{
    int ival;
    float fval;
    char *texte;
}
/* Line 1529 of yacc.c.  */
#line 93 "compiler/parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

