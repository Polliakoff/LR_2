#include "KS_type.h"
#include "truba_type.h"


using namespace std;

void input_and_check(double& subject, const bool& int_check) {
    
	while (true) {
		subject = 0;
		cin >> subject;

		if (int_check) {
			
			if (cin.good() && !(subject - floor(subject))) {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}
			else {
				cout << "Введите целое число" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

			}


		}
		else {
			
			if (cin.good()) {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}
			else {
				cout << "Введите вещественное число" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}


		}
	
	}

}

void name_check(std::string& name) {
	
	bool error;
	while (true) {
		cin >> name;
		error = false;
		for (auto i : name) {
			if (i == '|') {
				cout << "Вы ввели зарезервированный символ |, введите другое нзвание" << endl;
				error = true;
			}
		}

		if (error == false) {
			break;
		}
	}
}


void menu() {
	
	cout << "Выберите действие которое необходимо осуществить: " <<
		endl << "1 - Добавить трубу " << endl << "2 - Добавить КС " << endl
			<< "3 - Просмотр объектов " << endl << "4 - Редактировать трубу " << endl
				<< "5 - Редактировать КС " << endl << "6 - Сохранить (Файлы перезаписываются) " << endl
					<< "7 - Загрузить (введенные структуры удаляются и заменяются загруженнми из файла)"
						<< endl << "8 - Вывести/редактировать трубы по фильтрам" << endl << "9 - Вывести/редактировать КС по фильтрам "
							<< endl << "10 - Удаление Трубы" << endl << "11 - Удаление КС" << endl << "0 - Выйти" << endl <<"Ввод : ";



}


vector<int> pipes_in_service(vector <truba_type> pipes, bool in_service) {

	vector<int> return_vector;

	for (int i = 0; i < pipes.size(); i++) {
		if (pipes[i].in_servise == in_service) {
			return_vector.push_back(i);
		}
	}

	return return_vector;

}

vector<int> ks_by_eff(vector<KS_type> KS_es, double effectiveness) {

	vector<int> return_vector;

	for (int i = 0; i < KS_es.size(); i++) {
		if (KS_es[i].effectiveness == effectiveness) {
			return_vector.push_back(i);
		}
	}

	return return_vector;



}

