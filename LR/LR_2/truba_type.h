#pragma once
#include "func.h"

class truba_type
{
public:		

	//статические параметры
	static int sId;

	//параметры
	int id;
	std::string name;
	double length;
	double diameter;
	bool in_servise = false;	

	//методы
	void vvod();
	void vivod();
	void servise();
	void save(std::ofstream& fout);
	void load(std::ifstream& fin, std::string load_string);
	truba_type();

};

