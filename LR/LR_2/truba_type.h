#pragma once
#include "func.h"

class truba_type
{
private:
	int id;
	static int sId;
public:		

	//параметры
	std::string name;
	double length;
	double diameter;
	bool in_servise = false;	

	//методы
	void vvod();
	void edit();
	int get_id() const;
	void load(std::ifstream& fin, std::string load_string);
	truba_type();

};

std::ostream& operator<<(std::ostream&, const truba_type&);
std::ofstream& operator<<(std::ofstream&, const truba_type&);

