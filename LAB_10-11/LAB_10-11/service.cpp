#include "service.h"
#include <assert.h>
#include <functional>
#include <algorithm>
#include <string>
#include <fstream>
#include "undo.h"

vector<Film> Service_Filme::filtreaza_filme(function<bool(const Film&)> fct)
{
	vector<Film> rez;
	for (const auto& film : rep.get_filme()) {
		if (fct(film)) {
			rez.push_back(film);
		}
	}
	return rez;
}

vector<Film> Service_Filme::sorteaza_filme(bool (*functie_comparare)(const Film&, const Film&))
{
	vector<Film> v{ rep.get_filme() };//fac o copie	
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!functie_comparare(v[i], v[j])) {
				//interschimbam
				Film aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

const vector<Film>& Service_Filme::get_toate_filmele() const
{
	return rep.get_filme();
}

void Service_Filme::undo() {
	if (undo_actions.empty()) {
		throw RepoException("Nu se mai poate face undo.");
	}
	undo_actions.back()->do_undo();
	undo_actions.pop_back();
}

void Service_Filme::adauga_film(const string& titlu, const string& gen, int an, const string& actor)
{
	Film f{ titlu,gen,an,actor };
	val.valideaza(f);
	rep.store(f);
	undo_actions.push_back(std::make_unique<Undo_Adauga>(rep, f));
}

void Service_Filme::sterge_film(const string& titlu, const string& gen, int an, const string& actor)
{
	Film f{ titlu,gen,an,actor };
	rep.sterge(f);
	undo_actions.push_back(std::make_unique<Undo_Sterge>(rep, f));
}

void Service_Filme::modifica_film(const string& titlu, const string& gen, int an, const string& actor, const string& gen_nou, int an_nou)
{
	Film f{ titlu,gen,an,actor };
	rep.modifica(f, gen_nou, an_nou);
	undo_actions.push_back(std::make_unique<Undo_Modifica>(rep, f, Film{ titlu,gen_nou,an_nou,actor }));
}

const Film& Service_Filme::cauta_film(const string& titlu, int an, const string& actor)
{
	return rep.find(titlu, an, actor);
}

//vector<Film> Service_Filme::filtrare_titlu(string titlu)
//{
//	return filtreaza_filme([titlu](const Film& f) {
//		return f.get_titlu().find(titlu) != string::npos;
//	});
//}

vector<Film> Service_Filme::filtrare_titlu(string titlu)
{
	const vector<Film> toate = get_toate_filmele();
	vector<Film> filme_filtrate;
	std::copy_if(toate.begin(), toate.end(), back_inserter(filme_filtrate),
		[titlu](const Film& f) {return f.get_titlu().find(titlu) != string::npos; });
	return filme_filtrate;
}

//vector<Film> Service_Filme::filtrare_an(int an)
//{
//	return filtreaza_filme([an](const Film& f) {
//		return f.get_an() == an;
//	});
//}

vector<Film> Service_Filme::filtrare_an(int an)
{
	const vector<Film> toate = get_toate_filmele();
	vector<Film> filme_filtrate;
	std::copy_if(toate.begin(), toate.end(), back_inserter(filme_filtrate),
		[=](const Film& f) {return f.get_an() == an; });
	return filme_filtrate;
}

//vector<Film> Service_Filme::sortare_titlu()
//{
//	return sorteaza_filme(compara_titlu);
//}

vector<Film> Service_Filme::sortare_titlu()
{
	vector<Film> copie_sortata{ rep.get_filme() };
	sort(copie_sortata.begin(), copie_sortata.end(), compara_titlu);
	return copie_sortata;
}

//vector<Film> Service_Filme::sortare_actor_principal()
//{
//	return sorteaza_filme(compara_actor_principal);
//}

vector<Film> Service_Filme::sortare_actor_principal()
{
	vector<Film> copie_sortata{ rep.get_filme() };
	sort(copie_sortata.begin(), copie_sortata.end(), compara_actor_principal);
	return copie_sortata;
}

//vector<Film> Service_Filme::sortare_an_gen()
//{
//	return sorteaza_filme(compara_an_gen);
//}

vector<Film> Service_Filme::sortare_an_gen()
{
	vector<Film> copie_sortata{ rep.get_filme() };
	sort(copie_sortata.begin(), copie_sortata.end(), compara_an_gen);
	return copie_sortata;
}

void Service_Filme::adauga_in_watchlist(string titlu, int an, string actor)
{
	const auto& film = rep.find(titlu, an, actor);
	watchlist_curent.adauga_la_watchlist(film);
}

void Service_Filme::goleste_watchlist()
{
	watchlist_curent.goleste_watchlist();
}

int Service_Filme::adauga_random_in_watchlist(int cate)
{
	int lungime_inainte;
	lungime_inainte = (int)watchlist_curent.get_filme_watchlist().size();
	watchlist_curent.adauga_film_random_la_watchlist(this->get_toate_filmele(), cate);
	return (int)watchlist_curent.get_filme_watchlist().size() - lungime_inainte;
}

const vector<Film>& Service_Filme::get_watchlist()
{
	return watchlist_curent.get_filme_watchlist();
}

unordered_map<string, DTO> Service_Filme::rapoarte_filme()
{
	unordered_map<string, DTO> raport;
	for (const Film& f : get_toate_filmele())
	{
		if (raport.find(std::to_string(f.get_an())) == raport.end())
		{
			int an;
			an = f.get_an();
			unsigned int contor;
			contor = (unsigned int)std::count_if(get_toate_filmele().begin(), get_toate_filmele().end(), [an](const Film& f) {
				return f.get_an() == an; });
			DTO dto(std::to_string(an), contor);
			raport.insert({ std::to_string(an) , dto });
		}
	}
	return raport;
}

void Service_Filme::export_watchlist_to_html(const string& nume_fisier)
{
	std::ofstream fo(nume_fisier + ".html");
	if (!fo.is_open()) {
		throw RepoException("Nu se poate deschide fisierul " + nume_fisier);
	}
	for (const auto& f : get_watchlist()) {
		fo << "<p>";
		fo << f.get_titlu() << ";" << f.get_gen() << ";" << f.get_an() << ";" << f.get_actor_principal() << std::endl;
	}
	fo.close();
}

void test_adaugare()
{
	Repo_Filme rep;
	FilmValidator val;
	Service_Filme srv{ rep,val };
	srv.adauga_film("The Batman", "sf, actiune, aventura", 2022, "Robert Pattinson");
	assert(srv.get_toate_filmele().size() == 1);

	try
	{
		srv.adauga_film("", "", 0, "");
	}
	catch (ValidationException&)
	{
		assert(true);
	}

	try
	{
		srv.adauga_film("The Batman", "sf, actiune, aventura", 2022, "Robert Pattinson");
	}
	catch (const RepoException& re)
	{
		assert(re.get_erori() == "Exista deja un film cu aceste date!");
	}
}

void test_stergere()
{
	Repo_Filme rep;
	FilmValidator val;
	Service_Filme srv{ rep,val };
	srv.adauga_film("The Batman", "sf, actiune, aventura", 2022, "Robert Pattinson");
	srv.adauga_film("bla", "plictisitor", 2022, "cineva");
	assert(srv.get_toate_filmele().size() == 2);
	srv.sterge_film("bla", "plictisitor", 2022, "cineva");
	assert(srv.get_toate_filmele().size() == 1);

	try
	{
		srv.sterge_film("bla", "plictisitor", 2022, "cineva");
	}
	catch (RepoException&)
	{
		assert(true);
	}
}

void test_modificare()
{
	Repo_Filme rep;
	FilmValidator val;
	Service_Filme srv{ rep,val };
	srv.adauga_film("The Batman", "sf, actiune, aventura", 2022, "Robert Pattinson");
	srv.adauga_film("bla", "plictisitor", 2022, "cineva");
	assert(srv.get_toate_filmele().size() == 2);
	srv.modifica_film("bla", "plictisitor", 2022, "cineva", "meh", 2023);
	assert(srv.get_toate_filmele().size() == 2);

	try
	{
		srv.modifica_film("bla", "plictisitor", 2022, "cineva", "yuk", 2024);
	}
	catch (RepoException&)
	{
		assert(true);
	}
}

void test_cautare()
{
	Repo_Filme rep;
	FilmValidator val;
	Service_Filme srv{ rep,val };
	srv.adauga_film("The Batman", "sf, actiune, aventura", 2022, "Robert Pattinson");
	srv.adauga_film("bla", "plictisitor", 2022, "cineva");
	assert(srv.get_toate_filmele().size() == 2);
	Film film_cautat = srv.cauta_film("bla", 2022, "cineva");
	assert(film_cautat.get_gen() == "plictisitor");
	try
	{
		Film film_cautat2 = srv.cauta_film("asd", 2000, "chris");
	}
	catch (RepoException&)
	{
		assert(true);
	}
}

void test_filtrare()
{
	Repo_Filme rep;
	FilmValidator val;
	Service_Filme srv{ rep,val };
	srv.adauga_film("The Batman", "sf, actiune, aventura", 2022, "Robert Pattinson");
	srv.adauga_film("The best movie", "super", 2021, "Toti");
	assert(srv.get_toate_filmele().size() == 2);
	assert(srv.filtrare_titlu("The").size() == 2);
	assert(srv.filtrare_titlu("man").size() == 1);
	assert(srv.filtrare_titlu("der").size() == 0);
	assert(srv.filtrare_an(2022).size() == 1);
	assert(srv.filtrare_an(2000).size() == 0);
}

void test_sortare()
{
	Repo_Filme rep;
	FilmValidator val;
	Service_Filme srv{ rep,val };
	srv.adauga_film("The Batman", "sf, actiune, aventura", 2022, "Robert Pattinson");
	srv.adauga_film("The best movie", "super", 2021, "Toti");
	srv.adauga_film("Filmul Meu", "bun", 2004, "Eu");
	srv.adauga_film("Ultimul roman", "excelent", 2004, "Sebastian Stan");
	assert(srv.get_toate_filmele().size() == 4);

	auto primul_film = srv.sortare_titlu()[0];
	assert(primul_film.get_titlu() == "Filmul Meu");

	primul_film = srv.sortare_actor_principal()[0];
	assert(primul_film.get_actor_principal() == "Eu");

	primul_film = srv.sortare_an_gen()[0];
	assert(primul_film.get_an() == 2004);
	assert(primul_film.get_gen() == "bun");
}

void test_watchlist()
{
	Repo_Filme rep;
	FilmValidator val;
	Service_Filme srv{ rep,val };
	srv.adauga_film("The Batman", "sf, actiune, aventura", 2022, "Robert Pattinson");
	srv.adauga_film("The best movie", "super", 2021, "Toti");
	srv.adauga_film("Filmul Meu", "bun", 2004, "Eu");
	srv.adauga_film("Ultimul roman", "excelent", 2004, "Sebastian Stan");
	assert(srv.get_toate_filmele().size() == 4);

	srv.adauga_random_in_watchlist(4);
	assert(srv.get_watchlist().size() == 4);
	srv.goleste_watchlist();
	assert(srv.get_watchlist().size() == 0);
	srv.adauga_random_in_watchlist(10);
	assert(srv.get_watchlist().size() == 4);
	srv.goleste_watchlist();
	srv.adauga_in_watchlist("The Batman", 2022, "Robert Pattinson");
	assert(srv.get_watchlist().size() == 1);

	try
	{
		srv.adauga_in_watchlist("asa", 2009, "joe");
	}
	catch (RepoException&)
	{
		assert(true);
	}
}

void test_rapoarte()
{
	Repo_Filme rep;
	FilmValidator val;
	Service_Filme srv{ rep,val };
	srv.adauga_film("The Batman", "sf, actiune, aventura", 2022, "Robert Pattinson");
	srv.adauga_film("The best movie", "super", 2021, "Toti");
	srv.adauga_film("Filmul Meu", "bun", 2004, "Eu");
	srv.adauga_film("Ultimul roman", "excelent", 2004, "Sebastian Stan");
	assert(srv.get_toate_filmele().size() == 4);

	unordered_map<string, DTO> rap = srv.rapoarte_filme();
	assert(rap.begin()->first == "2022");
}

void test_export()
{
	Repo_Filme rep;
	FilmValidator val;
	Service_Filme srv{ rep,val };
	srv.adauga_film("The Batman", "actiune", 2022, "Robert Pattinson");
	srv.adauga_film("The best movie", "super", 2021, "Toti");
	srv.adauga_film("Filmul Meu", "bun", 2004, "Eu");
	srv.adauga_film("Ultimul roman", "excelent", 2004, "Sebastian Stan");
	assert(srv.get_toate_filmele().size() == 4);

	srv.adauga_random_in_watchlist(4);
	assert(srv.get_watchlist().size() == 4);

	srv.export_watchlist_to_html("test_export");
	std::ifstream in("test_export.html");
	assert(in.is_open());

	try {
		srv.export_watchlist_to_html("a/b");
	}
	catch (RepoException&) {
		assert(true);
	}
}

void teste_service()
{
	test_adaugare();
	test_stergere();
	test_modificare();
	test_cautare();
	test_filtrare();
	test_sortare();
	test_watchlist();
	test_rapoarte();
	test_export();
}