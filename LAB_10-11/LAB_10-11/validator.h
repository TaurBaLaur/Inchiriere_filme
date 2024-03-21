#pragma once
#include "domain.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

class ValidationException
{
private:
	vector<string> mesaje_de_eroare;
public:
	//constructor
	ValidationException(vector<string> erori) : mesaje_de_eroare{ erori } {};

	string get_erori() const;
};

class FilmValidator
{
public:
	void valideaza(const Film& f);
};

void test_validator();