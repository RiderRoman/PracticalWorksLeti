#include <iostream>
#include <windows.h>
#include <limits>
#include <cstdlib>
#undef max

using namespace std;

const int ACTION_PRINT_MENU = 100;
const int ACTION_PRINT_NOTATION = 200;

const int ACTION_TRANSFORM_PROBLEM = 1;
const int ACTION_CHECK_PROBLEM = 2;
const int ACTION_SOLVE_PROBLEM = 3;
const int ACTION_TURN_OFF = 0;

const int DIRECT_POLISH_NOTATION = 1;
const int REVERSE_POLISH_NOTATION = 2;

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
		cout << ACTION_TRANSFORM_PROBLEM << " - Преобразовать выражение\n"
			<< ACTION_CHECK_PROBLEM << " - Проверить на корректность\n"
			<< ACTION_SOLVE_PROBLEM << " - Вычислить выражение\n"
			<< ACTION_TURN_OFF << " - Завершить работу\n\n"
			<< "Выберите действие: ";
	}
	if (variant == ACTION_PRINT_NOTATION) {
		cout << DIRECT_POLISH_NOTATION << " - прямая польская нотация\n"
			<< REVERSE_POLISH_NOTATION << " - обратная польская нотация\n"
			<< ACTION_TURN_OFF << " - назад\n\n"
			<< "Выберите нотацию: ";
	}
}


int main() {
	int choice = 0;
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
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

			while (!(cin >> choice_solve) || choice_solve < 0 || choice_solve > 2) {
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