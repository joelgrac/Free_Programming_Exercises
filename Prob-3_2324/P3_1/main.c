#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PALAVRAS 10 /* número máximo de palavras */
#define MAX_LEN 100     /* tamanho máximo de uma palavra */


/** \brief função para ler um vector de "n_words" palavras/strings do teclado para o vector "vect"
 *
 * \param vect[MAX_PALAVRAS][MAX_LEN] char: vector para armazenar as palavras/strings
 * \param n_words int: número de strings realmente usadas no vector
 * \return void
 *
 */
void load_vect(char vect[MAX_PALAVRAS][MAX_LEN], int n_words)  /* MAX_PALAVRAS pode ser omitido */
{
    int i;
    char format[MAX_LEN];

    /* o formato a ler no scanf é uma string com (MAX_LEN-1) caracteres e um terminador de string */
    /* se MAX_LEN for 100, format fica com "%99s", o que no scanf permite ler strings até 99 caracteres */
    /* o sprintf é semelhante ao printf, mas em vez de escrever no écran, escreve numa variável do tipo string */
    sprintf(format, "%%%ds", MAX_LEN-1);
    for (i=0 ; i<n_words ; i++) {
        printf("Palavra %d:", i+1);
        if (scanf(format, vect[i]) < 1)  {
            printf("Nao consegui ler a palavra. Programa terminado\n");
            exit(EXIT_FAILURE);
        }
    }
}

/** \brief função de comparação de strings para qsort(), fazendo as conversões de tipos adequadas
 *
 * \param p1 const void*: primeira string
 * \param p2 const void*: segunda string
 * \return int: retorna um inteiro menor que, igual a, ou maior que zero consoante p1 seja, respectivamente,
 *              menor, igual ou maior que p2
 *
 */
int cmpstringp(const void *p1, const void *p2)
{
   /* The actual arguments to this function are "pointers to void", but strcmp(3) arguments are "pointers
      to char", hence the following cast */

   return strcmp((char *) p1, (char *) p2);
}


/** \brief função para ordenar as palavras no vector usando qsort() da biblioteca do C
 *
 * \param vect[MAX_PALAVRAS][MAX_LEN] char: vector de palavras/strings a ordenar
 * \param n_words int: número de strings realmente usadas no vector
 * \return void
 *
 */
void  sort_vect(char vect[MAX_PALAVRAS][MAX_LEN], int n_words)
{
    qsort(vect, n_words, sizeof(char)*MAX_LEN, cmpstringp);
}


/** \brief função para ordenar as palavras no vector usando algoritmo de ordenação que troca de palavras fora de ordem
 *
 * \param vect[MAX_PALAVRAS][MAX_LEN] char: vector de palavras/strings a ordenar
 * \param n_words int: número de strings realmente usadas no vector
 * \return void
 *
 */
void my_sort_vect(char vect[MAX_PALAVRAS][MAX_LEN], int n_words)
{
    int i;
    bool trocas;
    char temp[MAX_LEN];

    /* algoritmo de ordenação BubbleSort */
    /* percorrer o vector todo, enquanto houver trocas */
    do {
        trocas= false;
        for (i=0 ; i+1<n_words ; i++)
            /* se encontra 2 entradas consecutivas fora de ordem, troca-as de ordem */
            if (strcmp(vect[i], vect[i+1]) > 0) { /* há 2 palavras fora de ordem */
                strcpy(temp, vect[i]); /* troca palavras de ordem */
                strcpy(vect[i], vect[i+1]);
                strcpy(vect[i+1], temp);
                trocas= true; /* houve 1 troca, necessário percorrer a lista toda novamente */
            }
    } while (trocas);
}


/** \brief função para escrever no écran um vector com "n_words" palavras/strings
 *
 * \param vect[MAX_PALAVRAS][MAX_LEN] char: vector de palavras/strings a escrever
 * \param n_words int: número de strings realmente usadas no vector
 * \return void
 *
 */
void print_vect(char vect[MAX_PALAVRAS][MAX_LEN], int n_words)
{
    int i;

    for (i=0 ; i < n_words ; i++) {
        printf("%s\n", vect[i]);
    }
}



/** \brief programa para ler strings e ordená-las alfabeticamente
 *
 * \return int: 0 em caso de sucesso, 1 em caso de insucesso
 *
 */
int main()
{
    int n_words;
    char str_vect[MAX_PALAVRAS][MAX_LEN];

    do {
        printf("Insira nº de palavras (2-%d): ", MAX_PALAVRAS);
        if (scanf("%d", &n_words) < 1)  {
            printf("Nao consegui ler um numero. Programa terminado\n");
            return EXIT_FAILURE;
        }
    } while (n_words < 2 || n_words > MAX_PALAVRAS);

    printf("\nInsira Palavras\n");
    load_vect(str_vect, n_words);  // vector passado por referência: str_vect é o mesmo que &str_vect[0] (apontador para o 1º elemento)

    printf("\nPalavras Lidas:\n");
    print_vect(str_vect, n_words);

    sort_vect(str_vect, n_words);   // n_words passado por valor

    printf("\nPalavras Ordenadas:\n");
    print_vect(str_vect, n_words);

    return EXIT_SUCCESS;
}
