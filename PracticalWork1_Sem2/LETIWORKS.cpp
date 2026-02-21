#include <iostream>
#include <limits>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#undef max

#define GREEN "\x1b[32m"
#define WHITE "\x1b[0m"
using namespace std;

void problem() {
	system("cls");
	cout << WHITE << "Хмм, что-то пошло не так...\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

struct Student {
	string full_name;
	bool sex;
	int group = 0;
	int human_number = 0;
	int marks[8];
	int student_id = -1;
};
struct Student students[1000];

int read_students() {
	ifstream file;
	int number_students = 0;
	int field_number = 0;
	string line;
	file.open("students.txt");
	while (getline(file, line)) {
		if (line.length() == 0) {
			// new student
			number_students++;
			field_number = 0;
			continue;
		}
		if (field_number >= 15) {
			cout << "Too many fields";
			return 0;
		}
		switch (field_number) {
		case 0:
			students[number_students].full_name = line;
			break;
		case 1:
			students[number_students].sex = stoi(line);
			break;
		case 2:
			students[number_students].group = stoi(line);
			break;
		case 3:
			students[number_students].human_number = stoi(line);
			break;
		case 4:
			students[number_students].marks[0] = stoi(line);
			break;
		case 5:
			students[number_students].marks[1] = stoi(line);
			break;
		case 6:
			students[number_students].marks[2] = stoi(line);
			break;
		case 7:
			students[number_students].marks[3] = stoi(line);
			break;
		case 8:
			students[number_students].marks[4] = stoi(line);
			break;
		case 9:
			students[number_students].marks[5] = stoi(line);
			break;
		case 10:
			students[number_students].marks[6] = stoi(line);
			break;
		case 11:
			students[number_students].marks[7] = stoi(line);
			break;
		case 12:
			students[number_students].student_id = number_students + 1;
			break;
		}
		field_number++;
	}
	return number_students;
}

void print_students(string* subjects, int i) {
	int number_students = read_students();
	cout << "ФИО: " << students[i].full_name << "\nПол: " << (students[i].sex ? "Мужской" : "Женский") << "\nГруппа: " << students[i].group << "\nНомер в группе: " << students[i].human_number << "\nОценки за сессию:\n";
	for (int j = 0; j < 8; j++) cout << subjects[j] << students[i].marks[j] << endl;
	cout << "ID: " << students[i].student_id << endl << endl;
}

void average_mark() {
	int number_students = read_students();
	vector<double> avg_score(number_students);
	vector<int> indexes(number_students);

	for (int i = 0; i < number_students; i++) {
		double sum = 0;
		for (int j = 0; j < 8; j++) { sum += students[i].marks[j]; }
		sum /= 8;
		avg_score[i] = sum;
	}
	
	for (int i = 0; i < number_students; i++) indexes[i] = i;

	for (int i = 0; i < number_students - 1; i++) {
		for (int j = 0; j < number_students - i - 1; j++) {
			if (avg_score[indexes[j]] < avg_score[indexes[j + 1]]) {
				swap(indexes[j], indexes[j + 1]);
			}
		}
	}
	cout << "==============ТОП САМЫХ УСПЕШНЫХ СТУДЕНТОВ==============\n";
	for (int i = 0; i < 10; i++) {
		int index = indexes[i];
		cout << (i + 1) << "-е место: " << avg_score[index] << " баллов\t" << "ФИО: " << students[index].full_name << endl;
	}
}

void new_student_file(Student* s) {
	ofstream record;
	record.open("students.txt", ios::app);
	if (!record.is_open()) { cout << "Не получилось открыть файл."; }
	else {
		record << s->full_name << endl << s->sex << endl << s->group << endl << s->human_number << endl;
		for (int i = 0; i < 8; i++) record << s->marks[i] << endl;
		record << s->student_id << endl << endl;
		record.close();
		cout << "Новый студент(-ка) " << GREEN "успешно" << WHITE << " записан(-а) в файл.\n";
	}
}

bool new_student(Student* s, string* subjects) {
	short choice = 0;
	while (true) {
		cout << "1 - Начать запись\n"
			<< "2 - Назад\n\n"
			<< "Чтобы создать запись о студенте, необходимы следующие данные:\n\n"
			<< "1. Фамилия Имя Отчество\n"
			<< "2. Пол (М/Ж)\n"
			<< "3. Номер группы\n"
			<< "4. Номер в списке группы\n"
			<< "5. Оценки за прошедшую сессию (3 экзамена, 5 диф.З.).\n\n"
			<< "Выберите действие: " << GREEN;
		if(!(cin >> choice)) problem();
		cout << WHITE;
		switch (choice) {
			case 1: {
				system("cls");
				int number_students = read_students();

				cout << "Введите ФИО: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin, s->full_name);

				cout << "Введите пол. 1 - Мужчина, 0 - Женщина: "; cin >> s->sex;
				cout << "Введите номер группы: "; cin >> s->group;
				cout << "Введите номер в списке группы: "; cin >> s->human_number;
				cout << "Введите оценки за сессию: \n";
				for (int i = 0; i < 8; i++) {
					cout << subjects[i]; cin >> s->marks[i];
				}
				s->student_id = number_students + 1;
				system("cls");
				
				new_student_file(s);
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

void change_file(int id_line, string new_name, int new_number, int* new_marks, int flag) {
	ifstream in("students.txt");
	ofstream out("temp.txt");
	string line;
	int current_line = 0;
	int i = 0;

	while (getline(in, line)) {
		if (current_line == id_line + i && i != 8) {
			if (flag == 1) out << new_name << endl;
			if (flag == 2) out << new_number << endl;
			if (flag == 3 && i < 8) {
				out << new_marks[i] << endl;
				i++;
			}
		}
		else out << line << endl;
		++current_line;
	}

	in.close();
	out.close();
	remove("students.txt");
	rename("temp.txt", "students.txt");
	cout << "Новые изменения были " << GREEN "успешно" << WHITE << " применены.\n";
}

int change_student(string* subjects, int id) {
	short choice;
	int MAX_LINES = 14;
	while (true) {
		cout << "\nВы можете изменить: \n"
			<< "1. ФИО\n"
			<< "2. Пол (М/Ж)\n"
			<< "3. Номер группы\n"
			<< "4. Номер в списке группы\n"
			<< "5. Оценки за прошедшую сессию (3 экзамена, 5 диф.З.).\n"
			<< "6. Назад\n\n"
			<< "Выберите действие: ";
			cin >> choice;
			switch (choice) {
			case 1: { //ФИО
				system("cls");
				cout << "Введите ФИО: ";
				string full_name;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin, full_name);
				change_file(MAX_LINES * (id - 1), full_name , 0, 0, 1);
				break;
			}
			case 2: { // ПОЛ
				system("cls");
				bool new_num;
				cout << "Введите пол. 1 - Мужчина, 0 - Женщина: ";
				cin >> new_num;
				change_file(MAX_LINES * (id - 1) + 1, "", new_num, 0, 2);
				break;
			}
			case 3: { // ГРУППА
				system("cls");
				cout << "Введите номер группы: ";
				int new_num;
				cin >> new_num;
				change_file(MAX_LINES * (id - 1) + 2, "", new_num, 0, 2);
				break;
			}	
			case 4: {// НОМЕР В СПИСКЕ
				system("cls");
				cout << "Введите номер в списке группы: ";
				int new_num;
				cin >> new_num;
				change_file(MAX_LINES * (id - 1) + 3, "", new_num, 0, 2);
				break;
			} 
			case 5: { // ОЦЕНКИ
				system("cls");
				int new_marks[8];
				cout << "Введите оценки за сессию: \n";
				for (int i = 0; i < 8; i++) {
					cout << subjects[i]; cin >> new_marks[i];
				}
				change_file(MAX_LINES * (id - 1) + 4, "", 0, new_marks, 3);
				break;
			}
			case 6:
				system("cls");
				return false;
			default:
				break;
		}
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string subjects[] = { "Матан экзамен: ", "Программирование экзамен: ", "АиГ экзамен: ", "Иностранный язык диф.З: ", "Информатика диф.З: ", "Физика диф.З: ", "ОРГ диф.З: ", "Философия диф.З: " };
	short choice;
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
		if (!(cin >> choice)) problem();
		cout << WHITE;
		switch (choice) {
		case 1: {
			system("cls");
			new_student(students, subjects);
			break;
		}
		case 2: {
			system("cls");
		point:
			int id = 0;
			int number_students = read_students();
			cout << "Выберите студента, информацию о котором вы хотели бы изменить (1-" << number_students <<")\n\n";
			for (int i = 0; i < number_students; i++) cout << "ID: " << students[i].student_id << "\tФИО: " << students[i].full_name << endl;

			cout << "\n0 - Назад\n"
				<< "Выберите студента: ";
			cin.ignore();
			cin >> id;
			if (id == 0) {
				system("cls");
				break;
			} 
			system("cls");
			cout << "ФИО: " << students[id - 1].full_name << "\nПол: " << (students[id - 1].sex ? "Мужской" : "Женский") << "\nГруппа: " << students[id - 1].group << "\nНомер в группе: " << students[id - 1].human_number << "\nОценки за сессию:\n";
			for (int i = 0; i < 8; i++) cout << subjects[i] << students[id - 1].marks[i] << endl;
			if (!change_student(subjects, id)) goto point;
			break;
		}
		case 3: {
			system("cls");
			int number_students = read_students();
			for (int i = 0; i < number_students; i++) print_students(subjects, i);
			
			break;
		}
		case 4: {
			system("cls");
			int search_group = 0;
			int number_students = read_students();
			cout << "Ведите номер группы: ";
			cin >> search_group;
			for (int i = 0; i < number_students; i++) { if (students[i].group == search_group) print_students(subjects, i); }
			break;
		}
		case 5:
			system("cls");
			average_mark();
			break;
		case 6: {
			system("cls");
			int number_students = read_students();
			int man_result = 0;
			int woman_result = 0;
			for (int i = 0; i < number_students; i++) {
				if (students[i].sex) man_result++;
				else woman_result++;
			}
			cout << "Кол-во мужчин: " << man_result << "\nКол-во женщин: " << woman_result << endl;
			break;
		}
		case 7:
			system("cls");

			break;
		case 8: {
			system("cls");
			int number_students = read_students();
			int snig = 0;
			cout << "Введите номер в списке группы: ";
			cin >> snig;
			for (int i = 0; i < number_students; i++) {
				if (students[i].human_number == snig) print_students(subjects, i);
			}
			break;
		}
		case 9:
			cout << "\nРабота завершена.";
			return false;			
		default: 
			if (choice > 9) {
				system("cls");
				cout << WHITE << "Хмм, что-то пошло не так...\n";
			}
		}
	}
	return 0;
}