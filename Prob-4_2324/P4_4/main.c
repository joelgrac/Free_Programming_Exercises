#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* nome do ficheiro com a lista telefónica */
#define NOME_FICHEIRO "phonebook.txt"

/* tamanho máximo de uma linha */
#define LINE_SIZE 100
/* tamanho máximo de uma palavra */
#define STR_SIZE 100
/* tamanho máximo da lista telefónica */
#define MAX_PHONEBOOK_SIZE 1000

/* Estrutura que guarda uma entrada da lista telefónica */
typedef struct  {
    char name[STR_SIZE]; /* nome */
    unsigned number;     /* número de telefone */
} phoneEntry;


/** \brief lê uma lista telefónica de um ficheiro
 *
 * \param fp FILE*: ponteiro para o ficheiro já aberto
 * \param phonebook phoneEntry*: vector de entradas da lista telefónica. Como não é passado o número de entradas,
 *                               convenciona-se que o vector acaba com uma string vazia e número de telefone a 0.
 * \return void
 *
 */
void load_phonebook(FILE *fp, phoneEntry *phonebook)
{
    int contact_number= 0;  /* para contar o número de registos preenchidos no vector */
    char line[LINE_SIZE];   /* para guardar uma linha lida do ficheiro */
    char name[STR_SIZE];    /* para guardar um nome da lista telefónica */
    unsigned telephone; /* para guardar um número de telefone */
    /* Ler linhas do ficheiro e processá-las */
    while( fgets(line, LINE_SIZE, fp) != NULL && contact_number < MAX_PHONEBOOK_SIZE) {
        /* ler a informação da linha: ler string até vírgula, vírgula e número */
        if (sscanf(line, "%[^,],%u", name, &telephone) != 2) {
            printf("ERROR parsing phonebook line\n");
            continue;  // saltar para a próxima linha do ficheiro
        }
        /* guardar a informação no vector da lista telefónica */
        strcpy(phonebook[contact_number].name, name);
        phonebook[contact_number].number= telephone;
        contact_number++;
    }
    /* pôr marcador de fim da lista telefónica */
    phonebook[contact_number].name[0]= '\0';
    phonebook[contact_number].number= 0;
    if (contact_number >= MAX_PHONEBOOK_SIZE)
        printf("Erro em load_phonebook(): tamanho máximo da lista telefónica atingido\n");
}


/** \brief escrever o conteúdo de uma ou mais entradas da lista telefónica no écran
 *
 * \param phonebook phoneEntry*: vector de entradas da lista telefónica. Como não é passado o número de entradas,
 *                               convenciona-se que o vector acaba com uma string vazia e número de telefone a 0.
 * \param pname char*: nome a procurar, ou "*" para mostrar toda a lista telefónica
 * \return void
 *
 */
void print_number(phoneEntry *phonebook, char *pname)
{
    bool print_all_flag= false;
    int i;

    if (phonebook==NULL || pname==NULL)
        return;  // protecção: se algum ponteiro for NULL, sai */
    if (strcmp(pname, "*") == 0)
        print_all_flag= true;
    for (i= 0 ; phonebook[i].name[0]!= '\0' && phonebook[i].number != 0 ; i++) {
        if (print_all_flag || (strcmp(pname, phonebook[i].name) == 0)) {
            //printf("%s %u\n", (phonebook+i)->name, (phonebook+i)->number);  /* é igual à linha seguinte */
            printf("%s %u\n", phonebook[i].name, phonebook[i].number);  /* é igual à linha anterior */
        }
    }
}


/** \brief programa para gerir uma lista telefónica, utilizando vectores alocados estaticamente
 *
 * \return int: EXIT_SUCCESS(0) em caso de sucesso, EXIT_FAILURE(1) em caso de erro
 *
 */
int main()
{
    phoneEntry phonebook[MAX_PHONEBOOK_SIZE+1]; /* vector com a lista telefónica, mais um para o terminador */
    char pname[STR_SIZE]= "end";    /* nome a pesquisar */
    FILE *fp;

    fp= fopen(NOME_FICHEIRO, "r");
    if (fp == NULL)  {
        printf("ERROR 1: Can't open input file %s!\n", NOME_FICHEIRO);
        exit(EXIT_FAILURE);
    }
    load_phonebook(fp, phonebook);
    fclose(fp);
    printf("===== Phonebook Lida =====\n");
    print_number(phonebook, "*");
    do  {
        printf("\nName to find or \"*\" to show all or \"end\" to finish: ");
        scanf("%s", pname);
        print_number(phonebook, pname);
    } while(strcmp(pname, "end") != 0);
    return EXIT_SUCCESS;
}
