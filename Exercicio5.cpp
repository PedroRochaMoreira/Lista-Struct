#include <stdio.h>

struct Data {
    int dia;
    int mes;
    int ano;
};

struct Paciente {
    int codigo;
    char nome[50];
    int idade;
    char telefone[20];
};

struct Consulta {
    struct Paciente paciente;
    struct Data data;
    char descricao[100];
};

int buscarPaciente(struct Paciente pacientes[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (pacientes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

struct Data lerData() {
    struct Data d;
    do {
        printf("Data (dd mm aaaa): ");
        scanf("%d %d %d", &d.dia, &d.mes, &d.ano);
        if (d.dia < 1 || d.dia > 31 || d.mes < 1 || d.mes > 12) {
            printf("Data invalida!\n");
        }
    } while (d.dia < 1 || d.dia > 31 || d.mes < 1 || d.mes > 12);
    return d;
}

int datasIguais(struct Data a, struct Data b) {
    return a.dia == b.dia && a.mes == b.mes && a.ano == b.ano;
}

int contarConsultas(struct Consulta consultas[], int totalConsultas, int codigo) {
    int i, contador = 0;
    for (i = 0; i < totalConsultas; i++) {
        if (consultas[i].paciente.codigo == codigo) {
            contador++;
        }
    }
    return contador;
}

void cadastrarPaciente(struct Paciente pacientes[], int *totalPacientes) {
    int codigo;

    if (*totalPacientes == 15) {
        printf("\nLimite de pacientes atingido!\n");
        return;
    }

    printf("\nCodigo: ");
    scanf("%d", &codigo);
    if (buscarPaciente(pacientes, *totalPacientes, codigo) != -1) {
        printf("Ja existe um paciente com esse codigo!\n");
        return;
    }

    pacientes[*totalPacientes].codigo = codigo;
    printf("Nome: ");
    scanf(" %49[^\n]", pacientes[*totalPacientes].nome);
    printf("Idade: ");
    scanf("%d", &pacientes[*totalPacientes].idade);
    printf("Telefone: ");
    scanf(" %19[^\n]", pacientes[*totalPacientes].telefone);

    (*totalPacientes)++;
    printf("Paciente cadastrado com sucesso!\n");
}

void registrarConsulta(struct Paciente pacientes[], int totalPacientes, struct Consulta consultas[], int *totalConsultas) {
    int codigo, posicao;

    if (*totalConsultas == 30) {
        printf("\nLimite de consultas atingido!\n");
        return;
    }
    if (totalPacientes == 0) {
        printf("\nCadastre um paciente primeiro!\n");
        return;
    }

    printf("\nCodigo do paciente: ");
    scanf("%d", &codigo);
    posicao = buscarPaciente(pacientes, totalPacientes, codigo);
    if (posicao == -1) {
        printf("Paciente nao encontrado!\n");
        return;
    }

    consultas[*totalConsultas].paciente = pacientes[posicao];
    consultas[*totalConsultas].data = lerData();
    printf("Descricao do atendimento: ");
    scanf(" %99[^\n]", consultas[*totalConsultas].descricao);

    (*totalConsultas)++;
    printf("Consulta registrada com sucesso!\n");
}

void consultasPorPaciente(struct Consulta consultas[], int totalConsultas) {
    int i, codigo, encontrou = 0;

    printf("\nCodigo do paciente: ");
    scanf("%d", &codigo);

    for (i = 0; i < totalConsultas; i++) {
        if (consultas[i].paciente.codigo == codigo) {
            if (encontrou == 0) {
                printf("\nConsultas de %s:\n", consultas[i].paciente.nome);
            }
            printf("%02d/%02d/%04d - %s\n", consultas[i].data.dia, consultas[i].data.mes,
                   consultas[i].data.ano, consultas[i].descricao);
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhuma consulta encontrada para esse codigo!\n");
    }
}

void consultasPorData(struct Consulta consultas[], int totalConsultas) {
    int i, encontrou = 0;
    struct Data data;

    printf("\n");
    data = lerData();

    for (i = 0; i < totalConsultas; i++) {
        if (datasIguais(consultas[i].data, data)) {
            printf("%s - %s\n", consultas[i].paciente.nome, consultas[i].descricao);
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhuma consulta nessa data!\n");
    }
}

void totalPorPaciente(struct Paciente pacientes[], int totalPacientes, struct Consulta consultas[], int totalConsultas) {
    int i;

    if (totalPacientes == 0) {
        printf("\nNenhum paciente cadastrado!\n");
        return;
    }

    printf("\n---- CONSULTAS POR PACIENTE ----\n");
    for (i = 0; i < totalPacientes; i++) {
        printf("%d - %s: %d consulta(s)\n", pacientes[i].codigo, pacientes[i].nome,
               contarConsultas(consultas, totalConsultas, pacientes[i].codigo));
    }
}

void pacienteMaisAtendido(struct Paciente pacientes[], int totalPacientes, struct Consulta consultas[], int totalConsultas) {
    int i, quantidade, maior = 0, posicaoMaior = -1;

    for (i = 0; i < totalPacientes; i++) {
        quantidade = contarConsultas(consultas, totalConsultas, pacientes[i].codigo);
        if (quantidade > maior) {
            maior = quantidade;
            posicaoMaior = i;
        }
    }

    if (posicaoMaior == -1) {
        printf("\nNenhuma consulta registrada!\n");
        return;
    }

    printf("\nPaciente com mais atendimentos: %s (%d consulta(s))\n", pacientes[posicaoMaior].nome, maior);
}

int main() {
    struct Paciente pacientes[15];
    struct Consulta consultas[30];
    int totalPacientes = 0, totalConsultas = 0;
    int opcao;

    do {
        printf("\n==============================\n");
        printf("       CLINICA - CONSULTAS\n");
        printf("==============================\n");
        printf("  1 - Cadastrar paciente\n");
        printf("  2 - Registrar consulta\n");
        printf("  3 - Pesquisar consultas por paciente\n");
        printf("  4 - Listar consultas por data\n");
        printf("  5 - Consultas por paciente\n");
        printf("  6 - Paciente com mais atendimentos\n");
        printf("  0 - Sair\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPaciente(pacientes, &totalPacientes);
                break;
            case 2:
                registrarConsulta(pacientes, totalPacientes, consultas, &totalConsultas);
                break;
            case 3:
                consultasPorPaciente(consultas, totalConsultas);
                break;
            case 4:
                consultasPorData(consultas, totalConsultas);
                break;
            case 5:
                totalPorPaciente(pacientes, totalPacientes, consultas, totalConsultas);
                break;
            case 6:
                pacienteMaisAtendido(pacientes, totalPacientes, consultas, totalConsultas);
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
