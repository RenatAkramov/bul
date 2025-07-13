#include "bul.h"

int trees_equal(struct NODE* a, struct NODE* b)
{
    if (a == NULL && b == NULL) return true;
    if (a == NULL && b != NULL) return false;
    if (b == NULL && a != NULL) return false;
    if (a->type != b->type) return false;
    switch (a->type) 
    {
        case NUM: return a->value.num_value == b->value.num_value;
        case VAR: return a->value.var_value == b->value.var_value;
        case OPER: return a->value.oper_value == b->value.oper_value;
        default: return false;
    }
}


int is_constant(struct NODE* node, int value) 
{
    return (node && node->type == NUM && node->value.num_value == value);
}

struct NODE* simplify(struct NODE* node) 
{
    if (!node) return NULL;

   
    if (node->left != NULL) node->left = simplify(node->left);
    if (node->right != NULL) node->right = simplify(node->right);

    switch (node->type) 
    {
        case OPER: 
        {
            int op = node->value.oper_value;
            struct NODE* left = node->left;
            struct NODE* right = node->right;

            if (op == NOT && left && left->type == OPER && left->value.oper_value == NOT) 
            {
                struct NODE* simplified = left->left;
                free(left);
                free(node);
                return simplify(simplified);
            }


            if (op == AND) 
            {
                if (is_constant(left, 0) || is_constant(right, 0)) 
                {
                    free_tree(node);
                    return new_node(NUM, (union values){0}, NULL, NULL); 
                }
                if (is_constant(left, 1)) 
                {
                    free(node);
                    return simplify(right); 
                }
                if (is_constant(right, 1)) 
                {
                    free(node);
                    return simplify(left); 
                }
            } 
            else if (op == OR) 
            {
                if (is_constant(left, 1) || is_constant(right, 1)) 
                {
                    free_tree(node);
                    return new_node(NUM, (union values){1}, NULL, NULL);
                }
                if (is_constant(left, 0)) 
                {
                    free(node);
                    return simplify(right);
                }
                if (is_constant(right, 0)) {
                    free(node);
                    return simplify(left);
                }
            }

           
            
            if (op == AND && right->type == OPER && right->value.oper_value == OR && 
                (trees_equal(left, right->left) || trees_equal(left, right->right))) 
            {
                free_tree(node);
                return simplify(left);
            }
            if (op == OR && right->type == OPER && right->value.oper_value == AND && 
                (trees_equal(left, right->left) || trees_equal(left, right->right))) 
            {
                free_tree(node);
                return simplify(left);
            }

            if (op == OR && left->type == OPER && left->value.oper_value == NOT 
                && right->type == OPER && right->value.oper_value == NOT) 
            {
                struct NODE* a = left->left;
                struct NODE* b = right->left;
                union  values value1;
                union  values value2;
                value1.oper_value = AND;
                value2.oper_value = NOT;
                struct NODE*  new_and = new_node(OPER, value1, a, b);
                struct NODE*  new_not = new_node(OPER, value2, new_and, NULL);
                free_tree(node);
                return simplify(new_not);
            }

            if (op == OR && left->type == OPER && left->value.oper_value == AND 
                && right->type == OPER && right->value.oper_value == AND) 
            {
                
                if (trees_equal(left->left, right->left)) 
                {
                    struct NODE* a = left->left;
                    struct NODE* b = left->right;
                    struct NODE* c = right->right;
                    union  values value;
                    value.oper_value = AND;
                    struct NODE* new_or = new_node(OPER, node->value, b, c);
                    struct NODE* new_and = new_node(OPER, value, a, new_or);
                    free_tree(node);
                    return simplify(new_and);
                }
                
                else if (trees_equal(left->right, right->right)) 
                {
                    struct NODE* a = left->right;
                    struct NODE* b = left->left;
                    struct NODE* c = right->left;
                    union  values value;
                    
                    value.oper_value = AND;
                    struct NODE* new_or = new_node(OPER, node->value, b, c);
                    struct NODE* new_and = new_node(OPER, value, new_or, a);
                    free_tree(node);
                    return simplify(new_and);
                }
            }
            break;
        }
        default:
            break;
    }

    return node;
}

void free_tree(struct NODE* node)
{
    if (node->left != NULL) free_tree(node->left);
    if (node->left != NULL) free_tree(node->right);
    free(node);  
}

