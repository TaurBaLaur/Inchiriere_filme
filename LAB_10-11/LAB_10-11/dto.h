#pragma once
#include <string>
using std::string;

class DTO
{
private:
	string cheie;
	unsigned int contor_filme;
public:
	DTO() = default;
	DTO(string ch, unsigned int contor) :cheie{ ch }, contor_filme{ contor } {};
	string get_cheie();
	unsigned int get_contor();
};