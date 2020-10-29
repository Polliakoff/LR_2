
#include "KS_type.h"
#include "truba_type.h"


using namespace std;


int main() {
	setlocale(LC_ALL, "Russian");

	//������� �������
	vector <truba_type> pipes;
	vector <KS_type> KS_es;

	string temp_string;//���������� ��������� ���������� (��������� ������ �. �. ������������ �����������)

	while (true) {

		menu();
		//���������� ������ ��������
		double selection; 
		string str_selection;
		input_and_check(selection, 1);



			switch (int(selection)) {

			case 1:{
				//�������� ����� ������ ����� � ��������� �� � ������ ����
				truba_type temp_truba;
				temp_truba.vvod();
				pipes.push_back(temp_truba);
			}
				break;

			case 2: {
				//�������� ����� ������ �� � ��������� �� � ������ ��
				KS_type temp_KS;
				temp_KS.vvod();
				KS_es.push_back(temp_KS);

			}
				break;
			case 3: {
				
				if (pipes.size() == 0 && KS_es.size() == 0) {
					cout << endl << "�� ������ ������ ��� �� ������ �������" << endl;
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
				cout << "������� id �����, ������� ������ ������������� "<<endl;
				double id_selection;
				
				input_and_check(id_selection, 1);

				if (id_to_ind(pipes, int(id_selection)) == -1) {
					cout << "������� id ����� �� ������������ ����" << endl;
				}
				else {
					cout << "�� ������ �������� ��������� ���� ����� ��� ������ �����c �������?"
						<< endl << "��������� - 1, ������ ������� - 2" << endl;
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
							cout << "������� 1 ��� 2 " << endl;
						}
					}
				}
			}
				break;
			case 5: {
				cout << "������� id ��, ������� ������ ������������� " << endl;
				double id_selection;

				input_and_check(id_selection, 1);

				if (id_to_ind(KS_es, int(id_selection)) == -1) {
					cout << "������� id ����� �� ������������ ��" << endl;
				}
				else {
					cout << "�� ������ �������� ��������� ���� �� ��� ������ ���������� ���������� �����?"
						<< endl << "��������� - 1, ���������� ���������� ����� - 2" << endl;
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
							cout << "������� 1 ��� 2 " << endl;
						}
					}
				}
			}
				break;

			case 6: {
				
				ofstream fout;
				string filename;

				cout << "������� �������� ����� ��� ���������� "<<endl;
				cin >> filename;

				//���������� ���� � ����
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
					cout << "�� ������� �������/������� ���� ��� ����������";
				}

				fout.close();
			}
				break;

			case 7: {
				ifstream fin;//�������� ������ ������ �� �����
				
				string filename;

				cout << "������� �������� ����� �������� " << endl;
				cin >> filename;

				//���������� ���� � ����
				fin.open(filename + ".txt");

				
				if (fin.is_open() == false) {
					cout << "�� ������� ������� ���� ���� ��� ��������" << endl;
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
				bool are_there_any = false; //��� ����������� ����� �� �� ���� ��� �� 
				cout << "�������� ������� ����������: " << endl<<
					"1 - ����� �� �������� � ��������"<< endl<< "2 - ����� �� �������� ����� "<<endl
						<<"3 - ����� �� �������� � �������� � �������"<<endl;

				while (true) {
					
					input_and_check(selection, 1);
						
						switch (int(selection)) {
						
						case 1: {
							vector<int> service_checked;

							cout << "� ������� �� �����? (y/n)" << endl;

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
									cout << "������� y ��� n" << endl;
									continue;
								}
							}

							if (are_there_any == false) {
								cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
							}
						}
							  break;
							
						case 2: {

							cout << "������� �������� �����, ������� ���������� ������� " << endl;
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
								cout << "������� ���� �� �������� c����������� ���� (����� ���������� �������� 3)" << endl;
							}
							if (are_there_any == false) {
								cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
							}
						}
							  break;
						case 3: {
							cout << "������� �������� �����, ������� ���������� ������� " << endl;
							string name_selection;
							cin >> name_selection;

							vector<int> names = name_to_ind(pipes, name_selection);
							if (names.size() == 0) {
								cout << "������� ���� �� �������� c����������� ���� (����� ���������� �������� 3)" << endl;
								break;
							}

							cout << "� ������� �� �����? (y/n)" << endl;
							str_selection = "";
							bool service;
							while (true) {
								cin >> str_selection;
								if (str_selection != "y" && str_selection != "n") {
									cout << "������� y ��� n" << endl;
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
								cout << "�� ������ �� ���� ������ �� �������� ����������"<<endl;
							}

						}
							  break;

						default :{
							cout << "������� 1 - 3" << endl;
							}
								break;



						}
						if (are_there_any == true) {
							cout << "������ ������������� ��������� �����? (y/n)" << endl;
							while (true) {
								cin >> str_selection;
								if (str_selection == "y") {
									for (auto i : found) {
										cout << "�� ������ �������� ��������� ����� " << i << " ��� ������ �����c �������?"
											<< endl << "��������� - 1, ������ ������� - 2" << endl;
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
												cout << "������� 1 ��� 2 " << endl;
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
									cout << "������� y ��� n" << endl;
								}
							}
						}
					break;
				}


			}
				  break;

			case 9: {

				vector<size_t> found;
				bool are_there_any = false; //��� ����������� ����� �� �� ���� ��� �� 
				cout << "�������� ������� ����������: " << endl <<
					"1 - ����� �� �������������" << endl << "2 - ����� �� �������� �� " << endl
					<< "3 - ����� �� �������� � �������������" << endl;

				while (true) {

					input_and_check(selection, 1);

						switch (int(selection)) {

						case 1: {
							vector<int> eff_checked;
							cout << "������� ������������� ��" << endl;
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
										cout << "������� ������������ ����� ������ ���� � ������ �������" << endl;
										continue;
									}
							}

							if (are_there_any == false) {
								cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
							}
						}
							  break;

						case 2: {

							cout << "������� �������� ��, ������� ���������� ������� " << endl;
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
								cout << "������� ���� �� �������� c����������� �C (����� ���������� �������� 3)" << endl;
							}
							if (are_there_any == false) {
								cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
							}
						}
							  break;
						case 3: {
							
							cout << "������� �������� ��, ������� ���������� ������� " << endl;
							string name_selection;
							cin >> name_selection;

							vector<int> names = name_to_ind(KS_es, name_selection);
							if (names.size() == 0) {
								cout << "������� ���� �� �������� c����������� �� (����� ���������� �������� 3)" << endl;
								break;
							}
							
							
							double effectiveness;
							cout << "������� ������������� ��" << endl;

							while (true) {
								input_and_check(effectiveness);

									if (effectiveness > 0 && effectiveness < 1) {
										break;
									}
									else {
										cout << "������� ������������ ����� ������ ���� � ������ �������" << endl;
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
								cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
							}

						}
							  break;

						default: {
							cout << "������� 1 - 3" << endl;
						}
							   break;



						}
						if (are_there_any == true) {
							cout << "������ ������������� ��������� ��? (y/n)" << endl;
							while (true) {
								cin >> str_selection;
								if (str_selection == "y") {
									for (auto i : found) {
										cout << "�� ������ �������� ��������� �� " << i << " ��� ������ ����� ���������� �����?"
											<< endl << "��������� - 1, ����� ���. ����� - 2" << endl;
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
												cout << "������� 1 ��� 2 " << endl;
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
									cout << "������� y ��� n" << endl;
								}
							}
						}
					break;
				}


			}
				  break;

			case 10:{
				if (pipes.size() > 0) {
					cout << endl << "������� id �����, ������� ������ ������� " << endl;
					double id_selection;

						input_and_check(id_selection, 1);

						if (id_to_ind(pipes, int(id_selection)) != -1) {
							
							pipes.erase(pipes.begin() + id_to_ind(pipes, int(id_selection)));

							cout << "����� " << id_selection << " ������� ������� " << endl;
							break;
						}
						else {
							cout << "������� id ����� �� ������������ ���� (����� ���������� �������� 3)" << endl;
						}
					
						
				}
				else {
					cout << "�� ������ ������ ��� �� ����� �����" << endl;
				}
			}
				 break;



			case 11: {
				
				if (KS_es.size() > 0) {
					cout << endl << "������� id ��, ������� ������ ������� " << endl;
					double id_selection;

					input_and_check(id_selection, 1);

					if (id_to_ind(KS_es, int(id_selection)) != -1) {
						
						KS_es.erase(KS_es.begin() + id_to_ind(KS_es, int(id_selection)));

						cout << "�� " << id_selection << " ������� ������� " << endl;
						break;
					}
					else {
						cout << "������� id ����� �� ������������ �� (����� ���������� �������� 3)" << endl;
					}


				}
				else {
					cout << "�� ������ ������ ��� �� ����� ��" << endl;
				}
			}
				  break;


			case 0: {
				return 0;
			}
				  break;

			default: {
				cout << "������� ����� �� 0 �� 11 ��� ������ ��������" << endl;
			}
				   break;
			}

		std::system("pause");
		std::system("cls");
	}
	return 0;
}