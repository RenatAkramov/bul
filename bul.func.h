#ifndef differentiator_h
#define differentiator_h

#include <stdio.h>
#include <stdlib.h>

struct CONVERSIONS
{
    char s[999];
    int p;
    int amount_var;
};

union values
{
    int num_value;
    int var_value;
    int sym_value;
};

struct NODE
{
    int type;
    union values value;
    NODE* left;
    NODE* parent;
    NODE* right;
};

enum operations
{
    MUL = 1,
    NOT = 2,
    ADD = 3,
    IMP = 4,
    EQV = 5,
};


const int amount_operations = 5;

struct var_t
{
    char name_var;
    int definition_var;
};

enum type
{
    SYM  = 1,
    VAR  = 2,
    NUM  = 3
};

struct operations_t
{
    char name_symbol;
    int code;
};

enum errorcode
{
    ERROR_E = 0,
    ERROR_P = 1,
    ERROR_V = 2,
    ERROR_T = 3,
    ERROR_G = 4,
    ERROR_N = 5,
    ERROR_F = 6,
    ERROR_H = 7
};

const operations_t operations[amount_operations] = {{'*', MUL}, {'!', NOT}, {'+', ADD},{'~', EQV}, {'-', IMP}};

/*struct token
{

};*/


NODE* new_node(int type, values value, NODE* vol, NODE* vol2);

NODE* create_tree(CONVERSIONS* conversion);

NODE* GetP(CONVERSIONS* conversion);
NODE* GetE(CONVERSIONS* conversion);
NODE* GetT(CONVERSIONS* conversion);
NODE* GetG(CONVERSIONS* conversion);
NODE* GetN(CONVERSIONS* conversion);
NODE* GetF(CONVERSIONS* conversion);
NODE* GetH(CONVERSIONS* conversion);
void  SyntaxERROR(int code_error);
NODE* GetV(CONVERSIONS* conversion);
void  spend(NODE* node);
int   DrawTree(NODE* root);
int   DrawNode(NODE* node, FILE* file_ptr);
CONVERSIONS* make_conversion();
NODE* copy_node(NODE* node);
void amount_var(NODE* node, CONVERSIONS* conversion);
var_t* create_var(CONVERSIONS* conversion);
NODE* substitute_value(NODE* node, var_t* mas_var, CONVERSIONS* conversion);
NODE* decision(NODE* node);



#endif
