#include "validator.h"
#include <assert.h>

string ValidationException::get_erori() const
{
	string erori = "";
	for (const string e : mesaje_de_eroare)
		erori += e + "\n";
	return erori;
}

void FilmValidator::valideaza(const Film& f)
{
	vector<string> erori;
	if (f.get_titlu().size() == 0)
		erori.push_back("Nu ati specificat titlul filmului!");
	if (f.get_gen().size() == 0)
		erori.push_back("Nu ati specificat genul filmului!");
	if (f.get_an() < 1)
		erori.push_back("An invalid!");
	if (f.get_actor_principal().size() == 0)
		erori.push_back("Nu ati specificat numele actorului principal!");

	if (erori.size() > 0)
		throw ValidationException(erori);
}

void test_validator()
{
	FilmValidator v;
	Film f{ "","",0,"" };
	try
	{
		v.valideaza(f);
	}
	catch (const ValidationException& ex)
	{
		assert(ex.get_erori().find("titlul"));
		assert(ex.get_erori().find("genul"));
		assert(ex.get_erori().find("invalid"));
		assert(ex.get_erori().find("principal"));
	}
}