#include "truba_type.h"

using namespace std;

int truba_type::sId = 0;


truba_type::truba_type():id(sId++) {

}

void truba_type::vvod() {
	string name_input;
	double input;


	cout << endl << "Введите параметры для Трубы:" << endl;

	input_and_check(name_input, "название трубы");
	name = name_input;

	cout << "Введите длину трубы" << endl;
	input_and_check(input);
	length = input;

	cout << "Введите диаметр трубы" << endl;
	input_and_check(input);
	diameter = input;

	cout << "Ввод парамтеров завершен"<<endl;

}

void truba_type::vivod() {

	cout << endl <<"Параметры Трубы "<<id<< endl;

	cout << "Id трубы : "<< id << endl;

	cout << "Название трубы: " << name << endl;

	cout << "Длина трубы: "<< length << endl;

	cout << "Диаметр трубы: "<< diameter << endl;

	string service_status; //временная строка

	if (in_servise == 1) service_status = "yes";
	else service_status = "no";

	cout << "В ремонте ли труба (yes/no) : \t "<< service_status << endl;

}
//Изменения статуса в ремонте
void truba_type::servise() {

	   string input;

		cout << endl << "В ремонте ли труба (y/n)" << endl;
		cin >> input;

		while (true) {

			if (input == "y") {
				in_servise = 1;
				break;
			}
			else if (input == "n") {
				in_servise = 0;
				break;
			}
			else {
				cout << "Введите 'y' или 'n' (строчными буквами)";
			}
			cout << endl;
			cin >> input;
		}

		if (in_servise == 1) input = "y";
		else input = "n";
	
}

void truba_type::save(std::ofstream& fout) {

	fout <<"t"<<"|"<<id<<"|" << name << "|" << length << "|" <<
		diameter << "|" <<in_servise << "|" <<endl;
	cout << "Труба " << id << " Успешно Сохранена!" << endl;

}

void truba_type::load(std::ifstream& fin, std::string load_string) {
	
	string temp_string; //временная строка

	//счетчики для цикла
	int i = 0;
	int j = 0;
	temp_string = "";//инициализируем временную строку
	while (true) {

		if (i > 1) {
			if (load_string[i] != '|') {
				temp_string += load_string[i];
			}
			else {
				switch (j) {
				case 0:
					id = stoi(temp_string);
					break;
				
				case 1:
					name = temp_string;
					break;
				
				case 2:
					for (int k = 0; k < temp_string.length(); k++) {
						if (temp_string[k] == '.') temp_string[k] = ',';
					}
					length = stod(temp_string);
					break;
				case 3:
					for (int k = 0; k < temp_string.length(); k++) {
						if (temp_string[k] == '.') temp_string[k] = ',';
					}
					diameter = stod(temp_string);
					break;

				case 4:
					in_servise = stoi(temp_string);
					cout << "Труба " << id << " Успешно Загружена!" << endl;
					break;
				}

				temp_string = "";
				j++;
			}
			
			if (i + 1 < load_string.length())i++;
			else return;
		}
		else {
			if (i + 1 < load_string.length())i++;
			else return;
		}
		
	}

}

