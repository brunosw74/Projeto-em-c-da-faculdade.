#include "cadastro.h"

// Funcao exibe o menu do trabalho
void mostra_menu() {
    printf("------------------------------ Olimpíadas Paris 2024 ------------------------------\n\n");

    printf("0 - Sair do programa\n");
    printf("1 - Cadastro de Atletas\n");
    printf("2 - Listar Atletas\n");
    printf("3 - Pesquisar Atleta\n");
    printf("4 - Listar Ranqueamento e delegações\n");
    printf("5 - Calendário da Olimpíadas Paris 2024\n");
}

atleta preencher_questionario_atleta() {
    // Essa funcao cria a struct atleta e vai preenchendo os valores necessarios com fgets
    // Como pegar uma string com espacos
    // https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf
    atleta questionario_do_atleta;

    printf("\nInsira o nome do atleta:\n");
    // Usando fgets ao inves de scanf pra pegar espacos
    fgets(questionario_do_atleta.nome, TAM_STRING_PADRAO, stdin);

    printf("\nInsira a modalidade olimpica:\n");
    fgets(questionario_do_atleta.modalidade_olimpica, TAM_STRING_PADRAO, stdin);

    printf("\nInsira o pais do atleta:\n");
    fgets(questionario_do_atleta.pais, TAM_STRING_PADRAO, stdin);

    printf("\nInsira a equipe do atleta:\n");
    fgets(questionario_do_atleta.equipe, TAM_STRING_PADRAO, stdin);

    printf("\nInsira o alojamento do atleta:\n");
    fgets(questionario_do_atleta.alojamento, TAM_STRING_PADRAO, stdin);

    printf("\nInsira o local dos esportes do atleta:\n");
    fgets(questionario_do_atleta.local_esportes, TAM_STRING_PADRAO, stdin);

    printf("\nInsira os equipamentos dos esportes do atleta:\n");
    fgets(questionario_do_atleta.equipamentos, TAM_STRING_PADRAO, stdin);

    // Checa se o usuario quer preencher os agendamentos
    printf("\nDeseja preencher os agendamentos dos treinos do atleta?\n");
    printf("\nInsira 1 para preencher os agendamentos\nInsira 0 para nao preencher os agendamentos\n");

    int preencher_agendamentos = pega_opcao_do_usuario();
    int contador = 0;  // Contador para iterar entre os agendamentos
    if (preencher_agendamentos) {
        while (contador < MAX_AGENDAMENTOS) {  // preenchendo os agendamentos ate o maximo permitido
            printf("\nInsira a data do agendamento:\n");
            fgets(questionario_do_atleta.agendamentos_de_treino[contador].data, TAM_STRING_PADRAO, stdin);

            printf("\nInsira o local do agendamento:\n");
            fgets(questionario_do_atleta.agendamentos_de_treino[contador].local, TAM_STRING_PADRAO, stdin);

            contador++;
            questionario_do_atleta.num_agendamentos_preenchidos = contador;

            // Checa se o usuario deseja continuar inserindo
            printf("\nInsira 0 para continuar preenchendo os agendamentos\nInsira 1 para parar de preencher os agendamentos\n");
            int parar = pega_opcao_do_usuario();
            if (parar) {
                break;
            }
        }
    } else {  // seta que nenhum questionario foi preenchido
        questionario_do_atleta.num_agendamentos_preenchidos = 0;
    }

    // Checa se o usuario quer preencher os agendamentos
    printf("\nDeseja preencher os funcionarios do atleta?\n");
    printf("\nInsira 1 para preencher os funcionarios\nInsira 0 para nao preencher os funcionarios\n");
    int preencher_funcionarios = pega_opcao_do_usuario();
    contador = 0;
    if (preencher_funcionarios) {
        while (contador < MAX_FUNCIONARIOS) {  // preenchendo os funcionarios ate o maximo permitido
            printf("\nInsira o tipo do funcionario:\n");
            fgets(questionario_do_atleta.funcionarios[contador].tipo, 12, stdin);

            printf("\nInsira o nome do funcionario:\n");
            fgets(questionario_do_atleta.funcionarios[contador].nome, TAM_STRING_PADRAO, stdin);

            if (strcmp(questionario_do_atleta.funcionarios[contador].tipo, "Medico") == 0) {
                printf("\nInsira a equipe do funcionario:\n");
                fgets(questionario_do_atleta.funcionarios[contador].equipe, TAM_STRING_PADRAO, stdin);
            }

            contador++;
            questionario_do_atleta.num_funcionarios_preenchidos = contador;

            // Checa se o usuario deseja continuar inserindo
            printf("\nInsira 0 para continuar preenchendo funcionarios\nInsira 1 para parar de preencher os funcionarios\n");
            int parar = pega_opcao_do_usuario();
            if (parar) {
                break;
            }
        }
    }

    // Essa aqui eh a parte do questionario do covid pra ver se o atleta esta de acordo com as normas
    printf("\nResponda [1] para [sim] e [0] para [nao] no seguinte questionario:\n");
    printf("O atleta foi vacinado ?\n");
    int vacinado = pega_opcao_do_usuario();
    if (vacinado) {
        questionario_do_atleta.questionario_covid_19.vacinado = true;
    } else {
        questionario_do_atleta.questionario_covid_19.vacinado = false;
    }

    printf("O atleta fez teste de covid ?\n");
    int fez_teste_covid = pega_opcao_do_usuario();
    if (fez_teste_covid) {
        questionario_do_atleta.questionario_covid_19.fez_teste_covid = true;
    } else {
        questionario_do_atleta.questionario_covid_19.fez_teste_covid = false;
    }

    printf("O atleta esteve em um pais proibido ?\n");
    int esteve_em_um_pais_proibido = pega_opcao_do_usuario();
    if (esteve_em_um_pais_proibido) {
        questionario_do_atleta.questionario_covid_19.esteve_em_um_pais_proibido = true;
    } else {
        questionario_do_atleta.questionario_covid_19.esteve_em_um_pais_proibido = false;
    }

    printf("Fim do Questionario! As informacoes estao sendo salvas\n");
    return questionario_do_atleta;
}

void salvar_atleta_no_arquivo(atleta cadastro_atleta) {
    // Checa se o arquivo existe antes de abrir:
    // https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c

    FILE* arquivo_de_cadastro = NULL;
    FILE* file;
    if ((file = fopen("atletas.txt", "r")) != NULL) {
        // Se o arquivo existe... abre com append
        fclose(file);
        arquivo_de_cadastro = fopen("atletas.txt", "a");
    } else {
        // Arquivo nao existe... abre com write
        arquivo_de_cadastro = fopen("atletas.txt", "w");
    }

    // Checa se abriu certinho
    if (arquivo_de_cadastro == NULL) {
        printf("Falha ao abrir arquivo(s)!\n");
        exit(EXIT_FAILURE);
    }

    // Escreve arquivo_de_cadastro do atleta
    fprintf(arquivo_de_cadastro, "%s", "---\n");
    fprintf(arquivo_de_cadastro, "%s", "Nome:\n");
    fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.nome);
    fprintf(arquivo_de_cadastro, "%s", "Modalidade olimpica:\n");
    fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.modalidade_olimpica);
    fprintf(arquivo_de_cadastro, "%s", "Pais:\n");
    fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.pais);
    fprintf(arquivo_de_cadastro, "%s", "Equipe:\n");
    fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.equipe);
    fprintf(arquivo_de_cadastro, "%s", "Alojamento:\n");
    fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.alojamento);
    fprintf(arquivo_de_cadastro, "%s", "Local dos esportes:\n");
    fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.local_esportes);
    fprintf(arquivo_de_cadastro, "%s", "Equipamentos:\n");
    fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.equipamentos);

    // Coloca o numero de agendamentos
    fprintf(arquivo_de_cadastro, "%s", "Agendamentos:\n");
    fprintf(arquivo_de_cadastro, "%d\n", cadastro_atleta.num_agendamentos_preenchidos);

    // Preenche os agendamentos
    for (int i = 0; i < cadastro_atleta.num_agendamentos_preenchidos; i++) {
        fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.agendamentos_de_treino[i].data);
        fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.agendamentos_de_treino[i].local);
    }

    // Coloca o numero de funcionarios
    fprintf(arquivo_de_cadastro, "%s", "Funcionarios:\n");
    fprintf(arquivo_de_cadastro, "%d\n", cadastro_atleta.num_funcionarios_preenchidos);

    // Prenche os cadastros de funcionarios
    for (int i = 0; i < cadastro_atleta.num_funcionarios_preenchidos; i++) {
        fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.funcionarios[i].tipo);
        fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.funcionarios[i].nome);

        // Se eh um medico ele tem uma equipe
        if (strcmp(cadastro_atleta.funcionarios[i].tipo, "Medico") == 0) {
            fprintf(arquivo_de_cadastro, "%s", cadastro_atleta.funcionarios[i].equipe);
        }
    }

    if (cadastro_atleta.questionario_covid_19.vacinado) {
        fprintf(arquivo_de_cadastro, "%s", "Vacinado:\nSim\n");
    } else {
        fprintf(arquivo_de_cadastro, "%s", "Vacinado:\nNao\n");
    }

    if (cadastro_atleta.questionario_covid_19.fez_teste_covid) {
        fprintf(arquivo_de_cadastro, "%s", "Fez teste de Covid:\nSim\n");
    } else {
        fprintf(arquivo_de_cadastro, "%s", "Fez teste de Covid:\nNao\n");
    }

    if (cadastro_atleta.questionario_covid_19.esteve_em_um_pais_proibido) {
        fprintf(arquivo_de_cadastro, "%s", "Esteve em um pais proibido:\nSim\n");
    } else {
        fprintf(arquivo_de_cadastro, "%s", "Esteve em um pais proibido:\nNao\n");
    }
    fprintf(arquivo_de_cadastro, "%s", "---\n");

    // Fecha o arquivo
    fclose(arquivo_de_cadastro);
}
//ler questionarios dos atletas
void ler_questionarios_dos_atletas() {
    // Como ler de um arquivo linha a linha em C
    // https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    // Abre o arquivo
    fp = fopen("atletas.txt", "r");
    if (fp == NULL) {
        printf("Nao ha nenhum arquivo");
        return;
    }

    // Le o arquivo linha a linha
    while ((read = getline(&line, &len, fp)) != -1) {  // le linha por linha
        printf("%s", line);
    }

    // Fecha o arquivo
    fclose(fp);

    // Se a linha tinha alguma coisa, libera ela
    if (line) {
        free(line);
    }
}
//ler ranqueamento
void ler_ranqueamento() {
    // Como ler de um arquivo linha a linha em C
    // https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    // Abre o arquivo
    fp = fopen("ranqueamento.txt", "r");
    if (fp == NULL) {
        printf("Nao ha nenhum arquivo");
        return;
    }

    // Le o arquivo linha a linha
    while ((read = getline(&line, &len, fp)) != -1) {  // le linha por linha
        printf("%s", line);
    }

    // Fecha o arquivo
    fclose(fp);

    // Se a linha tinha alguma coisa, libera ela
    if (line) {
        free(line);
    }
}
// ler calendario.
void ler_calendario() {
    // Como ler de um arquivo linha a linha em C
    // https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    // Abre o arquivo
    fp = fopen("calendario.txt", "r");
    if (fp == NULL) {
        printf("Nao ha nenhum arquivo");
        return;
    }

    // Le o arquivo linha a linha
    while ((read = getline(&line, &len, fp)) != -1) {  // le linha por linha
        printf("%s", line);
    }

    // Fecha o arquivo
    fclose(fp);

    // Se a linha tinha alguma coisa, libera ela
    if (line) {
        free(line);
    }
}

void pesquisar_atletas(char* nome) {
    // Como ler de um arquivo linha a linha em C
    // https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    // Abre o arquivo
    fp = fopen("atletas.txt", "r");
    if (fp == NULL) {
        printf("Nao ha nenhum arquivo");
        return;
    }

    atleta cadastro_atleta[10];

    int i = 0; // num de cadastros preenchidos
    while ((read = getline(&line, &len, fp)) != -1) {
        read = getline(&line, &len, fp);  // le "nome:"
        read = getline(&line, &len, fp);  // le o nome do atleta
        remove_barra_ene(line);

        // snprintf eh doideira
        // https://stackoverflow.com/questions/2606539/snprintf-vs-strcpy-etc-in-c
        snprintf(cadastro_atleta[i].nome, sizeof(cadastro_atleta[i].nome), "%s", line);

        read = getline(&line, &len, fp);  // le "modalidade olimpica:"
        read = getline(&line, &len, fp);  // le a resposta
        remove_barra_ene(line);
        snprintf(cadastro_atleta[i].modalidade_olimpica, sizeof(cadastro_atleta[i].modalidade_olimpica), "%s", line);

        read = getline(&line, &len, fp);  // le "pais:"
        read = getline(&line, &len, fp);  // le a resposta
        remove_barra_ene(line);
        snprintf(cadastro_atleta[i].pais, sizeof(cadastro_atleta[i].pais), "%s", line);

        read = getline(&line, &len, fp);  // le "equipe:"
        read = getline(&line, &len, fp);  // le a resposta
        remove_barra_ene(line);
        snprintf(cadastro_atleta[i].equipe, sizeof(cadastro_atleta[i].modalidade_olimpica), "%s", line);

        read = getline(&line, &len, fp);  // le "alojamento:"
        read = getline(&line, &len, fp);  // le a resposta
        remove_barra_ene(line);
        snprintf(cadastro_atleta[i].alojamento, sizeof(cadastro_atleta[i].alojamento), "%s", line);

        read = getline(&line, &len, fp);  // le "local dos esportes:"
        read = getline(&line, &len, fp);  // le a resposta
        remove_barra_ene(line);
        snprintf(cadastro_atleta[i].local_esportes, sizeof(cadastro_atleta[i].local_esportes), "%s", line);

        read = getline(&line, &len, fp);  // le "equipamentos:"
        read = getline(&line, &len, fp);  // le a resposta
        remove_barra_ene(line);
        snprintf(cadastro_atleta[i].equipamentos, sizeof(cadastro_atleta[i].equipamentos), "%s", line);

        read = getline(&line, &len, fp);  // le "agendamentos:"
        read = getline(&line, &len, fp);  // le o numero de agendamentos

        int num_agendamentos;
        if (!(1 == sscanf(line, "%d", &num_agendamentos))) {  // tenta pegar um numero igual scanf
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < num_agendamentos; i++) {
            read = getline(&line, &len, fp);  // le a data do agendamento
            remove_barra_ene(line);

            // copia a data do agendamento
            snprintf(cadastro_atleta[i].agendamentos_de_treino[i].data, sizeof(cadastro_atleta[i].agendamentos_de_treino[i].data), "%s", line);

            read = getline(&line, &len, fp);  // le o local do agendamentos
            remove_barra_ene(line);

            // copia o local do agendamento
            snprintf(cadastro_atleta[i].agendamentos_de_treino[i].local, sizeof(cadastro_atleta[i].agendamentos_de_treino[i].local), "%s", line);
        }

        read = getline(&line, &len, fp);  // le o "funcionarios:"
        read = getline(&line, &len, fp);  // le o numero de funcionarios
        int num_funcionarios;
        if (!(1 == sscanf(line, "%d", &num_funcionarios))) {  // tenta pegar um numero igual scanf
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < num_funcionarios; i++) {
            read = getline(&line, &len, fp);  // le o tipo do funcionario
            remove_barra_ene(line);

            snprintf(cadastro_atleta[i].funcionarios[i].tipo, sizeof(cadastro_atleta[i].funcionarios[i].tipo), "%s", line);

            read = getline(&line, &len, fp);  // le o nome do funcionario
            remove_barra_ene(line);
            snprintf(cadastro_atleta[i].funcionarios[i].nome, sizeof(cadastro_atleta[i].funcionarios[i].nome), "%s", line);

            if (strcmp(cadastro_atleta[i].funcionarios[i].tipo, "Medico") == 0) {
                read = getline(&line, &len, fp);  // le a equipe
                remove_barra_ene(line);           //
                snprintf(cadastro_atleta[i].funcionarios[i].equipe, sizeof(cadastro_atleta[i].funcionarios[i].equipe), "%s", line);
            }
        }

        read = getline(&line, &len, fp);  // le a linha "Vacinado:""
        read = getline(&line, &len, fp);  // le se ja foi vacinado
        remove_barra_ene(line);
        if (strcmp(line, "Sim") == 0) {
            cadastro_atleta[i].questionario_covid_19.vacinado = true;
        } else {
            cadastro_atleta[i].questionario_covid_19.vacinado = false;
        }

        read = getline(&line, &len, fp);  // le a linha "Fez teste de Covid:"
        read = getline(&line, &len, fp);  // le se ja fez o teste
        remove_barra_ene(line);
        if (strcmp(line, "Sim") == 0) {
            cadastro_atleta[i].questionario_covid_19.fez_teste_covid = true;
        } else {
            cadastro_atleta[i].questionario_covid_19.fez_teste_covid = false;
        }

        read = getline(&line, &len, fp);  // le a linha "Esteve em um pais proibido:"
        read = getline(&line, &len, fp);  // le se ja esteve num pais proibido
        remove_barra_ene(line);
        if (strcmp(line, "Sim") == 0) {
            cadastro_atleta[i].questionario_covid_19.esteve_em_um_pais_proibido = true;
        } else {
            cadastro_atleta[i].questionario_covid_19.esteve_em_um_pais_proibido = false;
        }
        read = getline(&line, &len, fp);  // le os "---"
        i++;
    }

    // Fecha o arquivo
    fclose(fp);

    // Se a linha tinha alguma coisa, libera ela
    if (line) {
        free(line);
    }

    for(int count_atleta = 0; count_atleta < i; count_atleta++){
        printf("O valor do e: %d\n", count_atleta);
        if (strcmp(cadastro_atleta[count_atleta].nome, nome) == 0){
            printf("O atleta %s esta cadastrado!\n", nome);
            return;
        }
    }
    printf("O atleta nao esta cadastrado!\n");
}