#include "domain.h"
#include <assert.h>

string Film::get_titlu() const
{
	return this->titlu;
}

string Film::get_gen() const
{
	return this->gen;
}

const int& Film::get_an() const noexcept
{
	return this->an;
}

string Film::get_actor_principal() const
{
	return this->actor_principal;
}

void Film::set_titlu(string titlu_nou)
{
	this->titlu = titlu_nou;
}

void Film::set_gen(string gen_nou)
{
	this->gen = gen_nou;
}

void Film::set_an(int an_nou) noexcept
{
	this->an = an_nou;
}

void Film::set_actor_principal(string actor_principal_nou)
{
	this->actor_principal = actor_principal_nou;
}

bool compara_titlu(const Film& f1, const Film& f2)
{
	return f1.get_titlu() < f2.get_titlu();
}

bool compara_actor_principal(const Film& f1, const Film& f2)
{
	return f1.get_actor_principal() < f2.get_actor_principal();
}

bool compara_an_gen(const Film& f1, const Film& f2)
{
	if (f1.get_an() == f2.get_an())
	{
		return f1.get_gen() < f2.get_gen();
	}
	else
	{
		return f1.get_an() < f2.get_an();
	}
}

void teste_get_set()
{
	Film f1{ "Pirates of the Caribbean: The Curse of the Black Pearl","actiune, aventura",2003,"Johnny Depp" };
	assert(f1.get_titlu() == "Pirates of the Caribbean: The Curse of the Black Pearl");
	assert(f1.get_gen() == "actiune, aventura");
	assert(f1.get_an() == 2003);
	assert(f1.get_actor_principal() == "Johnny Depp");

	Film f2{ "Iron Man","sf, actiune, aventura",2008,"Robert Downey Jr." };
	assert(f2.get_titlu() == "Iron Man");
	assert(f2.get_gen() == "sf, actiune, aventura");
	assert(f2.get_an() == 2008);
	assert(f2.get_actor_principal() == "Robert Downey Jr.");

	f2.set_titlu("Back to the Future");
	f2.set_gen("sf, aventura, comedie");
	f2.set_an(1985);
	f2.set_actor_principal("Michael J. Fox");

	assert(f2.get_titlu() == "Back to the Future");
	assert(f2.get_gen() == "sf, aventura, comedie");
	assert(f2.get_an() == 1985);
	assert(f2.get_actor_principal() == "Michael J. Fox");
}

void teste_domain()
{
	teste_get_set();
}