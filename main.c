#include "bul.h"

int main(int argc, char* argv[])
{
    if (argc == 1) 
    {
        print_help();
        return 1;
    }
    struct Config* config = parse_args(argc, argv);
    assert(config);
    if (task_selection(config) == 0) return 0;

    return 1;
}

int task_selection(struct Config* config)
{
    if(strcmp(config->task, "table") == 0)
    {
        make_root;
        print_truth_table(root);
    }
    else if(strcmp(config->task, "graf") == 0)
    {
        make_root;
        DrawTree(root);
    }
    else if(strcmp(config->task, "dnf") == 0) 
    {
        make_root;
        create_dnf(root);
    }
    else if(strcmp(config->task, "knf") == 0) 
    {
        make_root;
        create_knf(root);
    }
    else if(strcmp(config->task, "simplifare") == 0)
    {
        make_root;
        root = simplify(root);
        print_expression_pretty(root);
    }
    else
    {
        fprintf(stderr,"ERROR: некорректное название задания\n");
        return 0;
    }
    
    return 1;
}