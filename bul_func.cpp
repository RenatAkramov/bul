#include "bul.func.h"



int main()
{
    CONVERSIONS* conversion = make_conversion();
    NODE* root = create_tree(conversion);


    amount_var(root, conversion);
    printf("amount Var: %d\n",  conversion->amount_var);


    var_t* mas_var = create_var(conversion);

    for (int i = 0; i < conversion->amount_var; i++)
    {
        printf(" %c %d \n", mas_var[i].name_var, mas_var[i].definition_var);
    }

    root = substitute_value(root, mas_var, conversion);
    root = decision(root);

    DrawTree(root);
    printf("ANSWER: %d", root->value);
}


CONVERSIONS* make_conversion()
{
    CONVERSIONS* conversion = (CONVERSIONS*) calloc(1, sizeof(CONVERSIONS));
    conversion->p = 0;
    conversion->amount_var = 0;
    FILE* file_in = fopen("primer.txt", "r");
    fscanf(file_in, "%s",conversion->s);
    printf("%s\n", conversion->s);
    fclose(file_in);
    return conversion;
}

void amount_var(NODE* node, CONVERSIONS* conversion)
{
    if (node->type == VAR)
    {
        conversion->amount_var++;
    }
    if (node->right != NULL)
    {
        amount_var(node->right, conversion);
    }
    if (node->left != NULL)
    {
        amount_var(node->left, conversion);
    }

}

var_t* create_var(CONVERSIONS* conversion)
{
    var_t* mas_var = (var_t*) calloc(conversion->amount_var, sizeof(var_t));
    for (int i = 0; i < conversion->amount_var; i++)
    {
        printf("Enter definition\n");
        int def = -1;
        scanf("%d", &def);
        while (def > 1 || def < 0)
        {
            printf("your defifinition can be 0 or 1 Please enter definition\n");
            scanf("%d", &def);
        }

        mas_var[i].definition_var = def;

        mas_var[i].name_var = 'a' + i;

    }
    return mas_var;
}

NODE* substitute_value(NODE* node, var_t* mas_var, CONVERSIONS* conversion)
{

    if (node->type == VAR)
    {
        printf("In var\n");
        for (int i = 0; i < conversion->amount_var; i++)
        {
            if(node->value.var_value == (int) mas_var[i].name_var)
            {
                values value;
                value.num_value = mas_var[i].definition_var;
                node->type = NUM;
                printf("In var after num %c %d\n", mas_var[i].name_var, mas_var[i].definition_var);
                node->value = value;
                printf("In var after val %d\n", node->value.num_value);
            }
        }
    }

    if (node->right != NULL)
    {
        substitute_value(node->right, mas_var, conversion);
    }
    if (node->left != NULL)
    {
        substitute_value(node->left, mas_var, conversion);
    }
    return node;
}

NODE* decision(NODE* node)
{
    if (node->type == NUM)
    {
        return node;
    }
    else
    {
        switch(node->value.sym_value)
        {
            case NOT:
            {
                printf("in NOT\n");
                node->type = NUM;
                int val = node->left->value.num_value;
                if (val == 0) node->value.num_value = 1;
                if (val == 1) node->value.num_value = 0;
                printf(" NOT:: val1 = %d, all val = %d\n", val, node->value.num_value);

                break;
            }
            case MUL:
            {
                printf("in MUL\n");
                node->left = decision(node->left);
                node->right = decision(node->right);
                printf("after decision in mul\n");
                int val2 = node->right->value.num_value;
                int val1 = node->left->value.num_value;
                printf("mul after val1 val2\n");
                values value;
                value.num_value = val1 * val2;
                node->type = NUM;
                node->value = value;
                printf(" MUL:: val1 = %d, val2 = %d, all val = %d\n", val1, val2, node->value.num_value);

                break;
            }
            case IMP:
            {
                printf("in IMP\n");
                decision(node->left);
                decision(node->right);

                int val2 = node->right->value.num_value;
                int val1 = node->left->value.num_value;
                values value;
                if (val1 == 1 && val2 == 0)
                {
                    value.num_value = 0;
                }
                else
                {
                    value.num_value = 1;
                }
                node->type = NUM;
                node->value = value;
                printf(" IMP:: val1 = %d, val2 = %d, all val = %d\n", val1, val2, node->value.num_value);

                break;
            }
            case ADD:
            {
                printf("in ADD\n");
                decision(node->left);
                decision(node->right);

                int val2 = node->right->value.num_value;
                int val1 = node->left->value.num_value;
                values value;
                if (val1 == 0 && val2 == 0)
                {
                    value.num_value = 0;
                }
                else
                {
                    value.num_value = 1;
                }
                node->type = NUM;
                node->value = value;
                printf(" ADD:: val1 = %d, val2 = %d, all val = %d\n", val1, val2, node->value.num_value);

                break;
            }
            case EQV:
            {
                printf("in EQV\n");
                decision(node->left);
                decision(node->right);

                int val2 = node->right->value.num_value;
                int val1 = node->left->value.num_value;
                values value;
                if (val1 == val2)
                {
                    value.num_value = 1;
                }
                else
                {
                    value.num_value = 0;
                }
                node->type = NUM;
                node->value = value;
                printf(" EQV:: val1 = %d, val2 = %d, all val = %d\n", val1, val2, node->value.num_value);

                break;
            }

            default:
            {
                fprintf(stderr, "Error: unknown operation(%d)", node->value.sym_value);
                return NULL;
            }
        }
    return node;
    }

}
/*NODE* diff(NODE* node)
{
    values value = {};

    if (node->type == NUM)
    {
        value.num_value = 0;
        return new_node(NUM, value, NULL, NULL);
    }
    if (node->type == VAR)
    {
        value.num_value = 1;
        return new_node(NUM, value, NULL, NULL);
    }
    switch(node->value.sym_value)
    {
        case ADD:
        {
            value.sym_value = ADD;
            return new_node(SYM, value, diff(node->left), diff(node->right));
        }
        case SUB:
        {
            value.sym_value = SUB;
            return new_node(SYM, value, diff(node->left), diff(node->right));
        }
        case MUL:
        {
            NODE* dr = diff(node->right);
            NODE* dl = diff(node->left);
            NODE* cl = copy_node(node->left);
            NODE* cr = copy_node(node->right);

            value.sym_value = MUL;


            union values value_add = {};
            value_add.sym_value     = ADD;

            return new_node(SYM, value_add, new_node(SYM, value, dl, cr), new_node(SYM, value, cl, dr));
        }
        case DIV:
        {
            NODE* dl = diff(node->left);
            NODE* dr = diff(node->right);

            NODE* cl = copy_node(node->left);
            NODE* cr = copy_node(node->right);

            value.sym_value = MUL;

            union values value_sub = {};
            union values value_div = {};

            value_sub.sym_value = SUB;
            value_div.sym_value = DIV;

            return new_node(SYM, value_div, new_node(SYM, value_sub, new_node(SYM, value, dl, cr), new_node(SYM, value, cl, dr)),new_node(SYM, value, copy_node(cr), copy_node(cr)));
        }
        default:
        {
            printf("ERROR IN DIFF\n");
            return NULL;
        }

    }
}
*/

NODE* copy_node(NODE* node)
{
    if (!node)
    {
        return NULL;
    }

    NODE* copynode =  new_node(node->type, node->value, copy_node(node->left), copy_node(node->right));

    return copynode;

}




/*
CONVERSIONS* simplifare(CONVERSIONS* node)
{

}
*/


