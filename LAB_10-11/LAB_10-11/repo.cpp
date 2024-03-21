#include "repo.h"
#include <assert.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <random>
#include <vector>
using std::vector;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::getline;
using std::stoi;

//-----REPO NORMAL-----

string RepoException::get_erori() const
{
	return this->mesaje_de_eroare;
}

void Repo_Filme::store(const Film& f)
{
	if (exista(f)) {
		throw RepoException("Exista deja un film cu aceste date!");
	}
	filme.push_back(f);
}

void Repo_Filme::sterge(const Film& f)
{
	if (!exista(f))
		throw RepoException("Nu exista film cu aceste date!");
	else
	{
		/*int i;
		for (i=0;i<filme.size();i++)
		{
			if (f.get_titlu() == filme[i].get_titlu() && f.get_an() == filme[i].get_an() && f.get_actor_principal() == filme[i].get_actor_principal())
				break;
		}
		filme.erase(filme.begin()+i);*/

		int i = 0;
		for (const Film& fl : filme)
		{
			if (f.get_titlu() == fl.get_titlu() && f.get_an() == fl.get_an() && f.get_actor_principal() == fl.get_actor_principal())
				break;
			i++;
		}
		filme.erase(filme.begin() + i);
	}
}

void Repo_Filme::modifica(const Film& f, const string& gen_nou, int an_nou)
{
	if (!exista(f))
		throw RepoException("Nu exista film cu aceste date!");
	else
	{
		for (Film& film : filme)
		{
			if (f.get_titlu() == film.get_titlu() && f.get_an() == film.get_an() && f.get_actor_principal() == film.get_actor_principal())
			{
				film.set_gen(gen_nou);
				film.set_an(an_nou);
				break;
			}
		}
	}
}

const vector<Film>& Repo_Filme::get_filme() noexcept
{
	return filme;
}

const Film& Repo_Filme::find(string titlu, int an, string actor)
{
	/*for (const Film& f : filme)
	{
		if (f.get_titlu() == titlu && f.get_an() == an && f.get_actor_principal() == actor)
			return f;
	}
	throw RepoException("Nu exista film cu aceste date!");*/

	vector<Film>::iterator it = std::find_if(this->filme.begin(), this->filme.end(),
		[=](const Film& f) {
			return f.get_titlu() == titlu && f.get_an() == an && f.get_actor_principal() == actor;
		});

	if (it != this->filme.end())
		return (*it);
	else
		throw RepoException("Nu exista film cu aceste date!");
}

bool Repo_Filme::exista(const Film& f)
{
	try
	{
		find(f.get_titlu(), f.get_an(), f.get_actor_principal());
		return true;
	}
	catch (RepoException&)
	{
		return false;
	}
}

//-----REPO FISIER-----

void RepoFisier_Filme::load_from_file() {
	ifstream fisier_filme(this->nume_fisier);
	if (!fisier_filme.is_open())
	{
		throw RepoException("Nu se poate citi din fisierul " + nume_fisier);
	}
	string line;
	while (getline(fisier_filme, line))
	{
		string titlu, gen, actor_principal;
		int an = 0;

		stringstream linestream(line);
		string atribut_curent;
		int nr_atribut = 0;
		//Citire linie de tip "titlu;gen;an;actor principal"
		//separam linia cu separator = ;
		while (getline(linestream, atribut_curent, ';'))
		{
			if (nr_atribut == 0) titlu = atribut_curent;
			if (nr_atribut == 1) gen = atribut_curent;
			if (nr_atribut == 2) an = stoi(atribut_curent);
			if (nr_atribut == 3) actor_principal = atribut_curent;
			nr_atribut++;
		}
		Film f{ titlu, gen, an, actor_principal };

		Repo_Filme::store(f);
	}
	fisier_filme.close();
}

void RepoFisier_Filme::save_to_file()
{
	ofstream fisier_filme(this->nume_fisier);
	/*if (!fisier_filme.is_open())
		throw RepoException("Nu se poate scrie in fisierul " + nume_fisier);*/
	for (auto& film : get_filme()) {
		fisier_filme << film.get_titlu() << ";" << film.get_gen() << ";" << film.get_an() << ";" << film.get_actor_principal() << endl;
	}
	fisier_filme.close();
}

void RepoFisier_Filme::store(const Film& f)
{
	Repo_Filme::store(f);
	save_to_file();
}

void RepoFisier_Filme::sterge(const Film& f)
{
	Repo_Filme::sterge(f);
	save_to_file();
}

void RepoFisier_Filme::modifica(const Film& f, const string& gen_nou, int an_nou)
{
	Repo_Filme::modifica(f, gen_nou, an_nou);
	save_to_file();
}

//-----REPO LAB-----

double Repo_Lab::genereaza_probabilitate_aleatoare()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(0, 1);
	return dist(gen);
}

double Repo_Lab::get_probabilitate()
{
	return this->probabilitate;
}

void Repo_Lab::store(const Film& f)
{
	double p;
	p = genereaza_probabilitate_aleatoare();
	if (p < get_probabilitate())
		throw RepoException("Momentan nu se poate adauga filmul, incercati mai tarziu.");
	else
	{
		if (exista(f)) {
			throw RepoException("Exista deja un film cu aceste date!");
		}
		filme.insert({ f.get_titlu(), f });
	}

}

void Repo_Lab::sterge(const Film& f)
{
	double p;
	p = genereaza_probabilitate_aleatoare();
	if (p < get_probabilitate())
		throw RepoException("Momentan nu se poate sterge filmul, incercati mai tarziu.");
	else
	{
		if (exista(f)) {
			throw RepoException("Nu exista film cu aceste date!");
		}
		filme.erase(f.get_titlu());
	}
}

void Repo_Lab::modifica(const Film& f, const string& gen_nou, int an_nou)
{
	double p;
	p = genereaza_probabilitate_aleatoare();
	if (p < get_probabilitate())
		throw RepoException("Momentan nu se poate modifica filmul, incercati mai tarziu.");
	else
	{
		if (exista(f)) {
			throw RepoException("Nu exista film cu aceste date!");
		}
		Film f_nou = f;
		f_nou.set_gen(gen_nou);
		f_nou.set_an(an_nou);
		filme[f.get_titlu()] = f_nou;
	}
}

const vector<Film>& Repo_Lab::get_filme() noexcept
{
	for (auto& f : filme)
	{
		v_lab.push_back(f.second);
	}
	return v_lab;
}

const Film& Repo_Lab::find(string titlu, int an, string actor)
{
	double p;
	p = genereaza_probabilitate_aleatoare();
	if (p < get_probabilitate())
		throw RepoException("Momentan nu se poate cauta filmul, incercati mai tarziu.");
	else
	{
		unordered_map<string, Film>::iterator it = filme.find(titlu);
		if (it != filme.end())
		{
			if ((*it).second.get_an() == an && (*it).second.get_actor_principal() == actor)
				return (*it).second;
			else
			{
				throw RepoException("Nu exista film cu aceste date!");
			}
		}
		else
		{
			throw RepoException("Nu exista film cu aceste date!");
		}
	}
}

bool Repo_Lab::exista(const Film& f)
{
	return filme.find(f.get_titlu()) != filme.end();
}

//-----TESTE-----

void test_adauga()
{
	Repo_Filme rep;
	rep.store(Film{ "The Batman","sf, actiune, aventura",2022,"Robert Pattinson" });
	assert(rep.get_filme().size() == 1);
	assert(rep.find("The Batman", 2022, "Robert Pattinson").get_an() == 2022);

	rep.store(Film{ "bla","plictisitor",2022,"cineva" });
	assert(rep.get_filme().size() == 2);

	try
	{
		rep.store(Film{ "bla","plictisitor",2022,"cineva" });
		//assert(false);
	}
	catch (const RepoException&)
	{
		assert(true);
	}
}

void test_sterge()
{
	Repo_Filme rep;
	rep.store(Film{ "The Batman","sf, actiune, aventura",2022,"Robert Pattinson" });
	rep.store(Film{ "bla","plictisitor",2022,"cineva" });
	assert(rep.get_filme().size() == 2);

	Film f{ "bla","plictisitor",2022,"cineva" };
	rep.sterge(f);
	assert(rep.get_filme().size() == 1);

	try
	{
		rep.sterge(Film{ "bla","plictisitor",2022,"cineva" });
	}
	catch (const RepoException&)
	{
		assert(true);
	}
}

void test_cauta()
{
	Repo_Filme rep;
	rep.store(Film{ "The Batman","sf, actiune, aventura",2022,"Robert Pattinson" });
	rep.store(Film{ "bla","plictisitor",2022,"cineva" });
	assert(rep.get_filme().size() == 2);
	Film f = rep.find("bla", 2022, "cineva");
	assert(f.get_titlu() == "bla");
	assert(f.get_gen() == "plictisitor");

	try
	{
		rep.find("a", 2000, "B");
		//assert(false);
	}
	catch (const RepoException& ex)
	{
		assert(ex.get_erori().find("exista"));
	}
}

void test_modifica()
{
	Repo_Filme rep;
	rep.store(Film{ "The Batman","sf, actiune, aventura",2022,"Robert Pattinson" });
	rep.store(Film{ "bla","plictisitor",2022,"cineva" });
	assert(rep.get_filme().size() == 2);
	rep.modifica(Film{ "bla","plictisitor",2022,"cineva" }, "meh", 2023);

	try
	{
		rep.modifica(Film{ "bla","plictisitor",2022,"cineva" }, "yuk", 2024);
	}
	catch (const RepoException&)
	{
		assert(true);
	}
}

void test_repo_fisiere()
{
	ofstream out_fs;
	out_fs.open("test_filme.txt");
	out_fs << "The Batman;actiune;2022;Robert Pattinson\n";
	out_fs << "Spider-Man: No Way Home;actiune;2021;Tom Holland\n";
	out_fs << "The Mask;comedie;1994;Jim Carrey\n";
	out_fs << "Spider-Man: Homecoming;actiune;2017;Tom Holland\n";
	out_fs.close();
	try {
		RepoFisier_Filme test_repf{ "test_filme2.txt" };
	}
	catch (RepoException&) {
		assert(true);
	}
	RepoFisier_Filme test_repf{ "test_filme.txt" };
	assert(test_repf.get_filme().size() == 4);

	Film film_gasit = test_repf.find("The Mask", 1994, "Jim Carrey");
	assert(film_gasit.get_gen() == "comedie");
	assert(film_gasit.get_an() == 1994);

	Film film{ "Back to the Future", "sf", 1985, "Michael J. Fox" };
	test_repf.store(film);
	assert(test_repf.get_filme().size() == 5);
	try {
		test_repf.store(film);
	}
	catch (RepoException&) {
		assert(true);
	}

	Film film_de_sters{ "Spider-Man: No Way Home", "actiune", 2021, "Tom Holland" };
	test_repf.sterge(film_de_sters);
	assert(test_repf.get_filme().size() == 4);
	try {
		test_repf.sterge(film_de_sters);
	}
	catch (RepoException&) {
		assert(true);
	}

	test_repf.modifica(Film{ "Back to the Future", "sf", 1985, "Michael J. Fox" }, "super", 1955);

	try
	{
		test_repf.modifica(Film{ "Back to the Future", "sf", 1985, "Michael J. Fox" }, "buun", 1987);
	}
	catch (const RepoException&)
	{
		assert(true);
	}
}

void teste_repo()
{
	test_adauga();
	test_sterge();
	test_cauta();
	test_modifica();
	test_repo_fisiere();
}