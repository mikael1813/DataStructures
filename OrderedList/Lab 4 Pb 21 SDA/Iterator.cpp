#include "Iterator.h"
#include "LO.h"
#include <exception>
#include <iostream>
#include <algorithm> 
 
using namespace std;

Iterator::Iterator(const LO& lo) : lista(lo) {
	/*Complexitate 0(n^2) caz mediu, caz defavorabil O(n^2)*, cel mai bun caz O(n)*/
	int i = lista.prim;
	bool ok = false;
	if (lista.nr_elem >= 2)
		while (!ok) {
			ok = true;
			int i = lista.prim;
			while (lista.urm[i] != -1 && i<lista.dimensiune && lista.urm[i]<lista.dimensiune) {
				if (!lista.rel(lista.elem[i], lista.elem[lista.urm[i]])) {
					ok = false;
					TElement e = lista.elem[lista.urm[i]];
					//int j = lista.urm[lista.urm[i]];
					lista.elem[lista.urm[i]] = lista.elem[i];
					//lista.urm[lista.urm[i]] = i;
					lista.elem[i] = e;
					//lista.urm[i] = j;
				}
				i = lista.urm[i];
			}
		}
	curent = lista.prim;
}

void Iterator::prim() {
	/* Complexitate O(1) */
	curent = lista.prim;
}

void Iterator::urmator() {
	/* Complexitate O(1) */
	if (curent == -1) {
		throw std::exception();
	}		
	curent = lista.urm[curent];
}

bool Iterator::valid() const {
	/* Complexitate O(1) */
	if (curent == -1)return false;
	return true;
}

TElement Iterator::element() const {
	/* Complexitate O(1) */
	if (lista.elem[curent] == -111) {
		throw std::exception();
	}
	return lista.elem[curent];
}

