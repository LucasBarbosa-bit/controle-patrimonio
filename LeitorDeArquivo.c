#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAXN 1000

int main(){

    FILE *fp;
    char row[MAXN];
    char *token;

    fp = fopen("teste1.csv","r");



    while(fgets(row, MAXN, fp)) {

            token = strtok(row, ",");

            while(token != NULL)
           {
              printf("%s\n", token);
              token = strtok(NULL, ",");
           }
    }


    return 0;
}
