#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 100000
#define MAX_USERS 20

// tipo de dados itens

typedef struct {
    int codigo;
    char nome[50];
    char categoria[30];
    int quantidade;
    char localizacao[50];
    char estado[20];
    char data_aquisicao[11];  // "DD-MM-AAAA"
} Item;

Item inventario[MAX_ITENS];
int num_itens = 0;

typedef struct {
        char codigo[9];
        int pin;
    }login;

login usuarios[MAX_USERS];
int num_users = 0;

//ele preenche o vetor usuarios
void users(const char *nomeArquivo){

    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return;
    }

    while (fscanf(file, "%8[^;];%d", usuarios[num_users].codigo, &usuarios[num_users].pin) == 2) {
        num_users++;
    }

    fclose(file);
}

int initLogin() {
    char loginUser[9];
    int pin;

    printf("=== Bem-Vindo! ===\n");

    printf("\nDigite seu Login de acesso: ");
    fgets(loginUser, sizeof(loginUser), stdin);
    loginUser[strcspn(loginUser, "\n")] = '\0'; // Remove o '\n' ao final da entrada

    printf("Digite sua senha de acesso: ");
    scanf("%d", &pin);

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

// carregar dados do arquivo CSV
void carregarDados(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return;
    }

    // lê o CSV e preenche o inventario
    while (fscanf(file, "%d,%49[^;],%29[^;],%d,%49[^;],%19[^;],%10[^\n]",
                  &inventario[num_itens].codigo,
                  inventario[num_itens].nome,
                  inventario[num_itens].categoria,
                  &inventario[num_itens].quantidade,
                  inventario[num_itens].localizacao,
                  inventario[num_itens].estado,
                  inventario[num_itens].data_aquisicao) == 7) { // 7 é numero de propiedades no struct
        num_itens++;
    }

    fclose(file);
}

// salva os dados no arquivo
void salvarDados(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo CSV para escrita.\n");
        return;
    }

    int i;
    for (i = 0; i < num_itens; i++) {
        fprintf(file, "%d,%s,%s,%d,%s,%s,%s\n",
                inventario[i].codigo,
                inventario[i].nome,
                inventario[i].categoria,
                inventario[i].quantidade,
                inventario[i].localizacao,
                inventario[i].estado,
                inventario[i].data_aquisicao);
    }

    fclose(file);
}

// para cadastrar novos itens
void cadastrarItem() {
    if (num_itens >= MAX_ITENS) {
        printf("O inventario esta cheio. Não eh possivel adicionar mais itens.\n");
        return;
    }

    Item novo_item;

    printf("=== Cadastro de Novo Item ===\n");
    printf("Codigo do item: ");
    scanf("%d", &novo_item.codigo);

    int i;
    for (i = 0; i < num_itens; i++) {
        if (inventario[i].codigo == novo_item.codigo) {
            printf("Erro: Ja existe um item com este codigo.\n");
            return;
        }
    }

    printf("Nome do item: ");
    scanf(" %[^\n]", novo_item.nome);
    printf("Categoria: ");
    scanf(" %[^\n]", novo_item.categoria);
    printf("Quantidade: ");
    scanf("%d", &novo_item.quantidade);
    printf("Localizacao: ");
    scanf(" %[^\n]", novo_item.localizacao);
    printf("Estado (funcional/em reparo): ");
    scanf(" %[^\n]", novo_item.estado);
    printf("Data de aquisicao (YYYY-MM-DD): ");
    scanf(" %[^\n]", novo_item.data_aquisicao);

    // Adiciona o item no inventário
    inventario[num_itens] = novo_item;
    num_itens++;

    printf("Item cadastrado com sucesso!\n");
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

            int encontrado = 0;
            int i;
            for (i = 0; i < num_itens; i++) {
                if (inventario[i].codigo == codigo) {
                    printf("Item encontrado:\n");
                    printf("Codigo: %d\nNome: %s\nCategoria: %s\nQuantidade: %d\nLocalizacao: %s\nEstado: %s\nData de aquisição: %s\n",
                           inventario[i].codigo, inventario[i].nome, inventario[i].categoria,
                           inventario[i].quantidade, inventario[i].localizacao, inventario[i].estado,
                           inventario[i].data_aquisicao);
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
            int encontrado = 0;
            int i;
            for (i = 0; i < num_itens; i++) {
                if (strcmp(inventario[i].categoria, categoria) == 0) {
                    printf("Codigo: %d, Nome: %s, Quantidade: %d, Localizacao: %s, Estado: %s\n",
                           inventario[i].codigo, inventario[i].nome, inventario[i].quantidade,
                           inventario[i].localizacao, inventario[i].estado);
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
            int encontrado = 0;
            int i;
            for (i = 0; i < num_itens; i++) {
                if (strcmp(inventario[i].localizacao, localizacao) == 0) {
                    printf("Codigo: %d, Nome: %s, Categoria: %s, Quantidade: %d, Estado: %s\n",
                           inventario[i].codigo, inventario[i].nome, inventario[i].categoria,
                           inventario[i].quantidade, inventario[i].estado);
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

// mostrar relatorios (exibe todos os dados do inventario
void exibirRelatorio() {
    printf("\n=== Relatorio de Patrimonio ===\n");
    printf("%-10s %-20s %-15s %-10s %-20s %-15s %-12s\n",
           "Codigo", "Nome", "Categoria", "Qtd", "Localizacao", "Estado", "Data");
    printf("----------------------------------------------------------------------------------\n");

    int i;
    for (i = 0; i < num_itens; i++) {
        printf("%-10d %-20s %-15s %-10d %-20s %-15s %-12s\n",
               inventario[i].codigo, inventario[i].nome, inventario[i].categoria,
               inventario[i].quantidade, inventario[i].localizacao, inventario[i].estado,
               inventario[i].data_aquisicao);
    }
}

void alterarItem(){
    int codigo;
    printf("Digite o codigo do item que voce deseja alterar: ");
            scanf("%d", &codigo);

            int a = 0;
            int i;
            for (i = 0; i < num_itens; i++) {
                if (inventario[i].codigo == codigo) {

                    a = 1;
                    printf("Nome do item: ");
                    scanf(" %[^\n]", inventario[i].nome);
                    printf("Categoria: ");
                    scanf(" %[^\n]", inventario[i].categoria);
                    printf("Quantidade: ");
                    scanf("%d", &inventario[i].quantidade);
                    printf("Localizacao: ");
                    scanf(" %[^\n]", inventario[i].localizacao);
                    printf("Estado (funcional/em reparo): ");
                    scanf(" %[^\n]", inventario[i].estado);
                    printf("Data de aquisicao (YYYY-MM-DD): ");
                    scanf(" %[^\n]", inventario[i].data_aquisicao);

                    printf("Item Alterado: \n");
                    printf("Codigo: %d\nNome: %s\nCategoria: %s\nQuantidade: %d\nLocalizacao: %s\nEstado: %s\nData de aquisição: %s\n",
                           inventario[i].codigo, inventario[i].nome, inventario[i].categoria,
                           inventario[i].quantidade, inventario[i].localizacao, inventario[i].estado,
                           inventario[i].data_aquisicao);
                }
            }

    if (!a) {
    printf("Item com codigo %d não encontrado.\n", codigo);
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

    } while(login_sucesso == 0);

    return 0;
}
