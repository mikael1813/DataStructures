#pragma once
#include<vector>
#include<utility>

using namespace std;
#define NULL_TCHEIE = 0

typedef int TCheie;
typedef int TValoare;



typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

struct elem {
	TCheie val_cheie;
	vector <TValoare> valori{};
};



class MD
{
	friend class IteratorMD;

private:
	/* aici e reprezentarea */
	int m;
	int nr_elem;
	elem* tabela;
	elem Nil, Sters;


public:
	// constructorul implicit al MultiDictionarului
	MD();

	int dublu(TCheie c,int i);

	void afisare();

	void realocare();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) ;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	TCheie cheieMaxima() const;

	// destructorul MultiDictionarului	
	~MD();



};
