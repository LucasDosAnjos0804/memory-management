/*
    Objeto abstracao da estrutura de dados usada no algoritmo segunda_chance
    de mapeamento de memoria
*/

#define SEGUNDA_CHANCE_SIZE 20

typedef Fila SegundaChance;

SegundaChance* segunda_chance_create();
Pagina* segunda_chance_drop( SegundaChance* f );
void segunda_chance_add( SegundaChance* f, Pagina* p);
void segunda_chance_print( SegundaChance* f);

SegundaChance*
segunda_chance_create()
{
    SegundaChance* f = (SegundaChance*) malloc (sizeof(SegundaChance));
    if (f)
    {
        f->tam_atual = 0;
        f->start = NULL;
        f->end = NULL;
    }
    return f;
}


Pagina*
segunda_chance_drop( SegundaChance* f )
{
    Pagina* remover = fila_drop(f)->data;
    while ( remover->bit_r )
    {
        remover->bit_r = 0;
        fila_add(f, remover);
        remover = fila_drop(f)->data;
    }
    return remover;
}

void
segunda_chance_add( SegundaChance* f, Pagina* p) {
    if ( f->tam_atual >= SEGUNDA_CHANCE_SIZE )
    {
        No* node = fila_drop(f);
        Pagina* pagina_removida = node->data;
        pagina_removida->bit_r = 0; // define o bit_r da pagina removida como 0
    }
    fila_add(f, p);
    logs(l, "Pagina adicionada ao segunda_chance", 'e');
}

void
segunda_chance_print( SegundaChance* f )
{
    printf("SEGUNDA-CHANCE : ");
    fila_print(f);
    puts("");
}