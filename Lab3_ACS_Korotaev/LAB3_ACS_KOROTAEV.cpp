// LAB3_ACS_KOROTAEV.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
	Все возможные логические операторы в программе:
		¬ - Отрицание
		& - Конъюнкция
		+ - Дизъюнкция
		± - Сумма по модулю 2
		> - Импликация
		| - Штрих Шеффера
		† - Стрелка Пирса
		= - Эквивалентность
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

map<string, int> BOOL_VALUES4 = { {"0000", 0}, {"0001", 0}, {"0010", 0}, {"0011", 0},
							{"0100", 0}, {"0101", 0}, {"0110", 0}, {"0111", 0},
							{"1000", 0}, {"1001", 0}, {"1010", 0}, {"1011", 0},
							{"1100", 0}, {"1101", 0}, {"1110", 0}, {"1111", 0} };

map<string, int> BOOL_VALUES3 = { {"000", 0}, {"001", 0}, {"010", 0}, {"011", 0},
							{"100", 0}, {"101", 0}, {"110", 0}, {"111", 0} };

map<string, int> BOOL_VALUES2 = { {"00", 0}, {"01", 0}, {"10", 0}, {"11", 0} };
map<string, int> BOOL_VALUES1 = { {"0", 0}, {"1", 0} };

char Not(int a) {
	if (a == 1) return '0';
	return '1';
}

char And(int a, int b) {
	if ((a == 1) & (b == 1)) {
		return '1';
	}
	else return '0';
}

char Or(int a, int b) {
	if ((a == 0) & (b == 0)) {
		return '0';
	}
	else return '1';
}

char Xor(int a, int b) {
	if ((a == 0) & (b == 0)) {
		return '0';
	}
	else if ((a == 1) & (b == 1)) {
		return '0';
	}
	else return '1';
}

char Implication(int a, int b) {
	if ((a == 1) & (b == 0)) {
		return '0';
	}
	else return '1';
}

char Sheffer(int a, int b) {
	if ((a == 1) & (b == 1)) {
		return '0';
	}
	else return '1';
}

char Pirse(int a, int b) {
	if ((a == 0) & (b == 0)) {
		return '1';
	}
	else return '0';
}

char Equivalention(int a, int b) {
	if ((a == 0) & (b == 0)) {
		return '1';
	}
	else if ((a == 1) & (b == 1)) {
		return '1';
	}
	else return '0';
}

bool IsRightBracketSequence(const string& s) {
	int bracket_counter = 0;
		for (auto i = 0; i < s.size(); i++) {
			if (s[i] == '(') {
				bracket_counter++;
			}
			else if (s[i] == ')') {
				bracket_counter--;
			}
			if (bracket_counter < 0) break;
	}
	if (bracket_counter == 0) return true;
	return false;
}

void FindTheDeepestBracket(const string& s, int& pos1, int& pos2) {
	int bracket_counter = 0;
	int max = 0;
	vector<int> bracket_counters;
	for (auto i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			bracket_counter++;
		}
		else if (s[i] == ')') {
			bracket_counter--;
		}
		if (bracket_counter < 0) break;
		bracket_counters.push_back(bracket_counter);
	}

	for (auto i = 0; i < bracket_counters.size(); i++) {
		if (bracket_counters[i] > max) {
			max = bracket_counters[i];
			pos1 = i;
		}
	}

	for (auto i = pos1 + 1; i < bracket_counters.size(); i++) {
		if (bracket_counters[i] == max - 1) {
			pos2 = i;
			break;
		}
	}
}

string WhatTypeOfСontent(const string& s) {
	/*
		Существует три типа содержимого скобки:
			1) Просто один операнд
			2) Логическое отрицание одного операнда
			3) Булевы фунции двух операндов
	*/
	if (s.size() == 1) {
		if ((s[0] - '0' == 0) || (s[0] - '0' == 1)) {
			return "type_one";
		}
	}
	else if (s.size() == 2) {
		if ((s[0] == -84) and ((s[1] == '0') || (s[1] == '1'))) {
			return "type_two";
		}
	}
	else if (s.size() == 3) {
		if (((s[0] - '0' == 0) || (s[0] - '0' == 1)) &
			((s[1] == L'&') || (s[1] == L'+') || (s[1] == -79) ||
			(s[1] == L'>') || (s[1] == L'|') ||
			(s[1] == -122) || (s[1] == L'=')) &
			((s[2] - '0' == 0) || (s[2] - '0' == 1))) {
			return "type_three";
		}
	}
	return "not_valid";
}

int CountOperands(const string& s) {
	map<char, int> count;
	int counter = 0;
	for (int i = 0; i < s.size(); i++) {
		count[s[i]] += 1;
	}
	if (count.count('a') > 0) {
		counter++;
	}
	if (count.count('b') > 0) {
		counter++;
	}
	if (count.count('c') > 0) {
		counter++;
	}
	if (count.count('d') > 0) {
		counter++;
	}
	return counter;
}

map<string, int> GetValuesMap(const string& str) {
	map<string, int> bool_values;
	int count_operands = CountOperands(str);
	if (count_operands == 4) {
		bool_values = BOOL_VALUES4;
	}
	else if (count_operands == 3) {
		bool_values = BOOL_VALUES3;
	}
	else if (count_operands == 2) {
		bool_values = BOOL_VALUES2;
	}
	else if (count_operands == 1) {
		bool_values = BOOL_VALUES1;
	}
	return bool_values;
}

map<string, int> BuildTruthTable(const string& str) {
	int pos1, pos2;
	map<string, int> bool_values;
	string s;
	bool_values = GetValuesMap(str);
	for (auto& item : bool_values) {
		s = str;
		char a, b, c, d;

		if (item.first.size() == 1) {
			a = item.first[0];
		}
		else if (item.first.size() == 2) {
			a = item.first[0];
			b = item.first[1];
		}
		else if (item.first.size() == 3) {
			a = item.first[0];
			b = item.first[1];
			c = item.first[2];
		}
		else if (item.first.size() == 4) {
			a = item.first[0];
			b = item.first[1];
			c = item.first[2];
			d = item.first[3];
		}

			for (int i = 0; i < s.size(); i++) {
				if (s[i] == 'a') {
					s[i] = a;
				}
				else if (s[i] == 'b') {
					s[i] = b;
				}
				else if (s[i] == 'c') {
					s[i] = c;
				}
				else if (s[i] == 'd') {
					s[i] = d;
				}
			}

			while (s.size() > 1) {
				FindTheDeepestBracket(s, pos1, pos2);
				cout << s << endl;
				string s_bracket = "";
				for (int i = pos1 + 1; i < pos2; i++) {
					s_bracket += s[i];
				}

				string type_of_content = WhatTypeOfСontent(s_bracket);
				if (type_of_content == "type_one") {
					return { {"0", 0 }, {"1", 1} };
				}
				else if (type_of_content == "type_two") {
					char res = Not(s_bracket[1] - '0');
					s[pos1] = res;
					s.erase(pos1 + 1, 3);
				}
				else if (type_of_content == "type_three") {
					char res;
					if (s_bracket[1] == L'&') {
						res = And(s_bracket[0] - '0', s_bracket[2] - '0');
					}
					else if (s_bracket[1] == L'+') {
						res = Or(s_bracket[0] - '0', s_bracket[2] - '0');
					}
					else if (s_bracket[1] == -79) {
						res = Xor(s_bracket[0] - '0', s_bracket[2] - '0');
					}
					else if (s_bracket[1] == L'>') {
						res = Implication(s_bracket[0] - '0', s_bracket[2] - '0');
					}
					else if (s_bracket[1] == L'|') {
						res = Sheffer(s_bracket[0] - '0', s_bracket[2] - '0');
					}
					else if (s_bracket[1] == -122) {
						res = Pirse(s_bracket[0] - '0', s_bracket[2] - '0');
					}
					else if (s_bracket[1] == L'=') {
						res = Equivalention(s_bracket[0] - '0', s_bracket[2] - '0');
					}
					s[pos1] = res;
					s.erase(pos1 + 1, 4);
				}
				else if (type_of_content == "not_valid") {
					map<string, int> wrong = {};
					return wrong;
				}
			}
			item.second = (int)s[0] - 48;
		}
		return bool_values;
	}

int main()
{
	string str;
	int pos1 = 0;
	int pos2 = 0;
	map<string, int> truth_table;
	ifstream fin;
	ofstream fout;
	int n;
	int count = 1;
	fin.open("input.txt");
	fout.open("output.txt");
	fin >> n;
	for (int i = 0; i < n; i++) {
		fin >> str;
		str.insert(0, "(");
		str += ')';
		if (IsRightBracketSequence(str)) {
			truth_table = BuildTruthTable(str);
			if (truth_table.size() != 0) {
				fout << "F" << count << " : ";
				for (auto& item : truth_table) {
					fout << item.first << ":" << item.second <<  " ; ";
				}
				fout << endl;
				count++;
			}
			else {
				fout << "not valid" << endl;
			}
		}
		else {
			fout << "not right bracket's sequence" << endl;
		}
	}
	
	return 0;
}