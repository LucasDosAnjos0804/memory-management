/*
    Objeto abstracao de uma pagina de memoria
*/

typedef struct Pagina
{

    /*
        algumas caracteristicas sobre paginas
    */

    unsigned int endereco_inicio; 
    unsigned int endereco_fim;
    int tam;
    int tam_atual;

    struct Pagina* prox; // proxima pagina no encadeamento
    struct Pagina* ant;  // pagina anterior no encadeamento

}Pagina;

Pagina* create_pagina(int endereco, int tam);


/// @brief Cria uma pagina com um endereco de inicio, endereco de fim, e tamanho;
/// @param endereco endereco de inicio do bloco
/// @param tam tamanho do bloco
Pagina*
create_pagina(int endereco, int tam)
{
    Pagina* p = (Pagina*) malloc (sizeof(Pagina));
    p->endereco_inicio = endereco;
    p->tam = tam;
    p->endereco_fim = p->endereco_inicio+p->tam;

    p->prox = p->ant = NULL;
    
    logs("Pagina criada");
    return p;
}
