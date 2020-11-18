#include "KS_type.h"
#include "truba_type.h"

using namespace std;

vector<int> find_by_parameter(map<int,truba_type>& pipes, const bool& output) {
	
	cout << "� ������� �� �����? (y/n)" << endl;
	vector<int> found;
	while (true) {
		string str_selection;
		cin >> str_selection;
		if (str_selection == "y") {

			  found = pipes_in_service(pipes, true);
			if (found.size() != 0) {
				for (auto i : found) {
					if (output) pipes[i].vivod();
				}
			}
			break;
		}
		else if (str_selection == "n") {
			 found = pipes_in_service(pipes, false);
			if (found.size() != 0) {

				for (auto i : found) {
					if (output) pipes[i].vivod();
				}
			}
			break;
		}
		else {
			cout << "������� y ��� n" << endl;
			continue;
		}
	}

	if (found.size() == 0) {
		if (output) cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
	}

	return found;
}

vector<int> find_by_parameter(map<int, KS_type>& KS_es, const bool& output) {

	cout << "������� ������������� ��" << endl;
	double effectiveness;

	vector<int> found;

	while (true) {
		input_and_check(effectiveness);
		if (effectiveness > 0 && effectiveness < 1) {
			found = ks_by_eff(KS_es, effectiveness);
			if (found.size() > 0) {
				for (auto i : found) {
					if (output) KS_es[i].vivod();
				}
			}
			break;
		}
		else {
			cout << "������� ������������ ����� ������ ���� � ������ �������" << endl;
			continue;
		}
	}

	if (found.size() == 0) {
		if (output) cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
	}

	return found;
}

void package_edit(vector<int>& found, map<int,truba_type>& pipes) {
	
	if (found.size() != 0) {
		cout << "������ ������������� ��������� �����? (y/n)" << endl;
		while (true) {
			string str_selection;
			cin >> str_selection;
			if (str_selection == "y") {
				for (auto i : found) {
					pipes[i].servise();
				}
				break;
			}
			else if (str_selection == "n") {
				found.clear();
				return;
			}
			else {
				cout << "������� y ��� n" << endl;
			}
		}
	}
}

void package_edit(vector<int>& found, map<int,KS_type>& KS_es){

	if (found.size() != 0) {
		cout << "������ ������������� ��������� �����? (y/n)" << endl;
		while (true) {
			string str_selection;
			cin >> str_selection;
			if (str_selection == "y") {
				for (auto i : found) {
					KS_es[i].number_working();
				}
				break;
			}
			else if (str_selection == "n") {
				found.clear();
				return;
			}
			else {
				cout << "������� y ��� n" << endl;
			}
		}
	}
}

void edit_by_id(map<int, truba_type>& pipes){
	
	cout << "������� id �����, ������� ������ ������������� " << endl;
	double id_selection;

	input_and_check(id_selection, 1);

	if (!(pipes.find(int(id_selection)) != pipes.end())) {
		cout << "������� id ����� �� ������������ ����" << endl;
	}
	else {
		pipes[id_selection].servise();
		}
}

void edit_by_id(map<int, KS_type>& KS_es) {

	cout << "������� id ��, ������� ������ ������������� " << endl;
	double id_selection;

	input_and_check(id_selection, 1);

	if (!(KS_es.find(int(id_selection)) != KS_es.end())) {
		cout << "������� id ����� �� ������������ ��" << endl;
	}
	else {
		KS_es[id_selection].number_working();
	}
}


void save_all(const map<int,truba_type>& pipes, const map<int,KS_type>& KS_es) {
	
	ofstream fout;
	string filename;

	cout << "������� �������� ����� ��� ���������� " << endl;
	cin >> filename;

	//���������� � ����
	fout.open(filename + ".clbr");

	if (fout.is_open()) {

		for (auto i : pipes) {
			i.second.save(fout);
		}

		for (auto i : KS_es) {
			i.second.save(fout);
		}
	}
	else {
		cout << "�� ������� �������/������� ���� ��� ����������";
	}

	fout.close();
}

void load_all(map<int,truba_type>& pipes, map<int, KS_type>& KS_es) {
	ifstream fin;//�������� ������ ������ �� �����
	string filename;
	cout << "������� �������� ����� �������� " << endl;
	cin >> filename;
	//���������� ���� � ����
	fin.open(filename + ".clbr");

	if (fin.is_open() == false) {
		cout << "�� ������� ������� ���� ���� ��� ��������" << endl;
		return;
	}

	pipes.clear();
	KS_es.clear();

	string temp_string;
	int max_KS_id = 0;
	int max_pipe_id = 0;

	while (std::getline(fin, temp_string)) {

		if (temp_string[0] == 't') {
			truba_type temp_truba;
			temp_truba.load(fin, temp_string);
			if (temp_truba.id > max_pipe_id) max_pipe_id = temp_truba.id;
			pipes.emplace(temp_truba.id, temp_truba);
		}
		else {
			KS_type temp_KS;
			temp_KS.load(fin, temp_string);
			if (temp_KS.id > max_KS_id) max_KS_id = temp_KS.id;
			KS_es.emplace(temp_KS.id, temp_KS);
		}
	}

	truba_type::sId = max_pipe_id+1;
	KS_type::sId = max_KS_id+1;

	fin.close();
}

void input_and_check(double& subject, const bool& int_check) {
	while (true) {
		subject = 0;
		cin >> subject;
		if (cin.good() && (!(subject - floor(subject)) || int_check == 0)) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		else {
			if (int_check == 1) cout << "������� ����� �����" << endl;
			else                cout << "������� ������������ �����" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

void input_and_check(std::string& subject, const std::string& name) {

	cout << "������� " << name << endl;
	getline(std::cin, subject);

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

vector<int> pipes_in_service(map <int,truba_type> pipes, bool in_service) {

	vector<int> return_vector;

	for (auto i:pipes) {
		if (i.second.in_servise == in_service) {
			return_vector.push_back(i.first);
		}
	}

	return return_vector;

}

vector<int> ks_by_eff(map<int, KS_type> KS_es, double effectiveness) {

	vector<int> return_vector;

	for (auto i:KS_es) {
		if (i.second.effectiveness == effectiveness) {
			return_vector.push_back(i.first);
		}
	}

	return return_vector;
}

