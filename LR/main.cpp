#include <iostream>
#include "truba_type.h"
#include "KS_type.h"
#include <string>
#include "func.h"
#include <vector>
#include <fstream>
using namespace std;


int main() {
	setlocale(LC_ALL, "Russian");

	//массивы классов
	vector <truba_type> pipes;
	vector <KS_type> KS_es;

	string temp_string;//врмененная строковая переменная (объявлена сверху т. к. используется повсеместно)

	while (true) {

		cout << "Выберите действие которое необходимо осуществить: " <<
			endl << "1 - Добавить трубу " << endl << "2 - Добавить КС " << endl
				<< "3 - Просмотр всех объектов " << endl << "4 - Редактировать трубу " << endl
					<< "5 - Редактировать КС " << endl << "6 - Сохранить (Файлы перезаписываются) " << endl 
						<< "7 - Загрузить (Загруженные структуры добавятся к существующим и получат соответвующие ID)" 
							<< endl << "0 - Выйти" << endl;
		
		string selection; //переменная выбора действия
		cin >> selection;

		if (is_int(selection) == true) {

			switch (stoi(selection)) {

			case 1:{
				//создание новой пустой трубы и помещение ее в вектор труб
				truba_type temp_truba;
				temp_truba.vvod();
				temp_truba.vivod();
				pipes.push_back(temp_truba);
			}
				break;

			case 2: {
				//создание новой пустой КС и помещение ее в вектор КС
				KS_type temp_KS;
				temp_KS.vvod();
				temp_KS.vivod();
				KS_es.push_back(temp_KS);

			}
				break;
			case 3: {

				if (pipes.size() == 0 && KS_es.size() == 0) {
					cout << endl << "На данный момент в оперативной памяти нет ни одного объекта"<<endl;
				}
				else {
					for (auto i : pipes) {
						i.vivod();
					}

					for (auto i : KS_es) {
						i.vivod();
					}
				}
				
			}
				break;

			case 4: {
				cout <<endl<< "Введите id Трубы, которую хотите редактировать "<<endl;
				string id_selection;
				bool correct_check = false;
				cin >> id_selection;
				if (is_int(id_selection) == true) {
					for (size_t i = 0; i < pipes.size();i++ ) {
						if (pipes[i].id == stoi(id_selection)) {
							correct_check = true;
							cout << "Ви хотите изменить измерения этой трубы или только статуc ремонта?"
								<<endl<<"Измерения - 1, Статус ремонта - 2"<<endl;
							while (true) {
								cin >> temp_string;
								if (temp_string == "1") {
									pipes[i].vvod();
									pipes[i].vivod();
									break;
								}
								else if (temp_string == "2") {
									pipes[i].servise();
									pipes[i].vivod();
									break;
								}
								else {
									cout << "Введите 1 или 2 "<<endl;
								}
							}
							break;
						}	
					}
					if (correct_check == false) {
						cout << "Введите один из id cуществующих труб (можно посмотреть командой 3)"<<endl;
					}
				}
				else {
					cout << "Введите один из id cуществующих труб (можно посмотреть командой 3)" << endl;
				}
			}
				break;
			case 5: {
				cout << endl << "Введите id КС, которую хотите редактировать " << endl;
				string id_selection;
				bool correct_check = false;
				cin >> id_selection;
				if (is_int(id_selection) == true) {
					for (size_t i = 0; i < KS_es.size(); i++) {
						if (KS_es[i].id == stoi(id_selection)) {
							correct_check = true;
							cout << "Ви хотите изменить все параметры этой КС или только количество работающих цехов? " 
								<< endl <<"Все - 1, Кол-во цехов - 2"<<endl;
							while (true) {
								cin >> temp_string;
								if (temp_string == "1") {
									KS_es[i].vvod();
									KS_es[i].vivod();
									break;
								}
								else if (temp_string == "2") {
									KS_es[i].number_working();
									KS_es[i].vivod();
									break;
								}
								else {
									cout << "Введите 1 или 2 "<<endl;
								}
							}
							break;
						}
					}
					if (correct_check == false) {
						cout << "Введите один из id cуществующих КС (можно посмотреть командой 3)" << endl;
					}
				}
				else {
					cout << "Введите один из id cуществующих КС (можно посмотреть командой 3)" << endl;
				}
			}
				break;

			case 6: {
				ofstream fout;
				//очистка файла
				fout.open("save.txt");
				fout << "";
				fout.close();
				//сохранение труб в файл
				fout.open("save.txt", std::ios::app);

				for (auto i : pipes) {
					i.save(fout);
				}

				for (auto i : KS_es) {
					i.save(fout);
				}

				fout.close();
			}
				break;

			case 7: {
				ifstream fin;//создание потока вывода из файла
				
							 //загрузка из файла

				fin.open("save.txt");
				
				if (fin.is_open() == false) {
					cout << endl << "ФАЙЛ 'save.txt' НЕ НАЙДЕН!!!!" << endl;
					break;
				}

				//проверим не пустой ли файл (зпгрузилось ли хоть что то)
				size_t p_siz, k_siz;
				p_siz = pipes.size();
				k_siz = KS_es.size();
				
				while(std::getline(fin, temp_string)){
						
						if (temp_string[0] == 't') {
							truba_type temp_truba;
							temp_truba.load(fin, temp_string);
							pipes.push_back(temp_truba);
						}
						else {
							KS_type temp_KS;
							temp_KS.load(fin, temp_string);
							KS_es.push_back(temp_KS);
						}


					}

				if(p_siz == pipes.size() && k_siz == KS_es.size()){
					cout << endl << "ФАЙЛ 'save.txt' ПУСТ!!!!" << endl;
				}
			
				fin.close();



			}
				break;
			
			case 0: {
				return 0;
			}
				break;

			default: {
				cout << "введите цифру от 0 до 7 для выбора действия" << endl;
			}

			}
		}
		else {
			cout << "введите цифру от 0 до 7 для выбора действия" << endl;
		}
		system("pause");
		system("cls");
	}
	return 0;
}