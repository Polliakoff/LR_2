#pragma once


#include "func.h"

class truba_type
{

	
public:	
	

	//id
	static int sId;

	//���������
	int id;
	std::string name;
	double length;
	double diameter;
	bool in_servise = false;

	//������
	void vvod();
	void vivod();
	void servise();
	void save(std::ofstream& fout);
	void load(std::ifstream& fin, std::string load_string);
	truba_type();

};

