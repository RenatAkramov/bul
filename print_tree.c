
#include "bul.h" 


int get_priority(int oper) 
{
    switch (oper) 
    {
        case NOT:   return 4;
        case AND:   return 3;
        case OR:    return 2;
        case XOR:   return 2;
        case IMP:   return 1;
        case XNOR:  return 1;
        default:    return 0;
    }
}


const char* get_op_symbol(int oper) 
{
    switch (oper) 
    {
        case NOT:   return "NOT";
        case AND:   return "AND";
        case OR:    return "OR";
        case XOR:   return "XOR";
        case IMP:   return "IMP";
        case XNOR:  return "XNOR";
        default:    return "";
    }
}


int is_unary(int oper) 
{
    return (oper == NOT);
}


void print_expression(struct NODE *node, int parent_priority) 
{
    if (!node) return;

    switch (node->type) 
    {
        case NUM:
            fprintf(stdout, "%d", node->value.num_value);
            break;
            
        case VAR:
            fprintf(stdout, "%c", node->value.var_value);
            break;
            
        case OPER: 
        {
            int current_op = node->value.oper_value;
            int current_priority = get_priority(current_op);
            const char *op_symbol = get_op_symbol(current_op);

            
            if (is_unary(current_op)) 
            {
                fprintf(stdout, "%s ", op_symbol);
                
                
                if (node->left && node->left->type == OPER) 
                {
                    fprintf(stdout, "(");
                    print_expression(node->left, current_priority);
                    fprintf(stdout, ")");
                } 
                else 
                {
                    print_expression( node->left, current_priority);
                }
            }
           
            else 
            {
                int need_parentheses = (current_priority < parent_priority);

                if (need_parentheses) fprintf(stdout, "(");

               
                print_expression( node->left, current_priority);

               
                fprintf(stdout, " %s ", op_symbol);

                print_expression(node->right, current_priority);

                if (need_parentheses) fprintf(stdout, ")");
            }
            break;
        }
    }
}


void print_expression_pretty(struct NODE *root) 
{
    print_expression(root, 0); 
}