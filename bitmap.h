/*
    uma abstração do que é uma estrutura bimap mantida pelo gerenciador de memoria

    bitmap serve para dizer ao SO qual endereço virtual está livre 
*/
#define BITMAP_SIZE (int) VMEMORY_SIZE / PAGE_SIZE
//                                  20 / 4         = 5

typedef struct Bitmap
{
    int data[BITMAP_SIZE];
}Bitmap;

Bitmap* bitmap_create ();
int bitmap_find (Bitmap* bitmap);
void bitmap_print (Bitmap* bitmap);
void bitmap_free (Bitmap* bitmap, int endereco);

Bitmap*
bitmap_create ()
{
    Bitmap *bitmap;

    bitmap = (Bitmap *) malloc (sizeof (Bitmap));

    return bitmap;
}

int
bitmap_find (Bitmap* bitmap)
{
    int i;

    for (i = 0; i < BITMAP_SIZE; i++)
    {
        if (bitmap->data[i] == 0)
        {   
            bitmap->data[i] = 1;
            return i;
        }
    }

    return -1;
}

void
bitmap_free (Bitmap* bitmap, int endereco)
{
    bitmap->data[0] = 0;
}

void
bitmap_print (Bitmap* bitmap)
{
    int i;
    printf ("BITMAP:\n");
    for (i = 0; i < BITMAP_SIZE; i++)
    {
        printf ("%d %d\n", i, bitmap->data[i]);
    }
}