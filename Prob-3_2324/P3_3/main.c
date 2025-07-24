#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_SIZE 10 /* dimensão máxima da matriz, em número de linhas ou de colunas */


/** \brief função para ler uma matriz de m x n do teclado
 *
 * \param matriz[MAX_SIZE][MAX_SIZE] double: matriz onde se guarda a matriz lida
 * \param m int: número de linhas realmente usadas na matriz
 * \param n int: número de colunas realmente usadas na matriz
 * \return void
 *
 */
void load_mat(double matriz[MAX_SIZE][MAX_SIZE], int m, int n)
{
    int i, j;

    printf("\nInsira matriz %d x %d\n", m, n);
    for (i=0 ; i<m ; i++)
        for(j=0 ; j<n ; j++)  {
            printf("M[%d][%d]= ", i, j);
            if (scanf("%lf", &matriz[i][j])<1)  {
                printf("Não consegui ler um número. Programa terminado\n");
                exit(EXIT_FAILURE);
            }
        }
}


/** \brief função para somar 2 matrizes de m x n, guardando o resultado na primeira matriz
 *
 * \param mat1[MAX_SIZE][MAX_SIZE] double: primeira matriz e onde se guarda a soma
 * \param mat2[MAX_SIZE][MAX_SIZE] double: segunda matriz a somar à primeira matriz
 * \param m int: número de linhas realmente usadas nas matrizes
 * \param n int: número de colunas realmente usadas nas matrizes
 * \return void
 *
 */
void sum_mat(double mat1[MAX_SIZE][MAX_SIZE], double mat2[MAX_SIZE][MAX_SIZE], int m, int n)
{
    int i, j;

    for (i=0 ; i<m ; i++)
        for(j=0 ; j<n ; j++) {
            mat1[i][j]+= mat2[i][j];
        }
}

/** \brief função para subtrair 2 matrizes de m x n, guardando o resultado na primeira matriz
 *
 * \param mat1[MAX_SIZE][MAX_SIZE] double: primeira matriz e onde se guarda a diferença
 * \param mat2[MAX_SIZE][MAX_SIZE] double: segunda matriz a subtrair da primeira matriz
 * \param m int: número de linhas realmente usadas nas matrizes
 * \param n int: número de colunas realmente usadas nas matrizes
 * \return void
 *
 */
void subtract_mat(double mat1[MAX_SIZE][MAX_SIZE], double mat2[MAX_SIZE][MAX_SIZE], int m, int n)
{
    int i, j;

    for (i=0 ; i<m ; i++)
        for(j=0 ; j<n ; j++) {
            mat1[i][j]-= mat2[i][j];
        }
}

/** \brief função para escrever uma matriz de m x n no ecrã
 *
 * \param matriz[MAX_SIZE][MAX_SIZE] double: matriz a escrever
 * \param m int: número de linhas realmente usadas na matriz
 * \param n int: número de colunas realmente usadas na matriz
 * \return void
 *
 */
void print_mat(double matriz[MAX_SIZE][MAX_SIZE], int m, int n)
{
    int i, j;

    for (i=0 ; i<m ; i++)  {
        for (j=0 ; j<n ; j++) {
            printf("%f ", matriz[i][j]);
        }
        printf("\n");
    }
}

/** \brief mostra as instruções de utilização do programa
 *
 * \param programa char*: nome do programa
 * \return void
 *
 */
void usage(char *programa)
{
    printf("Utilização: %s [opções]\n", programa);
    printf("opções válidas:\n");
    printf("[-h]\t\t   mostrar instruções\n");
    printf("[-m linhas]\t   definir o número de linhas da matriz, sendo 2 por omissão\n");
    printf("[-n colunas]\t   definir o número de colunas da matriz, sendo 2 por omissão\n");
    printf("[-s]\t\t   subtrair as matrizes em vez de as somar\n");
}


/** \brief programa para ler duas matrizes e somá-las
 *
 * \param argc int:     número de argumentos na linha de comando
 * \param argv[] char*: vector de strings com os argumentos na linha de comando
 * \return int: 0 em caso de sucesso, 1 em caso de insucesso
 *
 */
int main(int argc, char *argv[])
{
    double matrix1[MAX_SIZE][MAX_SIZE], matrix2[MAX_SIZE][MAX_SIZE];
    int m= 2, n= 2; /* dimensões das matrizes por omissão */
    bool subtrair= false;  /* true se for para subtrair em vez de somar */
    int opt= 'h';    /* opção para getopt(), por omissão é help */

    opterr= 0; /* para getopt() não gerar erros por opções inválidas */
    /* processar as opções da linha de comando */
    while ((opt= getopt(argc, argv, "hsn:m:")) != -1) {
        switch (opt) {
            case 's': /* é para subtrair */
                subtrair= true;
                break;
            case 'n':
                if (sscanf(optarg, "%d", &n)!=1)
                    printf("Valor do n \"%s\" inválido. Ignorado\n", optarg);
                break;
            case 'm':
                if (sscanf(optarg, "%d", &m)!=1)
                    printf("Valor do m \"%s\" inválido. Ignorado\n", optarg);
                break;
            default: /* '?' opções inválidas, continua para o próximo case */
                printf("Erro: opção '%c' desconhecida.\n\n", optopt);
            case 'h': /* help */
                usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (m<1 || n<1 || m>MAX_SIZE || n>MAX_SIZE) {
        printf("Erro: Dimensões da matriz inválidas. Programa terminado\n");
        return EXIT_FAILURE;
    }

    load_mat(matrix1, m, n);
    load_mat(matrix2, m, n);

    printf("Impressão da matriz1:\n");
    print_mat(matrix1,m,n);
    printf("Impressão da matriz2:\n");
    print_mat(matrix2,m,n);

    if (subtrair) {
        subtract_mat(matrix1, matrix2, m, n);
        printf("\nSubtração:\n");
    }  else  {
        sum_mat(matrix1, matrix2, m, n);
        printf("\nSoma:\n");
    }
    print_mat(matrix1, m, n);

    return EXIT_SUCCESS;
}
