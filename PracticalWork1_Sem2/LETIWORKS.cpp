#include <iostream>
#include <limits>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#undef max

#define GREEN "\x1b[32m"
#define WHITE "\x1b[0m"
using namespace std;

void problem() {
    system("cls");
    cout << WHITE << "Ошибка ввода, повторите еще раз.\n";
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
    bool open = true;
    int hours;
    int minutes;
    int prolong;
};
struct Hall hall[1000];

void new_hall_file() { // new info in file
    ofstream record;
    record.open("halls.txt", ios::app);
    if (!record.is_open()) { cout << "Не получилось открыть файл."; }
    else {
        record << hall->hall_number << endl << hall->building << endl << hall->hall_size << endl
            << hall->projector << endl << hall->rent << endl << hall->open << endl << hall->hours << endl << hall->minutes << endl << hall->prolong << endl << endl;
        record.close();
        cout << "Новая аудитория " << GREEN "успешно" << WHITE << " записана в файл.\n";
    }
}

bool time_record(int& x, int& y);

void change_halls_file(int id_line, int new_number, double new_rent, int print_flag) { // new changes in file
    ifstream in("halls.txt");
    ofstream out("temp.txt");
    string line;
    int current_line = 0;

    while (getline(in, line)) {
        if (current_line == id_line) {
            if (!(new_number == -1)) out << new_number << endl;
            if (!(new_rent == -1)) out << new_rent << endl;
        }
        else out << line << endl;
        ++current_line;
    }

    in.close();
    out.close();
    remove("halls.txt");
    rename("temp.txt", "halls.txt");
    if (print_flag) cout << "Новые изменения были " << GREEN "успешно" << WHITE << " применены.\n";
}

void change_halls(int index) {
    short choice = 0;
    int MAX_LINES = 10;
    
    if (!(cin >> choice)) {
        problem();
    }
    switch (choice) {
    case 1: {
    point1:
        system("cls");
        int new_number = 0;
        cout << "Номер аудитории: ";
        if (!(cin >> new_number)) {
            problem();
            goto point1;
        }
        change_halls_file(MAX_LINES * index, new_number, -1, 1);
        break;
    }
    case 2: {
    point2:
        system("cls");
        int new_number = 0;
        cout << "Корпус: ";
        if (!(cin >> new_number)) {
            problem();
            goto point2;
        }
        change_halls_file(MAX_LINES * index + 1, new_number, -1, 1);
        break;
    }
    case 3: {
    point3:
        system("cls");
        int new_number = 0;
        cout << "Вместимость (чел.): ";
        if (!(cin >> new_number)) {
            problem();
            goto point3;
        }
        change_halls_file(MAX_LINES * index + 2, new_number, -1, 1);
        break;
    }
    case 4: {
    point4:
        system("cls");
        int new_number = 0;
        cout << "Наличие проектора (1 - есть, 0 - нету): ";
        if (!(cin >> new_number)) {
            problem();
            goto point4;
        }
        change_halls_file(MAX_LINES * index + 3, new_number, -1, 1);
        break;
    }
    case 5: {
    point5:
        system("cls");
        double new_rent = 0;
        cout << "Аренда в час: ";
        if (!(cin >> new_rent)) {
            problem();
            goto point5;
        }
        change_halls_file(MAX_LINES * index + 4, -1, new_rent, 1);
        break;
    }
    case 6: {
        system("cls");
        int hour, minute, MAX_LINES = 10;

        time_record(hour, minute);
        int j = 0;
        while (abs(hour - 23 + j) != 1) {
            cout << "Забронировать на " << abs(hour - 23 + j) << " часов\n";
            j++;
        }
        cout << "Выберите продолжительность брони: ";
        int booking_time;

        if (!(cin >> booking_time)) {
            problem();
            break;
        }

        cout << "\n\nАудитория " << GREEN << "успешно " << WHITE << "забронирована с " << hour << ":";
        if (minute < 10) {
            cout << 0 << minute << " до " << (hour + booking_time) << ':' << 0 << minute << endl << endl;
        }
        else cout << minute << " до " << (hour + booking_time) << ':' << minute << endl << endl;

        change_halls_file(MAX_LINES * index + 6, hour, -1, 0);
        change_halls_file(MAX_LINES * index + 7, minute, -1, 0);
        change_halls_file(MAX_LINES * index + 8, booking_time, -1, 0);
        break;
    }
    default:
        if (choice > 6) {
            system("cls");
            cout << "Ошибка ввода, повторите еще раз.\n";
        }
    }
}

int read_halls() {
    ifstream file;
    int count_hall = 0;
    int field_number = 0;
    string line;
    file.open("halls.txt");
    if (!(file.is_open())) {
        cout << "Не удалось открыть файл.\n";
        return false;
    }
    while (getline(file, line)) {
        if (line.length() == 0) {
            // new hall
            count_hall++;
            field_number = 0;
            continue;
        }
        if (field_number >= 10) {
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
        case 5:
            hall[count_hall].open = stoi(line);
            break;
        case 6:
            hall[count_hall].hours = stoi(line);
            break;
        case 7:
            hall[count_hall].minutes = stoi(line);
            break;
        case 8:
            hall[count_hall].prolong = stoi(line);
            break;
        }
        field_number++;
    }
    file.close();
    return count_hall;
}

void print_halls(int index, int booking_flag) {
    cout << "Номер аудитории: " << hall[index].hall_number << "\nКорпус: " << hall[index].building << "\nВместимость (чел.): " << hall[index].hall_size
        << "\nНаличие проектора: " << (hall[index].projector ? "Есть" : "Нету") << "\nСтоимость аренды в час: "
        << hall[index].rent << " руб." << "\nЗабронированна: " << (hall[index].open ? "Нет\n" : "Да\n");
    if (booking_flag) {
        cout << "Время брони: " << hall[index].hours << ":";
        if (hall[index].minutes < 10) cout << 0 << hall[index].minutes << " - " << hall[index].hours + hall[index].prolong << ":0" << hall[index].minutes << endl << endl;
        else cout << hall[index].minutes << " - " << hall[index].hours + hall[index].prolong << ":" << hall[index].minutes << endl << endl;
    }
}

bool time_record(int& hours, int& minutes) {
    while (true) {
        cin.ignore();
        string time1;
        int test1, test2;
        cout << "Введите нужное время: ";
        
        getline(cin, time1);
        if (time1.length() != 5) {
            if (('0' + time1).length() == 5 && ('0' + time1)[2] == ':') {
                time1 = '0' + time1;
            }
        }

        if (time1.length() == 5 && time1[2] == ':') {
            test1 = stoi(time1.substr(0, 2));
            test2 = stoi(time1.substr(3, 2));
        }
        else {
            cout << "Вы неверно указали время.\n";
            return false;
        }

        if (test1 < 7 || test1 > 21 || test2 < 0 || test2 > 59) {
            cout << "Вы неверно указали время.\n";
            return false;
        }
        if (test1 == 21 && test2 > 0) {
            cout << "Вы неверно указали время.\n";
            return false;
        }
        hours = test1; minutes = test2; test1 = 0; test2 = 0;
        break;
    }
}

bool booking() {
    short select_hall, counter = 0;
    int index = 0, MAX_LINES = 10;

    while (true) {
        cout << "Бронирование аудиторий.\nСписок свободных аудиторий:\n";
        int count_halls = read_halls();
        for (int i = 0; i < count_halls; i++) {
            if (hall[i].open) {
                cout << "Аудитория: " << hall[i].hall_number << endl;
                counter++;
            }
        }
        if (counter == 0) {
            system("cls");
            cout << "Список пуст.\n\n";
            return false;
        }
        cout << "\nВведите номер аудитории, чтобы забронировать: ";
        if (!(cin >> select_hall)) problem();
        for (int i = 0; i < count_halls; i++) {
            if (hall[i].hall_number == select_hall) {
                index = i;
                break;
            }
        }
        
        system("cls");
        cout << "Забронировать можно только с 7:00 до 21:00\n";

        if (!(time_record(hall[index].hours, hall[index].minutes))) break;
        int j = 0;
        while (abs(hall[index].hours - 23 + j) != 1) {
            if (j == 0) {
                if (hall[index].hours + abs(hall[index].hours - 23 + j) == 23 && hall[index].minutes >= 1) {
                    j++;
                    continue;
                }
            }
            cout << "Забронировать на " << abs(hall[index].hours - 23 + j) << " часов\n";
            j++;
        }
        cout << "Выберите продолжительность брони: ";
        int choice2;

        if (!(cin >> choice2)) {
            problem();
            break;
        }
        
        hall[index].prolong = choice2;

        cout << "\n\nАудитория " << GREEN << "успешно " << WHITE << "забронирована с " << hall[index].hours << ":";
        if (hall[index].minutes < 10) {
            cout << 0 << hall[index].minutes << " до " << (hall[index].hours + hall[index].prolong) << ':' << 0 << hall[index].minutes << endl << endl;
        }
        else cout << hall[index].minutes << " до " << (hall[index].hours + hall[index].prolong) << ':' << hall[index].minutes << endl << endl;

        change_halls_file(MAX_LINES * index + 5, 0, -1, 0);
        change_halls_file(MAX_LINES * index + 6, hall[index].hours, -1, 0);
        change_halls_file(MAX_LINES * index + 7, hall[index].minutes, -1, 0);
        change_halls_file(MAX_LINES * index + 8, hall[index].prolong, -1, 0);
        read_halls();
    }
}

bool output_halls() {
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
            int count_halls = read_halls();
            for (int i = 0; i < count_halls; i++) {
                if (hall[i].projector) {
                    print_halls(i, 0);
                    cout << endl;
                }
            }
            break;
        }
        case 2: {
            system("cls");
            int hour, minute;
            cout << "Все брони с 7:00 до 21:00\nВыводит только если: \n1. До начала брони минимум 2 часа\n2. До 23:00 осталось минимум 2 часа\n\n";

            if (!(time_record(hour, minute))) {
                break;
            }
            int count_halls = read_halls();
            
            for (int i = 0; i < count_halls; i++) {
                int start = hall[i].hours;
                int end = hall[i].hours + hall[i].prolong;

                if ((end) <= hour && hall[i].minutes <= minute) {
                    print_halls(i, 1);
                    continue;
                }

                if ((start - 2) >= hour && hall[i].minutes >= minute) {
                    print_halls(i, 1);
                    continue;
                }
            }
            break;
        }
        case 3: {
            system("cls");
            int count_halls = read_halls();
            vector<double> rents(count_halls);

            for (int i = 0; i < count_halls; i++) rents[i] = hall[i].rent;

            double mini = rents[0];
            for (int i = 0; i < count_halls - 1; i++) if (mini > rents[i + 1]) mini = rents[i + 1];

            for (int i = 0; i < count_halls; i++) if (hall[i].rent == mini) print_halls(i, 0);
            break;
        }
        case 4:
            system("cls");
            return false;
        default:
            if (choice > 4) {
                system("cls");
                cout << "Ошибка ввода, повторите еще раз.\n";
            }
        }
    }
}

bool new_halls() {
    short choice = 0;
    while (true) {
        cout << "1 - Начать запись\n"
            << "2 - Вывести записи\n"
            << "3 - Забронировать аудиторию\n"
            << "4 - Изменить запись\n"
            << "5 - Назад\n\n"
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
            int count_halls = read_halls();
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
            hall->open = true; hall->hours = 0; hall->minutes = 0, hall->prolong = 0;
            system("cls");
            new_hall_file();
            break;
        }
        case 2:
            system("cls");
            output_halls();
            break;
        case 3:
            system("cls");
            booking();
            break;
        case 4: {
            system("cls");
            int count_halls = read_halls(), select_hall = 0, index = 0;
            for (int i = 0; i < count_halls; i++) cout << "Аудитория: " << hall[i].hall_number << endl;
   
            cout << "\n0 - Назад\nВыберите аудиторию, чтобы изменить данные: ";
            if (!(cin >> select_hall)) {
                problem();
            }
            else if (select_hall == 0) return false;
            system("cls");
            for (int i = 0; i < count_halls; i++) { 
                if (hall[i].hall_number == select_hall) {
                    print_halls(i, 1);
                    index = i;
                    break;
                }
            }
            cout << "Вы можете изменить:\n1 - Номер аудитории\n2 - Корпус\n3 - Вместимость\n4 - Наличие проектора\n5 - стоимость аренды в час\n6 - время брони\n\nВыберите действие: ";
            change_halls(index);
            break;
        } 
        case 5:
            system("cls");
            return false;
        default:
            if (choice > 5) {
                system("cls");
                cout << "Ошибка ввода, повторите еще раз.\n";
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

void change_student_file(int id_line, string new_name, int new_number, int* new_marks, int flag) {
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

bool new_student(string* subjects) {
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
            return false;
        default:
            if (choice > 2) {
                system("cls");
                cout << "Ошибка ввода, повторите еще раз.\n";
            }
        }
    }
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
            change_student_file(MAX_LINES * (id - 1), full_name, 0, 0, 1);
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
            change_student_file(MAX_LINES * (id - 1) + 1, "", new_num, 0, 2);
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
            change_student_file(MAX_LINES * (id - 1) + 2, "", new_num, 0, 2);
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
            change_student_file(MAX_LINES * (id - 1) + 3, "", new_num, 0, 2);
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
            change_student_file(MAX_LINES * (id - 1) + 4, "", 0, new_marks, 3);
            break;
        }
        case 6:
            system("cls");
            return false;
        default:
            if (choice > 6) {
                system("cls");
                cout << "Ошибка ввода, повторите еще раз.\n";
            }
        }
    }
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
        if (i == 5) break;
        int index = indexes[i];
        cout << (i + 1) << "-е место: " << avg_score[index] << " балл\t" << "ФИО: " << students[index].full_name << endl;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string subjects[] = { "Матан экзамен: ", "Программирование экзамен: ", "АиГ экзамен: ", "Иностранный язык диф. зачет: ", "Информатика диф. зачет: ", "Физика диф. зачет: ", "ОРГ диф. зачет: ", "Философия диф. зачет: " };
    short choice;
    while (true) {
        cout << "1 - Новая запись\n"
            << "2 - Изменить запись\n"
            << "3 - Вывести все записи\n"
            << "4 - Вывести всю информацию о студентах из группы N\n"
            << "5 - Топ самых успешных студентов\n"
            << "6 - Кол-во студентов М/Ж пола\n"
            << "7 - Успеваемость студентов\n"
            << "8 - Вывод студентов имеющих номер в списке N\n"
            << "9 - Аудитории\n"
            << "10 - Завершить работу\n\n"
            << "Выберите действие: ";
        if (!(cin >> choice)) problem();

        switch (choice) {
        case 1: 
            system("cls");
            new_student(subjects);
            break;
        case 2: {
            system("cls");
        point2:
            int id = 0;
            int number_students = read_students();
            cout << "Выберите студента, информацию о котором вы хотели бы изменить (1-" << number_students << ")\n\n";
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
        case 9: {
            system("cls");
            new_halls();
            break;
        }
        case 10:
            cout << "\nРабота завершена.";
            return false;
        default:
            if (choice > 10) {
                system("cls");
                cout << WHITE << "Ошибка ввода, повторите еще раз.\n";
            }
        }
    }
    return 0;
}
