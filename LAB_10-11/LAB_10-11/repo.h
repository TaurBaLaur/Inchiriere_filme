#pragma once
#include "domain.h"
#include <vector>
#include <string>
#include <unordered_map>
using std::vector;
using std::string;
using std::unordered_map;

class Repo_Abstract
{
public:
	virtual void store(const Film& f) = 0;
	virtual void sterge(const Film& f) = 0;
	virtual void modifica(const Film& f, const string& gen_nou, int an_nou) = 0;
	virtual const vector<Film>& get_filme() noexcept = 0;
	virtual const Film& find(string titlu, int an, string actor) = 0;
	virtual bool exista(const Film& f) = 0;
	virtual ~Repo_Abstract() = default;
};

class RepoException
{
private:
	string mesaje_de_eroare;
public:
	//constructor
	RepoException(string erori) : mesaje_de_eroare{ erori } {};

	string get_erori() const;
};

class Repo_Filme : public Repo_Abstract
{
private:
	vector<Film> filme;

public:
	//constructor default
	Repo_Filme() = default;
	//pt a nu copia repo-ul
	Repo_Filme(const Repo_Filme& ot) = delete;

	virtual ~Repo_Filme() = default;

	/*
	* Salveaza film
	*/
	virtual void store(const Film& f);

	/*
	* Sterge un film
	*/
	virtual void sterge(const Film& f);

	/*
	* Modifica un film
	*/
	virtual void modifica(const Film& f, const string& gen_nou, int an_nou);

	/*
	* Returneaza o lista de filme
	*/
	const vector<Film>& get_filme() noexcept;

	/*
	* Gaseste un film cu titlu, an si actor principal date
	*/
	const Film& find(string titlu, int an, string actor);

	/*
	* Verifica daca un film se gaseste in lista de filme
	*/
	bool exista(const Film& f);
};

class RepoFisier_Filme : public Repo_Filme
{
private:
	string nume_fisier;
	/*
	Incarca datele din fisier
	*/
	void load_from_file();
	/*
	* Salveaza datele din fisier
	* Format: titlu;an,gen,actor principal\n
	*/
	void save_to_file();
public:
	RepoFisier_Filme(string nume_fis) :Repo_Filme(), nume_fisier{ nume_fis } {
		load_from_file();
	};
	void store(const Film& f) override;

	void sterge(const Film& f) override;

	void modifica(const Film& f, const string& gen_nou, int an_nou) override;
};

class Repo_Lab : public Repo_Abstract
{
private:
	unordered_map<string, Film> filme;
	vector<Film> v_lab;
	double probabilitate;
	double genereaza_probabilitate_aleatoare();
public:
	//constructor default
	Repo_Lab(double prob) :probabilitate{ prob } {};
	//pt a nu copia repo-ul
	Repo_Lab(const Repo_Lab& ot) = delete;

	virtual ~Repo_Lab() = default;

	double get_probabilitate();
	/*
	* Salveaza film
	*/
	void store(const Film& f);

	/*
	* Sterge un film
	*/
	void sterge(const Film& f);

	/*
	* Modifica un film
	*/
	void modifica(const Film& f, const string& gen_nou, int an_nou);

	/*
	* Returneaza o lista de filme
	*/
	const vector<Film>& get_filme() noexcept;

	/*
	* Gaseste un film cu titlu, an si actor principal date
	*/
	const Film& find(string titlu, int an, string actor);

	/*
	* Verifica daca un film se gaseste in lista de filme
	*/
	bool exista(const Film& f);
};

void teste_repo();