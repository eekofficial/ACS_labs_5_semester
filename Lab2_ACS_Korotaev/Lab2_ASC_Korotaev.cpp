// Lab2_ASC_Korotaev.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;

map<string, string> HEX_TO_DEC = { {"0", "0"}, {"1", "1"},
{"2", "2"}, {"3", "3"}, {"4", "4"}, {"5", "5"}, {"6", "6"},
{"7", "7"}, {"8", "8"}, {"9", "9"}, {"10", "A"},{"11", "B"},
{"12", "C"}, {"13", "D"}, {"14", "E"}, {"15", "F"}, };

bool IsFloat(const string& number) {
	for (int i = 0; i < number.size(); i++) {
		if ((number[i] == ',') || (number[i] == '.')) {
			return true;
		}
	}
	return false;
}

bool IfOnlyZeros(const string& number) {
	for (int i = 0; i < number.size(); i++) {
		if (number[i] != '0' && number[i] != '.') {
			return false;
		}
	}
	return true;
}

void cut_zeros(string& number) {
	while (true) {
		if (IfOnlyZeros(number)) {
			number = "0";
			break;
		}
		else if (number != "0") {
			if (number[0] == '0') {
				number.erase(0, 1);
			}
			else if ((IsFloat(number)) && (number[number.size() - 1] == '0')) {
				number.erase(number.size() - 1, 1);
			}
			else if ((IsFloat(number)) && (number[number.size() - 1] == '.')) {
				number.erase(number.size() - 1, 1);
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
}

int find_point_place(const string& number) {
	for (int i = 0; i < number.size(); i++) {
		if ((number[i] == ',') || (number[i] == '.')) {
			return i;
		}
	}
	return number.size();
}

void normalize_hexes(string& quater_one, string& quater_two) {
	if (!IsFloat(quater_one)) {
		quater_one += ".0";
	}
	if (!IsFloat(quater_two)) {
		quater_two += ".0";
	}
	
	int point_place_one = find_point_place(quater_one);
	int point_place_two = find_point_place(quater_two);
	
	if (point_place_one < point_place_two) {
		int s = point_place_two - point_place_one;
		for (int i = 0; i < s; i++) {
			quater_one.insert(0, "0");
		}
	}
	else if (point_place_one > point_place_two) {
		int s = point_place_one - point_place_two;
		for (int i = 0; i < s; i++) {
			quater_two.insert(0, "0");
		}
	}

	point_place_one = find_point_place(quater_one);
    point_place_two = find_point_place(quater_two);
	int delta_one = quater_one.size() - point_place_one;
	int delta_two = quater_two.size() - point_place_two;

	if (delta_one < delta_two) {
		int s = delta_two - delta_one;
		for (int i = 0; i < s; i++) {
			quater_one += to_string('0' - 48);
		}
	}
	else if (delta_one > delta_two) {
		int s = delta_one - delta_two;
		for (int i = 0; i < s; i++) {
			quater_two += to_string('0' - 48);
		}
	}
}

string add_hex(string quater_one, string quater_two) {
	string result;
	int remember = 0;
	normalize_hexes(quater_one, quater_two);
	for (int i = quater_one.size() - 1; i >= 0; i--) {
		if ((quater_one[i] == '.') || (quater_one[i] == ',')) {
			result.insert(0, ".");
		}
		else {
			int quater_one_i, quater_two_i;
			if (quater_one[i] >= 65 && quater_one[i] <= 70) {
				quater_one_i = (int)quater_one[i] - 55;
			 }
			else {
				quater_one_i = (int)quater_one[i] - 48;
			}
			if (quater_two[i] >= 65 && quater_two[i] <= 70) {
				quater_two_i = (int)quater_two[i] - 55;
			}
			else {
				quater_two_i = (int)quater_two[i] - 48;
			}
			int add = quater_one_i + quater_two_i + remember;
			int count = add / 16;
			int mod = add % 16;
			result.insert(0, HEX_TO_DEC[to_string(mod)]);
			remember = count;
		}
	}
	if (remember) {
		result.insert(0, to_string(remember));
	}
	return result;
}

bool IsValidNumber(const string& hex_number) {
	for (int i = 0; i < hex_number.size(); i++) {
		if ((hex_number[i] != '0') && (hex_number[i] != '1') && (hex_number[i] != '2') &&
			(hex_number[i] != '3') && (hex_number[i] != '4') && (hex_number[i] != '5') &&
			(hex_number[i] != '6') && (hex_number[i] != '7') && (hex_number[i] != '8') &&
			(hex_number[i] != '9') && (hex_number[i] != 'A') && (hex_number[i] != 'B') &&
			(hex_number[i] != 'C') && (hex_number[i] != 'D') && (hex_number[i] != 'E') &&
			(hex_number[i] != 'F') && (hex_number[i] != ',') && (hex_number[i] != '.')) {
			return false;
		}
	}
	return true;
}

int main()
{
	ifstream fin;
	ofstream fout;
	int n; //количество чисел
	string hex_number_one, hex_number_two, result;
	fin.open("input.txt");
	fout.open("output.txt");
	fin >> n;
	for (int i = 0; i < n; i++) {
		fin >> hex_number_one >> hex_number_two;
		if (!IsValidNumber(hex_number_one) || !IsValidNumber(hex_number_two)) {
			fout << hex_number_one << " " << hex_number_two << " -> Числа введены некорректно" << endl;
		}
		else {
			result = add_hex(hex_number_one, hex_number_two);
			cut_zeros(result);
			fout << hex_number_one << " + " << hex_number_two << " = " << result << endl;
		}
	}
	fin.close();
	fout.close();
	return 0;
}
