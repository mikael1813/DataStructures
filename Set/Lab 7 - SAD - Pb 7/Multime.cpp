#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
	/* Complexitate O(1) */
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

Multime::Multime() {
	/* Complexitate O(2) */
	nr_elem = 0;
	dimens = 2;
	left = (int*)malloc(sizeof(int) * dimens);
	right = (int*)malloc(sizeof(int) * dimens);
	null = (int*)malloc(sizeof(int) * dimens);
	elemente = (TElem*)malloc(sizeof(TElem) * dimens);
	for (int i = 0; i < 2; i++) {
		left[i] = NULL_TELEM;
		right[i] = NULL_TELEM;
		elemente[i] = NULL_TELEM;
		null[i];
	}
	rad = NULL_TELEM;
}

void Multime::realocare() {
	/* Complexitate O(dimensiune/2) */
	dimens = dimens * 2;
	left = (int*)realloc(left, sizeof(int) * dimens);
	right = (int*)realloc(right, sizeof(int) * dimens);
	null = (int*)realloc(null, sizeof(int) * dimens);
	elemente = (TElem*)realloc(elemente, sizeof(TElem) * dimens);
	for (int i = dimens / 2; i < dimens; i++) {
		left[i] = NULL_TELEM;
		right[i] = NULL_TELEM;
		elemente[i] = NULL_TELEM;
		null[i] = 1;
	}
}


bool Multime::adauga(TElem elem) {
	/* Complexitate caz mediu O(log2 n), caz favorabil O(1), caz defavorabil O(n) */
	if (nr_elem >= dimens) {
		realocare();
	}
	if (!cauta(elem)) {
		nr_elem++;
		if (rad == NULL_TELEM || elemente[rad]==NULL_TELEM) {
			rad = 0;
			elemente[rad] = elem;
			null[rad] = 0;
			return true;
		}
		else {
			int index = rad;
			bool ok = true;
			while (ok) {
				int k;
				if (elem < elemente[index]) {
					if (left[index] == NULL_TELEM || (elem > elemente[left[index]] && left[index] >= 0)) {
						if (left[index] == NULL_TELEM) {
							for (k = 0; k < dimens; k++) {
								if (elemente[k] == NULL_TELEM) {
									break;
								}
							}
							elemente[k] = elem;
							left[index] = k;
							null[k] = 0;
							return true;
						}
						else {
							ok = true;
							for (k = 0; k < dimens; k++) {
								if (elemente[k] == NULL_TELEM) {
									break;
								}
							}
							elemente[k] = elem;
							left[k] = left[index];
							left[index] = k;
							null[k] = 0;
							return true;
						}
					}
					else {
						index = left[index];
					}
				}
				else {
					if (right[index] == NULL_TELEM || (elem < elemente[right[index]] && right[index] >= 0)) {
						if (right[index] == NULL_TELEM) {
							for (k = 0; k < dimens; k++) {
								if (elemente[k] == NULL_TELEM) {
									break;
								}
							}
							elemente[k] = elem;
							right[index] = k;
							null[k] = 0;
							return true;
						}
						else {
							ok = true;
							for (k = 0; k < dimens; k++) {
								if (elemente[k] == NULL_TELEM) {
									break;
								}
							}
							elemente[k] = elem;
							right[k] = right[index];
							right[index] = k;
							null[k] = 0;
							return true;
						}
					}
					else {
						index = right[index];
					}
				}
			}
		}
	}
	return false;
}


bool Multime::sterge(TElem elem) {
	int index;
	bool gasit = false;
	for (index = 0; index < dimens; index++) {
		if (elemente[index] == elem && null[index] == 0) {
			gasit = true;
			break;
		}
	}
	if (gasit) {
		nr_elem--;
		if (Frunza) {
			int i = 0;
			while (left[i] != index && right[i] != index) {
				i++;
			}
			if (left[i] == index) {
				left[i] = NULL_TELEM;
				elemente[index] = NULL_TELEM;
				null[index] = 1;
			}
			if (right[i] == index) {
				right[i] = NULL_TELEM;
				elemente[index] = NULL_TELEM;
				null[index] = 1;
			}
		}
		else {
			if (Cazul1) {
				if (Caz_left) {
					elemente[index] = NULL_TELEM;
					int i = 0;
					while (left[i] != index) i++;
					left[i] = left[index];
					left[index] = NULL_TELEM; 
					null[index] = 1;
				}
				else {
					elemente[index] = NULL_TELEM;
					int i = 0;
					while (right[i] != index) i++;
					right[i] = right[index];
					right[index] = NULL_TELEM;
					null[index] = 1;
				}
			}
			else {
				int i = 0;
				while (!Cazul0) i++;
				int c = i; i = index; index = c;
				if (Caz_left) {
					elemente[i] = elemente[index];
					int k = 0;
					while (left[k] != index) k++;
					left[k] = right[index];
					left[index] = NULL_TELEM;
					elemente[index] = NULL_TELEM;
					null[index] = 1;
				}
				else {
					if (Caz_right) {
						elemente[i] = elemente[index];
						int k = 0;
						while (right[k] != index) k++;
						right[k] = right[index];
						right[index] = NULL_TELEM;
						elemente[index] = NULL_TELEM;
						null[index] = 1;
					}
					else {
						elemente[i] = elemente[index];
						int k = 0;
						while (left[k] != index && right[k] != index) {
							k++;
						}
						if (left[k] == index) {
							left[k] = NULL_TELEM;
							elemente[index] = NULL_TELEM;
							null[index] = 1;
						}
						if (right[k] == index) {
							right[k] = NULL_TELEM;
							elemente[index] = NULL_TELEM;
							null[index] = 1;
						}
					}
				}
			}
		}
	}
	return gasit;

}


bool Multime::cauta(TElem elem) const {
	/* Complexitate O(capacitate) */
	for (int i = 0; i < dimens; i++) {
		if (elemente[i] == elem && null[i] == 0) {
			return true;
		}
	}
	return false;
}


int Multime::dim() const {
	/* Complexitate O(1) */
	return nr_elem;
}



bool Multime::vida() const {
	/* Complexitate O(1) */
	if (nr_elem == 0) return true;
	return false;
}

IteratorMultime Multime::iterator() const {
	/* Complexitate O(1) */
	return IteratorMultime(*this);
}


Multime::~Multime() {
	//free(left);
	//free(right);
	//free(null);
	//free(elemente);
}





