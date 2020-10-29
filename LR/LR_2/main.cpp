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
				cout <<endl<< "������� id �����, ������� ������ ������������� "<<endl;
				double id_selection;
				bool id_found = false;
				input_and_check(id_selection, 1);
					for (size_t i = 0; i < pipes.size();i++ ) {
						if (pipes[i].id == id_selection) {
							id_found = true;
							cout << "�� ������ �������� ��������� ���� ����� ��� ������ �����c �������?"
								<<endl<<"��������� - 1, ������ ������� - 2"<<endl;
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
									cout << "������� 1 ��� 2 "<<endl;
								}
							}
							break;
						}	
					}
					if (id_found == false) {
						cout << "������� ���� �� id c����������� ���� (����� ���������� �������� 3)"<<endl;
					}
			}
				break;
			case 5: {
				cout << endl << "������� id ��, ������� ������ ������������� " << endl;
				double id_selection;
				bool id_found = false;
				cin >> id_selection;
					for (size_t i = 0; i < KS_es.size(); i++) {
						if (KS_es[i].id == id_selection) {
							id_found = true;
							cout << "�� ������ �������� ��� ��������� ���� �� ��� ������ ���������� ���������� �����? " 
								<< endl <<"��� - 1, ���-�� ����� - 2"<<endl;
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
									cout << "������� 1 ��� 2 "<<endl;
								}
							}
							break;
						}
					}
					if (id_found == false) {
						cout << "������� ���� �� id c����������� �� (����� ���������� �������� 3)" << endl;
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

				vector<size_t> found;
				bool are_there_any = false; //��� ����������� ����� �� �� ���� ��� �� 
				cout << "�������� ������� ����������: " << endl<<
					"1 - ����� �� �������� � ��������"<< endl<< "2 - ����� �� �������� ����� "<<endl
						<<"3 - ����� �� �������� � �������� � �������"<<endl;

				while (true) {
					
					input_and_check(selection, 1);
						
						switch (int(selection)) {
						
						case 1: {

							cout << "� ������� �� �����? (y/n)" << endl;
							while (true) {
								cin >> str_selection;
								if (str_selection == "y") {
									for (auto i : pipes) {
										if (i.in_servise == true) {
											found.push_back(i.id);
											i.vivod();
											are_there_any = true;
										}
									}
									break;
								}
								else if (str_selection == "n") {
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
							bool id_found = false;
							cin >> name_selection;
							for (size_t i = 0; i < pipes.size(); i++) {
								if (pipes[i].name == name_selection) {
									id_found = true;
									found.push_back(i);
									pipes[i].vivod();
									are_there_any = true;
								}
							}
							if (id_found == false) {
								cout << "������� ���� �� �������� c����������� ���� (����� ���������� �������� 3)" << endl;
							}


							if (are_there_any == false) {
								cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
							}
						}
							  break;
						case 3: {
							cout << "� ������� �� �����? (y/n)" << endl;
							str_selection = "";
							bool service;
							while (true) {
								cin >> selection;
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

							cout << "������� �������� �����, ������� ���������� ������� " << endl;
							
							string name_selection;
							bool id_found = false;
							string name;
							
							cin >> name_selection;
							for (size_t i = 0; i < pipes.size(); i++) {
								if (pipes[i].name == name_selection) {
									id_found = true;
									name = pipes[i].name;
								}
							}
							if (id_found == false) {
								cout << "������� ����� �� �������� c����������� ���� (����� ���������� �������� 3)" << endl;
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
							size_t t = 0;
							while (true) {
								cin >> str_selection;
								if (str_selection == "y") {
									while (t < found.size()) {
										for (size_t i = 0; i < pipes.size(); i++) {
											if (pipes[i].id == found[t]) {
												t++;
												cout << "�� ������ �������� ��������� ����� " << t - 1 << " ��� ������ �����c �������?"
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
													}
												}
												break;
											}
										}
									}
									t = 0;
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

							cout << "������� ������������� ��" << endl;
							double effectiveness;

							while (true) {
								input_and_check(effectiveness);
									if (effectiveness > 0 && effectiveness < 1) {
										for (auto i : KS_es) {
											if (i.effectiveness == effectiveness) {
												found.push_back(i.id);
												i.vivod();
												are_there_any = true;
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
							bool id_found = false;
							cin >> name_selection;
							for (size_t i = 0; i < KS_es.size(); i++) {
								if (KS_es[i].name == name_selection) {
									id_found = true;
									found.push_back(i);
									KS_es[i].vivod();
									are_there_any = true;
								}
							}
							if (id_found == false) {
								cout << "������� ����� �� �������� c����������� �� (����� ���������� �������� 3)" << endl;
							}
							
							if (are_there_any == false) {
								cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
							}
						}
							  break;
						case 3: {
							
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

							cout << "������� �������� ��, ������� ���������� ������� " << endl;

							string name_selection;
							bool id_found = false;
							string name;

							cin >> name_selection;
							for (size_t i = 0; i < KS_es.size(); i++) {
								if (KS_es[i].name == name_selection) {
									id_found = true;
									name = KS_es[i].name;
								}
							}
							if (id_found == false) {
								cout << "������� ����� �� �������� c����������� �� (����� ���������� �������� 3)" << endl;
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
							size_t t = 0;
							while (true) {
								cin >> str_selection;
								if (str_selection == "y") {
									while (t < found.size()) {
										for (size_t i = 0; i < KS_es.size(); i++) {
											if (KS_es[i].id == found[t]) {
												t++;
												cout << "�� ������ �������� ��������� �� " << t - 1 << " ��� ������ ����� ���������� �����?"
													<< endl << "��������� - 1, ���-�� ����� - 2" << endl;
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
													}
												}
												break;
											}
										}
									}
									t = 0;
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
					bool id_found = false;
					
					input_and_check(id_selection);
						for (size_t i = 0; i < pipes.size(); i++) {
							if (pipes[i].id == id_selection) {
								int temp_id = pipes[i].id;
								id_found = true;
								pipes.erase(pipes.begin() + i);
								cout << "����� " << temp_id << " ������� ������� " << endl;
								break;
							}
						}
						if (id_found == false) {
							cout << "������� ���� �� id c����������� ���� (����� ���������� �������� 3)" << endl;
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
					bool id_found = false;

					input_and_check(id_selection);

						for (size_t i = 0; i < KS_es.size(); i++) {
							if (KS_es[i].id == id_selection) {
								
								int temp_id = KS_es[i].id;
								id_found = true;
								KS_es.erase(KS_es.begin() + i);
								cout << "�� " << temp_id << " ������� ������� " << endl;
								break;
	                            

							}
						}
						if (id_found == false) {
							cout << "������� ���� �� id c����������� �� (����� ���������� �������� 3)" << endl;
						}

				}
				else {
					cout << "�� ������ ������ � ����������� ������ ��� �� ����� ��" << endl;
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