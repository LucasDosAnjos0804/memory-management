
/*
    Objeto abstracao da estrutura de dados usada no algoritmo fifo
    de mapeamento de memoria
*/


#define FIFO_SIZE 20

typedef Fila Fifo;

Fifo* fifo_create();
Pagina* fifo_drop(Fifo* f);
void fifo_add( Fifo* f, Pagina* p);
void fifo_print( Fifo* f);

/// @brief Cria um Fifo
/// @param tam tamanho do FIFO
Fifo*
fifo_create()
{
    Fifo* f = (Fifo*) malloc (sizeof(Fifo));
    if (f)
    {
        f->tam_atual = 0;
        f->start = NULL;
        f->end = NULL;
    }
    return f;
}


/// @brief Retira a pagina mais antiga (o primeiro elemento) do fifo
/// @param f Endereco de memoria de FIFO
Pagina*
fifo_drop(Fifo* f)
{
    Pagina* remover = fila_drop(f)->data;

    return remover;
}


/// @brief Adiciona uma pagina ao final de um fifo
/// e retira o seu elemento mais antigo se a fila já estiver cheia
/// @param f Endereco de memoria de FIFO
/// @param p Pagina que sera adicionada ao FIFO 
void
fifo_add( Fifo* f, Pagina* p)
{
    // falta a condição de memoria cheia
    if (f->tam_atual >= FIFO_SIZE)
    {
        fila_drop(f);
    }
    fila_add (f,p);
    
    logs(l,"Pagina adicionada ao FIFO",'e');
}


/// @brief Exibe cada elemento de FIFO
/// @param f Endereco de memoria de FIFO
void
fifo_print( Fifo* f)
{
    printf("FIFO : ");
    fila_print(f);
    puts("");
}