#include "bul.h"
#include <string.h>

void create_dnf(struct NODE* root) 
{
    struct variable vars[max_variable];
    int var_count = 0;
    collect_variables(root, vars, &var_count);

    struct numbers numb[max_constants];
    int num_count = 0;
    collect_number(root, numb, &num_count);

    if (var_count == 0) 
    {
        int result = evaluate(root, NULL, 0);
        printf("ДНФ: %d\n", result);
        return;
    }
    
    char* output;
    size_t sz;

    FILE* outf  = open_memstream(&output, &sz); 
    int var_count_2 = 1 << var_count; 
    int first_clause = 1;

    for (int mask = 0; mask < var_count_2; mask++) 
    {
        for (int i = 0; i < var_count; i++) 
        {
            vars[i].value = (mask >> (var_count - 1 - i)) & 1;
        }

        int result = evaluate(root, vars, var_count);
        if (result == 1) 
        {
            if (first_clause) 
            {
                fprintf(outf, "(");
                first_clause = 0;
            } 
            else 
            {
                fprintf(outf, ") OR (");
            }
            fprintf(outf, "%c", '(');
            for (int i = 0; i < var_count; i++) 
            {
                if (vars[i].value == 1) 
                {
                    fprintf(outf, "%c", vars[i].name);
                } 
                else 
                {
                    fprintf(outf, "NOT %c", vars[i].name);
                }

                if (i != var_count - 1) 
                {
                    fprintf(outf," %s ", "AND");
                }
            }
            
        }
    }
    fprintf(outf, "%c", ')');
    fwrite("", 1,1, outf);
    fclose(outf);


    if (strlen(output) == 0) 
    {
        int const_result = evaluate(root, NULL, 0);
        fprintf(stdout, "ДНФ: %d\n", const_result);
    } 
    else 
    {
        fprintf(stdout, "ДНФ: %s\n", output);
    }

    free(output);
}

void create_knf(struct NODE* root) 
{
    struct variable vars[max_variable];
    int var_count = 0;
    collect_variables(root, vars, &var_count);

    struct numbers numb[max_constants];
    int num_count = 0;
    collect_number(root, numb, &num_count);

  
    if (var_count == 0)
    {
        int result = evaluate(root, NULL, 0);
        printf("КНФ: %d\n", result);
        return;
    }

    char* output;
    size_t sz;
    FILE* outf = open_memstream(&output, &sz);
    int var_count_2 = 1 << var_count;
    int first_clause = 1;

    for (int mask = 0; mask < var_count_2; mask++) 
    {
        for (int i = 0; i < var_count; i++) 
        {
            vars[i].value = (mask >> (var_count - 1 - i)) & 1;
        }

        int result = evaluate(root, vars, var_count);
        
        
        if (result == 0) 
        {
            if (first_clause) 
            {
                fprintf(outf, "(");
                first_clause = 0;
            } 
            else 
            {
                fprintf(outf, ") AND (");
            }
            for (int i = 0; i < var_count; i++) 
            {
                if (vars[i].value == 0) 
                {
                    fprintf(outf, "%c", vars[i].name);
                } 
                else 
                {
                    fprintf(outf, "NOT %c", vars[i].name);
                }

                if (i != var_count - 1) 
                {
                    fprintf(outf, " OR ");
                }
            }
            
        }
    }
    fprintf(outf, ")");
    fwrite("", 1,1, outf);
    fclose(outf);

    if (strlen(output) == 0) 
    {
        printf("КНФ: 1\n");
    }
    else 
    {
        printf("КНФ: %s\n", output);
    }

    free(output);
}