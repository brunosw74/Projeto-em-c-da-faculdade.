#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>   // stat pra checar se o arquivo existe
#include "constantes.h"
#include "utils.h"

// Usuario do sistema para fazer o login
typedef struct usuario{
    char usuario[TAM_STRING_PADRAO];
    char senha[TAM_STRING_PADRAO];
} usuario;

// Agendamentos do cadastro dos atletas
typedef struct agendamentos{
    char data[TAM_STRING_PADRAO];
    char local[TAM_STRING_PADRAO];
} agendamentos;

// Funcionarios do cadastro dos atlestas
typedef struct funcionario{
    char tipo[12]; // pode ser funcionario\0, voluntario ou medico
    char nome[TAM_STRING_PADRAO];
    char equipe[TAM_STRING_PADRAO];
} funcionario;

// Questionario relacionado aos protocolos relacionados a Covid-19
typedef struct questionario_covid{
    bool vacinado;
    bool fez_teste_covid;
    bool esteve_em_um_pais_proibido;
} questionario_covid;

// Atleta para fazer o cadastro
typedef struct {
    char nome[TAM_STRING_PADRAO];
    char modalidade_olimpica[TAM_STRING_PADRAO];
    char pais[TAM_STRING_PADRAO];
    char equipe[TAM_STRING_PADRAO];
    char alojamento[TAM_STRING_PADRAO];
    char local_esportes[TAM_STRING_PADRAO];
    char equipamentos[TAM_STRING_PADRAO];
    
    int num_agendamentos_preenchidos;
    agendamentos agendamentos_de_treino[MAX_AGENDAMENTOS];

    int num_funcionarios_preenchidos;
    funcionario funcionarios[MAX_FUNCIONARIOS];

    questionario_covid questionario_covid_19;
} atleta;


////////////// Definicoes de funcoes
void mostra_menu();
atleta preencher_questionario_atleta();
void salvar_atleta_no_arquivo(atleta cadastro_atleta);
void ler_questionarios_dos_atletas();
void pesquisar_atletas(char* nome);
void ler_ranqueamento();
void ler_calendario();


 

