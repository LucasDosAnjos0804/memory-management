/*
    Objeto abstracao de uma pagina de memoria virtual
*/

#define PAGE_SIZE 4

typedef struct Pagina
{
    /*
        algumas caracteristicas sobre paginas
    */

    int endereco_virtual;
    int endereco_fisico;
    int bit_r;                      // bit_r da pagina 1 se ela foi referenciada recentemente 0 se não
    int tam;

    struct Pagina* prox;            // proxima pagina no encadeamento
    struct Pagina* ant;             // pagina anterior no encadeamento

}Pagina;

Pagina* pagina_create ( int endereco_v, int endereco_f );


/// @brief Cria uma pagina
Pagina*
pagina_create( int endereco_v, int endereco_f )
{
    Pagina* p = (Pagina*) malloc (sizeof(Pagina));
    p->endereco_virtual = endereco_v;
    p->endereco_fisico = endereco_f;
    p->tam = PAGE_SIZE;

    p->prox = p->ant = NULL;
    
    //logs(l,"Pagina criada",'e');
    return p;
}
