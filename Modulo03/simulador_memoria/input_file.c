#include "input_file.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "request.h"

#define LINE_MAX 150

void read_input_file()
{
    char line[LINE_MAX];
    FILE *file;
    int line_count = 1;
    file = fopen("config.txt", "r");
    if (file == NULL)
    {
        perror("Erro ao abrir arquivo de entrada!");
        return;
    }
    while (fgets(line, LINE_MAX, file) != NULL)
    {
        *strstr(line, "\n") = '\0';
        int count = 0, number;
        char *process_ID, *ptr, op;
        ptr = strtok(line, " ()\r");
        while (ptr != NULL)
        {
            switch (count)
            {
            case 0:
                process_ID = malloc(strlen(ptr) * sizeof(char) + 1);
                strcpy(process_ID, ptr);
                break;
            case 1:
                op = ptr[0];
                break;
            case 2:
                number = atoi(ptr);
                break;
            }
            count++;
            ptr = strtok(NULL, " ()\r");
        }
        REQUEST *request = malloc(sizeof(REQUEST));
        request->process_ID = process_ID;
        request->op = op;
        request->number = number;
        receive_request(request);
    }
}