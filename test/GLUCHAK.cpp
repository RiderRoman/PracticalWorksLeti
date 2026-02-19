#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

struct Profile
{
	string fullName; // Фамилия Имя Отчество
	char sex;         // Пол: M/W
	int group;        // Номер группы
	int id;           // Номер студента в списке 
	int grades[8];    // Оценки за экзамены и диф. зачёты
	char depart[9];   // Форма обучения
	string date;      // Дата внесения изменнеия в запись (post/update) 
};

struct tm* timeinfo;
time_t tstamp;

void creatingRecord() {
	Profile student;          // Создаём экземляр профайла студента
	cin >> student.fullName; // Через оператор "." инициализируем ФИО
	cin >> student.group;     // Через оператор "." инициализируем номер группы
	cin >> student.id;        // Через оператор "." инициализируем номер в списке группы
	cin >> student.sex;       // Через оператор "." инициализируем пол
	cin >> student.depart;    // Через оператор "." инициализируем форму обучения
	for (int i = 0; i < 8; i++)  cin >> student.grades[i];

	/*
	Если возникли проблемы запси в файл (записывается мусор, возникаэт ошибки) рекомендуется
	чистить поток ввода cin.clear();
	*/

	time(&tstamp);
	timeinfo = localtime(&tstamp);
	student.date = asctime(timeinfo);



	int temp = 0;
	for (int i = 0; i < 8; i++) // Так оценка 2 не может стоять в ведомости, идёт проверка
	{
		if (student.grades[i] == 2)
			temp++; // Найдена оценка 2, увеличиваем счётчик
	}
	if (temp == 0) // Если двоек не обнаружено
	{
		ofstream database; // Создаем поток записи в файл 
		// Открываем файл student с флагом записи в конец файла с сохранением содержимого файла
		database.open("students.txt", ios::app);
		if (!database.is_open()) // Если файл открыть не удалось 
			cout << '\n' << "Saving error!"; // Выдаём соответсвующее сообщение
		else // Если файл успешно был открыт поочереди записываем всю информацию в файл.
		{
			database << student.fullName << '\n';
			database << student.group << '\n' << student.id << '\n' << student.sex << '\n';
			database << student.depart << '\n';
			for (int i = 0; i < 8; i++)
				database << student.grades[i] << " ";
			database << '\n' << student.date;
			database.close();
			cout << '\n' << "Profile is saved in the database.";
		}
	}
	else // Если у студента есть неуд, информация о нем, не может быть сохранена, т.к. он должен быть отчислен
		cout << '\n' << "This student will be expelled. The profile will not be saved in the database.";
}