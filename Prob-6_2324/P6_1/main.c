#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* nossos includes */
#include "phonebook.h"

/* tamanho máximo de uma palavra */
#define STR_SIZE 200
/* nome do ficheiro com a lista telefónica */
#define NOME_FICHEIRO "phonebook.txt"


/** \brief programa para gerir uma lista telefónica, utilizando uma árvore alocadas dinamicamente
 *
 * \return int: EXIT_SUCCESS(0) em caso de sucesso, EXIT_FAILURE(1) em caso de erro
 *
 */
int main()
{
    tipo_arvore *phonebook= NULL;  /* árvore com a lista telefónica a ser alocada dinamicamente */
    char pname[STR_SIZE]= "end";   /* nome a pesquisar */
    FILE *fp;

    fp= fopen(NOME_FICHEIRO, "r");
    if (fp == NULL)  {
        printf("ERROR 1: Can't open input file %s!\n", NOME_FICHEIRO);
        exit(EXIT_FAILURE);
    }
    load_phonebook(fp, &phonebook);
    fclose(fp);
    printf("===== Phonebook Original =====\n");
    print_number(phonebook, "*");
    do  {
        printf("\nName to find or \"*\" to show all or \"end\" to finish: ");
        if (scanf("%s", pname)!=1)
            break;
        print_number(phonebook, pname);
    } while (strcmp(pname, "end") != 0);
    free_phonebook(phonebook);
    return EXIT_SUCCESS;
}
