#include <stdio.h>
#include <stdlib.h>

/* tamanho máximo de uma linha lida do teclado */
#define MAX_LEN 200

/** \brief Escreve os caracteres de uma string dada por ordem inversa,
 *         do último caracter para o primeiro caracter.
 *         Não funciona com caracteres acentuados UTF-8.
 *
 * \param str char*: string a escrever invertida
 * \return void
 *
 */
void printrevstr(char *str) {
    /* condição de terminação: se é o fim da string, retorna */
    if (str==NULL || *str=='\0')
        return;
    /* chama-se a si própria para escrever a string, excepto o 1º caracter, invertida */
    printrevstr(str+1);
    /* por fim, escreve o 1º caracter da string */
    printf("%c", str[0]);
}

int main()
{
    char string[MAX_LEN];

    printf("Introduza uma linha: ");
    fgets(string, MAX_LEN, stdin);  /* atenção que o fgets guarda '\n' no fim da string */
    printf("Linha invertida: ");
    printrevstr(string);
    printf("\n");
    return EXIT_SUCCESS;
}
