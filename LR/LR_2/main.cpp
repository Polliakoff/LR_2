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

		cout << "�������� �������� ������� ���������� �����������: " <<
			endl << "1 - �������� ����� " << endl << "2 - �������� �� " << endl
				<< "3 - �������� �������� " << endl << "4 - ������������� ����� " << endl
					<< "5 - ������������� �� " << endl << "6 - ��������� (����� ����������������) " << endl 
						<< "7 - ��������� (����������� ��������� ��������� � ������������ � ������� ������������� ID)" 
							<< endl <<"8 - �������/������������� ����� �� ��������"<<endl<<"9 - �������/������������� �� �� �������� "
								<<endl<<"10 - �������� �����"<<endl<<"11 - �������� ��"<<endl<< "0 - �����" << endl;
		
		string selection; //���������� ������ ��������
		cin >> selection;

		if (is_int(selection) == true) {

			switch (stoi(selection)) {

			case 1:{
				//�������� ����� ������ ����� � ��������� �� � ������ ����
				truba_type temp_truba;
				temp_truba.vvod();
				temp_truba.vivod();
				pipes.push_back(temp_truba);
			}
				break;

			case 2: {
				//�������� ����� ������ �� � ��������� �� � ������ ��
				KS_type temp_KS;
				temp_KS.vvod();
				temp_KS.vivod();
				KS_es.push_back(temp_KS);

			}
				break;
			case 3: {
				
				if (pipes.size() == 0 && KS_es.size() == 0) {
					cout << endl << "�� ������ ������ � ����������� ������ ��� �� ������ �������" << endl;
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
				string id_selection;
				bool correct_check = false;
				cin >> id_selection;
				if (is_int(id_selection) == true) {
					for (size_t i = 0; i < pipes.size();i++ ) {
						if (pipes[i].id == stoi(id_selection)) {
							correct_check = true;
							cout << "�� ������ �������� ��������� ���� ����� ��� ������ �����c �������?"
								<<endl<<"��������� - 1, ������ ������� - 2"<<endl;
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
									cout << "������� 1 ��� 2 "<<endl;
								}
							}
							break;
						}	
					}
					if (correct_check == false) {
						cout << "������� ���� �� id c����������� ���� (����� ���������� �������� 3)"<<endl;
					}
				}
				else {
					cout << "������� ���� �� id c����������� ���� (����� ���������� �������� 3)" << endl;
				}
			}
				break;
			case 5: {
				cout << endl << "������� id ��, ������� ������ ������������� " << endl;
				string id_selection;
				bool correct_check = false;
				cin >> id_selection;
				if (is_int(id_selection) == true) {
					for (size_t i = 0; i < KS_es.size(); i++) {
						if (KS_es[i].id == stoi(id_selection)) {
							correct_check = true;
							cout << "�� ������ �������� ��� ��������� ���� �� ��� ������ ���������� ���������� �����? " 
								<< endl <<"��� - 1, ���-�� ����� - 2"<<endl;
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
									cout << "������� 1 ��� 2 "<<endl;
								}
							}
							break;
						}
					}
					if (correct_check == false) {
						cout << "������� ���� �� id c����������� �� (����� ���������� �������� 3)" << endl;
					}
				}
				else {
					cout << "������� ���� �� id c����������� �� (����� ���������� �������� 3)" << endl;
				}
			}
				break;

			case 6: {
				ofstream fout;
				//������� �����
				fout.open("save.txt");
				fout << "";
				fout.close();
				//���������� ���� � ����
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
				ifstream fin;//�������� ������ ������ �� �����
				
							 //�������� �� �����

				fin.open("save.txt");
				
				if (fin.is_open() == false) {
					cout << endl << "���� 'save.txt' �� ������!!!!" << endl;
					break;
				}

				//�������� �� ������ �� ���� (����������� �� ���� ��� ��)
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
					cout << endl << "���� 'save.txt' ����!!!!" << endl;
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

				selection = "";
				while (true) {
					cin >> selection;
					if (is_int(selection) == true) {
						
						switch (stoi(selection)) {
						
						case 1: {

							cout << "� ������� �� �����? (y/n)" << endl;
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
								cout << "������� ���� �� �������� c����������� ���� (����� ���������� �������� 3)" << endl;
							}


							if (are_there_any == false) {
								cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
							}
						}
							  break;
						case 3: {
							cout << "� ������� �� �����? (y/n)" << endl;
							selection = "";
							bool service;
							while (true) {
								cin >> selection;
								if (selection != "y" && selection != "n") {
									cout << "������� y ��� n" << endl;
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

							cout << "������� �������� �����, ������� ���������� ������� " << endl;
							
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
								cin >> selection;
								if (selection == "y") {
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
														pipes[i].vivod();
														break;
													}
													else if (temp_string == "2") {
														pipes[i].servise();
														pipes[i].vivod();
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
								else if (selection == "n") {
									found.clear();
									break;
								}
								else {
									cout << "������� y ��� n" << endl;
								}
							}
						}

					}
					else {
						cout << "������� 1 - 3" << endl;
						continue;
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

				selection = "";
				while (true) {
					cin >> selection;
					if (is_int(selection) == true) {

						switch (stoi(selection)) {

						case 1: {

							cout << "������� ������������� ��" << endl;

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
										cout << "������� ������������ ����� ������ ���� � ������ �������" << endl;
										continue;
									}
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
								cin >> temp_string;
								if (is_double(temp_string) == true) {
									if (stod(temp_string) > 0 && stod(temp_string) < 1) {
										effectiveness = stod(temp_string);
										break;
									}
									else {
										cout << "������� ������������ ����� ������ ���� � ������ �������" << endl;
										continue;
									}
								}
								else {
									cout << "������� ������������ ����� ������ ���� � ������ �������" << endl;
									continue;
								}
							}

							cout << "������� �������� ��, ������� ���������� ������� " << endl;

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
								cin >> selection;
								if (selection == "y") {
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
														KS_es[i].vivod();
														break;
													}
													else if (temp_string == "2") {
														KS_es[i].number_working();
														KS_es[i].vivod();
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
								else if (selection == "n") {
									found.clear();
									break;
								}
								else {
									cout << "������� y ��� n" << endl;
								}



							}
						}


					}
					else {
						cout << "������� 1 - 3" << endl;
						continue;
					}
					break;
				}


			}
				  break;

			case 10:{
				if (pipes.size() > 0) {
					cout << endl << "������� id �����, ������� ������ ������� " << endl;
					string id_selection;
					bool correct_check = false;
					cin >> id_selection;
					if (is_int(id_selection) == true) {
						for (size_t i = 0; i < pipes.size(); i++) {
							if (pipes[i].id == stoi(id_selection)) {
								int temp_id = pipes[i].id;
								correct_check = true;
								pipes.erase(pipes.begin() + i);
								cout << "����� " << temp_id << " ������� ������� " << endl;
								break;
							}
						}
						if (correct_check == false) {
							cout << "������� ���� �� id c����������� ���� (����� ���������� �������� 3)" << endl;
						}
					}
					else {
						cout << "������� ���� �� id c����������� ���� (����� ���������� �������� 3)" << endl;
					}
				}
				else {
					cout << "�� ������ ������ � ����������� ������ ��� �� ����� �����" << endl;
				}
			}
				 break;



			case 11: {
				if (KS_es.size() > 0) {
					cout << endl << "������� id ��, ������� ������ ������� " << endl;
					string id_selection;
					bool correct_check = false;
					cin >> id_selection;
					if (is_int(id_selection) == true) {
						for (size_t i = 0; i < KS_es.size(); i++) {
							if (KS_es[i].id == stoi(id_selection)) {
								
								int temp_id = KS_es[i].id;
								correct_check = true;
								KS_es.erase(KS_es.begin() + i);
								cout << "�� " << temp_id << " ������� ������� " << endl;
								break;
	                            

							}
						}
						if (correct_check == false) {
							cout << "������� ���� �� id c����������� �� (����� ���������� �������� 3)" << endl;
						}
					}
					else {
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
		}
		else {
			cout << "������� ����� �� 0 �� 11 ��� ������ ��������" << endl;
		}
		std::system("pause");
		std::system("cls");
	}
	return 0;
}