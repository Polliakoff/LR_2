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
void save_all(const vector<truba_type>& pipes, const vector<KS_type>& KS_es);
void load_all(vector<truba_type>& pipes, vector<KS_type>& KS_es);
void input_and_check(double& subject, const bool& int_check = 0);
void input_and_check(std::string& subject, const std::string& name);
void edit_by_id(vector<truba_type>& pipes);
void edit_by_id(vector<KS_type>& KS_es);
vector<int> find_by_parameter(vector<truba_type>& pipes, const bool& output = 1);
vector<int> find_by_parameter(vector<KS_type>& KS_es, const bool& output = 1);
void package_edit(vector<int>& found, vector<truba_type>& pipes);
void package_edit(vector<int>& found, vector<KS_type>& KS_es);
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

template <typename T> void vivod_vsego(vector<T>& objects, std::string class_name)
{
	if (objects.size() > 0) {
		for (auto i : objects) {
			i.vivod();
		}
	}
	else {
		cout << "Нет ни одного объекта категории " << class_name << endl;
	}

}


template <typename T> vector<int> find_by_name(vector<T>& objects, const bool& output = 1) {
	string name_selection;
	input_and_check(name_selection, "название, по которому будет произведен поиск");

	vector <int>found = name_to_ind(objects, name_selection);
	if (found.size() > 0) {
		for (auto i : found) {
			if (output) objects[i].vivod();
		}
	}
	else {
		if(output) cout << "Введите одно из названий cуществующих Труб (можно посмотреть командой 3)" << endl;
	}
	if (found.size() == 0) {
		if (output) cout << "Не найден ни один объект по заданным параметрам" << endl;
	}

	return found;
}

template <typename T> vector<int> find_by_filter(vector<T>& objects) {

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
		cout << "Не найден ни один объект по заданным параметрам" << endl;
	}

	return found;
}

template <typename T> void switch_search(vector<T>& objects) {
	
	vector<int> found;
	double selection;

	cout << "Выберите вариант фильтрации: " << endl <<
		"1 - Вывод по признаку (ремонт/число раб. цехов)" << endl << "2 - Вывод по названию " << endl
		<< "3 - Вывод по названию и признаку в ремонте" << endl;

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
			cout << "Введите 1 - 3" << endl;
		}
			   break;
		}
		package_edit(found, objects);
		break;
	}
}

template <typename T> void delete_object(vector<T>& objects, string name) {
	
	if (objects.size() > 0) {
		cout << endl << "Введите id Объекта, который хотите удалить " << endl;
		double id_selection;

		input_and_check(id_selection, 1);

		if (id_to_ind(objects, int(id_selection)) != -1) {

			objects.erase(objects.begin() + id_to_ind(objects, int(id_selection)));

			cout << name << id_selection << " Успешно удалена " << endl;
		}
		else {
			cout << "Неверный id (Верные можно посмотреть коммандо 3)" << endl;
		}
	}
	else {
		cout << "На данный момент нет ни одного объекта" << endl;
	}

}






