
typedef struct Priority_row
{
    /*  Doc
        Descricao:
            Eh uma fila de prioridades;
            cada 'Row' eh uma lista ligada;
    */
    Round *p5; // prevencao a erro de memoria

    Round *p4; // mais alta prioridade
    Round *p3;
    Round *p2;
    Round *p1; // mais baixa prioridade

    int tam;
} Priority_row;

Priority_row* priority_row_create();
void priority_row_add( Priority_row *pr, Job *j);
Job* priority_row_drop( Priority_row *pr );
void priority_row_print( Priority_row *pr );


Priority_row*
priority_row_create()
{
    Priority_row *pr = malloc( sizeof( Priority_row ) );
    Round *p1 = round_create();
    Round *p2 = round_create();
    Round *p3 = round_create();
    Round *p4 = round_create();
    Round *p5 = round_create();

    pr->p1 = p1;
    pr->p2 = p2;
    pr->p3 = p3;
    pr->p4 = p4;
    pr->p5 = p5;
    
    pr->tam = 0;
    return pr;
}


void
priority_row_add( Priority_row *pr, Job *j )
{

    switch ( (int) j->priority )
    {
    case 1:
        round_add( pr->p1,j );
        break;

    case 2:
        round_add( pr->p2,j) ;
        break;

    case 3:
        round_add( pr->p3,j );
        break;

    case 4:
        round_add( pr->p4,j );
        break;

    default:
        if (j->priority < 1 || j->priority > 4)
            err("job com prioridade invalida!");
        break;
    }

    pr->tam++;
    //logs("Job adicionado a fila de prioridades");
}

Job*
priority_row_drop( Priority_row *pr ) 
{
    /*
        Dropa um job da primeira fila de prioridade que nao estiver vazia
    */
    Round *r;
    
    if ( pr->p4->tam_atual ) 
    {
        r = pr->p4;
    } else if ( pr->p3->tam_atual ) {
        r = pr->p3;
    } else if ( pr->p2->tam_atual ) {
        r = pr->p2;
    } else if ( pr->p1->tam_atual ) {
        r = pr->p1;
    } else {
        pr->tam--;
        return NULL;
    }
    pr->tam--;
    return round_drop(r);
}

void
priority_row_print( Priority_row *pr )
{
    printf("PRIORITY ROW:\n");
    round_print(pr->p4);
    round_print(pr->p3);
    round_print(pr->p2);
    round_print(pr->p1);
    puts("");
}
