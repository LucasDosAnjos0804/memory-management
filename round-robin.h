
typedef Fila Round;

Round* round_create();
void round_add( Round *robin, Job *j );
Job * round_drop( Round* robin );
void round_print( Round* robin );

Round*
round_create()
{
    Round* r = fila_create();
}

void
round_add( Round *robin, Job *j )
{
    fila_add( robin, j );
}

Job *
round_drop( Round* robin )
{
    return fila_drop( robin )->data;
}

void
round_print( Round* robin )
{
    printf("ROUND ");
    fila_print( robin );
    puts("");
}