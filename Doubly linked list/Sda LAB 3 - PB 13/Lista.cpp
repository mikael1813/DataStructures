
#include <exception>
#include <assert.h>

#include "IteratorLP.h"
#include "Lista.h"

#include <iostream>

using namespace std;

Lista::Lista() {
	/*Complexitate 0(1) */
	this->primul = nullptr;
}

NodLSI* Lista::creazanod(int e) {
	/*Complexitate 0(1) */
	NodLSI* p = new NodLSI;
	p->urm = nullptr;
	p->e = e;
	return p;
}

int Lista::dim() const {
	/*Complexitate 0(1) */
	return nr_elem;
}


bool Lista::vida() const {
	/*Complexitate 0(1) */
	if (nr_elem == 0)return true;
	return false;
}

IteratorLP Lista::prim() const {
	/*Complexitate 0(1) */
	return IteratorLP(*this);
}

TElem Lista::element(IteratorLP poz) const {
	/*Complexitate 0(1) */
	return poz.element();
}

TElem Lista::sterge(IteratorLP& poz) {
	/*Complexitate caz mediiu 0(capacitate), caz favorabil O(1) */
	if (poz.nod == nullptr)
		throw exception();
	else {
		
		NodLSI* c = this->primul;
		if (c == poz.nod) {
			this->primul = c->urm;
			this->nr_elem--;
			return c->e;
		}
		else {
			while (c->urm != poz.nod && c != nullptr) {
				c = c->urm;
			}
			if (c != nullptr) {
				TElem e = c->urm->e;
				c->urm = c->urm->urm;
				poz.nod = c->urm;
				this->nr_elem--;
				return e;
			}
		}

	}
}

IteratorLP Lista::cauta(TElem e) const {
	/*Complexitate caz mediiu 0(capacitate), caz favorabil O(1) */
	NodLSI* c = this->primul;
	while (c->e != e && c->urm!= nullptr) {
		c = c->urm;
	}

	IteratorLP it(*this);

	if (c->e != e) {
		it.nod = nullptr;
	}
	else {
		it.nod = c;
	}
	return it;
}

TElem Lista::modifica(IteratorLP poz, TElem e) {
	/*Complexitate 0(1) */
	if (poz.nod == nullptr)
		throw exception();
	else {
		TElem f = poz.nod->e;
		poz.nod->e = e;
		return f;
	}
}

void Lista::adauga(IteratorLP& poz, TElem e) {
	/*Complexitate caz mediiu 0(capacitate), caz favorabil O(1) */
	if (poz.nod == nullptr)
		throw exception();
	else {
		NodLSI* c = this->primul;
		while (c != poz.nod && c != nullptr) {
			c = c->urm;
		}
		NodLSI* p = creazanod(e);
		p->urm = c->urm;
		c->urm = p;
		poz.nod = p;
	}
}

void Lista::adaugaInceput(TElem e) {
	/*Complexitate 0(1) */
	NodLSI* p = creazanod(e);
	p->urm = this->primul;
	this->primul = p;
	this->nr_elem++;
}

void Lista::adaugaSfarsit(TElem e) {
	/*Complexitate 0(capacitate) */
	NodLSI* p = creazanod(e);
	if (this->primul != nullptr) {
		NodLSI* c = this->primul;
		while (c->urm != nullptr) {
			c = c->urm;
		}
		c->urm = p;
	}
	else {
		this->primul = p;
	}
	this->nr_elem++;
}

Lista::~Lista() {
	/*Complexitate 0(capacitate) */
	NodLSI* unu;
	NodLSI* doi;
	unu = this->primul;
	if (unu == nullptr) {
		delete unu;
	}
	else {
		while (unu != nullptr) {
			doi = unu;
			unu = unu->urm;
			delete doi;
		}
	}
}