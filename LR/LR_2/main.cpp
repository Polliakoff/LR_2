
#include "KS_type.h"
#include "truba_type.h"


using namespace std;


int main() {
	setlocale(LC_ALL, "Russian");

	//массивы классов
	vector <truba_type> pipes;
	vector <KS_type> KS_es;

	string temp_string;//врмененная строковая переменная (объявлена сверху т. к. используется повсеместно)

	while (true) {

		menu();
		//переменные выбора действия
		double selection; 
		string str_selection;
		input_and_check(selection, 1);



			switch (int(selection)) {

			case 1:{
				//создание новой пустой трубы и помещение ее в вектор труб
				truba_type temp_truba;
				temp_truba.vvod();
				pipes.push_back(temp_truba);
			}
				break;

			case 2: {
				//создание новой пустой КС и помещение ее в вектор КС
				KS_type temp_KS;
				temp_KS.vvod();
				KS_es.push_back(temp_KS);

			}
				break;
			case 3: {
				
				if (pipes.size() == 0 && KS_es.size() == 0) {
					cout << endl << "На данный момент нет ни одного объекта" << endl;
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
				cout << "Введите id Трубы, которую хотите редактировать "<<endl;
				double id_selection;
				
				input_and_check(id_selection, 1);

				if (id_to_ind(pipes, int(id_selection)) == -1) {
					cout << "Введите id одной из существующих труб" << endl;
				}
				else {
					cout << "Ви хотите изменить измерения этой трубы или только статуc ремонта?"
						<< endl << "Измерения - 1, Статус ремонта - 2" << endl;
					while (true) {
						cin >> temp_string;
						if (temp_string == "1") {
							pipes[id_to_ind(pipes, int(id_selection))].vvod();
							break;
						}
						else if (temp_string == "2") {
							pipes[id_to_ind(pipes, int(id_selection))].servise();
							break;
						}
						else {
							cout << "Введите 1 или 2 " << endl;
						}
					}
				}
			}
				break;
			case 5: {
				cout << "Введите id КС, которую хотите редактировать " << endl;
				double id_selection;

				input_and_check(id_selection, 1);

				if (id_to_ind(KS_es, int(id_selection)) == -1) {
					cout << "Введите id одной из существующих КС" << endl;
				}
				else {
					cout << "Ви хотите изменить измерения этой КС или только количетсво работающих цехов?"
						<< endl << "Измерения - 1, Количетсво работающих цехов - 2" << endl;
					while (true) {
						cin >> temp_string;
						if (temp_string == "1") {
							KS_es[id_to_ind(KS_es, int(id_selection))].vvod();
							break;
						}
						else if (temp_string == "2") {
							KS_es[id_to_ind(KS_es, int(id_selection))].number_working();
							break;
						}
						else {
							cout << "Введите 1 или 2 " << endl;
						}
					}
				}
			}
				break;

			case 6: {
				
				ofstream fout;
				string filename;

				cout << "Введите название файла для сохранения "<<endl;
				cin >> filename;

				//сохранение труб в файл
				fout.open(filename + ".txt");
				
				if (fout.is_open()) {

					for (auto i : pipes) {
						i.save(fout);
					}

					for (auto i : KS_es) {
						i.save(fout);
					}
				}
				else {
					cout << "Не удалось открыть/создать файл для сохранения";
				}

				fout.close();
			}
				break;

			case 7: {
				ifstream fin;//создание потока вывода из файла
				
				string filename;

				cout << "Введите название файла загрузки " << endl;
				cin >> filename;

				//сохранение труб в файл
				fin.open(filename + ".txt");

				
				if (fin.is_open() == false) {
					cout << "Не удалось открыть этот файл для загрузки" << endl;
					break;
				}

				pipes.clear();
				KS_es.clear();
				
				KS_type::sId = 0;
				truba_type::sId = 0;
				

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

			
				fin.close();



			}
				break;
			


			case 8: {

				vector<int> found;
				bool are_there_any = false; //для определения нашли ли мы хоть что то 
				cout << "Выберите вариант фильтрации: " << endl<<
					"1 - Вывод по признаку в ремонете"<< endl<< "2 - Вывод по названию трубы "<<endl
						<<"3 - Вывод по названию и признаку в ремонте"<<endl;

				while (true) {
					
					input_and_check(selection, 1);
						
						switch (int(selection)) {
						
						case 1: {
							vector<int> service_checked;

							cout << "В ремонте ли труба? (y/n)" << endl;

							while (true) {
								cin >> str_selection;
								if (str_selection == "y") {

									service_checked = pipes_in_service(pipes, 1);
									if (service_checked.size() != 0) {
										are_there_any = true;
										for (auto i : service_checked) {
											found.push_back(i);
											pipes[i].vivod();
										}
									}
									
									break;
								}
								else if (str_selection == "n") {	
									service_checked = pipes_in_service(pipes, 0);
									if (service_checked.size() != 0) {
										are_there_any = true;
										for (auto i : service_checked) {
											found.push_back(i);
											pipes[i].vivod();
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
							cin >> name_selection;

							vector<int> names = name_to_ind(pipes, name_selection);
							if (names.size() > 0) {
								are_there_any = true;
								for (auto i : names) {
									pipes[i].vivod();
									found.push_back(i);
								}
							}
							else {
								cout << "Введите одно из названий cуществующих Труб (можно посмотреть командой 3)" << endl;
							}
							if (are_there_any == false) {
								cout << "Не найден ни один объект по заданным параметрам" << endl;
							}
						}
							  break;
						case 3: {
							cout << "Введите название Трубы, которую необходимо вывести " << endl;
							string name_selection;
							cin >> name_selection;

							vector<int> names = name_to_ind(pipes, name_selection);
							if (names.size() == 0) {
								cout << "Введите одно из названий cуществующих Труб (можно посмотреть командой 3)" << endl;
								break;
							}

							cout << "В ремонте ли труба? (y/n)" << endl;
							str_selection = "";
							bool service;
							while (true) {
								cin >> str_selection;
								if (str_selection != "y" && str_selection != "n") {
									cout << "Введите y или n" << endl;
									continue;
								}
								else {
									if (str_selection == "y") {
										service = 1;
									}
									else {
										service = 0;
									}
									break;
								}
							}

							for (auto i : names) {
								if (pipes[i].in_servise == service) {
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
							while (true) {
								cin >> str_selection;
								if (str_selection == "y") {
									for (auto i : found) {
										cout << "Ви хотите изменить измерения трубы " << i << " или только статуc ремонта?"
											<< endl << "Измерения - 1, Статус ремонта - 2" << endl;
										while (true) {
											cin >> temp_string;
											if (temp_string == "1") {
												pipes[i].vvod();
												break;

											}
											else if (temp_string == "2") {
												pipes[i].servise();
												break;
												
											}
											else {
												cout << "Введите 1 или 2 " << endl;
												continue;
											}
										}
									}
									break;
								}
								else if (str_selection == "n") {
									found.clear();
									break;
								}
								else {
									cout << "Введите y или n" << endl;
								}
							}
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

				while (true) {

					input_and_check(selection, 1);

						switch (int(selection)) {

						case 1: {
							vector<int> eff_checked;
							cout << "Введите эффективность КС" << endl;
							double effectiveness;

							while (true) {
								input_and_check(effectiveness);
									if (effectiveness > 0 && effectiveness < 1) {
										eff_checked = ks_by_eff(KS_es, effectiveness);
										if (eff_checked.size() > 0) {
											are_there_any = true;
											for (auto i : eff_checked) {
												found.push_back(i);
												KS_es[i].vivod();
											}
										}
										break;
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
							cin >> name_selection;

							vector<int> names = name_to_ind(KS_es, name_selection);
							if (names.size() > 0) {
								are_there_any = true;
								for (auto i : names) {
									KS_es[i].vivod();
									found.push_back(i);
								}
							}
							else {
								cout << "Введите одно из названий cуществующих КC (можно посмотреть командой 3)" << endl;
							}
							if (are_there_any == false) {
								cout << "Не найден ни один объект по заданным параметрам" << endl;
							}
						}
							  break;
						case 3: {
							
							cout << "Введите название КС, которую необходимо вывести " << endl;
							string name_selection;
							cin >> name_selection;

							vector<int> names = name_to_ind(KS_es, name_selection);
							if (names.size() == 0) {
								cout << "Введите одно из названий cуществующих КС (можно посмотреть командой 3)" << endl;
								break;
							}
							
							
							double effectiveness;
							cout << "Введите эффективность КС" << endl;

							while (true) {
								input_and_check(effectiveness);

									if (effectiveness > 0 && effectiveness < 1) {
										break;
									}
									else {
										cout << "Введите вещественное число больше нуля и меньше единицы" << endl;
										continue;
									}

							}


							for (auto i: names) {
								if (KS_es[i].effectiveness == effectiveness) {
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
							while (true) {
								cin >> str_selection;
								if (str_selection == "y") {
									for (auto i : found) {
										cout << "Ви хотите изменить измерения КС " << i << " или только число работающих цехов?"
											<< endl << "Измерения - 1, Число раб. цехов - 2" << endl;
										while (true) {
											cin >> temp_string;
											if (temp_string == "1") {
												KS_es[i].vvod();
												break;

											}
											else if (temp_string == "2") {
												KS_es[i].number_working();
												break;

											}
											else {
												cout << "Введите 1 или 2 " << endl;
												continue;
											}
										}
									}
									break;
								}
								else if (str_selection == "n") {
									found.clear();
									break;
								}
								else {
									cout << "Введите y или n" << endl;
								}
							}
						}
					break;
				}


			}
				  break;

			case 10:{
				if (pipes.size() > 0) {
					cout << endl << "Введите id Трубы, которую хотите удалить " << endl;
					double id_selection;

						input_and_check(id_selection, 1);

						if (id_to_ind(pipes, int(id_selection)) != -1) {
							
							pipes.erase(pipes.begin() + id_to_ind(pipes, int(id_selection)));

							cout << "Труба " << id_selection << " Успешно удалена " << endl;
							break;
						}
						else {
							cout << "Введите id одной из чуществующих труб (Можно посмотреть коммандо 3)" << endl;
						}
					
						
				}
				else {
					cout << "На данный момент нет ни одной трубы" << endl;
				}
			}
				 break;



			case 11: {
				
				if (KS_es.size() > 0) {
					cout << endl << "Введите id КС, которую хотите удалить " << endl;
					double id_selection;

					input_and_check(id_selection, 1);

					if (id_to_ind(KS_es, int(id_selection)) != -1) {
						
						KS_es.erase(KS_es.begin() + id_to_ind(KS_es, int(id_selection)));

						cout << "КС " << id_selection << " Успешно удалена " << endl;
						break;
					}
					else {
						cout << "Введите id одной из чуществующих КС (Можно посмотреть коммандо 3)" << endl;
					}


				}
				else {
					cout << "На данный момент нет ни одной КС" << endl;
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

		std::system("pause");
		std::system("cls");
	}
	return 0;
}