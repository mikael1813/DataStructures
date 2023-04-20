#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>
#include <iostream>


IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	/* Complexitate O(1) */
	index = 0;
}

TElem IteratorMultime::element() const {
	/* Complexitate O(1) */
	if (index >= mult.dimens || mult.null[index] == 1) {
		throw std::exception();
	}
	else {
		return mult.elemente[index];
	}
}

bool IteratorMultime::valid() const {
	/* Complexitate O(1) */
	if (mult.null[index] == 0 && index<mult.dimens) return true;
	return false;
}

void IteratorMultime::urmator() {
	/* Complexitate O(dimensiune) */
	TElem e = mult.elemente[index];
	int min = 9999999999, k = 0;
	bool ok = true;
	for (int i = 0; i < mult.dimens; i++) {
		if (min > mult.elemente[i] && mult.elemente[i] > mult.elemente[index] && mult.null[i] == 0) {
			k = i;
			min = mult.elemente[i];
			ok = false;
		}
	}
	if (ok) {
		index = mult.dimens;
	}
	else {
		index = k;
	}
}

void IteratorMultime::prim() {
	/* Complexitate O(dimensiune) */
	int min = 9999999999, k = 0;
	for (int i = 0; i < mult.dimens; i++) {
		if (min > mult.elemente[i] && mult.elemente[i] != NULL_TELEM) {
			k = i;
			min = mult.elemente[i];
		}
	}
	index = k;
}
