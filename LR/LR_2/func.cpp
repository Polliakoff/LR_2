#include "func.h"
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
				cout << "������� ����� �����" << endl;
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
				cout << "������� ������������ �����" << endl;
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
				cout << "�� ����� ����������������� ������ |, ������� ������ �������" << endl;
				error = true;
			}
		}

		if (error == false) {
			break;
		}
	}
}


void menu() {
	
	cout << "�������� �������� ������� ���������� �����������: " <<
		endl << "1 - �������� ����� " << endl << "2 - �������� �� " << endl
			<< "3 - �������� �������� " << endl << "4 - ������������� ����� " << endl
				<< "5 - ������������� �� " << endl << "6 - ��������� (����� ����������������) " << endl
					<< "7 - ��������� (��������� ��������� ��������� � ���������� ����������� �� �����)"
						<< endl << "8 - �������/������������� ����� �� ��������" << endl << "9 - �������/������������� �� �� �������� "
							<< endl << "10 - �������� �����" << endl << "11 - �������� ��" << endl << "0 - �����" << endl <<"���� : ";



}


