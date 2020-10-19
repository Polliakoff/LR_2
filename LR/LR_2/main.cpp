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
				<< "3 - Просмотр объектов " << endl << "4 - Редактировать трубу " << endl
					<< "5 - Редактировать КС " << endl << "6 - Сохранить (Файлы перезаписываются) " << endl 
						<< "7 - Загрузить (Загруженные структуры добавятся к существующим и получат соответвующие ID)" 
							<< endl <<"8 - Вывести/редактировать трубы по фильтрам"<<endl<<"9 - Вывести/редактировать КС по фильтрам "
								<<endl<<"10 - Удаление Трубы"<<endl<<"11 - Удаление КС"<<endl<< "0 - Выйти" << endl;
		
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
					cout << endl << "На данный момент в оперативной памяти нет ни одного объекта" << endl;
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
			


			case 8: {

				vector<size_t> found;
				bool are_there_any = false; //для определения нашли ли мы хоть что то 
				cout << "Выберите вариант фильтрации: " << endl<<
					"1 - Вывод по признаку в ремонете"<< endl<< "2 - Вывод по названию трубы "<<endl
						<<"3 - Вывод по названию и признаку в ремонте"<<endl;

				selection = "";
				while (true) {
					cin >> selection;
					if (is_int(selection) == true) {
						
						switch (stoi(selection)) {
						
						case 1: {

							cout << "В ремонте ли труба? (y/n)" << endl;
							selection = "";
							while (true) {
								cin >> selection;
								if (selection == "y") {
									for (auto i : pipes) {
										if (i.in_servise == true) {
											found.push_back(i.id);
											i.vivod();
											are_there_any = true;
										}
									}
									break;
								}
								else if (selection == "n") {
									for (auto i : pipes) {
										if (i.in_servise == false) {
											found.push_back(i.id);
											i.vivod();
											are_there_any = true;
										}
									}
									break;
								}
								else {
									cout << "Введите y или n" << endl;
									continue;
								}
							}

							if (are_there_any == false) {
								cout << "Не найден ни один объект по заданным параметрам" << endl;
							}
						}
							  break;
							
						case 2: {

							cout << "Введите название Трубы, которую необходимо вывести " << endl;
							string name_selection;
							bool correct_check = false;
							cin >> name_selection;
							for (size_t i = 0; i < pipes.size(); i++) {
								if (pipes[i].name == name_selection) {
									correct_check = true;
									found.push_back(i);
									pipes[i].vivod();
									are_there_any = true;
								}
							}
							if (correct_check == false) {
								cout << "Введите одно из названий cуществующих Труб (можно посмотреть командой 3)" << endl;
							}


							if (are_there_any == false) {
								cout << "Не найден ни один объект по заданным параметрам" << endl;
							}
						}
							  break;
						case 3: {
							cout << "В ремонте ли труба? (y/n)" << endl;
							selection = "";
							bool service;
							while (true) {
								cin >> selection;
								if (selection != "y" && selection != "n") {
									cout << "Введите y или n" << endl;
									continue;
								}
								else {
									if (selection == "y") {
										service = 1;
									}
									else {
										service = 0;
									}
									break;
								}
							}

							cout << "Введите название Трубы, которую необходимо вывести " << endl;
							
							string name_selection;
							bool correct_check = false;
							string name;
							
							cin >> name_selection;
							for (size_t i = 0; i < pipes.size(); i++) {
								if (pipes[i].name == name_selection) {
									correct_check = true;
									name = pipes[i].name;
								}
							}
							if (correct_check == false) {
								cout << "Введите одино из названий cуществующих Труб (можно посмотреть командой 3)" << endl;
								break;
							}

							for (size_t i = 0; i < pipes.size(); i++) {
							 
								if (pipes[i].name == name && pipes[i].in_servise == service) {
									found.push_back(i);
									pipes[i].vivod();
									are_there_any = true;
								}
							}


							if (are_there_any == false) {
								cout << "Не найден ни один объект по заданным параметрам"<<endl;
							}

						}
							  break;

						default :{
							cout << "Введите 1 - 3" << endl;
							}
								break;



						}
						if (are_there_any == true) {
							cout << "Хотите редактировать найденные трубы? (y/n)" << endl;
							size_t t = 0;
							while (true) {
								cin >> selection;
								if (selection == "y") {
									while (t < found.size()) {
										for (size_t i = 0; i < pipes.size(); i++) {
											if (pipes[i].id == found[t]) {
												t++;
												cout << "Ви хотите изменить измерения трубы " << t - 1 << " или только статуc ремонта?"
													<< endl << "Измерения - 1, Статус ремонта - 2" << endl;
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
														cout << "Введите 1 или 2 " << endl;
													}
												}
												break;
											}
										}
									}
									t = 0;
									break;
								}
								else if (selection == "n") {
									found.clear();
									break;
								}
								else {
									cout << "Введите y или n" << endl;
								}
							}
						}

					}
					else {
						cout << "Введите 1 - 3" << endl;
						continue;
					}
					break;
				}


			}
				  break;

			case 9: {

				vector<size_t> found;
				bool are_there_any = false; //для определения нашли ли мы хоть что то 
				cout << "Выберите вариант фильтрации: " << endl <<
					"1 - Вывод по эффективности" << endl << "2 - Вывод по названию КС " << endl
					<< "3 - Вывод по названию и эффективности" << endl;

				selection = "";
				while (true) {
					cin >> selection;
					if (is_int(selection) == true) {

						switch (stoi(selection)) {

						case 1: {

							cout << "Введите эффективность КС" << endl;

							while (true) {
								cin >> temp_string;
								if (is_double(temp_string) == true) {
									if (stod(temp_string) > 0 && stod(temp_string) < 1) {
										for (auto i : KS_es) {
											if (i.effectiveness == stod(temp_string)) {
												found.push_back(i.id);
												i.vivod();
												are_there_any = true;
											}
										}
										break;
									}
									else {
										cout << "Введите вещественное число больше нуля и меньше единицы" << endl;
										continue;
									}
								}
								else {
									cout << "Введите вещественное число больше нуля и меньше единицы" << endl;
									continue;
								}
							}

							if (are_there_any == false) {
								cout << "Не найден ни один объект по заданным параметрам" << endl;
							}
						}
							  break;

						case 2: {

							cout << "Введите название КС, которую необходимо вывести " << endl;
							string name_selection;
							bool correct_check = false;
							cin >> name_selection;
							for (size_t i = 0; i < KS_es.size(); i++) {
								if (KS_es[i].name == name_selection) {
									correct_check = true;
									found.push_back(i);
									KS_es[i].vivod();
									are_there_any = true;
								}
							}
							if (correct_check == false) {
								cout << "Введите одино из названий cуществующих КС (можно посмотреть командой 3)" << endl;
							}
							
							if (are_there_any == false) {
								cout << "Не найден ни один объект по заданным параметрам" << endl;
							}
						}
							  break;
						case 3: {
							
							double effectiveness;
							cout << "Введите эффективность КС" << endl;

							while (true) {
								cin >> temp_string;
								if (is_double(temp_string) == true) {
									if (stod(temp_string) > 0 && stod(temp_string) < 1) {
										effectiveness = stod(temp_string);
										break;
									}
									else {
										cout << "Введите вещественное число больше нуля и меньше единицы" << endl;
										continue;
									}
								}
								else {
									cout << "Введите вещественное число больше нуля и меньше единицы" << endl;
									continue;
								}
							}

							cout << "Введите название КС, которую необходимо вывести " << endl;

							string name_selection;
							bool correct_check = false;
							string name;

							cin >> name_selection;
							for (size_t i = 0; i < KS_es.size(); i++) {
								if (KS_es[i].name == name_selection) {
									correct_check = true;
									name = KS_es[i].name;
								}
							}
							if (correct_check == false) {
								cout << "Введите одино из названий cуществующих КС (можно посмотреть командой 3)" << endl;
								break;
							}

							for (size_t i = 0; i < KS_es.size(); i++) {

								if (KS_es[i].name == name && KS_es[i].effectiveness == effectiveness) {
									found.push_back(i);
									KS_es[i].vivod();
									are_there_any = true;
								}
							}


							if (are_there_any == false) {
								cout << "Не найден ни один объект по заданным параметрам" << endl;
							}

						}
							  break;

						default: {
							cout << "Введите 1 - 3" << endl;
						}
							   break;



						}
						if (are_there_any == true) {
							cout << "Хотите редактировать найденные КС? (y/n)" << endl;
							size_t t = 0;
							while (true) {
								cin >> selection;
								if (selection == "y") {
									while (t < found.size()) {
										for (size_t i = 0; i < KS_es.size(); i++) {
											if (KS_es[i].id == found[t]) {
												t++;
												cout << "Ви хотите изменить измерения КС " << t - 1 << " или только число работающих цехов?"
													<< endl << "Измерения - 1, Кол-во цехов - 2" << endl;
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
														cout << "Введите 1 или 2 " << endl;
													}
												}
												break;
											}
										}
									}
									t = 0;
									break;
								}
								else if (selection == "n") {
									found.clear();
									break;
								}
								else {
									cout << "Введите y или n" << endl;
								}



							}
						}


					}
					else {
						cout << "Введите 1 - 3" << endl;
						continue;
					}
					break;
				}


			}
				  break;

			case 10:{
				if (pipes.size() > 0) {
					cout << endl << "Введите id Трубы, которую хотите удалить " << endl;
					string id_selection;
					bool correct_check = false;
					cin >> id_selection;
					if (is_int(id_selection) == true) {
						for (size_t i = 0; i < pipes.size(); i++) {
							if (pipes[i].id == stoi(id_selection)) {
								int temp_id = pipes[i].id;
								correct_check = true;
								pipes.erase(pipes.begin() + i);
								cout << "Труба " << temp_id << " Успешно удалена " << endl;
								break;
							}
						}
						if (correct_check == false) {
							cout << "Введите один из id cуществующих труб (можно посмотреть командой 3)" << endl;
						}
					}
					else {
						cout << "Введите один из id cуществующих труб (можно посмотреть командой 3)" << endl;
					}
				}
				else {
					cout << "На данный момент в оперативной памяти нет ни одной трубы" << endl;
				}
			}
				 break;



			case 11: {
				if (KS_es.size() > 0) {
					cout << endl << "Введите id КС, которую хотите удалить " << endl;
					string id_selection;
					bool correct_check = false;
					cin >> id_selection;
					if (is_int(id_selection) == true) {
						for (size_t i = 0; i < KS_es.size(); i++) {
							if (KS_es[i].id == stoi(id_selection)) {
								
								int temp_id = KS_es[i].id;
								correct_check = true;
								KS_es.erase(KS_es.begin() + i);
								cout << "КС " << temp_id << " Успешно удалена " << endl;
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
				else {
					cout << "На данный момент в оперативной памяти нет ни одной КС" << endl;
				}
			}
				  break;


			case 0: {
				return 0;
			}
				  break;

			default: {
				cout << "введите цифру от 0 до 11 для выбора действия" << endl;
			}
				   break;
			}
		}
		else {
			cout << "введите цифру от 0 до 11 для выбора действия" << endl;
		}
		std::system("pause");
		std::system("cls");
	}
	return 0;
}