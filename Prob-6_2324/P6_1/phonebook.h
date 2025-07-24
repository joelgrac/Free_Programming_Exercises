#ifndef PHONEBOOK_H_INCLUDED
#define PHONEBOOK_H_INCLUDED

/* phonebook.h: cabeçalhos de funções de gestão de uma lista telefónica */

/* Estrutura que guarda uma entrada da lista telefónica, definida no ficheiro .c e typedef no ficheiro .h */
typedef struct _tipo_arvore  tipo_arvore;

/* cabeçalhos das funções para gerir uma lista telefónica */
void load_phonebook(FILE *, tipo_arvore **);
void print_number(tipo_arvore *, char *);
void free_phonebook(tipo_arvore *);

#endif // PHONEBOOK_H_INCLUDED
