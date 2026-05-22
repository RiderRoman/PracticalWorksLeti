#include <iostream>
#include <windows.h>
#include <limits>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#undef max

using namespace std;

const int ACTION_PRINT_MENU = 100;
const int ACTION_PRINT_NOTATION = 200;
const int ACTION_PRINT_NOTATION_2 = 201;

const int ACTION_TRANSFORM_PROBLEM = 1;
const int ACTION_CHECK_PROBLEM = 2;
const int ACTION_SOLVE_PROBLEM = 3;
const int ACTION_TURN_OFF = 0;

const int COMMON_PROBLEM = 1;
const int DIRECT_POLISH_NOTATION = 2;
const int REVERSE_POLISH_NOTATION = 3;

class Stack {
private:
	vector<int> data;
public:
	void push(int value) { data.push_back(value); }
	void pop() { data.pop_back(); }
	int top() {
		if (data.empty()) return 0;
		return data.back();
	}
};

class Stack_transform {
private:
	vector<char> data;
public:
	void push(char value) { data.push_back(value); }
	void pop() { data.pop_back(); }
	char top() {
		if (data.empty()) return ' ';
		return data.back();
	}
};

class queue {
private:
	vector<int> data;
public:
	void push(int value) { data.push_back(value); }
	void pop() { if (!data.empty()) data.erase(data.begin()); }
	int front() { return data.front(); }
};

void clear_screen() {
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif
}

void error() {
	clear_screen();
	cout << "Ошибка ввода, повторите ещё раз.\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return;
}

void print_menu(int variant) {
	if (variant == ACTION_PRINT_MENU) {
		cout << "--------------------------------------\n"
			<< ACTION_TRANSFORM_PROBLEM << " - Преобразовать выражение\n"
			<< ACTION_CHECK_PROBLEM << " - Проверить на корректность\n"
			<< ACTION_SOLVE_PROBLEM << " - Вычислить выражение\n"
			<< ACTION_TURN_OFF << " - Завершить работу\n"
			<< "--------------------------------------\n"
			<< "Выберите действие: ";
	}
	if (variant == ACTION_PRINT_NOTATION) {
		cout << COMMON_PROBLEM << " - простое выражение\n"
			<< DIRECT_POLISH_NOTATION << " - прямая польская нотация\n"
			<< REVERSE_POLISH_NOTATION << " - обратная польская нотация\n"
			<< ACTION_TURN_OFF << " - назад\n\n"
			<< "Выберите нотацию: ";
	}
	if (variant == ACTION_PRINT_NOTATION_2) {
		cout << DIRECT_POLISH_NOTATION << " - прямая польская нотация\n"
			<< REVERSE_POLISH_NOTATION << " - обратная польская нотация\n"
			<< ACTION_TURN_OFF << " - назад\n\n"
			<< "Выберите нотацию: ";
	}
}

int reverse_polish_notation() {
	string input, token;
	getline(cin >> ws, input);

	stringstream ss(input);
	vector<string> tokens;

	while (ss >> token)
		tokens.push_back(token);

	Stack digits;

	for (int i = 0; i < tokens.size(); i++) {
		string& s = tokens[i];

		if (s.length() == 1 && string("+-*/").find(s[0]) != string::npos) {
			int a = digits.top(); digits.pop();
			int b = digits.top(); digits.pop();

			if (s[0] == '+') digits.push(b + a);
			else if (s[0] == '-') digits.push(b - a);
			else if (s[0] == '*') digits.push(b * a);
			else if (s[0] == '/') digits.push(b / a);
		}
		else {
			digits.push(stoi(s));
		}
	}
	return digits.top();
}

int direct_polish_notation() {
	string input, token;
	getline(cin >> ws, input);

	stringstream ss(input);
	vector<string> tokens;

	while (ss >> token) 
		tokens.push_back(token);
	
	Stack digits;

	for (int i = tokens.size() - 1; i >= 0; i--) {
		string& s = tokens[i];

		if (s.length() == 1 && string("+-*/").find(s[0]) != string::npos) {
			int a = digits.top(); digits.pop();
			int b = digits.top(); digits.pop();

			if (s[0] == '+') digits.push(a + b);
			else if (s[0] == '-') digits.push(a - b);
			else if (s[0] == '*') digits.push(a * b);
			else if (s[0] == '/') digits.push(a / b);
		}
		else {
			digits.push(stoi(s));
		}
	}
	return digits.top();
}

int get_priority(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

void to_reverse_polish(string& input) {
	string result = "";
	Stack_transform operators;
	stringstream ss(input);
	string token;

	while (ss >> token) {
		bool is_number = isdigit(token[0]) || (token.length() > 1 && token[0] == '-');

		if (is_number) {
			result += token + " ";
		}
		else if (token == "(") {
			operators.push('(');
		}
		else if (token == ")") {
			while (operators.top() != '(' && operators.top() != ' ') {
				result += string(1, operators.top()) + " ";
				operators.pop();
			}
			operators.pop();
		}
		else if (string("+-*/").find(token[0]) != string::npos && token.length() == 1) {
			while (operators.top() != ' ' && get_priority(operators.top()) >= get_priority(token[0])) {
				result += string(1, operators.top()) + " ";
				operators.pop();
			}
			operators.push(token[0]);
		}
	}

	while (operators.top() != ' ') {
		result += string(1, operators.top()) + " ";
		operators.pop();
	}

	if (!result.empty() && result.back() == ' ') {
		result.pop_back(); // Удаляем лишний пробел на конце
	}
	input = result; // Записываем результат обратно в переменную из main
}

void to_direct_polish(string& input) {
	stringstream ss(input);
	vector<string> tokens;
	string token;

	while (ss >> token) {
		tokens.push_back(token);
	}

	string reversed_input = "";
	for (int i = (int)tokens.size() - 1; i >= 0; i--) {
		if (tokens[i] == "(") reversed_input += ") ";
		else if (tokens[i] == ")") reversed_input += "( ";
		else reversed_input += tokens[i] + " ";
	}

	// Используем уже готовую функцию ОПН
	to_reverse_polish(reversed_input);

	stringstream ss2(reversed_input);
	vector<string> rpn_tokens;
	while (ss2 >> token) {
		rpn_tokens.push_back(token);
	}

	string result = "";
	for (int i = (int)rpn_tokens.size() - 1; i >= 0; i--) {
		result += rpn_tokens[i] + " ";
	}

	if (!result.empty() && result.back() == ' ') {
		result.pop_back();
	}
	input = result; // Записываем результат обратно в переменную из main
}

bool check_common_problem(const string& input) {
	stringstream ss(input);
	string token;
	int bracket_balance = 0;
	bool expect_number = true; // Первым должно быть число или '('

	while (ss >> token) {
		if (token == "(") {
			bracket_balance++;
			if (!expect_number) return false;
		}
		else if (token == ")") {
			bracket_balance--;
			if (bracket_balance < 0 || expect_number) return false;
		}
		else if (string("+-*/").find(token[0]) != string::npos && token.length() == 1) {
			if (expect_number) return false;
			expect_number = true;
		}
		else { // Число
			if (!expect_number) return false;
			expect_number = false;
		}
	}
	return bracket_balance == 0 && !expect_number;
}

int solve_common_problem() {
	string input, token;
	getline(cin >> ws, input);

	stringstream ss(input);
	Stack digits;
	Stack_transform operators;

	auto apply_op = [&]() {
		int b = digits.top(); digits.pop();
		int a = digits.top(); digits.pop();
		char op = operators.top(); operators.pop();
		if (op == '+') digits.push(a + b);
		if (op == '-') digits.push(a - b);
		if (op == '*') digits.push(a * b);
		if (op == '/') digits.push(a / b);
		};

	while (ss >> token) {
		// Правильная проверка: число это или знак минус у отрицательного числа
		bool is_number = false;
		if (isdigit(token[0])) is_number = true;
		if (token.length() > 1 && token[0] == '-' && isdigit(token[1])) is_number = true;

		if (is_number) {
			digits.push(stoi(token));
		}
		else if (token == "(") {
			operators.push('(');
		}
		else if (token == ")") {
			while (operators.top() != '(' && operators.top() != ' ') {
				apply_op();
			}
			operators.pop(); // Удаляем '('
		}
		else if (string("+-*/").find(token) != string::npos) {
			while (operators.top() != ' ' && get_priority(operators.top()) >= get_priority(token[0])) {
				apply_op();
			}
			operators.push(token[0]);
		}
	}

	while (operators.top() != ' ') {
		apply_op();
	}

	return digits.top();
}

int main() {
	int choice = 0;
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Stack digits;
	string problem;
	while (true) {
		print_menu(ACTION_PRINT_MENU);
		while (!(cin >> choice) || choice < 0 || choice > 3) {
			error();
			print_menu(ACTION_PRINT_MENU);
		}

		switch (choice) {
		case ACTION_TRANSFORM_PROBLEM: {
			clear_screen();
			print_menu(ACTION_PRINT_NOTATION_2);
			
			int choice_transform = 0;

			while (!(cin >> choice_transform) || choice_transform < 0 || choice_transform > 3) {
				error();
				print_menu(ACTION_PRINT_NOTATION_2);
			}
			cout << "Записывайте выражение строго через пробелы! Пример: ( 5 + 3 ) * 2\n\n";
			clear_screen();
			cout << "Введите выражение: ";
			getline(cin >> ws, problem);
			switch (choice_transform) {
			case DIRECT_POLISH_NOTATION: {
				to_direct_polish(problem);
				cout << "Результат: " << problem << "\n";
				problem = "";
				break;
			}
			case REVERSE_POLISH_NOTATION: {
				to_reverse_polish(problem);
				cout << "Результат: " << problem << "\n";
				problem = "";
				break;
			}
			case ACTION_TURN_OFF: {
				clear_screen();
				break;
			}
			}

			break;
		}

		case ACTION_CHECK_PROBLEM: {
			clear_screen();
			cout << "Записывайте выражение строго через пробелы! Пример: ( 5 + 3 ) * 2\n\n";
			cout << "Введите выражение: ";
			getline(cin >> ws, problem);
			if (check_common_problem(problem)) {
				cout << "Выражение записано корректно\n";
			}
			else {
				cout << "Выражение содержит ошибки\n";
			}
			problem = "";
			break;
		}

		case ACTION_SOLVE_PROBLEM: {
			clear_screen();
			print_menu(ACTION_PRINT_NOTATION);
			int choice_solve = 0;

			while (!(cin >> choice_solve) || choice_solve < 0 || choice_solve > 3) {
				error();
				print_menu(ACTION_PRINT_NOTATION);
			}

			switch (choice_solve) {
			case COMMON_PROBLEM: {
				clear_screen();
				cout << "Записывайте выражение строго через пробелы! Пример: ( 5 + 3 ) * 2\n\n";
				cout << "Введите выражение: ";
				int result = solve_common_problem();
				cout << "Результат: " << result << "\n\n";
				break;
			}
			case DIRECT_POLISH_NOTATION: {
				clear_screen();
				cout << "Записывайте выражение строго через пробелы! Пример: ( 5 + 3 ) * 2\n\n";
				cout << "Введите выражение: ";
				int result = direct_polish_notation();
				cout << "Результат: " << result << "\n\n";
				break;
			}
			case REVERSE_POLISH_NOTATION: {
				clear_screen();
				cout << "Записывайте выражение строго через пробелы! Пример: ( 5 + 3 ) * 2\n\n";
				cout << "Введите выражение: ";
				int result = reverse_polish_notation();
				cout << "Результат: " << result << "\n\n";
				break;
			}
			case ACTION_TURN_OFF: {
				clear_screen();
				break;
			}
			}

			break;
		}
		case ACTION_TURN_OFF: {
			cout << "Работа завршена.";
			return false;
		}
		}
	}

	return 0;
}