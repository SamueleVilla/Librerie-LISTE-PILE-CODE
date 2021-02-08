/* La libreria contiene le funzioni dell Pile */

typedef struct s_nodo
{
    int val;             // campo informazioni
    struct s_nodo *next; // puntatore nodo successivo
} Nodo;
typedef Nodo *Pnodo;
typedef struct
{
    int count;
    Pnodo header;
} pila_t;

/* La funzione ritorna una pila vuota */
pila_t inizializza_pila()
{
    pila_t myPila;
    myPila.count = 0;
    myPila.header = NULL;
    return myPila;
}

/* La funzione ritorna true se la pila e' vuota */
bool is_vuota(pila_t *mPila)
{
    if (mPila->count == 0)
        return true;
    else
        return false;
}

/* La funzione aggiunge un elemento in testa alla pila */
void push(int value, pila_t *mPila)
{
    Pnodo new_nodo = (Pnodo *)malloc(sizeof(Nodo));
    if (new_nodo == NULL)
        exit(1);
    new_nodo->val = value; // inserimento informzione

    new_nodo->next = mPila->header;
    mPila->header = new_nodo;
}

/* La funzione rimuove un elemento in testa */
void pop(pila_t *mPila)
{
    Pnodo to_dealloc = mPila->header;
    mPila->header = mPila->header->next;
    mPila->count--;
    free(to_dealloc);
}

/* La funzione stampa il conntenuto della pila */
void stampa_pila(pila_t *mPila)
{
    for (Pnodo p = mPila->header; p != NULL; p = p->next)
        printf("[%d]--", p->val);
    printf("NULL\n");
}

/* La funzione dealloca tutti gli elementi della pila*/
void dealloc_pila(pila_t *mPila)
{
    if (mPila->header->next == NULL)
    {
        free(mPila->header);
        mPila->count--;
        mPila->header = NULL;
    }
    else
    {
        Pnodo to_dealloc = mPila->header;
        mPila->header = mPila->header->next;
        mPila->count--;
        free(to_dealloc);
        return dealloc_pila(mPila);
    }
}