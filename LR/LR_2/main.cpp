#include "KS_type.h"
#include "truba_type.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	//массивы классов
	map <int, truba_type> pipes;
	map <int, KS_type> KS_es;
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
				pipes.emplace(temp_truba.id,temp_truba);
			}
				  break;
			case 2: {
				//создание новой пустой КС и помещение ее в вектор КС
				KS_type temp_KS;
				temp_KS.vvod();
				KS_es.emplace(temp_KS.id, temp_KS);
			}
				break;
			case 3: {
				vivod_vsego(pipes, "трубы");
				vivod_vsego(KS_es, "КС");
			}
				break;
			case 4: {
				edit_by_id(pipes);
			}
				break;
			case 5: {
				edit_by_id(KS_es);
			}
				break;
			case 6: {
				save_all(pipes, KS_es);
			}
				break;
			case 7: {
				load_all(pipes, KS_es);
			}
				break;
			case 8: {
				switch_search(pipes);
			}
				  break;
			case 9: {
				switch_search(KS_es);
			}
				  break;
			case 10:{
				delete_object(pipes, "Труба ");
			}
				 break;
			case 11: {
				delete_object(pipes, "КС ");
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