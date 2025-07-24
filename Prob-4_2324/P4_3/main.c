#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* tamanho máximo de uma linha */
#define MAX_LEN 1000


/** \brief Programa que pesquisa uma string num ficheiro
 *
 * \param argc int: número de parâmetros na linha de comando, incluíndo o nome do programa
 * \param argv[] char*: array com os argumentos na linha de comando
 * \return int: EXIT_SUCCESS(0) em caso de sucesso, EXIT_FAILURE(1) em caso de falha
 *
 */
int main(int argc, char *argv[])
{
    FILE *ficheiro;
    char linha[MAX_LEN];  /* buffer para uma linha lida do ficheiro */
    int n_linha= 0; /* número de linha onde vai no ficheiro */
    int n_encontradas= 0;  /* número de palavras encontradas */

    if (argc<3)  {
        printf("Programa que procura uma palavra num ficheiro\n");
        printf("Utilização:\n\t%s <palavra_a_procurar> <nome_do_ficheiro>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    /* abrir o ficheiro */
    printf("Lendo o ficheiro \"%s\"\n", argv[2]);
    if ((ficheiro= fopen(argv[2], "r"))==NULL)  {
        printf("Não consegui abrir o ficheiro. Programa terminado.\n");
        exit(EXIT_FAILURE);
    }
    /* ler o ficheiro */
    while (fgets(linha, MAX_LEN, ficheiro) != NULL) {  /* ler uma linha */
        n_linha++; /* incrementa o nº de linha no início para começar na linha 1 */
        if (strstr(linha, argv[1]) != NULL)  {
            printf("%d:%s", n_linha, linha);
            n_encontradas++;
        }
    }
    fclose(ficheiro);  /* fechar o ficheiro, senão o valgrind acusa erro */
    printf("Ficheiro de %d linhas lido. Total de %d linhas com a string \"%s\".\n", n_linha, n_encontradas, argv[1]);
    return EXIT_SUCCESS;
}
