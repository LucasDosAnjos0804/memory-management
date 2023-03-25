
/*
    Objeto abstracao da estrutura de dados usada no algoritmo fifo
    de mapeamento de memoria
*/

#include "paginas.h"

typedef struct Fifo
{
    int tam;
    int tam_atual;
    Pagina* start;
    Pagina* end;
}Fifo;

Fifo* create_fifo(int tam);
Pagina* drop_fifo(Fifo* f);
void addin_fifo( Fifo* f, Pagina* p);
void print_fifo( Fifo* f);

/// @brief Cria um Fifo
/// @param tam tamanho do FIFO
Fifo*
create_fifo(int tam)
{
    Fifo* f = (Fifo*) malloc (sizeof(Fifo));
    f->tam = tam;
    f->tam_atual = 0;
    f->start = NULL;
    f->end = NULL;
}


/// @brief Retira a pagina mais antiga (o primeiro elemento) do fifo
/// @param f Endereco de memoria de FIFO
Pagina*
drop_fifo(Fifo* f)
{
    Pagina* remover = f->start;

    if ( remover )
    {
        f->start = remover->prox;
        f->tam_atual--;

        f->start->ant = NULL; 
        remover->prox = NULL; 
    }
    return remover;
}


/// @brief Adiciona uma pagina ao final de um fifo
/// e retira o seu elemento mais antigo se a fila já estiver cheia
/// @param f Endereco de memoria de FIFO
/// @param p Pagina que sera adicionada ao FIFO 
void
addin_fifo( Fifo* f, Pagina* p)
{ 
    if ( f->tam_atual >= f->tam )
    {
        drop_fifo(f);
    } 
    
    if ( f->tam_atual )
    {
        f->end->prox = p;
        p->ant = f->end;
        f->end = p;
    } 
    else
    {
        f->start = p;
        f->end = p;
    }

    f->tam_atual++;
    logs("Pagina adicionada ao FIFO");
}


/// @brief Exibe cada elemento de FIFO
/// @param f Endereco de memoria de FIFO
void
print_fifo( Fifo* f)
{
    Pagina* p = f->start;
    printf("FIFO : ");
    while (p)
    {
        printf("%p",p);

        if ( p->prox )
            printf(" <-> ");
        
        p = p->prox;
    }
    puts("");
}