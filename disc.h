/*
    Uma abstração do que é uma unidade de memória não volátil no computador
*/

#define DISC_TAM 2048

typedef struct Disc
{
    int data[DISC_TAM];
}Disc;

int dread (Disc *d, int endereco);
void dwrite (Disc *d, int endereco, int data);

int
dread(Disc *d, int endereco)
{
    return d->data[endereco];
}

void
dwrite(Disc *d, int endereco, int data)
{
    d->data[endereco] = data;
}