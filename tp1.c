#include "cadastro.h"

int main(int argc, char* argv[]) {
    usuario usuario_padrao, usuario_do_sistema;

    // Seta o usuario padrao do sistema
    strcpy(usuario_padrao.usuario, "admin");
    strcpy(usuario_padrao.senha, "admin");

    //Recebe as infos pra fazer o login do usuario
    printf("Insira o login e a senha\n");
    printf("Login:\n");
    fgets(usuario_do_sistema.usuario, TAM_STRING_PADRAO, stdin);
    remove_barra_ene(usuario_do_sistema.usuario);

    printf("Senha:\n");
    fgets(usuario_do_sistema.senha, TAM_STRING_PADRAO, stdin);
    remove_barra_ene(usuario_do_sistema.senha);

    //Se as strings sao iguais == Sucesso no Login
    if ((strcmp(usuario_do_sistema.usuario, usuario_padrao.usuario) == 0) && (strcmp(usuario_do_sistema.senha, usuario_padrao.usuario) == 0)) {
    //if ((strcmp("admin", usuario_padrao.usuario) == 0) && (strcmp("admin", usuario_padrao.usuario) == 0)) {
        printf("Login feito com sucesso!\n");

        while (true) {
            mostra_menu();

            printf("Digite o numero da opcao: ");
            int opcao = pega_opcao_do_usuario();

            switch (opcao) {
                case 0:
                    printf("Saindo do programa\n");
                    exit(EXIT_SUCCESS);
                    break;
                case 1:
                    printf("Cadastrando atleta...\n");
                    atleta questionario_atleta = preencher_questionario_atleta();
                    salvar_atleta_no_arquivo(questionario_atleta);
                    break;
                case 2:
                    printf("Mostrando atletas cadastrados...\n");
                    ler_questionarios_dos_atletas();
                    break;
                case 3: {
                    char nome[TAM_STRING_PADRAO];
                    printf("Passe um nome imediatamente!");
                    fgets(nome, TAM_STRING_PADRAO, stdin);
                    remove_barra_ene(nome);
                    pesquisar_atletas(nome);
                    break;
                }
                case 4:
                    printf("Ranqueamento de medalhas e delegacoes...\n");
                    ler_ranqueamento();
                    break;
                case 5:
                    printf("Calendario Paris 2024...");
                    ler_calendario();
                    break;

                default:
                    printf("\nOpcao invalida!\n");
                    break;
            }
        }
    }
    // Login falhou
    else {
        printf("Login e/ou senha incorretos");
    }
    return 1;
}