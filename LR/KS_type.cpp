#include "KS_type.h"
using namespace std;

int KS_type::sId = 0;

KS_type::KS_type() :id(sId++) {

}

KS_type::~KS_type()
{

}

void KS_type::vvod() {
	
	string temp_string;//��������� ������
	bool error;//���������� ���������� �������������� ��� ����������� ������
	cout << endl << "������� ��������� ��� ��:" << endl;



	cout << "������� �������� ��" << endl;
	
	while (true) {
		cin >> temp_string;
		error = false;
		for (auto i : temp_string) {
			if (i == '|') {
				cout << "�� ����� ����������������� ������ |, ������� ������ �������" << endl;
				error = true;
			}
		}

		if (error == false) {
			this->name = temp_string;
			break;
		}
	}

	cout << "������� ����� ����� ��" << endl;
	
	while (true) {
		cin >> temp_string;

		if (is_int(temp_string) == true) {
			this->workshop_number = stoi(temp_string);
			break;
		}
		else {
			cout << "������� ����� �����" << endl;
		}

	}

	int temp_int; //��������� ������������ ����������
	
	cout << "������� ����� ���������� ����� �� (<= ����� �����)" << endl;

	while (true) {
		cin >> temp_string;

		if (is_int(temp_string) == true) {
			temp_int = stoi(temp_string);
		}
		else {
			cout << "������� ����� �����" << endl;
			continue;
		}

		if (temp_int <= this->workshop_number) {
			this->working_workshops = temp_int;
			break;
		}
		else {
			cout << "������� ����� <= ����� �����" << endl;
			continue;
		}
	}
	
	while (true) {
		if (temp_int <= this->workshop_number) {
			this->working_workshops = temp_int;
			break;
		}
		else cout << "������� ����� <= ����� �����"<<endl;
		cin >> temp_int;
	}

	cout << "������� ������������� ��" << endl;
	
	while (true) {
		cin >> temp_string;

		if (is_double(temp_string) == true && stod(temp_string)<=1) {
			this->effectiveness = stod(temp_string);
			break;
		}
		else {
			cout << "������� ������������ ����� ������ �������" << endl;
		}

	}
	
	this->is_loaded = true;
	cout << "���� ���������� ��������" << endl;

}

void KS_type::vivod() {
	if (this->is_loaded == true) {
		cout << endl << "��������� �� " << this->id << endl;

		cout << "Id �� : " << this->id << endl;

		cout << "�������� ��: " << this->name << endl;

		cout << "����� ����� ��: " << this->workshop_number << endl;

		cout << "����� ���������� ����� ��: " << this->working_workshops << endl;

		cout << "������������� ��: " << this->effectiveness << endl;
	}
	else {
		cout << endl << "��������� �� �����!" << endl;
	}

}
//��������� ���-�� ������� �����
void KS_type::number_working() {

	string temp_string; //��������� ������

	cout << endl << "������ �� �� ���������/�������� ��� ��? (y/n)" << endl;
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




	while (true) {
		cout << endl << "�� ������ ���������, �������� ��� ��� �����? (+/-/q (quit))" << endl;
		cin >> temp_string;
		
		if (temp_string == "+") {
			if((this->working_workshops+1)<=this->workshop_number) this->working_workshops++;
			else {
				cout << "���������� ������������ ����� ���������� �����";
				continue;
			}
			break;
		}
		else if (temp_string == "-") {
			if ((this->working_workshops - 1) >= 0) this->working_workshops--;
			else {
				cout << "���������� ����� ��� ���";
				continue;
			}
			break;
		}
		
		else if (temp_string == "q") {
			break;
		}
		
		else {
			cout << "������� '+', '-' ��� 'q' (��������� �������)";
		}
		cout << endl;
	}

	cout << "����� ���������� ����� �� ������ ������ :" << this->working_workshops << endl;





}
//���������� � ����
void KS_type::save(std::ofstream& fout) {

	fout << "k" << "|"<< this->id << "|" << this->name << "|" <<
		this->workshop_number << "|" << this->working_workshops <<"|"<< this->effectiveness << "|"<<endl;
	cout << "�� " << this->id << " ������� ���������!" << endl;
}
//�������� �� �����
void KS_type::load(std::ifstream& fin, std::string load_string) {

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
				cout << "�� " << this->id << " ������� ���������!" << endl;
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