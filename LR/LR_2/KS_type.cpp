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
	this->name = name_input;
    

	cout << "Введите число цехов КС" << endl;

	input_and_check(input, 1);
	this->workshop_number = input;

	
	cout << "Введите число работающих цехов КС (<= числа цехов)" << endl;

	while (true) {
		input_and_check(input, 1);

		if (input <= this->workshop_number) {
			this->working_workshops = input;
			break;
		}
		else {
			cout << "Введите число <= числа цехов" << endl;
			continue;
		}
	}
	
	
	this->effectiveness = int((double(this->working_workshops) / double(this->workshop_number)) * 100 + 0.5) / 100.0;
	


	cout << "Ввод парамтеров завершен" << endl;

}

void KS_type::vivod() {
		cout << endl << "Параметры КС " << this->id << endl;

		cout << "Id КС : " << this->id << endl;

		cout << "Название КС: " << this->name << endl;

		cout << "Число цехов КС: " << this->workshop_number << endl;

		cout << "Число работающих цехов КС: " << this->working_workshops << endl;

		cout << "Эффективность КС : " << this->effectiveness << endl;
}
//изменение кол-ва рабочих цехов
void KS_type::number_working() {    
	double ammount = 0;
	cout << "Введите число цехов (меньше нуля - выключить, больше нуля - включить)" << endl;
	
	while (true) {
		input_and_check(ammount, 1);
		
			if((this->working_workshops+ammount)<=this->workshop_number 
				&& (this->working_workshops + ammount) >= 0) this->working_workshops = this->working_workshops+ammount;
			else {
				cout << "Введите возможное число изменяемых цехов";
				continue;
			}
			break;
		
	}

	cout << "Число работающих цехов на данный момент :" << this->working_workshops << endl;





}
//сохранение в файл
void KS_type::save(std::ofstream& fout) {

	fout << "k" << "|"<< this->id << "|" << this->name << "|" <<
		this->workshop_number << "|" << this->working_workshops <<"|"<< this->effectiveness << "|"<<endl;
	cout << "КС " << this->id << " Успешно Сохранена!" << endl;
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
				this->name = temp_string;
				break;
			case 2:
				this->workshop_number = stoi(temp_string);
				break;

			case 3:
				this->working_workshops = stoi(temp_string);
				break;

			case 4:
				for (int k = 0; k < temp_string.length(); k++) {
					if (temp_string[k] == '.') temp_string[k] = ',';
				}
				this->effectiveness = stod(temp_string);
				cout << "КС " << this->id << " Успешно Загружена!" << endl;
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