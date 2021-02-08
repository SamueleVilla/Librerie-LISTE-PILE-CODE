/* Libreria contiene le funzioni pricipali delle code */

typedef struct s_nodo
{
    int val;             // campo informazione
    struct s_nodo *next; // puntatore nodo successivo
} Nodo;
typedef Nodo *Pnodo;
typedef struct
{
    int count;    // traccia elementi nella coda
    Nodo *header; // puntatore inzio coda
    Nodo *tailer; // puntatore fine coda
} coda_t;

/* La funzione inizializza la coda vuota*/
coda_t inizializza_coda()
{
    coda_t mCoda;
    mCoda.count = 0;
    mCoda.header = mCoda.tailer = NULL;
}

/* La funzione ritora true se la coda è vuota*/
bool is_vouta(coda_t *mCoda)
{
    if (mCoda->count == 0)
        return true;
    else
        return false;
}

/* La funzione inserisce un ulemento nella coda */
void in_coda(int value, coda_t *mCoda)
{
    Pnodo new_nodo = (Pnodo)malloc(sizeof(Nodo));
    if (new_nodo == NULL)
        exit(1);
    new_nodo->val = value;
    new_nodo->next = NULL;

    if (is_vouta(mCoda))
    {
        mCoda->header = mCoda->tailer = new_nodo;
    }
    else
    {
        mCoda->tailer->next = new_nodo;
        mCoda->tailer = new_nodo;
    }
    mCoda->count++;
}

/* La funzione rimuove il primo elemento nella coda */
void out_coda(coda_t *mCoda)
{
    if (is_vouta(mCoda))
        return;

    Pnodo to_dealloc = mCoda;
    mCoda->header = mCoda->header->next;
    mCoda->count--;
    free(to_dealloc);
}

/* La funzione dealloca tutti gli elementi dalla lista */
void dealloc_coda(coda_t *mCoda)
{

    while (mCoda->header != NULL)
    {
        Pnodo to_dealloc = mCoda->header;
        mCoda->header = mCoda->header->next;
        free(to_dealloc);
    }
    mCoda->header = mCoda->tailer = NULL;
    mCoda->count = 0;
}