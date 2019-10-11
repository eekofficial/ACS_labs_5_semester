// Lab1_ACS_Korotaev.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// 16 -- 4
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

map<char, string> HEX_TO_BIN = { {'0', "0000"}, {'1', "0001"}, 
{'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"}, 
{'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"}, 
{'A', "1010"}, {'B', "1011"}, {'C', "1100"},
{'D', "1101"}, {'E', "1110"}, {'F', "1111"} };
map<string, string> BIN_TO_QUATER = { {"00", "0"}, {"01", "1"}, 
{"10", "2"}, {"11", "3"} };

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

string bin_to_quater(const string& bin_number) {
	string quater_number = "";
	int point_place = find_point_place(bin_number);
	for (int i = point_place - 1; i > 0; i -= 2) {
		if (point_place % 2 == 0) {
			string tmp = "" + to_string(bin_number[i - 1] - 48) + to_string(bin_number[i] - 48);
			quater_number.insert(0, BIN_TO_QUATER[tmp]);
		}
		else {
			string tmp;
			if (i == 1) {
				tmp = "0" + to_string(bin_number[i] - 48);
			}
			else {
				tmp = "" + to_string(bin_number[i] - 48) + to_string(bin_number[i - 1]);
			}
			quater_number.insert(0, BIN_TO_QUATER[tmp]);
		}
	}
	if (IsFloat(bin_number)) {
		quater_number += ".";
		for (int i = point_place + 1; i < bin_number.size() - 1; i += 2) {
			if (point_place % 2 == 0) {
				string tmp = "" + to_string(bin_number[i] - 48) + to_string(bin_number[i + 1] - 48);
				quater_number += BIN_TO_QUATER[tmp];
			}
			else {
				string tmp = "" + to_string((bin_number[i] - 48)) + to_string('0' - 48);
				quater_number += BIN_TO_QUATER[tmp];
			}
		}
	}
	return quater_number;
}

string hex_to_bin(const string& hex_number) {
	string bin_number = "";
	int point_place = find_point_place(hex_number);
	for (int i = 0; i < hex_number.size(); i++) {
		if (i != point_place) {
			bin_number += HEX_TO_BIN[hex_number[i]];
		}
		else {
			bin_number += ".";
		}
	}
	return bin_number;
}

string hex_to_quater(const string& hex_number) {
	return bin_to_quater(hex_to_bin(hex_number));
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
	string hex_number;
	fin.open("input.txt");
	fout.open("output.txt");
	fin >> n;
	string quater_number;
	for (int i = 0; i < n; i++) {
		fin >> hex_number;
		if (!IsValidNumber(hex_number)) {
			fout << hex_number << " -> Число введено некорректно" << endl;
		}
		else {
			quater_number = hex_to_quater(hex_number);
			cut_zeros(quater_number);
			fout << hex_number << " -> " << quater_number << endl;
		}
	}
	fin.close();
	fout.close();
	return 0;
}
