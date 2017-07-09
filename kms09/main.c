#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char name[50];
    char dob[50];
    char day[50];
} delegate;

bool readFile(char* name, delegate* de[643]);
void freeMemory(delegate* de[643]);

int main()
{
    delegate* del[643];
    if (readFile("kms_ex09_bundestagsabgeordnete.csv", del))
    {
        for(int i = 0; i < 100; i++)
        {
            printf("%s,%s,%s\n", del[i]->name, del[i]->dob, del[i]->day);
        }
        freeMemory(del);
    }
    return 0;
}

bool readFile(char* name, delegate* de[643])
{
    FILE* fp = fopen(name, "r");
    if(fp != NULL)
    {
        char buff[100];
        if (fgets(buff, 99, fp) == NULL);
        for(int i = 0; i < 643; i++)
        {
            if(fgets(buff, 99, fp) != NULL)
            {
                delegate* d = malloc(sizeof(delegate));
                strcpy(d->name, strtok(buff, ","));
                strcpy(d->dob, strtok(NULL, ","));
                strcpy(d->day, strtok(NULL, ","));
                de[i] = d;
                //printf("%s,%s,%s\n", d->name, d->dob, d->day);
            }
        }
        fclose(fp);
        return true;
    }
    else
        return false;
}

void freeMemory(delegate* de[643])
{
    for(int i = 0; i < 643; i++)
        free(de[i]);
}
