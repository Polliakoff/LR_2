#include "KS_type.h"
using namespace std;

int KS_type::sId = 0;

KS_type::KS_type() :id(sId++) {

}

void KS_type::vvod() {
	
	double input;
	string name_input;


	cout << endl << "Введите параметры для КС:" << endl;


	cout << "Введите название КС" << endl;
	name_check(name_input);
	name = name_input;
    

	cout << "Введите число цехов КС" << endl;

	input_and_check(input, 1);
	workshop_number = input;

	
	cout << "Введите число работающих цехов КС (<= числа цехов)" << endl;

	while (true) {
		input_and_check(input, 1);

		if (input <= workshop_number) {
			working_workshops = input;
			break;
		}
		else {
			cout << "Введите число <= числа цехов" << endl;
			continue;
		}
	}
	
	
	effectiveness = int((double(working_workshops) / double(workshop_number)) * 100 + 0.5) / 100.0;
	


	cout << "Ввод парамтеров завершен" << endl;

}

void KS_type::vivod() {
		cout << endl << "Параметры КС " << id << endl;

		cout << "Id КС : " << id << endl;

		cout << "Название КС: " << name << endl;

		cout << "Число цехов КС: " << workshop_number << endl;

		cout << "Число работающих цехов КС: " << working_workshops << endl;

		cout << "Эффективность КС : " << effectiveness << endl;
}
//изменение кол-ва рабочих цехов
void KS_type::number_working() {    
	double ammount = 0;
	cout << "Введите число цехов (меньше нуля - выключить, больше нуля - включить)" << endl;
	
	while (true) {
		input_and_check(ammount, 1);
		
			if((working_workshops+ammount)<=workshop_number 
				&& (working_workshops + ammount) >= 0) working_workshops = working_workshops+ammount;
			else {
				cout << "Введите возможное число изменяемых цехов";
				continue;
			}
			break;
		
	}

	cout << "Число работающих цехов на данный момент :" << working_workshops << endl;





}
//сохранение в файл
void KS_type::save(std::ofstream& fout) {

	fout << "k" << "|"<< id << "|" << name << "|" <<
		workshop_number << "|" << working_workshops <<"|"<< effectiveness << "|"<<endl;
	cout << "КС " << id << " Успешно Сохранена!" << endl;
}
//загрузка из файла
void KS_type::load(std::ifstream& fin, std::string load_string) {

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

			case 1:
				name = temp_string;
				break;
			case 2:
				workshop_number = stoi(temp_string);
				break;

			case 3:
				working_workshops = stoi(temp_string);
				break;

			case 4:
				for (int k = 0; k < temp_string.length(); k++) {
					if (temp_string[k] == '.') temp_string[k] = ',';
				}
				effectiveness = stod(temp_string);
				cout << "КС " << id << " Успешно Загружена!" << endl;
				break;
			}

			temp_string = "";
			j++;
		}
		if (i + 1 <= load_string.length())i++;
		else return;
	}
		else {
			if (i + 1 < load_string.length())i++;
			else return;
		}

	}

}