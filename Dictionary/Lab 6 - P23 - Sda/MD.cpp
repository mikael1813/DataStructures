#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;


void MD::afisare() {
	/* Complexitate 0(capacitate) */
	int s = 0;
	for (int i = 0; i < m; i++) {
		cout << "Cheie: " << this->tabela[i].val_cheie;
		cout << endl<<"Valori ";
		for (auto j : this->tabela[i].valori) {
			cout << j << " ";
			if(j!=this->Nil.val_cheie && j!= this->Sters.val_cheie)
			s++;
		}
		cout << endl;
	}
	cout << "Raspuns = " << s << endl;
}

MD::MD() {
	/* Complexitate 0(m) */
	this->m = 4;
	this->Nil.val_cheie = -111111;
	this->Nil.valori.push_back(-111111);
	this->Sters.val_cheie = 111111;
	this->Sters.valori.push_back(111111);
	this->nr_elem = 0;
	this->tabela = new elem[m];
	for (int i = 0; i < m; i++)
	{
		this->tabela[i] = this->Nil;
	}
	//cout << "Done";
}

void MD::realocare() {
	/*Complexitate 0(m^2) caz defavorabil, 0(m) caz favorabil*/
	auto c = this->tabela;
	//this->nr_elem = 0;
	auto m1 = this->m;
	this->m = this->m * 2;
	int x = this->nr_elem;
	this->tabela = new elem[m];
	for (int i = 0; i < this->m; i++)
	{
		this->tabela[i].val_cheie = this->Nil.val_cheie;
		this->tabela[i].valori = this->Nil.valori;
	}
	for (int i = 0; i < m1; i++)
		for (auto j : c[i].valori) {
			this->adauga(c[i].val_cheie, j);
		}
	delete[]c;
	this->nr_elem = x;
}

int MD::dublu(TCheie c,int i) {
	/*Complexitate 0(1)*/
	return abs((abs(c % this->m) + i * (1 + abs(c % (this->m - 2)))) % this->m);
}


void MD::adauga(TCheie c, TValoare v) {
	/*Complexitate 0(capacitate) caz favorabil cu realocare
				   0(1) caz favorabil fara realocare
				   0(capacitate^2) caz defavorabil cu realocare
				   0(capacitate) caz defavorabil fara realocare*/
	int i = 0,j;
	elem e;
	e.val_cheie = c;
	e.valori = vector<int>{ v };
	bool gasit = false;
	do {
		j = this->dublu(c, i);

		if (this->tabela[j].val_cheie == c && !gasit) {
			this->tabela[j].valori.push_back(v);
			gasit = true;
			this->nr_elem++;
		}
		else
		if (this->tabela[j].val_cheie == this->Nil.val_cheie || this->tabela[j].val_cheie == this->Sters.val_cheie && !gasit) {
			this->tabela[j] = e;
			gasit = true;
			this->nr_elem++;
		}
		i++;

	} while (i!= this->m && !gasit);
	if (!gasit) {
		realocare();
		adauga(c, v);
	}
}


bool MD::sterge(TCheie c, TValoare v) {
	/* Complexitate O(capacitate) */

	int i = 0, j, s = -1;
	do {

		j = this->dublu(c, i);
		if (this->tabela[j].val_cheie == c) {
			s = -1;
			for (auto k : this->tabela[j].valori) {
				
				s++;
				if (v == k) {
					this->tabela[j].valori.erase(this->tabela[j].valori.begin() + s);
					this->nr_elem--;
					return true;
				}
			}
			if (this->tabela[j].valori.empty()) {
				this->tabela[j].val_cheie = this->Sters.val_cheie;
				this->tabela[j].valori = this->Sters.valori;
				//this->nr_elem--;
			}
		}
		i++;

	} while (this->tabela[j].val_cheie != this->Nil.val_cheie && i != this->m);

	return false;
}


vector<TValoare> MD::cauta(TCheie c)  {
	/*Complexitate O(nr chei)*/
	vector <TValoare> v{};
	int i = 0,j;
	do {
		j = this->dublu(c, i);
		if (this->tabela[j].val_cheie == c) {
			v = tabela[j].valori;
			break;
		}
		i++;
	} while (this->tabela[j].val_cheie != this->Nil.val_cheie && i != this->m);


	return v;
}


int MD::dim() const {
	/*Complexitate 0(1)*/
	
	return this->nr_elem;
}


bool MD::vid() const {
	/*Complexitate 0(1)*/
	if (this->nr_elem == 0) return true;
	else return false;
}

IteratorMD MD::iterator() const {
	/*Complexitate 0(1)*/
	return IteratorMD(*this);
}


MD::~MD() {
	/*Complexitate 0(1)*/
	delete[]this->tabela;
}

TCheie MD::cheieMaxima() const {
	/*Complexitate caz favorabil 0(1) daca nu exista elemente in tabela
				   caz defavorabil 0(capacitate) daca exista elemente in tabela trebuie sa se parcurga toata tabela pentru a afla chieia maxima*/
	TCheie max = 0;
	if (this->nr_elem != 0)
	for (int i = 0; i < this->m; i++)
		if (this->tabela[i].val_cheie != this->Nil.val_cheie && this->tabela[i].val_cheie != this->Sters.val_cheie && this->tabela[i].val_cheie > max)
			max = this->tabela[i].val_cheie;
	return max;
}