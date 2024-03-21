#pragma once
#include "domain.h"
#include "repo.h"
class Actiune_Undo {
public:
	virtual void do_undo() = 0;
	//destructorul e virtual pentru a ne asigura ca daca dau delete se apeleaza destructorul din clasa care trebuie
	virtual ~Actiune_Undo() = default;
};

class Undo_Adauga : public Actiune_Undo {
	Repo_Abstract& rep;
	Film film_adaugat;
public:
	Undo_Adauga(Repo_Abstract& rep, const  Film& f) :rep{ rep }, film_adaugat{ f } {}
	void do_undo() override {
		rep.sterge(film_adaugat);
	}
};

class Undo_Sterge : public Actiune_Undo {
	Repo_Abstract& rep;
	Film film_sters;
public:
	Undo_Sterge(Repo_Abstract& rep, const  Film& f) :rep{ rep }, film_sters{ f } {}
	void do_undo() override {
		rep.store(film_sters);
	}
};

class Undo_Modifica : public Actiune_Undo {
	Repo_Abstract& rep;
	Film film_original;
	Film film_modificat;
public:
	Undo_Modifica(Repo_Abstract& rep, const  Film& fo, const  Film& fm) :rep{ rep }, film_original{ fo }, film_modificat{ fm } {}
	void do_undo() override {
		rep.sterge(film_modificat);
		rep.store(film_original);
	}
};