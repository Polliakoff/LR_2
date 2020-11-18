#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <map>

using namespace std;

class truba_type;
class KS_type;

void menu();
void save_all(const map<int, truba_type>& pipes, const map<int, KS_type>& KS_es);
void load_all(map<int, truba_type>& pipes, map<int, KS_type>& KS_es);
void input_and_check(double& subject, const bool& int_check = 0);
void input_and_check(std::string& subject, const std::string& name);
void edit_by_id(map<int, truba_type>& pipes);
void edit_by_id(map<int, KS_type>& KS_es);
vector<int> find_by_parameter(map<int, truba_type>& pipes, const bool& output = 1);
vector<int> find_by_parameter(map<int,KS_type>& KS_es, const bool& output = 1);
void package_edit(vector<int>& found, map<int,truba_type>& pipes);
void package_edit(vector<int>& found, map<int, KS_type>& KS_es);
vector<int> pipes_in_service(map <int, truba_type> pipes, bool in_service);
vector<int> ks_by_eff(map<int, KS_type> KS_es, double effectiveness);

template <typename T> vector<int> name_to_id(map<int,T> objects, std::string name)
{
	vector<int> return_vector;

	for (auto i: objects) {
		if (i.second.name == name) {
			return_vector.push_back(i.first);
		}
	}

	return return_vector;

}

template <typename T> void vivod_vsego(map<int , T>& objects, std::string class_name)
{
	if (objects.size() > 0) {
		for (auto i : objects) {
			i.second.vivod();
		}
	}
	else {
		cout << "��� �� ������ ������� ��������� " << class_name << endl;
	}

}


template <typename T> vector<int> find_by_name(map<int,T>& objects, const bool& output = 1) {
	string name_selection;
	input_and_check(name_selection, "��������, �� �������� ����� ���������� �����");

	vector <int> found = name_to_id(objects, name_selection);
	if (found.size() > 0) {
		for (auto i : found) {
			if (output) objects[i].vivod();
		}
	}
	else {
		if(output) cout << "������� ���� �� �������� c����������� ���� (����� ���������� �������� 3)" << endl;
	}
	if (found.size() == 0) {
		if (output) cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
	}

	return found;
}

template <typename T> vector<int> find_by_filter(map<int,T>& objects) {

	vector<int> found_1 = find_by_name(objects,0);
	vector<int> found_2 = find_by_parameter(objects,0);
	vector<int> found;

	for (auto i : found_1) {
		for (auto j : found_2) {
			if (i == j) {
				found.push_back(i);
				objects[i].vivod();
			}
		}
	}

	if (found.size() == 0) {
		cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
	}

	return found;
}

template <typename T> void switch_search(map<int,T>& objects) {
	
	vector<int> found;
	double selection;

	cout << "�������� ������� ����������: " << endl <<
		"1 - ����� �� �������� (������/����� ���. �����)" << endl << "2 - ����� �� �������� " << endl
		<< "3 - ����� �� �������� � �������� � �������" << endl;

	while (true) {

		input_and_check(selection, 1);

		switch (int(selection)) {

		case 1: {
			found = find_by_parameter(objects);
		}
			  break;
		case 2: {
			found = find_by_name(objects);
		}
			  break;
		case 3: {
			found = find_by_filter(objects);
		}
			  break;
		default: {
			cout << "������� 1 - 3" << endl;
		}
			   break;
		}
		package_edit(found, objects);
		break;
	}
}

template <typename T> void delete_object(map<int,T>& objects, string name) {
	
	if (objects.size() > 0) {
		cout << endl << "������� id �������, ������� ������ ������� " << endl;
		double id_selection;

		input_and_check(id_selection, 1);

		if (objects.find(int(id_selection)) != objects.end()) {

			objects.erase(int(id_selection));

			cout << name << id_selection << " ������� ������� " << endl;
		}
		else {
			cout << "�������� id (������ ����� ���������� �������� 3)" << endl;
		}
	}
	else {
		cout << "�� ������ ������ ��� �� ������ �������" << endl;
	}

}






