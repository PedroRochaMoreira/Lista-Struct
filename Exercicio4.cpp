#include <stdio.h>

struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int estoque;
};

struct Venda {
    struct Produto produto;
    int quantidade;
    float valorTotal;
};

int buscarProduto(struct Produto produtos[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrarProduto(struct Produto produtos[], int *totalProdutos) {
    int codigo;

    if (*totalProdutos == 10) {
        printf("\nLimite de produtos atingido!\n");
        return;
    }

    printf("\nCodigo: ");
    scanf("%d", &codigo);
    if (buscarProduto(produtos, *totalProdutos, codigo) != -1) {
        printf("Ja existe um produto com esse codigo!\n");
        return;
    }

    produtos[*totalProdutos].codigo = codigo;
    printf("Nome: ");
    scanf(" %49[^\n]", produtos[*totalProdutos].nome);
    printf("Preco: ");
    scanf("%f", &produtos[*totalProdutos].preco);
    printf("Estoque: ");
    scanf("%d", &produtos[*totalProdutos].estoque);

    (*totalProdutos)++;
    printf("Produto cadastrado com sucesso!\n");
}

void listarProdutos(struct Produto produtos[], int totalProdutos) {
    int i;

    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    printf("\n---------- PRODUTOS ----------\n");
    for (i = 0; i < totalProdutos; i++) {
        printf("%d - %s - R$ %.2f - Estoque: %d\n", produtos[i].codigo, produtos[i].nome,
               produtos[i].preco, produtos[i].estoque);
    }
}

void registrarVenda(struct Produto produtos[], int totalProdutos, struct Venda vendas[], int *totalVendas) {
    int codigo, quantidade, posicao;

    if (*totalVendas == 20) {
        printf("\nLimite de vendas atingido!\n");
        return;
    }
    if (totalProdutos == 0) {
        printf("\nCadastre um produto primeiro!\n");
        return;
    }

    printf("\nCodigo do produto: ");
    scanf("%d", &codigo);
    posicao = buscarProduto(produtos, totalProdutos, codigo);
    if (posicao == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    printf("Quantidade: ");
    scanf("%d", &quantidade);
    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }
    if (quantidade > produtos[posicao].estoque) {
        printf("Estoque insuficiente! Disponivel: %d\n", produtos[posicao].estoque);
        return;
    }

    produtos[posicao].estoque = produtos[posicao].estoque - quantidade;

    vendas[*totalVendas].produto = produtos[posicao];
    vendas[*totalVendas].quantidade = quantidade;
    vendas[*totalVendas].valorTotal = produtos[posicao].preco * quantidade;

    printf("Venda registrada! Valor: R$ %.2f\n", vendas[*totalVendas].valorTotal);
    printf("Estoque restante: %d\n", produtos[posicao].estoque);
    (*totalVendas)++;
}

void listarVendas(struct Venda vendas[], int totalVendas) {
    int i;

    if (totalVendas == 0) {
        printf("\nNenhuma venda registrada!\n");
        return;
    }

    printf("\n----------- VENDAS -----------\n");
    for (i = 0; i < totalVendas; i++) {
        printf("Venda %d: %s  %dx  R$ %.2f\n", i + 1, vendas[i].produto.nome,
               vendas[i].quantidade, vendas[i].valorTotal);
    }
}

void faturamento(struct Produto produtos[], int totalProdutos, struct Venda vendas[], int totalVendas) {
    int i, j, posicaoMaior = -1;
    float total = 0, totalProduto, maiorFaturamento = 0;

    if (totalVendas == 0) {
        printf("\nNenhuma venda registrada!\n");
        return;
    }

    for (i = 0; i < totalVendas; i++) {
        total = total + vendas[i].valorTotal;
    }

    printf("\n-------- FATURAMENTO ---------\n");
    for (i = 0; i < totalProdutos; i++) {
        totalProduto = 0;
        for (j = 0; j < totalVendas; j++) {
            if (vendas[j].produto.codigo == produtos[i].codigo) {
                totalProduto = totalProduto + vendas[j].valorTotal;
            }
        }
        printf("%s: R$ %.2f\n", produtos[i].nome, totalProduto);

        if (totalProduto > maiorFaturamento) {
            maiorFaturamento = totalProduto;
            posicaoMaior = i;
        }
    }

    printf("------------------------------\n");
    printf("Faturamento total: R$ %.2f\n", total);
    printf("Produto com maior faturamento: %s (R$ %.2f)\n", produtos[posicaoMaior].nome, maiorFaturamento);
}

int main() {
    struct Produto produtos[10];
    struct Venda vendas[20];
    int totalProdutos = 0, totalVendas = 0;
    int opcao;

    do {
        printf("\n==============================\n");
        printf("       CONTROLE DE VENDAS\n");
        printf("==============================\n");
        printf("  1 - Cadastrar produto\n");
        printf("  2 - Listar produtos\n");
        printf("  3 - Registrar venda\n");
        printf("  4 - Listar vendas\n");
        printf("  5 - Faturamento\n");
        printf("  0 - Sair\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &totalProdutos);
                break;
            case 2:
                listarProdutos(produtos, totalProdutos);
                break;
            case 3:
                registrarVenda(produtos, totalProdutos, vendas, &totalVendas);
                break;
            case 4:
                listarVendas(vendas, totalVendas);
                break;
            case 5:
                faturamento(produtos, totalProdutos, vendas, totalVendas);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
