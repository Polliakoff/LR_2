#pragma once

#include <iostream>;
#include <string>;
#include <fstream>;
#include "func.h"

struct truba_type
{
	//id
private:
	
	static int sId;
	
public:	
	
	//параметры
	int id;
	double length;
	double diameter;
	bool in_servise = false;
	bool is_loaded = false;

	//методы
	void vvod();
	void vivod();
	void servise();
	void save(std::ofstream& fout);
	void load(std::ifstream& fin, std::string load_string);
	truba_type();
	~truba_type();

};

