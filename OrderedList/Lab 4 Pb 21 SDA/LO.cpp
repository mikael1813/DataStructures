#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

LO::LO(Relatie r) {
	/* Complexitate O(2) */
	elem = (TElement*) malloc(sizeof(TElement) * 2);
	urm = (int*)malloc(sizeof(int) * 2);
	for (int i = 0; i < 2; i++) {
		urm[i] = -1;
		elem[i] = -111;
	}
	prim = -1;
	rel = r;
	nr_elem = 0;
	dimensiune = 2;
}

// returnare dimensiune
//returneaza numarul de perechi (cheie, valoare) din dictionar
int LO::dim() const {
	/* Complexitate O(1) */
	return nr_elem;
}

void LO::realocare() {
	/* Complexitate O(dimensiune/2) */
	dimensiune = dimensiune * 2;
	urm = (int*)realloc(urm, sizeof(int) * dimensiune);
	elem = (TElement*)realloc(elem, sizeof(TElement) * dimensiune);
	for (int i = dimensiune/2; i < dimensiune; i++) {
		urm[i] = -1;
		elem[i] = -111;
	}
}

// verifica daca LO e vida
bool LO::vida() const {
	/* Complexitate O(1) */
	if (nr_elem == 0) return true;
	return false;
}

// returnare element
//arunca exceptie daca i nu e valid
TElement LO::element(int i) const {
	/* Complexitate O(1) */
	if (i == -1 || elem[i] == -111 || i >= dimensiune) {
		throw exception();
	}
	else {
		return elem[i];
	}
}

// sterge element de pe o pozitie i si returneaza elementul sters
//arunca exceptie daca i nu e valid
TElement LO::sterge(int i) {
	/*Complexitate 0(capacitate) */
	if (i == -1 || elem[i] == -111 || i >= dimensiune) {
		
		throw exception();
	}
	else {
		int j = 0;
		while (urm[j] != i) {
			j++;
		}
		urm[j] = urm[i];
		if (urm[j] != -1) urm[j]--;
		TElement e = elem[i];
		nr_elem--;
		int k = i;
		while (k != -1) {
			int prec = k;
			k = urm[k];
			urm[prec] = urm[k];
			if (urm[prec] != -1) urm[prec]--;
			elem[prec] = elem[k];
		}

		///

		
		return e;
	}
}

// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
	/*Complexitate 0(capacitate) */
	if (nr_elem == 0) return -1;
	if (elem[prim] == e) return prim;
	int i = prim;
	while (i != -1 && i <dimensiune ){
		if (elem[i] == e)
			return i;
		i = urm[i];
	}
	return -1;

}



// adaugare element in LO
void LO::adauga(TElement e) {
	/*Complexitate 0(capacitate) */
	if (nr_elem == 0) {
		prim = 0;
		elem[prim] = e;
		nr_elem++;
	}
	else {
		if (nr_elem == dimensiune) {
			realocare();
		}
		
			int j = 0,index;
			for (j = 0; j < dimensiune; j++) {
				if (elem[j] == -111) {
					break;
				}
			}
			int i = prim;
			while (urm[i] != -1) {	
				i = urm[i];
			}
			urm[i] = j;
			elem[j] = e;
			nr_elem++;

		

	}
}

// returnare iterator
Iterator LO::iterator() {
	/* Complexitate O(1) */
	return Iterator(*this);
}


//destructor
LO::~LO() {
	/* Complexitate O(capacitate) */
	for (int i = 0; i < dimensiune; ++i) {
		//free(this->elem[i]);
		//free(this->urm[i]);
	}
	free(this->elem);
	free(this->urm);
}