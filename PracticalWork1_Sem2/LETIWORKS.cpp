#include <iostream>
#include <limits>
#include <Windows.h>

#undef max
using namespace std;

#define GREEN "\x1b[32m"
#define WHITE "\x1b[0m"

void problem() {
	system("cls");
	cout << WHITE << "Хмм, что-то пошло не так...\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

struct Student {
	char first_name[25]; // Имя
	char last_name[25]; // Фамилия
	char patronymic[25]; // Отчество
	bool sex;
	short group;
	short human_number;
	int marks[8];
};

bool question_window(Student* s) {
	short choice;
	while (true) {
		system("cls");
		cout << "Входные данные: \n\n"
			<< "Фамилия - " << s->last_name << "\nИмя - " << s->first_name << "\nОтчество - " << s->patronymic << "\n\nХотите продолжить?" << "\n1 - Продолжить\n2 - Изменить\n\nВыберите действие: ";
		cin >> choice;
		switch (choice) {
		case 1:
			
			return true;
		case 2:
			system("cls");
			return false;
		}
	}
}

bool new_student(Student* s) {
	short choice;
	
	while (true) {
		cout << "Исправление записи на этапе записи возможно только для ФИО, глобальные исправления записи доступны в главном меню.\n\n"
			<< "1 - Начать запись\n"
			<< "2 - Назад\n\n"
			<< "Чтобы создать запись о студенте, необходимы следующие данные:\n\n"
			<< "1. Фамилия Имя Отчество\n"
			<< "2. Пол (М/Ж)\n"
			<< "3. Номер группы\n"
			<< "4. Номер в списке группы\n"
			<< "5. Оценки за прошедшую сессию (3 экзамена 5 диф.З.)\n\n"
			<< "Выберите действие: " << GREEN;
		if(!(cin >> choice)) problem();
		cout << WHITE;
		switch (choice) {
		change:
			case 1: {
				system("cls");
				SetConsoleCP(1251);
				SetConsoleOutputCP(1251);
			
				cout << "Введите фамилию: ";
				cin >> s->last_name;
				cout << "\nВведите имя: ";
				cin >> s->first_name;
				cout << "\nВведите Отчество : ";
				cin >> s->patronymic;
				if (question_window(s));
				else goto change;
				cout << "Введите пол. 1 - Мужчина, 0 - Женщина: ";
				cin >> s->sex;
				cout << "Введите номер группы: ";
				cin >> s->group;
				cout << "Введите номер в списке группы: ";
				cin >> s->human_number;
				cout << "Введите оценки за сессию: \n";
				string subjects[] = { "Матан экзамен - ", "Программирование экзамен - ", "АиГ экзамен - ", "Иностранный язык диф.З - ", "Информатика диф.З - ", "Физика диф.З - ", "ОРГ диф.З - ", "Философия диф.З - " };
				
				for (int i = 0; i < 8; i++) {
					cout << subjects[i];
					cin >> s->marks[i];
				}
				system("cls");
				cout << "Полученные данные:\n\n" << "Фамилия - " << s->last_name << "\nИмя - " << s->first_name << "\nОтчество - " << s->patronymic << "\nПол - " << (s->sex ? "Мужской" : "Женский")
					<< "\nГруппа - " << s->group << "\nНомер в группе - " << s->human_number << "\nОценки за сессию:\n";
				for (int i = 0; i < 8; i++) { cout << endl << subjects[i] << s->marks[i]; }
				cout << endl << endl;
				break;
			}
		case 2:
			system("cls");
			return false;
			break;
		default:
			if (choice > 2) {
				system("cls");
				cout << WHITE << "Хмм, что-то пошло не так...\n";
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	struct Student students[10];

	short choice;
	bool flag;
	while (true) {
		cout << "1 - Новая запись\n"
			<< "2 - Изменить запись\n"
			<< "3 - Вывести все записи\n"
			<< "4 - Вывести всю информацию из группы N\n"
			<< "5 - Топ успешных студентов\n"
			<< "6 - Кол-во студентов М/Ж пола\n"
			<< "7 - Студенты без стипендии + оценки студентов\n"
			<< "8 - Вывод студентов с номером N\n"
			<< "9 - Завершить работу\n\n"
			<< "Выберите действие: " << GREEN;
		if (!(cin >> choice)) {
			flag = false;
			problem();
		}
		else flag = true;
		cout << WHITE;
		switch (choice) {
		case 1:
			system("cls");
			new_student(students);
			break;
		case 2:
			system("cls");
			break;
		case 3:
			system("cls");
			break;
		case 4:
			system("cls");
			break;
		case 5:
			system("cls");
			break;
		case 6:
			system("cls");
			break;
		case 7:
			system("cls");
			break;
		case 8:
			system("cls");
			break;
		case 9:
			cout << "\nРабота завершена.";
			return false;			
			break;
		default: 
			if (choice > 9) {
				system("cls");
				cout << WHITE << "Хмм, что-то пошло не так...\n";
			}
		}
	}
	return 0;
}