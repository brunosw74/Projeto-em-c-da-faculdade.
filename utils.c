#include "utils.h"

void remove_barra_ene(char* string_pra_edit) {
    if ((strlen(string_pra_edit) > 0) && (string_pra_edit[strlen(string_pra_edit) - 1] == '\n'))
        string_pra_edit[strlen(string_pra_edit) - 1] = '\0';
}

void limpa_terminal() {
    // Copiado do stackoverflow:
    // https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
    printf("\e[1;1H\e[2J");
}

int pega_opcao_do_usuario() {
    int opcao;
    char opcao_string[TAM_STRING_PADRAO];
    // Como usa o fgets:
    // https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
    
    // Como usa sscanf:
    // https://www.cplusplus.com/reference/cstdio/sscanf/

    // Melhor jeito de ler input do usuario:
    // https://stackoverflow.com/questions/9278226/which-is-the-best-way-to-get-input-from-user-in-c
    
    // Lendo opcao com fgets pq o scanf buga
    if(fgets(opcao_string, TAM_STRING_PADRAO, stdin)){
        if( !(1 ==  sscanf(opcao_string, "%d", &opcao))) { // tenta pegar um numero igual scanf
            return -1;
        }
    }

    return opcao;
}