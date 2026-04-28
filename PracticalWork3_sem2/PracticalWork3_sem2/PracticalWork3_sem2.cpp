#include <iostream>
#include <windows.h>
#include <limits>
#include <cstdlib>
#include <vector>
#include <string>
#undef max

using namespace std;

const int ACTION_PRINT_MENU = 100;
const int ACTION_PRINT_NOTATION = 200;

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
	int top() { return data.back(); }
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
}

int digit_or_operation(string symbol, int index) {
	string digits = "0123456789";
	string operations = "+-/*";
	for (int i = 0; i < 10; i++) {
		if (symbol[index] == digits[i]) return 1;
	}
	for (int i = 0; i < 4; i++) {
		if (symbol[index] == operations[i]) return 2;
	}
	return -1;
}

void solve_problem(Stack &digits, char operation, int a, int b) {
	switch (operation) {
	case '+': {
		digits.push(a + b);
		break;
	}
	case '-': {
		digits.push(a - b);
		break;
	}
	case '/': {
		digits.push(a / b);
		break;
	}
	case '*': {
		digits.push(a * b);
		break;
	}
	}
}
int reverse_polish_notation(Stack &digits) {
	string problem;
	cin.ignore();
	getline(cin, problem);

	int count = 0;
	while (!problem.empty()) {

		while (true) {
			if (problem[count] == ' ' || problem[count] == '\0') {
				int check = digit_or_operation(problem, (count - 1));
				string sub = problem.substr(0, count);

				if (check == 2) {
					int a = digits.top(); digits.pop();
					int b = digits.top(); digits.pop();
					solve_problem(digits, problem[count - 1], a, b);
				}
				else if (check == 1) {
					digits.push(stoi(sub));
				}
				else if (check == -1) {
					clear_screen();
					cout << "Вы ввели неверный символ! Попробуйте ещё раз.";
					return false;
				}

				problem.erase(0, (count + 1));
				count = 0;
				break;
			}

			count++;
		}
	}

	return digits.top();
}

int direct_polish_notation(Stack digits) {
	string problem;
	cin.ignore();
	getline(cin, problem);

	int count = problem.length() - 1;
	while (!problem.empty()) {

		while (true) {
			if (problem[count] == ' ') {
				int check = digit_or_operation(problem, (count - 1));
				string sub = problem.substr(0, count);

				if (check == 2) {
					int a = digits.top(); digits.pop();
					int b = digits.top(); digits.pop();

					switch (problem[count - 1]) {
					case '+': {
						digits.push(a + b);

						break;
					}
					case '-': {
						digits.push(a - b);
						break;
					}
					case '/': {
						digits.push(a / b);
						break;
					}
					case '*': {
						digits.push(a * b);
						break;
					}
					}

				}
				else if (check == 1) {
					digits.push(stoi(sub));
				}
				else if (check == -1) {
					clear_screen();
					cout << "Вы ввели неверный символ! Попробуйте ещё раз.";
					return false;
				}

				problem.erase(0, (count + 1));
				count = 0;
				break;
			}

			count++;
		}
	}

	return digits.top();
}

int main() {
	int choice = 0;
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Stack digits;

	while (true) {
		print_menu(ACTION_PRINT_MENU);
		while (!(cin >> choice) || choice < 0 || choice > 3) {
			error();
			print_menu(ACTION_PRINT_MENU);
		}

		switch (choice) {
		case ACTION_TRANSFORM_PROBLEM: {
			clear_screen();
			cout << "Введите выражение: ";

			break;
		}
		case ACTION_CHECK_PROBLEM: {
			clear_screen();
			print_menu(ACTION_PRINT_NOTATION);
			int choice_check = 0;

			while (!(cin >> choice_check) || choice_check < 0 || choice_check > 2) {
				error();
				print_menu(ACTION_PRINT_NOTATION);
			}

			switch (choice_check) {
			case DIRECT_POLISH_NOTATION: {
				clear_screen();
				break;
			}
			case REVERSE_POLISH_NOTATION: {
				clear_screen();
				break;
			}
			case ACTION_TURN_OFF: {
				clear_screen();
				break;
			}
			}

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
			case DIRECT_POLISH_NOTATION: {
				clear_screen();
				break;
			}
			case REVERSE_POLISH_NOTATION: {
				clear_screen();
				cout << "Введите выражение: ";
				int result = reverse_polish_notation(digits);
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