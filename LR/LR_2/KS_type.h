#pragma once
#include "func.h"

class KS_type
{
public:

	//статические параметры
	static int sId;

	//параметры
	int id;
	std::string name;
	int workshop_number;
	int working_workshops;
	double effectiveness=0;

	//методы	
	void vvod();
	void vivod();
	void edit();
	void save(std::ofstream& fout);
	void load(std::ifstream& fin, std::string load_string);
	KS_type();

};

