#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ITENS 100000
#define MAX_USERS 20


char *nomeArquivoUSR = "cadUsers.csv";
char *nomeArquivoPlanilha = "items.csv";

typedef struct {
    char codigo[9];
    int pin;
} login;

login usuarios[MAX_USERS];
int num_users = 0;

typedef struct {
    char tipo[30];
    char marca[30];
    char modelo[30];
    char descricao[50];
    int novo;  // Usado para indicar se e novo (1) ou usado (0)
    char num_serie[30];
    char num_patrimonio[30];
    char alocacao[30];
    char status[20];  // "Funcionando", "Em reparo", etc.
} Item;

char filtros[9][50] =  {
    "",
    "",
    "",
    "",
    "todo", // n faz nada por enquanto (Novo)
    "",
    "",
    "",
    ""
};

Item inventario[MAX_ITENS];
int num_itens = 0;
GtkWidget* Linhas[MAX_ITENS];

void limpar_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//ele preenche o vetor usuarios
void reg_users(){

    FILE *file = fopen(nomeArquivoUSR, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return;
    }

    while (fscanf(file, "%8[^;];%d", usuarios[num_users].codigo, &usuarios[num_users].pin) == 2) {
        num_users++;
    }

    fclose(file);
}

int initLogin(const char loginUser[9],const int pin)
 {

    // Verifica credenciais
    for (int i = 0; i < num_users; i++) {
        if (strcmp(loginUser, usuarios[i].codigo) == 0 && pin == usuarios[i].pin) {
            return 1; // Login bem-sucedido
        }
    }
    // Caso falhe
    return 0;
}



const char* pegarValorStruct(int x, int p){
    switch(p){
        case 1: return inventario[x].tipo; break;
        case 2: return inventario[x].marca; break;
        case 3: return inventario[x].modelo; break;
        case 4: return inventario[x].descricao; break;
        case 5:
        int value = inventario[x].novo;
        if(value == 1){
            return "Verdadeiro";
        } else {
            return "Falso";
        }
        break;
        case 6: return inventario[x].num_serie; break;
        case 7: return inventario[x].num_patrimonio; break;
        case 8: return inventario[x].alocacao; break;
        case 9: return inventario[x].status; break;
    }
}

const int tamanhos[9] = {


    100, // tipo
    80, // marca
    160, // modelo
    120, // desc
    80, // novo
    250, // N. Serie
    250, // N. Pat
    120, // Aloc
    120 // Status
}; // soma = 1280

void remove_line_ending(char *str) {
    if (str != NULL && (str[0] == '\n' || str[0] == '\r')) {
        memmove(str, str + 1, strlen(str));
    }
}

GtkWidget* criar_linha(int x){
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(box, 1280, 40);
    gtk_container_add(GTK_CONTAINER(row), box);

    for (int i = 0; i < 9; i++) {
        const char *texto = pegarValorStruct(x, i+1);
        GtkWidget *label = gtk_label_new(texto);
        gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
        gtk_widget_set_size_request(label, tamanhos[i], 40);  //
        gtk_widget_show(label);
    }
    gtk_widget_show(box);
    gtk_widget_show(row);
    gtk_list_box_insert(GTK_LIST_BOX(Planilha), row, -1);
    return row;
}

void carregarDados(const char *nomeArquivo) {


    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo CSV: %s\n",nomeArquivo);
        return;
    }

    // Le o CSV e preenche o inventario
    int i = 0;
    while (fscanf(file, "%29[^;];%29[^;];%29[^;];%49[^;];%d;%29[^;];%29[^;];%29[^;];%19[^\n]",
                  inventario[i].tipo,
                  inventario[i].marca,
                  inventario[i].modelo,
                  inventario[i].descricao,
                  &inventario[i].novo,
                  inventario[i].num_serie,
                  inventario[i].num_patrimonio,
                  inventario[i].alocacao,
                  inventario[i].status) == 9) {  // 9 e o numero de propriedades na struct
                      Linhas[i] = criar_linha(i);
                      remove_line_ending(inventario[i].tipo);
                      i++;

        if (i >= MAX_ITENS) {
            break;  // Evita ultrapassar o limite de itens
        }
    }
    num_itens = i;  // Atualiza o numero de itens lidos

    fclose(file);
}

int checarLinha(int x){
    for(int i = 0; i < 9; i++){
        if(i!=4){
            char *flt = filtros[i];
            if(strncmp(flt, pegarValorStruct(x, i+1), strlen(flt))!=0) return 0;
        }
    }
    return 1;
}

void aplicarFiltros(){
    for(int i = 0; i < num_itens; i++){
        if(checarLinha(i)==0){
            gtk_widget_hide(Linhas[i]);
        }  else {
            gtk_widget_show(Linhas[i]);
        }
    }
    return;
}

