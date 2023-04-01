/*
    Uma abstração do que é uma memória no computador
*/

#define MEM_SIZE 10

typedef struct Memory
{
    int data[MEM_SIZE]; // cada linha da memoria é um inteiro
}Memory;

Memory* memory_create ();
int memory_read (Memory *m, int endereco);
void memory_write (Memory *m, int endereco, int data);

Memory*
memory_create ()
{
    Memory *m;

    m = malloc (sizeof (Memory));

    return m; // se for NULL é um erro
}

int
memory_read(Memory *m, int endereco)
{
    return m->data[endereco];
}

void
memory_write (Memory *m, int endereco, int data)
{
    m->data[endereco] = data;
}