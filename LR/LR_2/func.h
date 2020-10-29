#pragma once
//квази-класс в котором лежат все функции
#include <string> 
#include <iostream>
#include <limits>
#include <vector>



void menu();
void input_and_check(double& subject, const bool& int_check = 0);
void name_check(std::string& name);
