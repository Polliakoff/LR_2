#pragma once


#include "func.h"

class KS_type
{
	


public:


	//id

	static int sId;

	//���������
	int id;
	std::string name;
	int workshop_number;
	int working_workshops;
	double effectiveness=0;

	//������	
	void vvod();
	void vivod();
	void number_working();
	void save(std::ofstream& fout);
	void load(std::ifstream& fin, std::string load_string);
	KS_type();







};

