#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAXN 5000 // tamanho maximo de uma linha
#define MAXE 20 //  numero maximo de elementos em cada linha


char row[MAXN];
char *token;
int N_Ent = 0;
char elementos[MAXE][MAXN]; // elementos da primeira linha (nome dos elementos)

int main(){

    FILE *fp;

    fp = fopen("lista.csv","r");


    fgets(row, MAXN, fp);

    token = strtok(row , ",");
    while(token != NULL)
    {
        strcpy(elementos[N_Ent], token);
        N_Ent++;

        token = strtok(NULL, ",");
    }


    while(fgets(row, MAXN, fp)) {

            token = strtok(row, ",");

            int cnt = 0;
            while(token != NULL)
           {
              printf("%s: %s", elementos[cnt++] ,token);
              printf("\n");
              token = strtok(NULL, ",");
           }
    }


    return 0;
}
