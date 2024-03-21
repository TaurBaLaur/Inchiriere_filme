#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;

class Film
{
private:
	string titlu;
	string gen;
	int an;
	string actor_principal;

public:
	//constructor default
	Film() = default;
	//constructor cu parametrii
	Film(const string titlu, const string gen, int an, const string actor) : titlu{ titlu }, gen{ gen }, an{ an }, actor_principal{ actor } {};
	//constructor de copiere
	Film(const Film& ot) : titlu{ ot.titlu }, gen{ ot.gen }, an{ ot.an }, actor_principal{ ot.actor_principal }
	{
		//cout << "constructor copiere domain\n";
	};

	string get_titlu() const;
	string get_gen() const;
	const int& get_an() const noexcept;
	string get_actor_principal() const;

	void set_titlu(string titlu_nou);
	void set_gen(string gen_nou);
	void set_an(int an_nou) noexcept;
	void set_actor_principal(string actor_principal_nou);
};

/*
* Compara filmele dupa titlu
* returneaza true daca f1.get_titlu e mai mic decat f2.get_titlu
*/
bool compara_titlu(const Film& f1, const Film& f2);

/*
* Compara filmele dupa actorul principal
* returneaza true daca f1.get_actor_principal e mai mic decat f2.get_actor_principal
*/
bool compara_actor_principal(const Film& f1, const Film& f2);

/*
* Compara filmele dupa an si gen
* returneaza true daca f1.get_an e mai mic decat f2.get_an, dar si cand
	f1.get_an = f2.get_an si f1.get_gen e mai mic decat f2.get_gen
*/
bool compara_an_gen(const Film& f1, const Film& f2);

void teste_domain();