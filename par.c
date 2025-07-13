#include "bul.h"


int is_valid_task(const char *task) 
{
    const char* valid_tasks[] = {"simplifare", "graf", "dnf", "knf", "table"};
    for (int i = 0; i < amount_tasks; i++) 
    {
        if (strcmp(task, valid_tasks[i]) == 0) return 1;
    }
    return 0;
}


struct Config* parse_args(int argc, char *argv[]) 
{
    struct Config *config = calloc(1, sizeof(struct Config));
    config->t = 0;
    config->filename = NULL;
    config->funktion = NULL;
    config->task = NULL;

    for (int i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            print_help();
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            i = i + 1;
            if (i >= argc || argv[i][0] == '-') 
            {
                fprintf(stderr, "Ошибка: после -f должно быть имя файла\n");
                free(config);
                return NULL;
            }
            config->filename = argv[i];
            config->met_get.f = 1;
        } 
        else if (strcmp(argv[i], "-c") == 0) 
        {
            i = i + 1;
            if (i >= argc || argv[i][0] == '-') 
            {
                fprintf(stderr, "Ошибка: после -c должно быть выражение\n");
                free(config);
                return NULL;
            }
            config->funktion = argv[i];
            printf("%s\n", argv[i]);
            config->met_get.c = 1;
        } 
        else if (strcmp(argv[i], "-t") == 0) 
        { 
            i = i + 1;
            if (i >= argc || argv[i][0] == '-') 
            {
                fprintf(stderr, "Ошибка: после -t должна быть задача\n");
                free(config);
                return NULL;
            }
            config->task = argv[i];
            config->t = 1;
        } 
        else 
        {
            fprintf(stderr, "Неизвестный флаг: %s\n", argv[i]);
            free(config);
            return NULL;
        }
    }

    if (config->filename && config->funktion) 
    {
        fprintf(stderr, "Ошибка: нельзя использовать -f и -c одновременно\n");
        free(config);
        return NULL;
    }

    if (!config->filename && !config->funktion) 
    {
        fprintf(stderr, "Ошибка: необходимо указать -f или -c\n");
        free(config);
        return NULL;
    }

    if (!config->task) 
    {
        fprintf(stderr, "Ошибка: необходимо указать задачу (-t)\n");
        free(config);
        return NULL;
    }

    if (!is_valid_task(config->task)) 
    {
        fprintf(stderr, "Ошибка: недопустимая задача '%s'\n", config->task);
        fprintf(stderr, "Допустимые задачи: simplifare, graf, dnf, knf, table\n");
        free(config);
        return NULL;
    }

    return config;
}

void print_help() 
{
    printf("Использование:\n");
    printf("  -f <filename>   Указать входной файл\n");
    printf("  -c <(function)> Указать выражение в скобках в командной строке\n");
    printf("  -t <task>       Выбрать задачу (simplifare, graf, dnf, knf, table)\n");
    printf("  -h <task>       Помощь\n");
}


 