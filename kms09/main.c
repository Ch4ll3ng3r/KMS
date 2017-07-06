#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* dob;
    char* day;
} delegate;

int main()
{
    delegate* del[50];
    FILE* fp = fopen("kms_ex09_bundestagsabgeordnete.csv", "r");
    if(fp != NULL)
    {
        char buff[100];
        if (fgets(buff, 100, fp) == NULL);
        for(int i = 0; i < 50; i++)
        {
            if(fgets(buff, 100, fp) != NULL)
            {
                delegate* d = malloc(sizeof(delegate));
                d->name = strtok(buff, ",");
                d->dob = strtok(NULL, ",");
                d->day = strtok(NULL, ",");
                del[i] = d;
                //printf("%s,%s,%s\n", d->name, d->dob, d->day);
            }
        }
        fclose(fp);
        printf("%s,%s,%s\n", del[44]->name, del[44]->dob, del[44]->day);
        for(int i = 0; i < 50; i++)
            free(del[i]);
    }
    return 0;
}
