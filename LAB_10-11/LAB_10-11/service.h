#pragma once
#include "repo.h"
#include "validator.h"
#include "watchlist.h"
#include "dto.h"
#include "undo.h"
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <unordered_map>
using std::vector;
using std::string;
using std::function;
using std::unordered_map;
using std::unique_ptr;

class Service_Filme
{
private:
	//Repo_Filme& rep;
	Repo_Abstract& rep;
	//Repo_Lab& rep;
	//RepoFisier_Filme& rep;
	FilmValidator& val;

	Watch_List watchlist_curent;

	vector<unique_ptr<Actiune_Undo>> undo_actions;

	/*
	* Functie de filtrare generala
	*/
	vector<Film> filtreaza_filme(function<bool(const Film&)> fct);

	/*
	*
	*/
	vector<Film> sorteaza_filme(bool (*functie_comparare)(const Film&, const Film&));
public:
	//costructor
	Service_Filme(Repo_Abstract& rep, FilmValidator& val) noexcept : rep{ rep }, val{ val } {};
	//pt a nu copia service-ul
	Service_Filme(const Service_Filme& ot) = delete;

	void undo();

	/*
	* Returneaza o lista cu toate filmele
	*/
	const vector<Film>& get_toate_filmele() const;

	/*
	* Adauga un nou film
	*/
	void adauga_film(const string& titlu, const string& gen, int an, const string& actor);

	/*
	* Sterge un film
	*/
	void sterge_film(const string& titlu, const string& gen, int an, const string& actor);

	/*
	* Modifica film
	*/
	void modifica_film(const string& titlu, const string& gen, int an, const string& actor, const string& gen_nou, int an_nou);

	/*
	* Cauta film
	*/
	const Film& cauta_film(const string& titlu, int an, const string& actor);

	/*
	* Filtare dupa titlu
	*/
	vector<Film> filtrare_titlu(string titlu);

	/*
	* Filtare dupa an
	*/
	vector<Film> filtrare_an(int an);

	/*
	* Sorteaza filmele dupa titlu
	*/
	vector<Film> sortare_titlu();

	/*
	* Sorteaza filmele dupa actor principal
	*/
	vector<Film> sortare_actor_principal();

	/*
	* Sorteaza filmele dupa an si gen
	*/
	vector<Film> sortare_an_gen();

	/*
	* Adauga un film in watchlist
	*/
	void adauga_in_watchlist(string titlu, int an, string actor);

	/*
	* Elimina toate filmele din watchlist
	*/
	void goleste_watchlist();

	/*
	* Adauga un numar aleator de filme in watchlist si returneaza cate filme s-au adaugat
	*/
	int adauga_random_in_watchlist(int cate);

	/*
	* Returneaza un vector cu toate filmele din watchlist
	*/
	const vector<Film>& get_watchlist();

	/*
	* rapoarte filme
	*/
	unordered_map<string, DTO> rapoarte_filme();

	void export_watchlist_to_html(const string& nume_fisier);

	Watch_List& get_watchlist_obj()
	{
		return watchlist_curent;
	}
};

void teste_service();