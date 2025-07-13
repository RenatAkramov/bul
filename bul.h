#ifndef differentiator_h
#define differentiator_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/stat.h>
#include <stdbool.h>

#define amount_operations 6
#define max_variable 28
#define max_constants 200
#define amount_tasks 5
#define make_root struct CONVERSIONS* conversion = make_conversion(config);\
        assert(conversion);\
        struct tokens_t* arr_token = create_lec(conversion);\
        assert(arr_token);\
        struct NODE* root = create_tree(conversion, arr_token);\
        assert(root)


struct CONVERSIONS
{
    char* s;
    int p;
    int amount_var;
};

union values
{
    int num_value;
    int var_value;
    int oper_value;
};

struct variable
{
    char name;
    int value;
};

struct numbers
{
    int value;
};

struct NODE
{
    int type;
    
    union values value;
    struct NODE* left;
    struct NODE* parent;
    struct NODE* right;
};

struct tokens_t
{
    int type;
    union values value;
    char* name;
    struct NODE* node;
};



enum type
{
    OPER  = 1,
    VAR   = 2,
    NUM   = 3,
    END   = 4,
    bracket_left  = 5,
    bracket_right = 6,
};
enum operations
{
    AND  = 7,
    NOT  = 8,
    OR   = 9,
    IMP  = 10,
    XOR  = 11,
    XNOR = 12,
};

union method_to_get_function
{
    int f;
    int c;
};


struct Config 
{
    union method_to_get_function met_get;
    int   t;
    char* filename;     
    char* funktion;  
    char* task;      
};


struct operations_t
{
    char* name_symbol;
    int code;
};

enum errorcode
{
    ERROR_H = 0,
    ERROR_F = 1,
    ERROR_X = 2,
    ERROR_E = 3,
    ERROR_T = 4,
    ERROR_P = 5,
    ERROR_V = 6,
    ERROR_N = 7,
    ERROR_G = 8
};

struct var_t
{
    char name_var;
    int definition_var;
};

extern const struct operations_t operations[];

struct FUNKTION_T
{
    const char* name;
    int code;
};



struct CONVERSIONS* make_conversion(struct Config* config);
struct tokens_t* create_lec(struct CONVERSIONS* conversion);
int    create_tokens(int len_buf, struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* create_tree(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetP(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetX(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetN(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetF(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetH(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetG(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetE(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetT(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
void   SyntaxERROR(int errorcode);
struct NODE* new_node(int type, union values value, struct NODE* vol, struct NODE* vol2);
struct NODE* GetV(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
int    DrawTree(struct NODE* root);
int    DrawNode(struct NODE* node, FILE* file_ptr);
void print_truth_table(struct NODE* root);
void collect_variables(struct NODE* node, struct variable* vars, int* count); 
void collect_number(struct NODE* node, struct numbers* numb ,int* count);
struct Config* parse_args(int argc, char *argv[]);
int evaluate(struct NODE* node,struct variable* vars, int var_count);
void print_help();
int task_selection(struct Config* config);
void collect_number(struct NODE* node, struct numbers* numb, int* count);
void create_dnf(struct NODE* root);
void create_knf(struct NODE* root);
int is_constant(struct NODE* node, int value);
struct NODE* simplify(struct NODE* node);
void free_tree(struct NODE* node);
void print_expression_pretty(struct NODE *root);
int is_unary(int oper);
const char* get_op_symbol(int oper);
int get_priority(int oper); 


#endif
