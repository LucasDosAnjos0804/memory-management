/*
    abstração do que é uma memoria virtual mantida pelo gerenciador de memoria
*/
#include "paginas.h"
#include "fifo.h"

#define VMEMORY_SIZE 20
typedef Fifo Vmemory;

Pagina* vm_drop ( Vmemory* f );
int vm_addin ( Vmemory *f, Pagina* p );
void vm_print ( Vmemory* f );
Vmemory* vm_create ();

Vmemory*
vm_create()
{
    Vmemory* f = (Vmemory*) malloc (sizeof(Vmemory));
    if (f)
    {
        f->tam_atual = 0;
        f->start = NULL;
        f->end = NULL;
    }
    return f;
}

Pagina*
vm_drop(Vmemory* f)
{
    Pagina* remover = fifo_drop(f);

    return remover;
}

int
vm_addin( Vmemory* f, Pagina* p)
{
    if ( f->tam_atual >= VMEMORY_SIZE )
    {
        return 0; // nao foi possivel adicionar mais um no na fila
    } 

    fifo_add ( f,p ); 
    
    logs(l,"Pagina adicionada ao Vmemory",'e');
    return 1;
}

void
vm_print( Vmemory* f )
{
    printf("Vmemory : ");
    fifo_print(f);
    puts("");
}