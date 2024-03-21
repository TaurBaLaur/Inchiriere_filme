#include "watchlist.h"
using std::shuffle;

void Watch_List::adauga_la_watchlist(const Film& f)
{
	this->watchlist.push_back(f);
	notify();
}
void Watch_List::goleste_watchlist()
{
	this->watchlist.clear();
	notify();
}

void Watch_List::adauga_film_random_la_watchlist(vector<Film> filme_disponibile, int cate)
{
	shuffle(filme_disponibile.begin(), filme_disponibile.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	int i = 0;
	while (i < cate && filme_disponibile.size() > 0) {
		watchlist.push_back(filme_disponibile.back());
		filme_disponibile.pop_back();
		i++;
	}
	notify();
}
const vector<Film>& Watch_List::get_filme_watchlist()
{
	return this->watchlist;
}