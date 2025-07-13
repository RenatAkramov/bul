#include "bul.h"

const struct operations_t operations[] = {
    {"AND", AND}, 
    {"OR", OR}, 
    {"NOT", NOT}, 
    {"XOR", XOR}, 
    {"IMP", IMP}, 
    {"XNOR", XNOR}
};

//Начало построение графического представления дерева
int DrawTree(struct NODE* root)
{   
    if (!root)
    {
        fprintf(stderr, "Drawing error: root(%p)\n", (void*) root);
        return -1;
    }

    FILE* file_ptr = fopen("grafdump.dot", "w");//Файл для вывода 
    if (!file_ptr)
    {
        fprintf(stderr, "File \"grafdump.dot\" error!\n");
        return -1;
    }

    fprintf(file_ptr, "digraph G\n{\n  rankdir = UD;\n  edge[color = \"green\"];\n");

    DrawNode(root, file_ptr);

    fprintf(file_ptr, "}");

    fclose(file_ptr);

    if (system("dot grafdump.dot -Tpng -o Dump.png") != 0)
    {
        fprintf(stderr, "ERROR: in system");
        perror("system error");
        return 0;
    }

    return 1;
}

int DrawNode(struct NODE* node, FILE* file_ptr)//Построение одного узла
{
    if (!node) return 0;

    if (!file_ptr)
    {
        fprintf(stderr, "File error!\n");
        return -1;
    }

    fprintf(file_ptr, "  \"%p\" [shape = Mrecord, ",(void*) node);

    if (!node->left && !node->right)
    {
        fprintf(file_ptr, "color = \"limegreen\", style = \"filled\", fillcolor = \"darkolivegreen1\", ");
    }
    else
    {
        fprintf(file_ptr, "color = \"khaki2\", style = \"filled\", fillcolor = \"lemonchiffon\", ");
    }


    fprintf(file_ptr, "label = \"");
    printf("NODE TYPE: %d\n", node->type);
    if (node->type == NUM)
    {
        printf("in NUM dump\n");
        fprintf(file_ptr,  "%1d", node->value.num_value);
    }
    else if (node->type == VAR)
    {
        fprintf(file_ptr,  "%c", node->value.var_value);
    }
    else
    {
        for (int i = 0; i < amount_operations; ++i)
        {
            if (node->value.oper_value == operations[i].code)
            {
                fprintf(file_ptr, "%s", operations[i].name_symbol);

                break;
            }
        }
    }

    fprintf(file_ptr, "\"];\n");

    if (DrawNode(node->left,  file_ptr) != 0) return -1;//Рекурсивный запуск построения следующих узлов
    if (DrawNode(node->right, file_ptr) != 0) return -1;

    if (node->left)
    {
        fprintf(file_ptr, "  \"%p\" -> \"%p\";\n",(void*) node,(void*) node->left);
    }

    if (node->right)
    {
        fprintf(file_ptr, "  \"%p\" -> \"%p\";\n",(void*) node,(void*) node->right);
    }

    return 0;
}
