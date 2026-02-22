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

struct Hall {
	int hall_number;
	int building;
	int hall_size = 0;
	bool projector;
	double rent;
};
struct Hall hall[1000];

int read_hall() {
	ifstream file;
	int count_hall = 0;
	int field_number = 0;
	string line;
	file.open("halls.txt");
	while (getline(file, line)) {
		if (line.length() == 0) {
			// new hall
			count_hall++;
			field_number = 0;
			continue;
		}
		if (field_number >= 6) {
			cout << "Too many fields";
			return 0;
		}
		switch (field_number) {
		case 0:
			hall[count_hall].hall_number = stoi(line);
			break;
		case 1:
			hall[count_hall].building = stoi(line);
			break;
		case 2:
			hall[count_hall].hall_size = stoi(line);
			break;
		case 3:
			hall[count_hall].projector = stoi(line);
			break;
		case 4:
			hall[count_hall].rent = stod(line);
			break;
		}
		field_number++;
	}
	file.close();
	return count_hall;
}

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

void print_halls(int i) {
	cout << "Номер аудитории: " << hall[i].hall_number << "\nКорпус: " << hall[i].building << "\nВместимость (чел.): " << hall[i].hall_size
		<< "\nНаличие проектора: " << (hall[i].projector ? "Есть" : "Нету") << "\nСтоимость аренды в час: " << hall[i].rent << " руб.\n";
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
	for (int i = 0; i < number_students; i++) {
		if (i == 10) break;
		int index = indexes[i];
		cout << (i + 1) << "-е место: " << avg_score[index] << " балл\t" << "ФИО: " << students[index].full_name << endl;
	}
}

bool screen_hall() {
	short choice = 0;
	while (true) {
		cout << "1 - Аудитории с проектором\n"
			<< "2 - Список свободных аудиторий на указанное время\n"
			<< "3 - Самая дешёвая аудитория\n"
			<< "4 - Назад\n\n"
			<< "Выберите информацию которую хотите узнать: ";
		if (!(cin >> choice)) problem();
		switch (choice) {
		case 1: {
			system("cls");
			int count_halls = read_hall();
			for (int i = 0; i < count_halls; i++) {
				if (hall[i].projector) print_halls(i);
			}
			break;
		}
		case 2:
			system("cls");

			break;
		case 3: {
			system("cls");
			int count_halls = read_hall();
			vector<double> rents(count_halls);
			
			
			for (int i = 0; i < count_halls; i++) rents[i] = hall[i].rent;
			
			double mini = rents[0];
			for (int i = 0; i < count_halls - 1; i++) if (mini > rents[i + 1]) mini = rents[i + 1];

			for (int i = 0; i < count_halls; i++) if (hall[i].rent == mini) print_halls(i);
			
			break;
		}
		case 4:
			system("cls");
			return false;
		default:
			system("cls");
		}
	}
}

void new_hall_file() {
	ofstream record;
	record.open("halls.txt", ios::app);
	if (!record.is_open()) { cout << "Не получилось открыть файл."; }
	else {
		record << hall->hall_number << endl << hall->building << endl << hall->hall_size << endl << hall->projector << endl << hall->rent << endl << endl;
		record.close();
		cout << "Новая аудитория " << GREEN "успешно" << WHITE << " записана в файл.\n";
	}
}

bool new_hall() {
	short choice = 0;
	while (true) {
		cout << "1 - Начать запись\n"
			<< "2 - Вывести записи\n"
			<< "3 - Назад\n\n"
			<< "Чтобы создать запись об аудитории, необходимы следующие данные:\n\n"
			<< "1. Номер аудитории\n"
			<< "2. Корпус\n"
			<< "3. Вместимость (чел.)\n"
			<< "4. Наличие проектора\n"
			<< "5. Стоимость аренды в час.\n\n"
			<< "Выберите действие: ";
		if (!(cin >> choice)) problem();
		switch (choice) {
		case 1: {
			system("cls");
			point_number:
			int count_halls = read_hall();
			cout << "Введите номер аудитории: ";
			if (!(cin >> hall->hall_number)) {
				problem();
				goto point_number;
			}

		point_building:
			cout << "Введите корпус: ";
			if (!(cin >> hall->building)) {
				problem();
				goto point_building;
			}

		point_size:
			cout << "Введите вместимость (чел.): ";
			if (!(cin >> hall->hall_size)) {
				problem();
				goto point_size;
			}

		point_projector:
			cout << "Наличие проектора (1 - есть, 0 - нету): ";
			if (!(cin >> hall->projector)) {
				problem();
				goto point_projector;
			}

			cout << "Введите стоимость аренды в час: \n";
		point_rent:
			if (!(cin >> hall->rent)) {
				problem();
				goto point_rent;
			}
			system("cls");
			new_hall_file();
			break;
		}
		case 2:
			system("cls");
			screen_hall();
			break;
		case 3:
			system("cls");
			return false;
		default:
			if (choice > 3) {
				system("cls");
				cout << "Хмм, что-то пошло не так...\n";
			}
		}
	}
}


void new_student_file() {
	ofstream record;
	record.open("students.txt", ios::app);
	if (!record.is_open()) { cout << "Не получилось открыть файл."; }
	else {
		record << students->full_name << endl << students->sex << endl << students->group << endl << students->human_number << endl;
		for (int i = 0; i < 8; i++) record << students->marks[i] << endl;
		record << students->student_id << endl << endl;
		record.close();
		cout << "Новый студент(-ка) " << GREEN "успешно" << WHITE << " записан(-а) в файл.\n";
	}
}

bool new_student(string* subjects) {
	short choice = 0;
	while (true) {
		cout << "1 - Начать запись\n"
			<< "2 - Меню для аудиторий\n"
			<< "3 - Назад\n\n"
			<< "Чтобы создать запись о студенте, необходимы следующие данные:\n\n"
			<< "1. Фамилия Имя Отчество\n"
			<< "2. Пол (М/Ж)\n"
			<< "3. Номер группы\n"
			<< "4. Номер в списке группы\n"
			<< "5. Оценки за прошедшую сессию (3 экзамена, 5 диф.З.).\n\n"
			<< "Выберите действие: ";
		if (!(cin >> choice)) problem();
		switch (choice) {
		case 1: {
			system("cls");
			int number_students = read_students();
			cout << "Введите ФИО: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, students->full_name);

		point_sex:
			cout << "Введите пол. 1 - Мужчина, 0 - Женщина: ";
			if (!(cin >> students->sex)) {
				problem();
				goto point_sex;
			}

		point_group:
			cout << "Введите номер группы: ";
			if (!(cin >> students->group)) {
				problem();
				goto point_group;
			}

		point_number:
			cout << "Введите номер в списке группы: ";
			if (!(cin >> students->human_number)) {
				problem();
				goto point_number;
			}

			cout << "Введите оценки за сессию: \n";
			for (int i = 0; i < 8; i++) {
			point_marks:
				cout << subjects[i];
				if (!(cin >> students->marks[i])) {
					problem();
					goto point_marks;
				}
			}
			students->student_id = number_students + 1;
			system("cls");
			new_student_file();
			break;
		}
		case 2:
			system("cls");
			if (new_hall())
			break;
		case 3:
			system("cls");
			return false;
		default:
			if (choice > 3) {
				system("cls");
				cout << "Хмм, что-то пошло не так...\n";
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
			if (!(cin >> choice)) problem();
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
				point2:
				bool new_num;
				cout << "Введите пол. 1 - Мужчина, 0 - Женщина: ";
				if (!(cin >> new_num)) {
					problem();
					goto point2;
				}
				change_file(MAX_LINES * (id - 1) + 1, "", new_num, 0, 2);
				break;
			}
			case 3: { // ГРУППА
				system("cls");
				point3:
				cout << "Введите номер группы: ";
				int new_num;
				if (!(cin >> new_num)) {
					problem();
					goto point3;
				}
				change_file(MAX_LINES * (id - 1) + 2, "", new_num, 0, 2);
				break;
			}	
			case 4: {// НОМЕР В СПИСКЕ
				system("cls");
				point4:
				cout << "Введите номер в списке группы: ";
				int new_num;
				if (!(cin >> new_num)) {
					problem();
					goto point4;
				}
				change_file(MAX_LINES * (id - 1) + 3, "", new_num, 0, 2);
				break;
			} 
			case 5: { // ОЦЕНКИ
				system("cls");
				int new_marks[8];
				cout << "Введите оценки за сессию: \n";
				for (int i = 0; i < 8; i++) {
					point_marks:
					cout << subjects[i]; 
					if (!(cin >> new_marks[i])) {
						problem();
						goto point_marks;
					}
				}
				change_file(MAX_LINES * (id - 1) + 4, "", 0, new_marks, 3);
				break;
			}
			case 6:
				system("cls");
				return false;
			default:
				if (choice > 6) {
					system("cls");
					cout << "Хмм, что-то пошло не так...\n";
				}
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
			<< "Выберите действие: ";
		if (!(cin >> choice)) problem();

		switch (choice) {
		case 1: {
			system("cls");
			new_student(subjects);
			break;
		}
		case 2: {
			system("cls");
		point2:
			int id = 0;
			int number_students = read_students();
			cout << "Выберите студента, информацию о котором вы хотели бы изменить (1-" << number_students <<")\n\n";
			for (int i = 0; i < number_students; i++) cout << "ID: " << students[i].student_id << "\tФИО: " << students[i].full_name << endl;

			cout << "\n0 - Назад\n"
				<< "Выберите студента: ";

			if (!(cin >> id)) {
				problem();
				goto point2;
			}
			if (id == 0) {
				system("cls");
				break;
			} 
			system("cls");
			cout << "ФИО: " << students[id - 1].full_name << "\nПол: " << (students[id - 1].sex ? "Мужской" : "Женский") << "\nГруппа: " << students[id - 1].group << "\nНомер в группе: " << students[id - 1].human_number << "\nОценки за сессию:\n";
			for (int i = 0; i < 8; i++) cout << subjects[i] << students[id - 1].marks[i] << endl;
			if (!change_student(subjects, id)) goto point2;
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
			point4:
			int search_group = 0;
			int number_students = read_students();
			cout << "Ведите номер группы: "; 
			if (!(cin >> search_group)) {
				problem();
				goto point4;
			}
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
		case 7: {
			system("cls");
		point7:
			int number_students = read_students();
			int id = 0;
			vector<int> index;
			for (int i = 0; i < number_students; i++) {
				int count_fives = 0;
				int other_marks = 0;
				int count_fours = 0;
				int count_threes = 0;
				for (int j = 0; j < 8; j++) {
					if (students[i].marks[j] == 3) {
						count_threes++;
						break;
					}
					else if (students[i].marks[j] == 4) count_fours++;
					else if (students[i].marks[j] == 5) count_fives++;
					else {
						other_marks++;
						break;
					}
				}
				if (count_threes > 0 || other_marks > 0) {
					cout << "ID: " << students[i].student_id << " ФИО: " << students[i].full_name << "\tНе получает стипендию\n";
					index.push_back(students[i].student_id);
				}
				else if (count_threes == 0 && (count_fours > 0 && count_fives >= 0)) {
					cout << "ID: " << students[i].student_id << " ФИО: " << students[i].full_name << "\tУчится на хорошо и отлично\n";
					index.push_back(students[i].student_id);
				}
				else if (count_fives == 8) {
					cout << "ID: " << students[i].student_id << " ФИО: " << students[i].full_name << "\tУчится на отлично\n";
					index.push_back(students[i].student_id);
				}
			}
			
			cout << "\n0 - Назад\nВыберите студента, информацию о котором хотите вывести: ";
			if (!(cin >> id)) {
				problem();
				goto point7;
			}
			if (id == 0) break;
			for (int i = 0; i < number_students; i++) {
				if (id == index[i]) {
					print_students(subjects, i);
					break;
				}
			}
			break;
		}
		case 8: {
			system("cls");
			point8:
			int number_students = read_students();
			int snig = 0;
			cout << "Введите номер в списке группы: ";
			if (!(cin >> snig)) {
				problem();
				goto point8;
			}
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