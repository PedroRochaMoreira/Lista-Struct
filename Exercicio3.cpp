#include <stdio.h>

struct Funcionario {
    int codigo;
    char nome[50];
    char cargo[30];
    float salarioBase;
    int horasExtras;
};

float valorHora(float salarioBase) {
    return salarioBase / 160;
}

float valorHorasExtras(float salarioBase, int horasExtras) {
    return valorHora(salarioBase) * 1.5 * horasExtras;
}

float salarioBruto(struct Funcionario f) {
    return f.salarioBase + valorHorasExtras(f.salarioBase, f.horasExtras);
}

float desconto(float bruto) {
    return bruto * 0.10;
}

float salarioLiquido(struct Funcionario f) {
    float bruto = salarioBruto(f);
    return bruto - desconto(bruto);
}

int main() {
    struct Funcionario funcionarios[8];
    int i, quantidade, posicaoMaior = 0;
    float bruto, liquido, maiorLiquido = 0, custoFolha = 0;

    printf("==============================\n");
    printf("   CADASTRO DE FUNCIONARIOS\n");
    printf("==============================\n");

    do {
        printf("Quantos funcionarios deseja cadastrar (1 a 8)? ");
        scanf("%d", &quantidade);
        if (quantidade < 1 || quantidade > 8) {
            printf("Quantidade invalida!\n");
        }
    } while (quantidade < 1 || quantidade > 8);

    for (i = 0; i < quantidade; i++) {
        printf("\n--- Funcionario %d ---\n", i + 1);
        printf("Codigo: ");
        scanf("%d", &funcionarios[i].codigo);
        printf("Nome: ");
        scanf(" %49[^\n]", funcionarios[i].nome);
        printf("Cargo: ");
        scanf(" %29[^\n]", funcionarios[i].cargo);
        printf("Salario base: ");
        scanf("%f", &funcionarios[i].salarioBase);
        printf("Horas extras: ");
        scanf("%d", &funcionarios[i].horasExtras);
    }

    printf("\n==============================\n");
    printf("      FOLHA DE PAGAMENTO\n");
    printf("==============================\n");
    for (i = 0; i < quantidade; i++) {
        bruto = salarioBruto(funcionarios[i]);
        liquido = salarioLiquido(funcionarios[i]);

        printf("\n%d - %s (%s)\n", funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].cargo);
        printf("Valor da hora: R$ %.2f\n", valorHora(funcionarios[i].salarioBase));
        printf("Horas extras: %d = R$ %.2f\n", funcionarios[i].horasExtras,
               valorHorasExtras(funcionarios[i].salarioBase, funcionarios[i].horasExtras));
        printf("Salario bruto: R$ %.2f\n", bruto);
        printf("Desconto (10%%): R$ %.2f\n", desconto(bruto));
        printf("Salario liquido: R$ %.2f\n", liquido);

        if (i == 0 || liquido > maiorLiquido) {
            maiorLiquido = liquido;
            posicaoMaior = i;
        }
        custoFolha = custoFolha + bruto;
    }

    printf("\n------------------------------\n");
    printf("Maior salario liquido: %s (R$ %.2f)\n", funcionarios[posicaoMaior].nome, maiorLiquido);
    printf("Custo total da folha (salarios brutos): R$ %.2f\n", custoFolha);

    return 0;
}
