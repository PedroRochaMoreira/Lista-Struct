#include <stdio.h>

struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
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

void cadastrar(struct Produto produtos[], int *total) {
    int codigo;

    if (*total == 15) {
        printf("\nCadastro cheio!\n");
        return;
    }

    printf("\nCodigo: ");
    scanf("%d", &codigo);

    if (buscarProduto(produtos, *total, codigo) != -1) {
        printf("Ja existe um produto com esse codigo!\n");
        return;
    }

    produtos[*total].codigo = codigo;
    printf("Nome: ");
    scanf(" %49[^\n]", produtos[*total].nome);
    printf("Preco: ");
    scanf("%f", &produtos[*total].preco);
    printf("Quantidade em estoque: ");
    scanf("%d", &produtos[*total].quantidade);

    (*total)++;
    printf("Produto cadastrado com sucesso!\n");
}

void listar(struct Produto produtos[], int total) {
    int i;

    if (total == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    printf("\n---------- PRODUTOS ----------\n");
    for (i = 0; i < total; i++) {
        printf("%d - %s - R$ %.2f - Estoque: %d\n", produtos[i].codigo, produtos[i].nome,
               produtos[i].preco, produtos[i].quantidade);
    }
}

void adicionarEstoque(struct Produto *produto, int quantidade) {
    produto->quantidade = produto->quantidade + quantidade;
}

int retirarEstoque(struct Produto *produto, int quantidade) {
    if (quantidade > produto->quantidade) {
        return 0;
    }
    produto->quantidade = produto->quantidade - quantidade;
    return 1;
}

void reporEstoque(struct Produto produtos[], int total) {
    int codigo, quantidade, posicao;

    printf("\nCodigo do produto: ");
    scanf("%d", &codigo);
    posicao = buscarProduto(produtos, total, codigo);
    if (posicao == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    printf("Quantidade para repor: ");
    scanf("%d", &quantidade);
    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    adicionarEstoque(&produtos[posicao], quantidade);
    printf("Estoque atualizado! %s agora tem %d unidades.\n", produtos[posicao].nome, produtos[posicao].quantidade);
}

void registrarVenda(struct Produto produtos[], int total) {
    int codigo, quantidade, posicao;

    printf("\nCodigo do produto: ");
    scanf("%d", &codigo);
    posicao = buscarProduto(produtos, total, codigo);
    if (posicao == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    printf("Quantidade vendida: ");
    scanf("%d", &quantidade);
    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    if (retirarEstoque(&produtos[posicao], quantidade) == 0) {
        printf("Estoque insuficiente! Disponivel: %d\n", produtos[posicao].quantidade);
        return;
    }

    printf("Venda registrada! Valor: R$ %.2f\n", produtos[posicao].preco * quantidade);
    printf("Estoque restante: %d\n", produtos[posicao].quantidade);
}

void consultar(struct Produto produtos[], int total) {
    int codigo, posicao;

    printf("\nCodigo do produto: ");
    scanf("%d", &codigo);
    posicao = buscarProduto(produtos, total, codigo);
    if (posicao == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    printf("Codigo: %d\n", produtos[posicao].codigo);
    printf("Nome: %s\n", produtos[posicao].nome);
    printf("Preco: R$ %.2f\n", produtos[posicao].preco);
    printf("Estoque: %d\n", produtos[posicao].quantidade);
}

void relatorio(struct Produto produtos[], int total) {
    int i, posicaoMaior = 0;
    float valorProduto, valorTotal = 0, maiorValor = 0;

    if (total == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    printf("\n---------- ESTOQUE -----------\n");
    for (i = 0; i < total; i++) {
        valorProduto = produtos[i].preco * produtos[i].quantidade;
        printf("%s: %d x R$ %.2f = R$ %.2f\n", produtos[i].nome, produtos[i].quantidade,
               produtos[i].preco, valorProduto);

        valorTotal = valorTotal + valorProduto;

        if (i == 0 || valorProduto > maiorValor) {
            maiorValor = valorProduto;
            posicaoMaior = i;
        }
    }
    printf("------------------------------\n");
    printf("Valor total em estoque: R$ %.2f\n", valorTotal);
    printf("Produto com maior valor em estoque: %s (R$ %.2f)\n", produtos[posicaoMaior].nome, maiorValor);
}

int main() {
    struct Produto produtos[15];
    int total = 0;
    int opcao;

    do {
        printf("\n==============================\n");
        printf("          PAPELARIA\n");
        printf("==============================\n");
        printf("  1 - Cadastrar produto\n");
        printf("  2 - Listar produtos\n");
        printf("  3 - Repor estoque\n");
        printf("  4 - Registrar venda\n");
        printf("  5 - Consultar produto\n");
        printf("  6 - Relatorio do estoque\n");
        printf("  0 - Sair\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar(produtos, &total);
                break;
            case 2:
                listar(produtos, total);
                break;
            case 3:
                reporEstoque(produtos, total);
                break;
            case 4:
                registrarVenda(produtos, total);
                break;
            case 5:
                consultar(produtos, total);
                break;
            case 6:
                relatorio(produtos, total);
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
