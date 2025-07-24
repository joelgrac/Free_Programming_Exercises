#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* phonebook.c: funções de gestão de uma lista telefónica, utilizando uma árvore alocadas dinamicamente */

/* nossos includes */
#include "phonebook.h"

/* tamanho máximo de uma linha */
#define LINE_SIZE 200
/* tamanho máximo de uma palavra */
#define STR_SIZE 200

/* número de letras: 26 */
#define NCHAR ('z'-'a'+1)

/* Estrutura que guarda a informação da lista telefónica para um nome: vector de números de telefone */
typedef struct _phoneInfo {
    int array_size;     /* tamanho do vector de números de telefone */
    unsigned *number;   /* vector de números de telefone */
} phoneInfo;

/* guarda um arvore de palavras */
typedef struct _tipo_arvore {
    struct {
        struct _tipo_arvore *proximo;   /* cada um dos possíveis filhos */
        phoneInfo dados;    /* informação guardada na árvore: vector de números de telefone */
    } vector[NCHAR];        /* vector de filhos deste nó da árvore */
} tipo_arvore;


/** \brief aloca um nó da árvore e inicializa-o todo vazio
 *
 * \param void
 * \return tipo_arvore*: nó da árvore da lista telefónica.
 *
 */
tipo_arvore *alloc_arvore(void) {
    int i;
    tipo_arvore *no;

    if ((no= (tipo_arvore*)malloc(sizeof(tipo_arvore)))==NULL)
        return no;
    /* iniciar a estrutura */
    for (i=0 ; i<NCHAR ; i++)  {
        no->vector[i].proximo= NULL;
        no->vector[i].dados.array_size= 0;
        no->vector[i].dados.number= NULL;
    }
    return no;
}


/** \brief liberta a memória alocada numa árvore
 *
 * \param arvore tipo_arvore*: árvore da lista telefónica.
 * \return void
 *
 */
void free_phonebook(tipo_arvore *arvore) {
    int i;

    if (arvore==NULL)
        return;
    for (i=0 ; i<NCHAR ; i++)  {
        if (arvore->vector[i].dados.number!= NULL)  {
            /* libertar o vector de números de telefone */
            free(arvore->vector[i].dados.number);
        }
        if (arvore->vector[i].proximo!= NULL)  {
            /* chama-se recursivamente para libertar os filhos todos */
            free_phonebook(arvore->vector[i].proximo);
        }
    }
    free(arvore);
}

/** \brief lê uma lista telefónica de um ficheiro para uma árvore
 *
 * \param fp FILE*: ponteiro para o ficheiro já aberto
 * \param phonebook tipo_arvore**: árvore da lista telefónica a devolver.
 * \return void
 *
 */
void load_phonebook(FILE *fp, tipo_arvore **phonebook)
{
    char line[LINE_SIZE];   /* para guardar uma linha lida do ficheiro */
    char name[STR_SIZE];    /* para guardar um nome da lista telefónica */
    unsigned int telephone, *aux_ptr; /* para guardar um número de telefone */
    tipo_arvore *arvore, *posicao;    /* a árvore e a posição na árvore onde se vai */
    int i;      /* para ciclos */
    int len;    /* tamanho do nome lido */
    int letra;  /* letra onde vamos no nome */
    bool nome_valido;   /* true se o nome for válido */

    arvore= alloc_arvore(); // criar o primeiro nó da árvore
    if (arvore!=NULL)
        while( fgets(line, LINE_SIZE, fp) != NULL )  { // ler uma linha do ficheiro
            if (sscanf(line, "%[^,],%u", name, &telephone) != 2) { // ler a informação da linha
                printf("ERROR parsing phonebook line: %s\n", line);
                continue;  // saltar para a próxima linha
            }
            /* verificar validade do nome */
            /* converter "name" para minúsculas */
            nome_valido= true;
            len= strlen(name);
            for (i=0 ; i<len ; i++) {
                name[i]= tolower(name[i]);
                if (!islower(name[i]))
                    nome_valido= false;  /* se tiver caracteres não alfabéticos, é inválido */
            }
            if (!nome_valido) {
                printf("ERROR invalid name: %s\n", name);
                continue;  // saltar para a próxima linha
            }
            /* inserir o "name" na árvore da lista telefónica */
            /* para cada letra, excepto a última, avançar na árvore, criando nós se necessário */
            for (i= 0, posicao= arvore; i<len-1 ; i++ )  {
                letra= name[i]-'a';  /* obter a letra, convertendo para 0..25(NCHAR) */
                if (posicao->vector[letra].proximo==NULL)  {
                    if ((posicao->vector[letra].proximo= alloc_arvore())==NULL)  {
                        *phonebook= arvore; // se malloc falhar, sai da função
                        return;
                    }
                }
                posicao= posicao->vector[letra].proximo;
            }
            /* na posição da última letra, fazer crescer o vector para adicionar mais um número de telefone ao vector */
            letra= name[i]-'a';  /* obter a letra, convertendo para 0..25(NCHAR) */
            aux_ptr= (unsigned*)realloc(posicao->vector[letra].dados.number, (posicao->vector[letra].dados.array_size + 1) * sizeof(unsigned));
            if (aux_ptr==NULL)
                break; // se realloc falhar, sai da função
            posicao->vector[letra].dados.number= aux_ptr;
            /* pôr mais um número de telefone no fim do vector */
            posicao->vector[letra].dados.number[posicao->vector[letra].dados.array_size]= telephone;
            posicao->vector[letra].dados.array_size++;
        }
    /* retornar a lista telefónica, preenchendo o parâmetro da função */
    *phonebook= arvore;
}

/** \brief função recursiva para escrever toda a árvore
 *
 * \param phonebook tipo_arvore*: nó da árvore onde se vai
 * \param name char*: letras do nome que estão nos nós pais a concatenar com as letras deste nó e dos filhos, na primeira invocação pôr ""
 * \return void
 *
 */
void print_all(tipo_arvore *phonebook, char *name)
{
    int i, j, len;
    char nome[STR_SIZE]; /* para ir concatenando as letras do nome */
    if (phonebook==NULL)
        return;
    strcpy(nome, name); /* começa com o nome que está no parâmetro da função */
    len= strlen(name);
    strcat(nome, "a");  /* acrescenta a letra deste nó, que varia ao longo do ciclo seguinte */
    for (i=0; i<NCHAR ; i++)  {
        /* escrever todos os números de telefone se houver */
        for (j=0 ; j<phonebook->vector[i].dados.array_size ; j++)  {
            printf("%s %u\n", nome, phonebook->vector[i].dados.number[j]);
        }
        /* percorrer os filhos deste nó da árvore recursivamente */
        if (phonebook->vector[i].proximo!=NULL)
            print_all(phonebook->vector[i].proximo, nome);
        nome[len]++; // avançar para a próxima letra deste nó: 'a', 'b', ... 'z'
    }
}

/** \brief escrever o conteúdo de uma ou mais entradas da lista telefónica no écran
 *
 * \param arvore tipo_arvore*: árvore da lista telefónica.
 * \param pname char*: nome a procurar, ou "*" para mostrar toda a lista telefónica
 * \return void
 *
 */
void print_number(tipo_arvore *phonebook, char *pname)
{
    int i, j, len;
    tipo_arvore *posicao;  /* a posição na árvore onde se vai */

    /* com ponteiros a NULL, não se faz nada */
    if (phonebook==NULL || pname==NULL)
        return;
    if (strcmp(pname, "*") == 0)  {
        /* é para percorrer toda a árvore e escrever tudo, é uma função recursiva separada */
        print_all(phonebook, "");
    } else {
        /* converter o nome a pesquisar para minúsculas */
        len= strlen(pname);
        for (i=0 ; i<len ; i++) {
            pname[i]= tolower(pname[i]);
            if (!islower(pname[i]))
                return;  /* se tiver caracteres não alfabéticos, não encontra */
        }
        /* procurar pname; desce na árvore até ao penúltimo caracter */
        for (i=0, posicao= phonebook ; posicao!=NULL && i<len-1 ; i++)  {
            posicao= posicao->vector[pname[i]-'a'].proximo;
        }
        /* se ficou a NULL, é porque a árvore não tem o ramo que procuramos */
        if (posicao==NULL)
            return;
        /* último caracter do nome: percorrer o vector de números de telefone e escrevê-los */
        for (j=0 ; j<posicao->vector[pname[i]-'a'].dados.array_size ; j++)  {
            printf("%s %u\n", pname, posicao->vector[pname[i]-'a'].dados.number[j]);
        }
    }
}
