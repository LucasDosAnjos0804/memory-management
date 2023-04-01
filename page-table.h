/*
    abstração do que é uma tabela de páginas mantida pelo gereneciador de memória
*/

typedef Fila Pagetable;

typedef struct Linha_Pagetable
{
    int endereco_mvirtual;
    int endereco_mfisica;
    int in_memory;
} Linha_Pagetable;

Pagetable* pagetable_create ();
void pagetable_map( Pagetable * p, int endereco_mvirtual, int endereco_mfisica );

Linha_Pagetable* pagetable_drop( Pagetable* f );
void paggtable_print( Pagetable* f );

Pagetable*
pagetable_create()
{
    Pagetable* pagetable;

    pagetable = fila_create ();

    return pagetable;
}

void
pagetable_map( Pagetable * p, int endereco_mvirtual, int endereco_mfisica )
{
    Linha_Pagetable* linha = ( Linha_Pagetable* ) malloc( sizeof( Linha_Pagetable ) );
    
    linha->endereco_mvirtual = endereco_mvirtual;
    linha->endereco_mfisica = endereco_mfisica;
    linha->in_memory = 0;

    fila_add( p,linha );
}

Linha_Pagetable*
pagetable_drop( Pagetable* f )
{
    Linha_Pagetable* remover = fila_drop( f )->data;

    return remover;
}

Linha_Pagetable*
pagetable_find( Pagetable* f, int endereco_mvirtual )
{
    No* p = f->start;
    Linha_Pagetable *l;
    while( p )
    {
        l = ( Linha_Pagetable* ) p->data;
        if( l->endereco_mvirtual == endereco_mvirtual )
            return p->data;

        p = p->prox;
    }
    return p->data; // not found
}