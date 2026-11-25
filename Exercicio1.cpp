#include <stdio.h>

struct Aluno {
    int matricula;
    char nome[50];
    float nota1;
    float nota2;
    float media;
};

float calcularMedia(float nota1, float nota2) {
    return (nota1 + nota2) / 2;
}

int main() {
    struct Aluno alunos[10];
    int i, posicaoMaior = 0, posicaoMenor = 0, acimaDaMedia = 0;
    float soma = 0, mediaGeral;

    printf("==============================\n");
    printf("      CADASTRO DE ALUNOS\n");
    printf("==============================\n");

    for (i = 0; i < 10; i++) {
        printf("\n--- Aluno %d ---\n", i + 1);
        printf("Matricula: ");
        scanf("%d", &alunos[i].matricula);
        printf("Nome: ");
        scanf(" %49[^\n]", alunos[i].nome);
        printf("Nota 1: ");
        scanf("%f", &alunos[i].nota1);
        printf("Nota 2: ");
        scanf("%f", &alunos[i].nota2);

        alunos[i].media = calcularMedia(alunos[i].nota1, alunos[i].nota2);
        soma = soma + alunos[i].media;
    }

    printf("\n==============================\n");
    printf("     SITUACAO DOS ALUNOS\n");
    printf("==============================\n");
    for (i = 0; i < 10; i++) {
        printf("%d - %s - Media: %.2f - ", alunos[i].matricula, alunos[i].nome, alunos[i].media);
        if (alunos[i].media >= 6.0) {
            printf("Aprovado\n");
        } else {
            printf("Reprovado\n");
        }
    }

    for (i = 1; i < 10; i++) {
        if (alunos[i].media > alunos[posicaoMaior].media) {
            posicaoMaior = i;
        }
        if (alunos[i].media < alunos[posicaoMenor].media) {
            posicaoMenor = i;
        }
    }

    mediaGeral = soma / 10;

    for (i = 0; i < 10; i++) {
        if (alunos[i].media > mediaGeral) {
            acimaDaMedia++;
        }
    }

    printf("------------------------------\n");
    printf("Maior media: %s (%.2f)\n", alunos[posicaoMaior].nome, alunos[posicaoMaior].media);
    printf("Menor media: %s (%.2f)\n", alunos[posicaoMenor].nome, alunos[posicaoMenor].media);
    printf("Media geral da turma: %.2f\n", mediaGeral);
    printf("Alunos acima da media geral: %d\n", acimaDaMedia);

    return 0;
}
