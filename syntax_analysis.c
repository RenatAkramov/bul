#include "bul.h"



//Создаем дерево
struct NODE* create_tree(struct CONVERSIONS* conversion, struct tokens_t* arr_token)
{
    struct NODE* root;
    root = GetG(conversion, arr_token);
    return root;
}

struct NODE* GetP(struct CONVERSIONS* conversion, struct tokens_t* arr_token)
{
    printf("Current token index: %d, token: %s (type=%d)\n", conversion->p, arr_token[conversion->p].name, arr_token[conversion->p].type);

    //Обработка левой скобки
    if (arr_token[conversion->p].value.oper_value == bracket_left)
    {
        conversion->p++;
        struct NODE* val = GetH(conversion, arr_token);
        //Обработка правой скобки
        if (arr_token[conversion->p].value.oper_value != bracket_right)
        {
            SyntaxERROR(ERROR_P);
        }
        conversion->p++;
        return val;
    }
    else
    {
        return GetV(conversion, arr_token);
    }
}

struct NODE* GetX(struct CONVERSIONS* conversion, struct tokens_t* arr_token)
{
    printf("Current token index: %d, token: %s (type=%d)\n", conversion->p, arr_token[conversion->p].name, arr_token[conversion->p].type);
    struct NODE* val = GetE(conversion, arr_token);

    //Обработка XOR
    if (arr_token[conversion->p].value.oper_value == XOR)
    {
        conversion->p++;
        struct NODE* val_2 = GetE(conversion, arr_token);

        union  values value;
        value.oper_value = XOR;
        val = new_node(OPER, value, val, val_2);
    }
    return val;
}

struct NODE* GetN(struct CONVERSIONS* conversion, struct tokens_t* arr_token)
{
    printf("Current token index: %d, token: %s (type=%d)\n", conversion->p, arr_token[conversion->p].name, arr_token[conversion->p].type);

    int val_value = 0;
    int j = 0;

    // Обработка чисел
    if (arr_token[conversion->p].type == NUM) 
    {
        while ('0' <= arr_token[conversion->p].name[j] && arr_token[conversion->p].name[j] <= '9') 
        {
            val_value = val_value * 10 + (arr_token[conversion->p].name[j] - '0');
            j++;
        }
        if (val_value != 0 && val_value != 1)
        {
            fprintf(stderr,"ERROR: number not 1 or 0 in GetN \n");
            SyntaxERROR(ERROR_N);
            return NULL;
        }
        union values value;
        value.num_value = val_value;
        struct NODE* val = new_node(NUM, value, NULL, NULL);
        conversion->p++;
        return val;
    }
    // Обработка переменных
    else if (arr_token[conversion->p].type == VAR) 
    {
        union values value;
        value.var_value = arr_token[conversion->p].value.var_value; 
        struct NODE* val = new_node(VAR, value, NULL, NULL);
        conversion->p++;
        return val;
    }
    else 
    {
        SyntaxERROR(ERROR_N);
        return NULL;
    }


}

struct NODE* GetF(struct CONVERSIONS* conversion, struct tokens_t* arr_token)
{
    printf("Current token index: %d, token: %s (type=%d)\n", conversion->p, arr_token[conversion->p].name, arr_token[conversion->p].type);
    struct NODE* val = GetX(conversion, arr_token);

    //Обработка IMP
    if (arr_token[conversion->p].value.oper_value == IMP)
    {
        conversion->p++;
        struct NODE* val_2 = GetX(conversion, arr_token);

        union  values value;
        value.oper_value = IMP;
        val = new_node(OPER, value, val, val_2);
    }
    
    return val;
}

struct NODE* GetH(struct CONVERSIONS* conversion, struct tokens_t* arr_token)
{
    printf("Current token index: %d, token: %s (type=%d)\n", conversion->p, arr_token[conversion->p].name, arr_token[conversion->p].type);
    struct NODE* val = GetF(conversion, arr_token);

    //Обработка XNOR
    if (arr_token[conversion->p].value.oper_value == XNOR)
    {
        conversion->p++;
        struct NODE* val_2 = GetF(conversion, arr_token);

        union  values value;
        value.oper_value = XNOR;
        val = new_node(OPER, value, val, val_2);
    }
    return val;
}

struct NODE* GetG(struct CONVERSIONS* conversion, struct tokens_t* arr_token)
{
    printf("Current token index: %d, token: %s (type=%d)\n", conversion->p, arr_token[conversion->p].name, arr_token[conversion->p].type);
    struct NODE* val = GetH(conversion, arr_token);

    //Обработка END
    if (arr_token[conversion->p].value.oper_value == END)
    {
        printf("END\n");
        conversion->p++;
        return val;
    }
    else
    {
        SyntaxERROR(ERROR_G);
        fprintf(stderr,"NO '$' in end");
        return NULL;
    }
}



struct NODE* GetE(struct CONVERSIONS* conversion, struct tokens_t* arr_token)
{
    printf("%s in GetE (type=%d)\n", arr_token[conversion->p].name, arr_token[conversion->p].type);
    struct NODE* val = GetT(conversion, arr_token);
    
    //Обработка OR
    if (arr_token[conversion->p].value.oper_value == OR)
    {
        printf("Processing OR in GetE\n");
        conversion->p++;
        struct NODE* val_2 = GetT(conversion, arr_token);
        union values value;
        value.oper_value = OR;
        val = new_node(OPER, value, val, val_2);
    }
    return val;

}
struct NODE* GetT(struct CONVERSIONS* conversion, struct tokens_t* arr_token)
{
    printf("Current token index: %d, token: %s (type=%d)\n", conversion->p, arr_token[conversion->p].name, arr_token[conversion->p].type);
    struct NODE* val = GetP(conversion, arr_token);
    
    //Обработка AND
    if (arr_token[conversion->p].value.oper_value == AND)
    {
        conversion->p++;
        struct NODE* val_2 = GetP(conversion, arr_token);

        union  values value;
        value.oper_value = AND;
        val = new_node(OPER, value, val, val_2);
    }
    return val;
}
struct NODE* GetV(struct CONVERSIONS* conversion, struct tokens_t* arr_token)
{
    printf("%s in GetV (type=%d)\n", arr_token[conversion->p].name, arr_token[conversion->p].type);
    
    //Обработка NOT
    if (arr_token[conversion->p].value.oper_value == NOT)
    {
        union values value;
        value.oper_value = NOT;
        conversion->p++;
        struct NODE* val = GetH(conversion, arr_token);
        return new_node(OPER, value, val, NULL);
    }
    // Проверка, что токен является переменной или числом
    else if (arr_token[conversion->p].type == VAR || arr_token[conversion->p].type == NUM)
    {
        return GetN(conversion, arr_token);
    }
    else
    {
        fprintf(stderr,"ERROR: Unexpected token '%s' in GetV\n", arr_token[conversion->p].name);
        SyntaxERROR(ERROR_V);
        return NULL;
    }
}


void  SyntaxERROR(int error_code)
{
    fprintf(stderr, "ERROR %d\n", error_code);
    exit(0);
}

struct NODE* new_node(int type, union  values value, struct NODE* vol, struct NODE* vol2)
{
   struct NODE*  node = (struct NODE*) calloc(1, sizeof(struct NODE));
   node->type  = type;
   node->value = value;
   node->left  = vol;
   node->right = vol2;
   return node;
}
