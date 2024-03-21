#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock
#include "observer.h"
using std::vector;

class Watch_List :public Observable {
private:
	vector<Film> watchlist;
public:
	Watch_List() = default;
	/*
	* Adauga un film in watchlist
	*/
	void adauga_la_watchlist(const Film& f);
	/*
	* Sterge toate filmele din watchlist
	*/
	void goleste_watchlist();
	/*
	* Adauga un numar random de filme in watchlist
	*/
	void adauga_film_random_la_watchlist(vector<Film> filme_disponibile, int cate);
	/*
	* Returneaza un vector care contine toate filmele din watchlist
	*/
	const vector<Film>& get_filme_watchlist();
};