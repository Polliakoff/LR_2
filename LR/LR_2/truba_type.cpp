#include "truba_type.h"

using namespace std;

int truba_type::sId = 0;

truba_type::truba_type():id(sId++) {

}

truba_type::~truba_type()
{

}

void truba_type::vvod() {
	
	bool error;//Логическая переменная использующаяся для определения ошибки
	string temp_string;//временная строка

	cout << endl << "Введите параметры для Трубы:" << endl;

	cout << "Введите название трубы" << endl;

	while (true) {
		cin >> temp_string;
		error = false;
		for (auto i : temp_string) {
			if (i == '|') {
				cout << "Вы ввели зарезервированный символ |, введите другое нзвание" << endl;
				error = true;
			}
		}

		if (error == false) {
			this->name = temp_string;
			break;
		}
	}


	cout << "Введите длину трубы" << endl;

	while (true) {
		cin >> temp_string;

		if (is_double(temp_string) == true) {
			this->length = stod(temp_string);
			break;
		}
		else {
			cout << "Введите вещественное число" << endl;
		}

	}

	cout << "Введите диаметр трубы" << endl;
	
	while (true) {
		cin >> temp_string;

		if (is_double(temp_string) == true) {
			this->diameter = stod(temp_string);
			break;
		}
		else {
			cout << "Введите вещественное число" << endl;
		}

	}


	this->is_loaded = true;

	cout << "Ввод парамтеров завершен"<<endl;

}

void truba_type::vivod() {
	if (this->is_loaded == true) {
	cout << endl <<"Параметры Трубы "<<this->id<< endl;

	cout << "Id трубы : "<< this->id << endl;

	cout << "Название трубы: " << this->name << endl;

	cout << "Длина трубы: "<< this->length << endl;

	cout << "Диаметр трубы: "<< this->diameter << endl;

	string temp_string; //временная строка

	if (this->in_servise == 1) temp_string = "yes";
	else temp_string = "no";

	cout << "В ремонте ли труба (yes/no) : \t "<< temp_string << endl;
	}
	else {
		cout << endl << "Структура Труба пуста!" << endl;
	}


}
//Изменения статуса в ремонте
void truba_type::servise() {
	
	string temp_string; //временная строка
	
		cout << endl << "Хотите ли вы изменить статус ремонта трубы? (y/n)" << endl;
		cin >> temp_string;
		
		while (true) {

			if (temp_string == "y") {
				break;
			}
			else if (temp_string == "n") {
				return;
			}
			else {
				cout << "Введите 'y' или 'n' (строчными буквами)";
			}
			cout << endl;
			cin >> temp_string;
		}



		cout << endl << "В ремонте ли труба (y/n)" << endl;
		cin >> temp_string;

		while (true) {

			if (temp_string == "y") {
				this->in_servise = 1;
				break;
			}
			else if (temp_string == "n") {
				this->in_servise = 0;
				break;
			}
			else {
				cout << "Введите 'y' или 'n' (строчными буквами)";
			}
			cout << endl;
			cin >> temp_string;
		}

		if (this->in_servise == 1) temp_string = "y";
		else temp_string = "n";

		cout << "В ремонте ли труба теперь (y/n) : " << temp_string << endl;
	
}


void truba_type::save(std::ofstream& fout) {

	fout <<"t"<<"|"<<this->id<<"|" << this->name << "|" << this->length << "|" <<
		this->diameter << "|" <<this->in_servise << "|" <<endl;
	cout << "Труба " << this->id << " Успешно Сохранена!" << endl;

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
				case 1:
					this->name = temp_string;
					break;
				
				case 2:
					for (int k = 0; k < temp_string.length(); k++) {
						if (temp_string[k] == '.') temp_string[k] = ',';
					}
					this->length = stod(temp_string);
					break;
				case 3:
					for (int k = 0; k < temp_string.length(); k++) {
						if (temp_string[k] == '.') temp_string[k] = ',';
					}
					this->diameter = stod(temp_string);
					break;

				case 4:
					this->in_servise = stoi(temp_string);
					cout << "Труба " << this->id << " Успешно Загружена!" << endl;
					this->is_loaded = true;
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

