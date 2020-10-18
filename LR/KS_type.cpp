#include "KS_type.h"
using namespace std;

int KS_type::sId = 0;

KS_type::KS_type() :id(sId++) {

}

KS_type::~KS_type()
{

}

void KS_type::vvod() {
	
	string temp_string;//временная строка
	bool error;//Логическая переменная использующаяся для определения ошибки
	cout << endl << "Введите параметры для КС:" << endl;



	cout << "Введите название КС" << endl;
	
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

	cout << "Введите число цехов КС" << endl;
	
	while (true) {
		cin >> temp_string;

		if (is_int(temp_string) == true) {
			this->workshop_number = stoi(temp_string);
			break;
		}
		else {
			cout << "Введите целое число" << endl;
		}

	}

	int temp_int; //Временная целочисленая переменная
	
	cout << "Введите число работающих цехов КС (<= числа цехов)" << endl;

	while (true) {
		cin >> temp_string;

		if (is_int(temp_string) == true) {
			temp_int = stoi(temp_string);
		}
		else {
			cout << "Введите целое число" << endl;
			continue;
		}

		if (temp_int <= this->workshop_number) {
			this->working_workshops = temp_int;
			break;
		}
		else {
			cout << "Введите число <= числа цехов" << endl;
			continue;
		}
	}
	
	while (true) {
		if (temp_int <= this->workshop_number) {
			this->working_workshops = temp_int;
			break;
		}
		else cout << "Введите число <= числа цехов"<<endl;
		cin >> temp_int;
	}

	cout << "Введите эффективность КС" << endl;
	
	while (true) {
		cin >> temp_string;

		if (is_double(temp_string) == true && stod(temp_string)<=1) {
			this->effectiveness = stod(temp_string);
			break;
		}
		else {
			cout << "Введите вещественное число меньше единицы" << endl;
		}

	}
	
	this->is_loaded = true;
	cout << "Ввод парамтеров завершен" << endl;

}

void KS_type::vivod() {
	if (this->is_loaded == true) {
		cout << endl << "Параметры КС " << this->id << endl;

		cout << "Id КС : " << this->id << endl;

		cout << "Название КС: " << this->name << endl;

		cout << "Число цехов КС: " << this->workshop_number << endl;

		cout << "Число работающих цехов КС: " << this->working_workshops << endl;

		cout << "Эффективность КС: " << this->effectiveness << endl;
	}
	else {
		cout << endl << "Структура КС пуста!" << endl;
	}

}
//изменение кол-ва рабочих цехов
void KS_type::number_working() {

	string temp_string; //временная строка

	cout << endl << "Хотите ли вы отключить/включить цех КС? (y/n)" << endl;
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




	while (true) {
		cout << endl << "Вы хотите отключить, включить цех или выйти? (+/-/q (quit))" << endl;
		cin >> temp_string;
		
		if (temp_string == "+") {
			if((this->working_workshops+1)<=this->workshop_number) this->working_workshops++;
			else {
				cout << "Достигнуто максимальное число работающих цехов";
				continue;
			}
			break;
		}
		else if (temp_string == "-") {
			if ((this->working_workshops - 1) >= 0) this->working_workshops--;
			else {
				cout << "Работающих цехов уже нет";
				continue;
			}
			break;
		}
		
		else if (temp_string == "q") {
			break;
		}
		
		else {
			cout << "Введите '+', '-' или 'q' (строчными буквами)";
		}
		cout << endl;
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
				this->is_loaded = true;
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