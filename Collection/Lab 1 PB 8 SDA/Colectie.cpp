#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	/* Complexitate O(1) */
	if (e1 <= e2) return true;
	return false;
}

Colectie::Colectie() {
	/* Complexitate O(1) */
	this->lista = (Element*)malloc(sizeof(Element) * 2);
	this->nr_elem = 0;
	this->dimensiune = 2;
}

void Colectie::realocare() {
	/* Complexitate O(1) */
	this->dimensiune = this->dimensiune * 2;
	this->lista = (Element*)realloc(this->lista, sizeof(Element) * this->dimensiune);
}

void Colectie::adauga(TElem e) {
	/* Complexitate O(capacitate) */
	Element t;
	t.e = e;
	t.frec = 0;
	if (this->nr_elem >= this->dimensiune) {
		realocare();
	}
	for (int i = 0; i < this->nr_elem; i++) {
		if (this->lista[i].e == e) {
			t.frec = lista[i].frec;
			lista[i].frec++;
		}
	}
	t.frec++;
	this->lista[nr_elem] = t;
	this->nr_elem++;

}


bool Colectie::sterge(TElem e) {
	/* Complexitate O(capacitate) */
	bool find = false;
	int index = 0;
	for (int i = 0; i < this->nr_elem; i++) {
		if (this->lista[i].e == e) {
			index = i;
			this->lista[i].frec--;
			find = true;
		}
	}
	if (find) {
		for (int i = index; i < this->nr_elem; i++){
			this->lista[i] = this->lista[i + 1];
		}
		this->nr_elem--;
	}
	return find;
}


bool Colectie::cauta(TElem elem) const {
	/* Complexitate caz mediu O(capacitate), caz favorabil O(1)*/
	bool find = false;
	for (int i = 0; i < this->nr_elem; i++) {
		if (this->lista[i].e == elem) {
			find = true;
			break;
		}
	}
	return find;
}


int Colectie::nrAparitii(TElem elem) const {
	/* Complexitate O(capacitate) */
	int nr = 0;
	for (int i = 0; i < this->nr_elem; i++) {
		if (this->lista[i].e == elem) {
			nr = this->lista[i].frec;
			break;
		}
	}
	return nr;
}



int Colectie::dim() const {
	/* Complexitate O(1) */
	return this->nr_elem;
}


bool Colectie::vida() const {
	/* Complexitate O(1) */
	if (this->nr_elem == 0) return true;
	return false;
}


IteratorColectie Colectie::iterator() const {
	/* Complexitate O(1) */
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	/* Complexitate O(1) */
	free(this->lista);
}