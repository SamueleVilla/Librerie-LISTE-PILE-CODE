
/* Libreria funzioni principali delle liste semplici*/

/* definizione del tipoLista / nodo */
typedef struct s_nodo
{
	int value;			 // campo informazione
	struct s_nodo *next; // puntatore al nodo successivo
} Nodo;
typedef Nodo *Pnodo;
typedef Nodo *Lista;

//------------------------------------------------ FUNZIONI PRIMITIVE ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

/* inizializza una lista vuota [NULL] */
Lista lista_vuota()
{
	return NULL;
}

/* La funzione ritorna true se la lista e' vuota; false se ha almeno un elemento */
bool is_vuota(Lista mLista)
{
	if (mLista == NULL)
		return true;
	else
		return false;
}

/* La funzione inserisce un elemento in testa alla lista */
void inserisci_testa(int value, Lista *mLista)
{
	Pnodo new_nodo = (Pnodo)malloc(sizeof(Nodo));
	if (new_nodo == NULL)
		exit(4);

	// inserimento valori	//
	new_nodo->value = value;
	// collego i puntatori	//
	new_nodo->next = *mLista;
	*mLista = new_nodo;
}

/* La funzione inserisce un elemento in coda alla lista*/
void inserisci_coda(int value, Lista *mLista)
{
	Pnodo p_current;

	if (*mLista == NULL)
	{
		*mLista = (Pnodo)malloc(sizeof(Nodo));
		(*mLista)->value = value;
		(*mLista)->next = NULL;
	}

	p_current = *mLista;
	while (p_current->next != NULL)
		p_current = p_current->next;

	p_current->next = (Pnodo)malloc(sizeof(Nodo));
	p_current = p_current->next;

	p_current->value = value;
	p_current->next = NULL;
}

/* La funzione ritorna una lista di n elementi presi come parametro */
Lista lista_casuale(int n_element)
{
	srand(time(NULL));
	Lista list_head = NULL;

	for (int i = 0; i < n_element; i++)
	{
		Pnodo newNodo = (Pnodo)malloc(sizeof(Nodo));
		newNodo->value = rand() % 100;
		newNodo->next = list_head;
		list_head = newNodo;
	}

	return list_head;
}

//------------------------------------------------ FUNZIONI NON PRIMITIVE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

/* la funzione ritorna il numero di elementi della lista*/
int conta_elementi(Lista mLista)
{
	Pnodo p = mLista;
	int contaElementi = 0;
	while (p != NULL)
	{
		p = p->next;
		contaElementi++;
	}
	return contaElementi;
}

/* la funzione stamapa la lista nella console */
void stampa_lista(Lista mLista)
{
	Pnodo p_current = mLista;

	if (is_vuota(mLista))
	{
		printf("NULL\n");
		return;
	}

	while (p_current != NULL)
	{
		printf("[%d] ---> ", p_current->value);
		p_current = p_current->next;
	}
	printf("NULL");
	putchar('\n');
}

/* La funzione ritorna valore del primo elemento della lista*/
int testa(Lista mLista)
{
	return mLista->value;
}

/* La funzione ritorna la lista senza il primo elemento */
Lista coda(Lista mLista)
{
	if (is_vuota(mLista))
		abort();
	else
		return mLista->next;
}

/* La funzione ritorna true se il dato è presente */
bool is_membro(int value, Lista root)
{

	if (is_vuota(root))
		return false;
	else if (value == testa(root))
		return true;
	else
		return is_membro(value, coda(root));
}

/* La funzione accoda la seconda lista alla prima lista*/
Lista accoda_liste(Lista first_list, Lista second_list)
{
	Pnodo p_current = first_list;

	while (p_current->next != NULL)
		p_current = p_current->next;

	p_current->next = second_list;

	return first_list;
}

/* La funzione rimuove l'elemento inserito dalla lista*/
void rimuovi_elemento(int value, Lista *mLista)
{
	Pnodo pCurrent = *mLista;
	Pnodo pPrev = NULL;

	if (!is_membro(value, *mLista))
		return;

	while (pCurrent != NULL && pCurrent->value != value)
	{
		pPrev = pCurrent;
		pCurrent = pCurrent->next;
	}

	if (pCurrent != NULL)
	{
		if (pPrev == NULL)
			*mLista = pCurrent->next;
		else
			pPrev->next = pCurrent->next;

		free(pCurrent);
	}
}

/* La funzione inserisce il valore dopo il nodo passato come parametro */
void inserisci_dopo(int value, Pnodo *node)
{
	Pnodo new_node = (Pnodo)malloc(sizeof(Nodo));
	if (new_node == NULL)
		exit(4);

	new_node->value = value;
	new_node->next = (*node)->next;
	(*node)->next = new_node;
}

/* La funzione inserisce elementi  in ordine crescente nella lista */
void inserisci_ordinato(int value, Lista *mLista)
{
	if (is_vuota(*mLista) || (*mLista)->value >= value)
	{
		inserisci_testa(value, mLista);
		return;
	}

	Pnodo pCurrent = *mLista;
	while (pCurrent->next != NULL)
	{
		if (pCurrent->next->value >= value)
			break;

		pCurrent = pCurrent->next;
	}
	inserisci_dopo(value, &pCurrent);
}

/* dealloca tutti i nodi della lista */
void dealloc(Lista *mLista)
{
	Pnodo curr = *mLista;
	while (curr != NULL)
	{
		Pnodo to_dealloc = curr;
		curr = curr->next;
		free(to_dealloc);
	}
	*mLista = NULL;
}

/* La funzione inverte la lista */
void inverti_Lista(Lista *mLista)
{
	Pnodo p_curr;
	Pnodo p_next;

	p_curr = *mLista;
	p_next = (*mLista)->next;

	p_curr->next = NULL;

	Pnodo p_curr2;

	p_curr2 = p_curr;

	while (p_next != NULL)
	{
		p_curr = p_next;
		p_next = p_next->next;
		p_curr->next = p_curr2;
		p_curr2 = p_curr;
	}
	*mLista = p_curr2;
}