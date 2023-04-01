/*
    metodos uteis
*/
#include "fila.h"

typedef Fila Logs;

typedef struct Log_cat
{
    char u;
    int enabled;
}Log_cat;

Logs *l;

void add_log_cat( Logs *l, char u );
Log_cat* log_cat_find( Logs *l, char u);
int log_cat_enabled( Logs * l, char u );
void logs( Logs *l, char c[], char u );
void logs_on( Logs *l,char u );
void logs_off( Logs *l,char u );
void err( char c[] );

void
add_log_cat( Logs * l, char u )
{
    Log_cat* log_cat = (Log_cat*) malloc ( sizeof( Log_cat) );
    log_cat->u = u;
    log_cat->enabled = 1;
    fila_add( l, log_cat );
}

Log_cat*
log_cat_find( Logs * l, char u )
{
    Log_cat * log_cat;
    No* p = l->start;
    while (p)
    {
        log_cat = p->data;
        if ( log_cat->u == u )
            return log_cat;

        p = p->prox;
    }
    return NULL;
}

int
log_cat_enabled( Logs * l, char u )
{
    Log_cat * lc = log_cat_find( l, u );
    return lc ? lc->enabled : -1;
}

/// @brief Exibe um Log
/// @param c um texto a ser exibido
void
logs( Logs* l, char c[], char u )
{
    if (log_cat_enabled( l, u) == 1)
    {
        printf(" - logs: ");
        puts(c);
    }
}

/// @brief Saida especifica para erros
/// @param c Um texto de erro a ser exibido
void
err(char c[])
{
    printf(" - Error: ");
    puts(c);
}


/// @brief ativa os logs
void
logs_on( Logs *l, char u )
{
    Log_cat *lc = log_cat_find( l, u );
    lc->enabled = 1;
}

/// @brief desativa os logs
void
logs_off( Logs *l, char u )
{
    Log_cat *lc = log_cat_find( l, u );
    lc->enabled = 0;
}
