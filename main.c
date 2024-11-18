#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 100000

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

// carregar dados do arquivo CSV
void carregarDados(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return;
    }

    // l� o CSV e preenche o inventario
    while (fscanf(file, "%d,%49[^,],%29[^,],%d,%49[^,],%19[^,],%10[^\n]",
                  &inventario[num_itens].codigo,
                  inventario[num_itens].nome,
                  inventario[num_itens].categoria,
                  &inventario[num_itens].quantidade,
                  inventario[num_itens].localizacao,
                  inventario[num_itens].estado,
                  inventario[num_itens].data_aquisicao) == 7) {
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
        printf("O invent�rio est� cheio. N�o � poss�vel adicionar mais itens.\n");
        return;
    }

    Item novo_item;

    printf("=== Cadastro de Novo Item ===\n");
    printf("C�digo do item: ");
    scanf("%d", &novo_item.codigo);

    int i;
    for (i = 0; i < num_itens; i++) {
        if (inventario[i].codigo == novo_item.codigo) {
            printf("Erro: J� existe um item com este c�digo.\n");
            return;
        }
    }

    printf("Nome do item: ");
    scanf(" %[^\n]", novo_item.nome);
    printf("Categoria: ");
    scanf(" %[^\n]", novo_item.categoria);
    printf("Quantidade: ");
    scanf("%d", &novo_item.quantidade);
    printf("Localiza��o: ");
    scanf(" %[^\n]", novo_item.localizacao);
    printf("Estado (funcional/em reparo): ");
    scanf(" %[^\n]", novo_item.estado);
    printf("Data de aquisi��o (YYYY-MM-DD): ");
    scanf(" %[^\n]", novo_item.data_aquisicao);

    // Adiciona o item no invent�rio
    inventario[num_itens] = novo_item;
    num_itens++;

    printf("Item cadastrado com sucesso!\n");
}

// fazar a pesquisa pelos atributos
void buscarItem() {
    int opcao;
    printf("=== Buscar Item ===\n");
    printf("1. Buscar por c�digo\n");
    printf("2. Buscar por categoria\n");
    printf("3. Buscar por localiza��o\n");
    printf("Escolha uma op��o: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            int codigo;
            printf("Digite o c�digo do item: ");
            scanf("%d", &codigo);

            int encontrado = 0;
            int i;
            for (i = 0; i < num_itens; i++) {
                if (inventario[i].codigo == codigo) {
                    printf("Item encontrado:\n");
                    printf("C�digo: %d\nNome: %s\nCategoria: %s\nQuantidade: %d\nLocaliza��o: %s\nEstado: %s\nData de aquisi��o: %s\n",
                           inventario[i].codigo, inventario[i].nome, inventario[i].categoria,
                           inventario[i].quantidade, inventario[i].localizacao, inventario[i].estado,
                           inventario[i].data_aquisicao);
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                printf("Item com c�digo %d n�o encontrado.\n", codigo);
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
                    printf("C�digo: %d, Nome: %s, Quantidade: %d, Localiza��o: %s, Estado: %s\n",
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
            printf("Digite a localiza��o: ");
            scanf(" %[^\n]", localizacao);

            printf("Itens na localiza��o '%s':\n", localizacao);
            int encontrado = 0;
            int i;
            for (i = 0; i < num_itens; i++) {
                if (strcmp(inventario[i].localizacao, localizacao) == 0) {
                    printf("C�digo: %d, Nome: %s, Categoria: %s, Quantidade: %d, Estado: %s\n",
                           inventario[i].codigo, inventario[i].nome, inventario[i].categoria,
                           inventario[i].quantidade, inventario[i].estado);
                    encontrado = 1;
                }
            }
            if (!encontrado) {
                printf("Nenhum item encontrado na localiza��o '%s'.\n", localizacao);
            }
            break;
        }

        default:
            printf("Op��o inv�lida. Tente novamente.\n");
            break;
    }
}

// mostrar relatorios (exibe todos os dados do inventario
void exibirRelatorio() {
    printf("=== Relat�rio de Patrim�nio ===\n");
    printf("%-10s %-20s %-15s %-10s %-20s %-15s %-12s\n",
           "C�digo", "Nome", "Categoria", "Qtd", "Localiza��o", "Estado", "Data");
    printf("----------------------------------------------------------------------------------\n");

    int i;
    for (i = 0; i < num_itens; i++) {
        printf("%-10d %-20s %-15s %-10d %-20s %-15s %-12s\n",
               inventario[i].codigo, inventario[i].nome, inventario[i].categoria,
               inventario[i].quantidade, inventario[i].localizacao, inventario[i].estado,
               inventario[i].data_aquisicao);
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
        printf("4. Salvar e Sair\n");
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
            case 4:
                salvarDados("inventario.csv");
                printf("Dados salvos e programa encerrado.\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (opcao != 4);
}

int main() {
    carregarDados("inventario.csv");
    exibirMenu();
    return 0;
}
