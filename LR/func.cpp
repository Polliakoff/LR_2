#include "func.h"
//функци€ провер€юща€ строку на то записано ли в ней целое число
bool is_int(std::string temp_string)
{
	for (int i = 0; i < temp_string.length(); i++) {
		if (!(temp_string[i] >= '0' && temp_string[i] <= '9')) {
			return false;;
		}
	}
	return true;
}
//функци€ провер€юща€ строку на то записано ли в ней вещественное число
bool is_double(std::string& temp_string)
{
	int dot_count = 0;
	for (int i = 0; i < temp_string.length(); i++) {
		if (!((temp_string[i] >= '0' && temp_string[i] <= '9') || temp_string[i] == '.')) {
			return false;
		}
		else if (temp_string[i] == '.') {
			dot_count++;
			temp_string[i] = ',';
		}
	}

	if (dot_count <= 1) {
		return true;
	}
	else return false;
}
