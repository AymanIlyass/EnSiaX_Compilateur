#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define SIZE 10007
// typedef enum
// {
//     ARRAY,
//     STRING,
//     RECORD
// } np_type;
typedef enum
{
    ERROR,
    NUM,
    ID,
    ID_FUNCTION,
    SPECIAL,
    STRING,
    CHAR

} enus;
typedef enum
{
    // SPECIAL
    CRO_TOKEN,   // [
    CRF_TOKEN,   // ]
    ACO_TOKEN,   // {
    ACF_TOKEN,   // }
    COLON_TOKEN, // :
    NOT_TOKEN,   // !
    AFF_TOKEN,   // =
    MOD_TOKEN,   // %
    PV_TOKEN,    // ;
    PLUS_TOKEN,  // +
    MOINS_TOKEN, // -
    MULT_TOKEN,  // *
    DIV_TOKEN,   // /
    VIR_TOKEN,   // ,
    EG_TOKEN,    // ==
    INF_TOKEN,   // <
    INFEG_TOKEN, // <=
    SUP_TOKEN,   // >
    SUPEG_TOKEN, // >=
    DIFF_TOKEN,  // !=
    PO_TOKEN,    // (
    PF_TOKEN,    // )
    // KEYWORD
    NUMCONST_TOKEN,    // numconst
    CHARCONST_TOKEN,   // charconstant
    STRINGCONST_TOKEN, // stringconstant
    TRUE_TOKEN,        // true
    FALSE_TOKEN,       // false
    IDFCT_TOKEN,       // idfunc
    INT_TOKEN,         // int
    BOOL_TOKEN,        // bool
    CHAR_TOKEN,        // char
    LET_TOKEN,         // let
    ELSE_TOKEN,        // else
    FOR_TOKEN,         // for
    TO_TOKEN,          // to
    BY_TOKEN,          // by
    RETURN_TOKEN,      // return
    BREAK_TOKEN,       // break
    CIN_TOKEN,         // cin
    COUT_TOKEN,        // cout
    OR_TOKEN,          // or
    AND_TOKEN,         // and
    IF_TOKEN,          // if
    THEN_TOKEN,        // then
    WHILE_TOKEN,       // while
    DO_TOKEN,          // do
    ID_TOKEN,          // id
    FIN_TOKEN,
    ERREUR_TOKEN,
    NULL_TOKEN
} Codes_LEX;
typedef enum
{
    // SPECIAL
    CRO_TOKEN_ERREUR,   // [
    CRF_TOKEN_ERREUR,   // ]
    ACO_TOKEN_ERREUR,   // {
    ACF_TOKEN_ERREUR,   // }
    COLON_TOKEN_ERREUR, // :
    NOT_TOKEN_ERREUR,   // !
    AFF_TOKEN_ERREUR,   // =
    MOD_TOKEN_ERREUR,   // %
    PV_TOKEN_ERREUR,    // ;
    PLUS_TOKEN_ERREUR,  // +
    MOINS_TOKEN_ERREUR, // -
    MULT_TOKEN_ERREUR,  // *
    DIV_TOKEN_ERREUR,   // /
    VIR_TOKEN_ERREUR,   // ,
    EG_TOKEN_ERREUR,    // ==
    INF_TOKEN_ERREUR,   // <
    INFEG_TOKEN_ERREUR, // <=
    SUP_TOKEN_ERREUR,   // >
    SUPEG_TOKEN_ERREUR, // >=
    DIFF_TOKEN_ERREUR,  // !=
    PO_TOKEN_ERREUR,    // (
    PF_TOKEN_ERREUR,    // )
    // KEYWORD
    NUMCONST_TOKEN_ERREUR,    // numconst
    CHARCONST_TOKEN_ERREUR,   // charconstant
    STRINGCONST_TOKEN_ERREUR, // stringconstant
    TRUE_TOKEN_ERREUR,        // true
    FALSE_TOKEN_ERREUR,       // false
    IDFCT_TOKEN_ERREUR,       // idfunc
    INT_TOKEN_ERREUR,         // int
    BOOL_TOKEN_ERREUR,        // bool
    CHAR_TOKEN_ERREUR,        // char
    LET_TOKEN_ERREUR,         // let
    ELSE_TOKEN_ERREUR,        // else
    FOR_TOKEN_ERREUR,         // for
    TO_TOKEN_ERREUR,          // to
    BY_TOKEN_ERREUR,          // by
    RETURN_TOKEN_ERREUR,      // return
    BREAK_TOKEN_ERREUR,       // break
    CIN_TOKEN_ERREUR,         // cin (read)
    COUT_TOKEN_ERREUR,        // cout (write)
    OR_TOKEN_ERREUR,          // or
    AND_TOKEN_ERREUR,         // and
    IF_TOKEN_ERREUR,          // if
    THEN_TOKEN_ERREUR,        // then
    WHILE_TOKEN_ERREUR,       // while
    DO_TOKEN_ERREUR,          // do
    ID_TOKEN_ERREUR,          // id
} Codes_LEX_Erreurs;
typedef struct
{
    Codes_LEX token;
    char identif[31];
    char value[31];
    int ligne;
    int colonne;
    int p_type;
    int np_type;
    int size;
    char r_value[100];
    bool isconst;
} Maptoken;

//--------
typedef struct
{
    Codes_LEX token;
    char message_erreur[100];

} Maptoken_erreur;

//-----
typedef enum
{
    CAR_INC,
    FICH_VID,
    ID_LONG,
    NUM_LONG,
    MORE_THEN_CHAR
} Erreurlyx;
//------
typedef struct
{
    Erreurlyx code_err;
    char message_erreur[50];
    int ligneErreur;
    int colonneErreur;
} Erreurs;
//-------------------------------------
Erreurs mes_err[5] = {{CAR_INC, "caract?re inconnu"},
                      {FICH_VID, "fichier vide"},
                      {ID_LONG, "l'identifiant est long"},
                      {NUM_LONG, "le nombre est grand"},
                      {MORE_THEN_CHAR, "le type char ne peut avoir plus d'un caract?re"}};
//--------
Erreurs Error_table[SIZE];
int curseur = 0;
//------
Maptoken specials[23] = {
    {CRO_TOKEN, "CRO_TOKEN"},
    {CRF_TOKEN, "CRF_TOKEN"},
    {ACO_TOKEN, "ACO_TOKEN"},
    {ACF_TOKEN, "ACF_TOKEN"},
    {COLON_TOKEN, "COLON_TOKEN"},
    {NOT_TOKEN, "NOT_TOKEN"},
    {AFF_TOKEN, "AFF_TOKEN"},
    {MOD_TOKEN, "MOD_TOKEN"},
    {PV_TOKEN, "PV_TOKEN"},
    {PLUS_TOKEN, "PLUS_TOKEN"},
    {MOINS_TOKEN, "MOINS_TOKEN"},
    {MULT_TOKEN, "MULT_TOKEN"},
    {DIV_TOKEN, "DIV_TOKEN"},
    {VIR_TOKEN, "VIR_TOKEN"},
    {EG_TOKEN, "EG_TOKEN"},
    {INF_TOKEN, "INF_TOKEN"},
    {INFEG_TOKEN, "INFEG_TOKEN"},
    {SUP_TOKEN, "SUP_TOKEN"},
    {SUPEG_TOKEN, "SUPEG_TOKEN"},
    {DIFF_TOKEN, "DIFF_TOKEN"},
    {PO_TOKEN, "PO_TOKEN"},
    {PF_TOKEN, "PF_TOKEN"},
    {FIN_TOKEN, "FIN_TOKEN"},
};

Maptoken key_words[24] = {
    {NUMCONST_TOKEN, "NUMCONST_TOKEN"},
    {CHARCONST_TOKEN, "CHARCONST_TOKEN"},
    {STRINGCONST_TOKEN, "STRINGCONST_TOKEN"},
    {TRUE_TOKEN, "TRUE_TOKEN"},
    {FALSE_TOKEN, "FALSE_TOKEN"},
    {IDFCT_TOKEN, "IDFCT_TOKEN"},
    {INT_TOKEN, "INT_TOKEN"},
    {BOOL_TOKEN, "BOOL_TOKEN"},
    {CHAR_TOKEN, "CHAR_TOKEN"},
    {LET_TOKEN, "LET_TOKEN"},
    {ELSE_TOKEN, "ELSE_TOKEN"},
    {FOR_TOKEN, "FOR_TOKEN"},
    {TO_TOKEN, "TO_TOKEN"},
    {BY_TOKEN, "BY_TOKEN"},
    {RETURN_TOKEN, "RETURN_TOKEN"},
    {BREAK_TOKEN, "BREAK_TOKEN"},
    {CIN_TOKEN, "CIN_TOKEN"},
    {COUT_TOKEN, "COUT_TOKEN"},
    {OR_TOKEN, "OR_TOKEN"},
    {AND_TOKEN, "AND_TOKEN"},
    {IF_TOKEN, "IF_TOKEN"},
    {THEN_TOKEN, "THEN_TOKEN"},
    {WHILE_TOKEN, "WHILE_TOKEN"},
    {DO_TOKEN, "DO_TOKEN"},
};

Maptoken_erreur maperror[35] = {
    {IF_TOKEN, "Error : un 'IF'est  manquant"},
    {THEN_TOKEN, "Error : un 'THEN'est  manquant"},
    {WHILE_TOKEN, "Error : un 'WHILE'est  manquant"},
    {DO_TOKEN, "Error : un 'DO'est  manquant"},
    {CIN_TOKEN, "Error : erreur de lecture "},
    {COUT_TOKEN, "Error : erreur d'?cr?ture"},
    {PV_TOKEN, "Error : un ';'est  manquant"},
    {PLUS_TOKEN, "Error :une op?ration math?matique ne peut etre eff?ctuer sans op?rateur"},
    {MOINS_TOKEN, "Error :une op?ration math?matique ne peut etre eff?ctuer sans op?rateur"},
    {MULT_TOKEN, "Error :une op?ration math?matique ne peut etre eff?ctuer sans op?rateur"},
    {DIV_TOKEN, "Error :une op?ration math?matique ne peut etre eff?ctuer sans op?rateur"},
    {VIR_TOKEN, "Error : un ','est  manquant"},
    {AFF_TOKEN, "Error : un ':='est  manquant"},
    {EG_TOKEN, "Error : un '='est  manquant"},
    {INF_TOKEN, "Error :une op?ration  bool?enne ne peut etre eff?ctuer sans op?rateur"},
    {INFEG_TOKEN, "Error :une op?ration  bool?enne ne peut etre eff?ctuer sans op?rateur"},
    {SUP_TOKEN, "Error :une op?ration  bool?enne ne peut etre eff?ctuer sans op?rateur"},
    {SUPEG_TOKEN, "Error :une op?ration  bool?enne ne peut etre eff?ctuer sans op?rateur"},
    {DIFF_TOKEN, "Error :une op?ration  bool?enne ne peut etre eff?ctuer sans op?rateur"},
    {PO_TOKEN, "Error : un '('est  manquant"},
    {PF_TOKEN, "Error : un ')'est  manquant"},
    {FIN_TOKEN, "Error :erreur"},
    {ERREUR_TOKEN, "Error : erreur de syntaxe"}};

//nombre total des token
int nbTokens = 0, ligne = 1, colonne = 1, indx;
//caractere courant
char cour_char;
// notre fichier a complier
FILE *file;
//courant token
Maptoken Cour_Token, Cour_symbole, prev_token;
//linked list(tokens table)
typedef struct node
{
    Maptoken info;
    struct node *next;
} node;
//the head of the linked list
node *head = NULL;

//-----
struct DataItem
{
    Maptoken data;
    int key;
    bool isset;
};
struct DataItem *hashArray[SIZE];
struct DataItem *dummyItem;
struct DataItem *item;
//functions
void read_char();
void read_string();
void read_number();
void read_symbole();
void tokenmap(int a);
void push();
void Analex();
void commentignore();
void display();
