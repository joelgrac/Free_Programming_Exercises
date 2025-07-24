#ifndef PHONEBOOK_H_INCLUDED
#define PHONEBOOK_H_INCLUDED

/* phonebook.h: cabeçalhos de funções de gestão de uma lista telefónica, utilizando vectores alocados dinamicamente */

/* Estrutura que guarda uma entrada da lista telefónica no ficheiro .c e typedef no ficheiro .h */
typedef struct _phoneEntry phoneEntry;

/* cabeçalhos das funções para gerir uma lista telefónica */
void load_phonebook(FILE *, phoneEntry **);
void print_number(phoneEntry *, char *);
void sort_phonebook(phoneEntry *);
void free_phonebook(phoneEntry *);

#endif // PHONEBOOK_H_INCLUDED
