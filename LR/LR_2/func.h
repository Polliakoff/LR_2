#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

class truba_type;
class KS_type;


void menu();
void input_and_check(double& subject, const bool& int_check = 0);
void name_check(std::string& name);

vector<int> pipes_in_service(vector <truba_type> pipes, bool in_service);
vector<int> ks_by_eff(vector<KS_type> KS_es, double effectiveness);

template <typename T> int id_to_ind(vector<T> objects, int id)
{

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].id == id) {
			return i;
		}
	}

	return -1;

}


template <typename T> vector<int> name_to_ind(vector<T> objects, std::string name)
{
	vector<int> return_vector;

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].name == name) {
			return_vector.push_back(i);
		}
	}


	return return_vector;

}






