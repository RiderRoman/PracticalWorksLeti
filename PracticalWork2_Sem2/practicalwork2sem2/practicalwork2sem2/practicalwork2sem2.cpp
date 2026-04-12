#include <iostream>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <string>
#include <chrono>
#undef max

#define GREEN "\x1b[32m"
#define WHITE "\x1b[0m"

using namespace std;
using namespace chrono;

void problem() {
	system("cls");
	cout << WHITE << "Ошибка ввода, повторите еще раз.\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

auto rightInput(auto& argument) {
	string input;
	if (!(cin >> input)) {
		problem();
		return 0;
	}

	try {
		size_t pos;
		argument = stoi(input, &pos);

		if (pos != input.length()) {
			problem();
			return 0;
		}
	}
	catch (const invalid_argument& e) {
		problem();
		return 0;
	}
	catch (const out_of_range& e) {
		problem();
		return 0;
	}
}

class Node {
public:
	int data;
	Node* prev;
	Node* next;

	Node(int value) {
		data = value;
		prev = nullptr;
		next = nullptr;
	}
};

class DoublyLinkedList {
public:
	Node* head;
	Node* tail;

	DoublyLinkedList() : head(nullptr), tail(nullptr) {}

	void createNode(int value) {
		Node* newNode = new Node(value);
		if (!head) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}

	void printUserList(int index1, int index2) {
		Node* current = head;
		int pos = 0;
		while (current) {
			if (pos == index1 || pos == index2) { cout << GREEN << current->data << WHITE << " "; }
			else cout << current->data << " ";
			pos++;
			current = current->next;
		}
		cout << endl;
	}

	void deleteUserList() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
	}
};

void record(int value) {
	ofstream record;
	record.open("list.txt", ios::app);
	if (!record.is_open()) { cout << "Список не найден, попробуйте создать новый."; }
	else {
		record << value << endl;
		record.close();
	}
}

int readList(DoublyLinkedList& list, int numberOfCretions) {
	ifstream file;
	string line;
	int n = 0;
	int number = 0;
	file.open("list.txt");
	if (!(file.is_open())) {
		cout << "Список не найден, попробуйте создать новый.\n";
		return false;
	}

	while (getline(file, line)) {
		if (line.length() > 0) {
			if (numberOfCretions == 0) {
				file.close();
				return -1;
			}
			n++;
			number = stoi(line);
			list.createNode(number);
		}
	}
	file.close();
	return n;
}

Node* getNumber(DoublyLinkedList& list, int index, int size) {
	if (index < size / 2) {
		Node* temp = list.head;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		return temp;
	}
	else {
		Node* temp = list.tail;
		for (int i = (size - 1); i > index; i--) {
			temp = temp->prev;
		}
		return temp;
	}
}

void addNumber(DoublyLinkedList& list, int index, int value) {
	Node* temp = list.head;
	Node* newNode = new Node(value);
	Node* save1;

	int i = 0;
	while (temp != NULL) {

		if ((i + 1) == index) {

			save1 = temp->next;
			newNode->next = save1;
			newNode->prev = temp;
			temp->next = newNode;
			if (save1 != NULL) {
				save1->prev = newNode;
			}
			break;
		}
		i++;
		temp = temp->next;
	}
}

bool checkNumber(string arr, int size) {
	string numbers = "0123456789";
	for (int i = 0; i < size; i++) {
		/*if (arr[i] == "\0") break;*/
		bool hit = false;

		for (int j = 0; j < 10; j++) {
			if (arr[i] == numbers[j]) {
				hit = true;
				break;
			}
			if (j == 9 && hit == false) {
				return false;
			}
		}
	}
	return true;
}

void extraRecord(DoublyLinkedList& list) {
	remove("list.txt");
	Node* temp = list.head;
	while (temp != NULL) {
		record(temp->data);
		temp = temp->next;
	}
}

int deleteIndex(DoublyLinkedList& list, int index) {
	Node* temp = list.head;
	int pos = 0;

	while (temp) {
		if (pos == index) {
			if (temp->prev != NULL) temp->prev->next = temp->next;
			else list.head = temp->next;

			if (temp->next != NULL) temp->next->prev = temp->prev;
			else list.tail = temp->prev;

			delete temp;
			return true;
		}
		pos++;
		temp = temp->next;
	}

	return false;
}

bool deleteNumber(DoublyLinkedList& list, int number) {
	Node* temp = list.head;

	while (temp) {
		if (temp->data == number) {
			if (temp->prev != NULL) temp->prev->next = temp->next;
			else list.head = temp->next;

			if (temp->next != NULL) temp->next->prev = temp->prev;
			else list.tail = temp->prev;

			delete temp;
			return true;
		}
		temp = temp->next;
	}

	return false;
}

bool swapNumbers(DoublyLinkedList& list, int index1, int index2) {
	Node* temp = list.head;
	Node* save = temp;
	int data1;
	int data2;
	int pos = 0;
	bool flag = false;
	int saveIndex;
	if (index1 > index2) {
		saveIndex = index1;
		index1 = index2;
		index2 = saveIndex;
	}

	while (temp) {
		if (pos == index1 && !flag) {
			data1 = temp->data;
			save = temp;
			flag = true;
		}
		if (pos == index2 && flag) {
			data2 = temp->data;
			temp->data = data1;
			save->data = data2;
			return true;
		}
		pos++;
		temp = temp->next;
	}
	return false;
}

const int ACTION_CREATE_LIST = 1;

int main() {
	DoublyLinkedList list;
	srand(time(NULL));
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	short numberOfCreatures = 0;
	while (true) {
		int userChoice;
		cout << "-----------------------------------------\n"
			<< ACTION_CREATE_LIST << " - Создать список с числами от 0 до 99\n"
			<< "2 - Создать список со своими числами\n"
			<< "3 - Вывести текущий список\n"
			<< "-----------------------------------------\n"
			<< "4 - Добавить элемент в список\n"
			<< "5 - Удалить элемент из списка\n"
			<< "6 - Поменять местами элементы в списке\n"
			<< "7 - Найти элемент в списке\n"
			<< "8 - Завершить работу\n"
			<< "-----------------------------------------\n"
			<< "Выбор: ";
		cin >> userChoice;
		switch (userChoice) {
		case ACTION_CREATE_LIST: {
			system("cls");

			if (numberOfCreatures == 0 && readList(list, numberOfCreatures) == -1) {
				remove("list.txt");
			}
			if (numberOfCreatures >= 1) {
				remove("list.txt");
			}
			numberOfCreatures++;

			cout << "Введите размер списка: ";
			int size = 0;
			if (!(rightInput(size))) {
				list.deleteUserList();
				break;
			}
			system("cls");
			for (int i = 0; i < size; i++) {
				int random = rand() % 100;
				list.createNode(random);
				record(random);
			}
			list.printUserList(-1, -1);
			list.deleteUserList();
			break;
		}
		case 2: {
			system("cls");
			if (numberOfCreatures == 0 && readList(list, numberOfCreatures) == -1) {
				remove("list.txt");
			}
			if (numberOfCreatures >= 1) {
				remove("list.txt");
			}
			numberOfCreatures++;
			cout << "e - выход\n"
				<< "enter - новый элемент\n";
			string number;
			while (true) {
				cout << "Введите элемент списка: ";
				cin >> number;
				if (number == "e" || number == "е") {
					break;
				}
				int size = number.length();
				if (checkNumber(number, size) == false) {
					cout << "\nОшибка ввода повторите ещё раз.\n";
					continue;
				}

				list.createNode(stoi(number));
				record(stoi(number));
			}

			list.printUserList(-1, -1);
			list.deleteUserList();
			break;
		}
		case 3: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}
			int size = readList(list, numberOfCreatures);
			list.printUserList(-1, -1);
			cout << "\nКол-во элементов: " << size << endl;
			list.deleteUserList();
			break;
		}
		case 4: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}

			int size = readList(list, numberOfCreatures);
			int index = 0, number = 0;

			cout << "Введите индекс: ";
			if (!(rightInput(index))) {
				list.deleteUserList();
				break;
			}
			if (index > size || index < 0) {
				system("cls");
				cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
				list.deleteUserList();
			}

			cout << "\nВведите целое число: ";
			if (!(rightInput(number))) {
				list.deleteUserList();
				break;
			}

			addNumber(list, index, number);
			extraRecord(list);

			list.printUserList(index, -1);
			list.deleteUserList();
			break;
		}
		case 5: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}

			int size = readList(list, numberOfCreatures);

			cout << "1 - Удалить по индексу\n"
				<< "2 - Удалить по значению\n"
				<< "0 - Выход\n\n"
				<< "Выберите действие: ";
			int userChoiceCase5;
			if (!(rightInput(userChoiceCase5))) {
				list.deleteUserList();
				break;
			}
			system("cls");

			if (userChoiceCase5 == 1) {
				cout << "Введите индекс: ";
				int index;
				if (!(rightInput(index))) {
					list.deleteUserList();
					break;
				}
				if (index > (size - 1) || index < 0) {
					cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
					list.deleteUserList();
					break;
				}

				list.printUserList(index, -1);
				cout << endl;
				deleteIndex(list, index);
				extraRecord(list);

				list.printUserList(-1, -1);
			}
			if (userChoiceCase5 == 2) {
				cout << "Введите число: ";
				int count = 0, userNumber = 0;

				if (!(rightInput(userNumber))) {
					list.deleteUserList();
					break;
				}

				Node* temp = list.head;
				while (temp) {
					if (temp->data == userNumber) {
						cout << GREEN << temp->data << WHITE << " ";
						count++;
					}
					else {
						cout << temp->data << " ";
					}
					temp = temp->next;
				}

				for (short i = 0; i < count; i++) deleteNumber(list, userNumber);

				extraRecord(list);
				cout << endl << endl;
				list.printUserList(-1, -1);
			}

			list.deleteUserList();
			break;
		}
		case 6: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}
		point6:
			unsigned int size = readList(list, numberOfCreatures);


			cout << "Введите индекс: ";
			unsigned int index1 = 0, index2 = 0;
			if (!(rightInput(index1))) {
				list.deleteUserList();
				break;
			}
			if (index1 > (size - 1) || index1 < 0) {
				cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
				list.deleteUserList();
				goto point6;
			}
			cout << "Введите индекс: ";
			if (!(rightInput(index2))) {
				list.deleteUserList();
				break;
			}
			if (index2 > (size - 1) || index1 < 0) {
				cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
				list.deleteUserList();
				goto point6;
			}

			list.printUserList(index1, index2);
			swapNumbers(list, index1, index2);
			extraRecord(list);
			cout << endl;
			list.printUserList(index1, index2);
			list.deleteUserList();
			break;
		}
		case 7: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}
			int size = readList(list, numberOfCreatures);
			int userChoiceCase6;

			cout << "1 - Найти по индексу\n"
				<< "2 - Найти по значению\n"
				<< "0 - Назад\n\n"
				<< "Выберите действие: ";

			rightInput(userChoiceCase6);

			if (userChoiceCase6 == 1) {
				system("cls");
				cout << "Введите индекс: ";
				int index;

				rightInput(index);
				if (index > size) {
					system("cls");
					cout << "Элемент не найден.\n";
					list.deleteUserList();
					break;
				}

				Node* userNumber;
				auto time1 = high_resolution_clock::now();
				userNumber = getNumber(list, index, size);
				auto time2 = high_resolution_clock::now();
				auto end = duration_cast<nanoseconds>(time2 - time1).count();

				list.printUserList(index, -1);
				cout << "\nЭлемент с индексом " << index << ": " << GREEN << userNumber->data << WHITE << endl;
				cout << "Время на поиск: " << end << " наносекунд\n";
			}
			else if (userChoiceCase6 == 2) {
				system("cls");
				cout << "Введите целое число: ";
				int userNumber;
				rightInput(userNumber);

				Node* temp = list.head;
				int mini = temp->data, maxi = temp->data;
				while (temp) {
					if (temp->data > maxi) maxi = temp->data;
					else if (temp->data < mini) mini = temp->data;

					temp = temp->next;
				}

				if (userNumber > maxi || userNumber < mini) {
					system("cls");
					cout << "Элемент не найден.\n";
					list.deleteUserList();
					break;
				}
				int i = 0, count = 0;
				int* index = new int[size];

				temp = list.head;

				auto time1 = high_resolution_clock::now();

				while (temp) {
					if (temp->data == userNumber) {
						*index = i;
						index++;
						count++;
					}
					else {
					}
					i++;
					temp = temp->next;
				}

				auto time2 = high_resolution_clock::now();
				auto end = duration_cast<nanoseconds>(time2 - time1).count();

				while (temp) { // DFGJDFLKGJLDFKJGKLFDJG!!!
					if (temp->data == userNumber) cout << GREEN << temp->data << WHITE << " ";
					else cout << temp->data << " ";

					temp = temp->next;
				}

				if (count == 0) {
					system("cls");
					cout << "Элемент не найден.\n";
					list.deleteUserList();
					break;
				}

				cout << "\nИндексы: ";
				for (int j = 0; j < count; j++) {
					cout << *(index - count + j) << " ";
				}
				cout << "\nВремя на поиск: " << end << " наносекунд\n";
				index = index - count;
				delete index;
			}
			else {
				system("cls");
			}

			list.deleteUserList();
			break;
		}
		case 8: {
			cout << "Работа завершена.";
			return false;
		}
		default:
			system("cls");
			problem();
		}
	}
	return 0;
}