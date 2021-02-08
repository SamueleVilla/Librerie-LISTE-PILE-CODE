/* Libreria contiene le fuuzioni delle Liste-Doppiamente-Puntate */

//Definizione della struttura //
typedef struct s_nodo
{
	// campo informzioni //
	int val;
	// putantaori ai nodi//
	struct s_nodo *next; // nodo successivo
	struct s_nodo *prev; // nodo precedente
} Nodo;
typedef Nodo *DLista;
typedef Nodo *Pnodo;

//-----------------------------------------------------Definizione delle funzioni-----------------------------------------//

/* La funzione inizializza la lista vuota */
DLista inizilizza_lista()
{
	return NULL;
}

/* La funzione ritorna true se la lista non contiene nessun elemento */
bool is_vuota(DLista mLista)
{
	if (mLista == NULL)
		return true;
	else
		return false;
}

/* La funzione ritorna true se il dato è presente nella lista */
bool is_membro(int value, DLista mLista)
{
	if (is_vuota(mLista))
		return false;

	if (mLista->val == value)
		return true;
	else
		return is_membro(value, mLista->next);
}

/* La funzione inserisce un elemento in testa alla lista */
void inserisci_testa(int value, DLista *mLista)
{
	Pnodo new_nodo = (Pnodo)malloc(sizeof(Nodo));
	if (new_nodo == NULL)
		exit(1);
	new_nodo->val = value; // inserimento dell'informazione

	// se la lista è vuota
	if (is_vuota(*mLista))
	{
		new_nodo->prev = NULL;
		new_nodo->next = NULL;
		*mLista = new_nodo;
		return;
	}
	// se la lista ha almeno un elemento
	new_nodo->next = *mLista;
	new_nodo->prev = NULL;
	new_nodo->next->prev = new_nodo;
	*mLista = new_nodo;
}

/* La funzione inserisce un elemento in coda alla lista */
void inserisci_coda(int value, DLista *mLista)
{
	Pnodo new_nodo = (Pnodo *)malloc(sizeof(Nodo));
	if (new_nodo == NULL)
		exit(1);
	new_nodo->val = value; // inserimento dell'informazione

	// se la lista è vuota
	if (is_vuota(mLista))
	{
		new_nodo->prev = NULL;
		new_nodo->next = NULL;
		*mLista = new_nodo;
		return;
	}

	// se la lista ha almeno un elemento
	Pnodo p_curr = *mLista;
	while (p_curr->next != NULL)
		p_curr = p_curr->next;
	p_curr->next = new_nodo;
	new_nodo->prev = p_curr;
	new_nodo->next = NULL;
}

/* La funzione inserisce gli elementi in ordine nella lista*/
void inserisci_ordinato(int value, DLista *mLista)
{
	if (is_vuota(*mLista) || (*mLista)->val >= value)
	{
		inserisci_testa(value, mLista);
		return;
	}

	Pnodo Pcurr = *mLista;
	while (Pcurr->next != NULL)
	{
		if (Pcurr->next->val >= value)
			break;

		Pcurr = Pcurr->next;
	}
	inserisci_dopo(value, &Pcurr);
}

/* La funzione inserisce un nuovo nodo dopo il nodo inserito come parametro */
void inserisci_dopo(int value, Pnodo *nodo)
{
	Pnodo new_nodo = (Pnodo)malloc(sizeof(Nodo));
	if (new_nodo == NULL)
		exit(1);
	new_nodo->val = value;

	if ((*nodo)->next == NULL)
	{
		new_nodo->next = (*nodo)->next;
		new_nodo->prev = *nodo;
		(*nodo)->next = new_nodo;
	}
	else
	{
		new_nodo->next = (*nodo)->next;
		new_nodo->next->prev = new_nodo;
		new_nodo->prev = *nodo;
		(*nodo)->next = new_nodo;
	}
}

void rimuovi_elemento(int value, DLista *mLista)
{
	if (is_vuota(mLista))
		return;

	Pnodo p_curr = *mLista;
	while (p_curr != NULL)
	{
		if (p_curr->val == value)
		{
			// è l'unico elemento della lista
			if (p_curr->prev == NULL && p_curr->next == NULL)
			{
				*mLista = NULL;
				free(p_curr);
				return;
			}
			// elemento in testa alla lista
			else if (p_curr->prev == NULL)
			{
				*mLista = p_curr->next;
				(*mLista)->prev = NULL;
				free(p_curr);
				return;
			}
			// è l'ultimo elemento della lista
			else if (p_curr->next == NULL)
			{
				p_curr->prev->next = p_curr->next;
				free(p_curr);
				return;
			}
			// elemento in mezzo alla lista
			else
			{
				p_curr->prev->next = p_curr->next;
				p_curr->next->prev = p_curr->prev;
				free(p_curr);
				return;
			}
		}
		p_curr = p_curr->next;
	}
}

void dealloc_lista(DLista *mLista)
{
	Pnodo p_curr = *mLista;
	while (p_curr != NULL)
	{
		Pnodo to_dealloc = p_curr;
		p_curr = p_curr->next;
		free(to_dealloc);
	}
	*mLista = NULL;
}

void stampa_lista(DLista mLista)
{
	for (Pnodo p = mLista; p != NULL; p = p->next)
		printf("[%d]-", p->val);
	printf("NULL\n");
}
