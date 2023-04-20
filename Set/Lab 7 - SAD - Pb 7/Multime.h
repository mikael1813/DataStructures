#pragma once
#include <iostream>

typedef int TElem;

#define NULL_TELEM -11111111

#define Cazul1 (left[index] != NULL_TELEM && right[index] == NULL_TELEM) || (left[index] == NULL_TELEM && right[index] != NULL_TELEM)
#define Caz_left (left[index] != NULL_TELEM && right[index] == NULL_TELEM)
#define Caz_right (left[index] == NULL_TELEM && right[index] != NULL_TELEM)
#define Cazul0 ((left[i] != NULL_TELEM && right[i] == NULL_TELEM) || (left[i] == NULL_TELEM && right[i] != NULL_TELEM) || (left[i] == NULL_TELEM && right[i] == NULL_TELEM)) && (elemente[i] > left[index] && elemente[i] < right[index])
#define Frunza (left[index] == NULL_TELEM && right[index] == NULL_TELEM)
 
typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;

class Multime {

	friend class IteratorMultime;

private:
	/* aici e reprezentarea */
	int* left, * right, * null;
	TElem* elemente;
	int dimens;
	int nr_elem;
	int rad;

public:
	//constructorul implicit
	Multime();

	void realocare();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;


	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();

	void suma() {
		int s = 0;
		for (int i = 0; i <= dimens; i++) {
			if (elemente[i] != NULL_TELEM) {
				s = s + elemente[i];
				std::cout << elemente[i] << " ";
			}
		}
		std::cout << s << std::endl;
	}

};
