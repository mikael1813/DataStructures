#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md) : md(_md) {
	/*Complexitate 0(n log2 n) caz mediu, caz defavorabil O(n^2)*/
	this->poz = 0;
	this->copie_tabela = new TElem[this->md.dim()];
	int i = -1;
	for (int j = 0; j < md.m; j++)
		if (md.tabela[j].val_cheie != md.Nil.val_cheie && md.tabela[j].val_cheie != md.Sters.val_cheie)
			for (auto k : md.tabela[j].valori) {
				i++;
				copie_tabela[i].first = md.tabela[j].val_cheie;
				copie_tabela[i].second = k;
			}
}

TElem IteratorMD::element() const {
	/*Complexitate 0(1)*/
	if (!this->valid())
		throw exception();
	TElem e;
	e.first = this->copie_tabela[poz].first;
	e.second = this->copie_tabela[poz].second;
	return e;
}

bool IteratorMD::valid() const {
	/*Complexitate 0(1)*/
	if (this->md.dim() > this->poz)
		return true;
	return false;
}

void IteratorMD::urmator() {
	/*Complexitate 0(1)*/
	if (!this->valid())
		throw exception();
	this->poz++;
}

void IteratorMD::prim() {
	/*Complexitate 0(1)*/
	this->poz = 0;
}
