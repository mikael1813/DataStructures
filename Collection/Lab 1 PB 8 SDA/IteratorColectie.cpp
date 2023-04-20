#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/*Complexitate 0(n^2) caz mediu, caz defavorabil O(n^2)*, cel mai bun caz O(n)*/
	this->index = 0;
	bool ok = false;

	//bubble sort by rel
	while (!ok) {
		ok = true;
		for (int i = 0; i < col.nr_elem - 1; i++) {
			if (!rel(col.lista[i].e, col.lista[i + 1].e)) {
				Element e = col.lista[i + 1];
				col.lista[i + 1] = col.lista[i];
				col.lista[i] = e;
				ok = false;
			}
		}
	}
}

TElem IteratorColectie::element() const {
	//Complexitate O(1)
	return col.lista[this->index].e;
}

bool IteratorColectie::valid() const {
	//Complexitate O(1)
	if (this->index >= col.nr_elem || this->index < 0) {
		return false;
	}
	return true;
}

void IteratorColectie::urmator() {
	//Complexitate O(1)
	if (this->index >= col.dimensiune) {
		throw std::exception();
	}
	this->index++;
}

void IteratorColectie::prim() {
	/* Complexitate O(1) */
	this->index = 0;
}