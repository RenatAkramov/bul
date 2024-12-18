#include "bul.func.h"

NODE* create_tree(CONVERSIONS* conversion)
{
    NODE* root;
    root = GetG(conversion);
    return root;
}

void spend(NODE* node)
{
    printf("val : %d\n",node->type);
    if (node->left != NULL) spend(node->left);
    if (node->right != NULL) spend(node->right);
}

NODE* GetH(CONVERSIONS* conversion)
{
    NODE* val = GetF(conversion);
    printf("In H after F early  %d %c\n", conversion->p, conversion->s[conversion->p]);
    while (conversion->s[conversion->p] == '~')
    {
        conversion->p++;

        NODE* val_2 = GetF(conversion);
        printf("In H after F last\n");
        values value;
        value.sym_value = EQV;
        val = new_node(SYM, value, val, val_2);
    }
    return val;
}

NODE* GetF(CONVERSIONS* conversion)
{
    NODE* val = GetE(conversion);
    printf("In F after E early  %d %c\n", conversion->p, conversion->s[conversion->p]);
    while (conversion->s[conversion->p] == '-')
    {
        conversion->p++;

        NODE* val_2 = GetH(conversion);
        printf("In F after E last\n");
        values value;
        value.sym_value = IMP;
        val = new_node(SYM, value, val, val_2);
    }
    return val;
}

NODE* GetP(CONVERSIONS* conversion)
{
    if (conversion->s[conversion->p] == '(')
    {
        conversion->p++;

        NODE* val = GetH(conversion);
        printf("in P after H\n");
        if (conversion->s[conversion->p] != ')')
        {
            printf("p: %c\n", conversion->s[conversion->p]);
            SyntaxERROR(ERROR_P);
        }

        conversion->p++;

        return val;
    }
    else
    {
        return GetV(conversion);
    }

}

NODE* GetE(CONVERSIONS* conversion)
{
    NODE* val = GetT(conversion);
    printf("in E after T early\n");
    while (conversion->s[conversion->p] == '+')
    {
        conversion->p++;

        NODE* val_2 = GetT(conversion);
        printf("in E after T last\n");
        values value;
        value.sym_value = ADD;
        val = new_node(SYM, value, val, val_2);

    }

    return val;
}

NODE* GetN(CONVERSIONS* conversion)
{

    int p_old = conversion->p;
    if ('a' - 1 < conversion->s[conversion->p] && conversion->s[conversion->p] < 'z' + 1)
    {
        values value;
        value.var_value = conversion->s[conversion->p];

        NODE* val = new_node(VAR, value, NULL, NULL);
        conversion->p++;
        return val;
    }
    else
    {
        printf("p: %c %d\n", conversion->s[conversion->p], conversion->p);
        SyntaxERROR(ERROR_N);
    }
    //if (p_old == conversion->p) SyntaxERROR(ERROR_N);

}

NODE* GetT(CONVERSIONS* conversion)
{
    NODE* val = GetP(conversion);
    printf("in T after P\n");
    while (conversion->s[conversion->p] == '*')
    {
        conversion->p++;
        NODE* val_2 = GetP(conversion);
        values value;
        value.sym_value = MUL;
        val = new_node(SYM, value, val, val_2);
    }
    return val;
}

NODE* GetG(CONVERSIONS* conversion)
{
    printf("Start\n");
    NODE* val = GetH(conversion);
    printf("in G after H\n");
    if (conversion->s[conversion->p] == '$')
    {
        printf("END\n");
        conversion->p++;
        return val;
    }
    else
    {
        printf("p: %c %d\n", conversion->s[conversion->p], conversion->p);
        SyntaxERROR(ERROR_G);
    }
}

NODE* GetV(CONVERSIONS* conversion)
{
    if (conversion->s[conversion->p] == '!')
    {
        printf("IN V after while !\n");
        values value;
        value.sym_value = NOT;
        conversion->p++;
        NODE* val = new_node(SYM, value, GetN(conversion), NULL);

        return val;
    }
    else
    {
        return GetN(conversion);
    }

}


void  SyntaxERROR(int code_error)
{
    printf("ERROR %d", code_error);
    exit(0);
}

NODE* new_node(int type, values value, NODE* vol, NODE* vol2)
{
   NODE*  node = (NODE*) calloc(1, sizeof(NODE));
   node->type  = type;
   node->value = value;
   node->left  = vol;
   node->right = vol2;
   return node;
}
