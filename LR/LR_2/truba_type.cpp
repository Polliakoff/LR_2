#include "truba_type.h"

using namespace std;

int truba_type::sId = 0;

truba_type::truba_type():id(sId++) {

}

truba_type::~truba_type()
{

}

void truba_type::vvod() {
	
	string temp_string;//��������� ������

	cout << endl << "������� ��������� ��� �����:" << endl;

	cout << "������� ����� �����" << endl;

	while (true) {
		cin >> temp_string;

		if (is_double(temp_string) == true) {
			this->length = stod(temp_string);
			break;
		}
		else {
			cout << "������� ������������ �����" << endl;
		}

	}

	cout << "������� ������� �����" << endl;
	
	while (true) {
		cin >> temp_string;

		if (is_double(temp_string) == true) {
			this->diameter = stod(temp_string);
			break;
		}
		else {
			cout << "������� ������������ �����" << endl;
		}

	}


	this->is_loaded = true;

	cout << "���� ���������� ��������"<<endl;

}

void truba_type::vivod() {
	if (this->is_loaded == true) {
	cout << endl <<"��������� ����� "<<this->id<< endl;

	cout << "Id ����� : "<< this->id << endl;

	cout << "����� �����: "<< this->length << endl;

	cout << "������� �����: "<< this->diameter << endl;

	string temp_string; //��������� ������

	if (this->in_servise == 1) temp_string = "yes";
	else temp_string = "no";

	cout << "� ������� �� ����� (yes/no) : \t "<< temp_string << endl;
	}
	else {
		cout << endl << "��������� ����� �����!" << endl;
	}


}
//��������� ������� � �������
void truba_type::servise() {
	
	string temp_string; //��������� ������
	
		cout << endl << "������ �� �� �������� ������ ������� �����? (y/n)" << endl;
		cin >> temp_string;
		
		while (true) {

			if (temp_string == "y") {
				break;
			}
			else if (temp_string == "n") {
				return;
			}
			else {
				cout << "������� 'y' ��� 'n' (��������� �������)";
			}
			cout << endl;
			cin >> temp_string;
		}



		cout << endl << "� ������� �� ����� (y/n)" << endl;
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
				cout << "������� 'y' ��� 'n' (��������� �������)";
			}
			cout << endl;
			cin >> temp_string;
		}

		if (this->in_servise == 1) temp_string = "y";
		else temp_string = "n";

		cout << "� ������� �� ����� ������ (y/n) : " << temp_string << endl;
	
}


void truba_type::save(std::ofstream& fout) {

	fout <<"t"<<"|"<<this->id<<"|"<< this->length << "|" <<
		this->diameter << "|" <<this->in_servise << "|" <<endl;
	cout << "����� " << this->id << " ������� ���������!" << endl;

}

void truba_type::load(std::ifstream& fin, std::string load_string) {
	
	string temp_string; //��������� ������

	//�������� ��� �����
	int i = 0;
	int j = 0;
	temp_string = "";//�������������� ��������� ������
	while (true) {

		if (i > 1) {
			if (load_string[i] != '|') {
				temp_string += load_string[i];
			}
			else {
				switch (j) {
				case 1:
					for (int k = 0; k < temp_string.length(); k++) {
						if (temp_string[k] == '.') temp_string[k] = ',';
					}
					this->length = stod(temp_string);
					break;
				case 2:
					for (int k = 0; k < temp_string.length(); k++) {
						if (temp_string[k] == '.') temp_string[k] = ',';
					}
					this->diameter = stod(temp_string);
					break;

				case 3:
					this->in_servise = stoi(temp_string);
					cout << "����� " << this->id << " ������� ���������!" << endl;
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

