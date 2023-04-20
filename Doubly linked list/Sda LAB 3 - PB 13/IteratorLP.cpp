#include "IteratorLP.h"
#include "Lista.h"
#include <exception>
#include <assert.h>

using namespace std;

IteratorLP::IteratorLP(const Lista& l) :lista(l) {
	/*Complexitate 0(1) */
	this->nod = lista.primul;
}

void IteratorLP::prim() {
	/*Complexitate 0(1) */
	this->nod = lista.primul;
}

void IteratorLP::urmator() {
	/*Complexitate 0(1) */
	if (this->nod == nullptr)
		throw exception();
	else {
		this->nod = this->nod->urm;
	}
}

bool IteratorLP::valid() const {
	/*Complexitate 0(1) */
	if (this->nod != nullptr) return true;
	return false;
}

TElem IteratorLP::element() const {
	/*Complexitate 0(1) */
	if (this->nod == nullptr)
		throw exception();
	else {
		return this->nod->e;
	}
}

