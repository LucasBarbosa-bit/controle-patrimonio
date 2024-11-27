#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 100000
#define MAX_USERS 20

// tipo de dados itens

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

Item inventario[MAX_ITENS];
int num_itens = 0;

typedef struct {
        char codigo[9];
        int pin;
    }login;

login usuarios[MAX_USERS];
int num_users = 0;

// Limpar Buffer

void limpar_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void users(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r"); // Corrigido para leitura
    if (!file) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return;
    }

    char linha[50]; // Tamanho adequado para uma linha do CSV
    while (fgets(linha, sizeof(linha), file)) {
        if (sscanf(linha, "%8[^;];%d", usuarios[num_users].codigo, &usuarios[num_users].pin) == 2) {
            num_users++;
        }
    }

    fclose(file);
}

int initLogin() {
    char loginUser[9];
    int pin;

    printf("=== Bem-Vindo! ===\n");

    printf("\nDigite seu Login de acesso: ");
    fgets(loginUser, sizeof(loginUser), stdin);
    loginUser[strcspn(loginUser, "\n")] = '\0'; // Remove o '\n'

    printf("Digite sua senha de acesso: ");
    scanf("%d", &pin);
    limpar_buffer(); // Corrige possíveis problemas de buffer

    // Verifica credenciais
    int i;
    for (i = 0; i < num_users; i++) {
        if (strcmp(loginUser, usuarios[i].codigo) == 0 && pin == usuarios[i].pin) {
            printf("Login Bem-sucedido!\n");
            exibirMenu();
            return 1; // Login bem-sucedido
        }
    }

    // Caso falhe
    printf("Login ou senha invalidos.\n");
    return 0;
}

// Funcao para carregar dados do arquivo CSV
void carregarDados(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo CSV: %s\n",nomeArquivo);
        return;
    }

    // Le o CSV e preenche o inventario
    int i = 0;
    while (fscanf(file, "%29[^;];%29[^;];%29[^;];%49[^;];%d;%29[^;];%29[^;];%19[^\n]",
                  inventario[i].tipo,
                  inventario[i].marca,
                  inventario[i].modelo,
                  inventario[i].descricao,
                  &inventario[i].novo,
                  inventario[i].num_serie,
                  inventario[i].num_patrimonio,
                  inventario[i].alocacao,
                  inventario[i].status) == 9) {  // 9 e o numero de propriedades na struct
        i++;
        if (i >= MAX_ITENS) {
            break;  // Evita ultrapassar o limite de itens
        }
    }
    num_itens = i;  // Atualiza o numero de itens lidos

    fclose(file);
}

// Funcao para salvar os dados no arquivo CSV
void salvarDados(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo CSV para escrita.\n");
        return;
    }

    int i;
    for (i = 0; i < num_itens; i++) {
        fprintf(file, "%s;%s;%s;%s;%d;%s;%s;%s;%s\n",
                inventario[i].tipo,
                inventario[i].marca,
                inventario[i].modelo,
                inventario[i].descricao,
                inventario[i].novo,
                inventario[i].num_serie,
                inventario[i].num_patrimonio,
                inventario[i].alocacao,
                inventario[i].status);
    }

    fclose(file);
}

// Funcao para cadastrar novos itens
void cadastrarItem() {
    if (num_itens >= MAX_ITENS) {
        printf("O inventario esta cheio. Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo_item;

    printf("=== Cadastro de Novo Item ===\n");
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo_item.tipo);
    printf("Marca: ");
    scanf(" %[^\n]", novo_item.marca);
    printf("Modelo: ");
    scanf(" %[^\n]", novo_item.modelo);
    printf("Descricao: ");
    scanf(" %[^\n]", novo_item.descricao);
    printf("E novo (1 para sim, 0 para nao): ");
    scanf("%d", &novo_item.novo);
    printf("Numero de serie: ");
    scanf(" %[^\n]", novo_item.num_serie);
    printf("Numero de patrimonio: ");
    scanf(" %[^\n]", novo_item.num_patrimonio);
    printf("Alocacao: ");
    scanf(" %[^\n]", novo_item.alocacao);
    printf("Status: ");
    scanf(" %[^\n]", novo_item.status);

    // Adiciona o item no inventario
    inventario[num_itens] = novo_item;
    num_itens++;

    printf("\nItem cadastrado com sucesso!\n");
}

// fazar a pesquisa pelos atributos
void buscarItem() {
    int opcao;
    printf("=== Buscar Item ===\n");
    printf("1. Buscar por codigo\n");
    printf("2. Buscar por categoria\n");
    printf("3. Buscar por localizacao\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            int codigo;
            printf("Digite o codigo do item: ");
            scanf("%d", &codigo);

            printf("\nItem(s) encontrado(s):\n");

            printf("%-10s %-20s %-15s %-10s %-20s %-15s %-12s\n",
           "Codigo", "Nome", "Categoria", "Qtd", "Localizacao", "Estado", "Data");

            printf("---------------------------------------------------------------"
           "------------------------------------------------------\n");

            int encontrado = 0;
            int i;
            for (i = 0; i < num_itens; i++) {
                if (strcmp(inventario[i].num_patrimonio,codigo) == 0) {
                    printf("%-10d %-20s %-15s %-10d %-20s %-15s %-12s\n",
                    inventario[i].tipo, inventario[i].marca, inventario[i].modelo, inventario[i].descricao,
                    inventario[i].novo, inventario[i].num_serie, inventario[i].num_patrimonio,
                    inventario[i].alocacao, inventario[i].status);
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                printf("Item com codigo %d nao encontrado.\n", codigo);
            }
            break;
        }

        case 2: {
            char categoria[30];
            printf("Digite a categoria: ");
            scanf(" %[^\n]", categoria);

            printf("Itens na categoria '%s':\n", categoria);

            printf("%-10s %-20s %-15s %-10s %-20s %-15s %-12s\n",
           "Codigo", "Nome", "Categoria", "Qtd", "Localizacao", "Estado", "Data");

            printf("---------------------------------------------------------------"
           "------------------------------------------------------\n");

            int encontrado = 0;
            int i;
            for (i = 0; i < num_itens; i++) {
                if (strcmp(inventario[i].tipo, categoria) == 0) {
                    printf("%-10d %-20s %-15s %-10d %-20s %-15s %-12s\n",
                    inventario[i].tipo, inventario[i].marca, inventario[i].modelo, inventario[i].descricao,
                    inventario[i].novo, inventario[i].num_serie, inventario[i].num_patrimonio,
                    inventario[i].alocacao, inventario[i].status);
                    encontrado = 1;
                }
            }
            if (!encontrado) {
                printf("Nenhum item encontrado na categoria '%s'.\n", categoria);
            }
            break;
        }

        case 3: {
            char localizacao[50];
            printf("Digite a localizacao: ");
            scanf(" %[^\n]", localizacao);

            printf("Itens na localizacao '%s':\n", localizacao);

            printf("%-10s %-20s %-15s %-10s %-20s %-15s %-12s\n",
           "Codigo", "Nome", "Categoria", "Qtd", "Localizacao", "Estado", "Data");

            printf("---------------------------------------------------------------"
           "------------------------------------------------------\n");

            int encontrado = 0;
            int i;
            for (i = 0; i < num_itens; i++) {
                if (strcmp(inventario[i].alocacao, localizacao) == 0) {
                     printf("%-10d %-20s %-15s %-10d %-20s %-15s %-12s\n",
                    inventario[i].tipo, inventario[i].marca, inventario[i].modelo, inventario[i].descricao,
                    inventario[i].novo, inventario[i].num_serie, inventario[i].num_patrimonio,
                    inventario[i].alocacao, inventario[i].status);
                    encontrado = 1;
                }
            }
            if (!encontrado) {
                printf("Nenhum item encontrado na localização '%s'.\n", localizacao);
            }
            break;
        }

        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
    }
}

// Funcao para exibir o relatorio de itens
void exibirRelatorio() {
    printf("\n=== Relatorio de Patrimonio ===\n");
    printf("%-10s %-20s %-15s %-10s %-20s %-15s %-12s\n",
           "Codigo", "Nome", "Categoria", "Qtd", "Localizacao", "Estado", "Data");
    printf("---------------------------------------------------------------"
           "------------------------------------------------------\n");

    int i;
    for (i = 0; i < num_itens; i++) {
        printf("%-10d %-20s %-15s %-10d %-20s %-15s %-12s\n",
               inventario[i].tipo, inventario[i].marca, inventario[i].modelo, inventario[i].descricao,
               inventario[i].novo, inventario[i].num_serie, inventario[i].num_patrimonio,
               inventario[i].alocacao, inventario[i].status);
    }
}

void alterarItem() {
    char num_serie[30];
    int i, encontrado = 0;

    printf("Digite o numero de serie do item que voce deseja alterar: ");
    scanf(" %[^\n]", num_serie);

    for (i = 0; i < num_itens; i++) {
        if (strcmp(inventario[i].num_serie, num_serie) == 0) {
            encontrado = 1;
            printf("Item encontrado. Insira os novos dados:\n");
            printf("Tipo do item: ");
            scanf(" %[^\n]", inventario[i].tipo);
            printf("Marca: ");
            scanf(" %[^\n]", inventario[i].marca);
            printf("Modelo: ");
            scanf(" %[^\n]", inventario[i].modelo);
            printf("Descricao: ");
            scanf(" %[^\n]", inventario[i].descricao);
            printf("E novo (1 para sim, 0 para nao): ");
            scanf("%d", &inventario[i].novo);
            printf("Numero de serie: ");
            scanf(" %[^\n]", inventario[i].num_serie);
            printf("Numero de patrimonio: ");
            scanf(" %[^\n]", inventario[i].num_patrimonio);
            printf("Alocacao: ");
            scanf(" %[^\n]", inventario[i].alocacao);
            printf("Status: ");
            scanf(" %[^\n]", inventario[i].status);

            printf("Item alterado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Item com numero de serie %s nao encontrado.\n", num_serie);
    }
}

// menu inicial (provisorio -  implementar GUI)
void exibirMenu() {
    int opcao;

    do {
        printf("\n=== GESTAO DE PATRIMONIOS ===\n");
        printf("1. Cadastrar Novo Item\n");
        printf("2. Buscar Item\n");
        printf("3. Exibir Relatorio\n");
        printf("4. Alterar Item\n");
        printf("5. Salvar e Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarItem();
                break;
            case 2:
                buscarItem();
                break;
            case 3:
                exibirRelatorio();
                break;
            case 5:
                salvarDados("inventario.csv");
                printf("Dados salvos e programa encerrado.\n");
                break;
            case 4:
                alterarItem();
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    } while (opcao != 5);
}

int main() {
    carregarDados("inventario.csv");
    users("cadUsers.csv");

    int login_sucesso;
    do {
            login_sucesso = initLogin();
            limpar_buffer();

    } while(login_sucesso == 0);

    return 0;
}
