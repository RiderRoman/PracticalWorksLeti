#include <iostream>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <string>
#include <chrono>
#undef max

#define GREEN "\x1b[32m"
#define WHITE "\x1b[0m"

const int ACTION_CREATE_LIST = 1;
const int ACTION_CREATE_USER_LIST = 2;
const int ACTION_PRINT_LIST = 3;
const int ACTION_ADD_NUMBER = 4;
const int ACTION_DELETE_NUMBER = 5;
const int ACTION_SWAP_NUMBER = 6;
const int ACTION_FIND_NUMBER = 7;
const int ACTION_TURN_OFF = 8;

const int DELETE_BY_INDEX = 1;
const int DELETE_BY_VALUE = 2;

const int FIND_BY_INDEX = 1;
const int FIND_BY_VALUE = 2;

const int ACTION_SECOND_TURN_OFF = 0;

using namespace std;
using namespace chrono;

void cinFail() {
	system("cls");
	cout << WHITE << "Ошибка ввода, повторите еще раз.\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

auto rightInput(auto& argument) {
	string input;
	if (!(cin >> input)) {
		cinFail();
		return 0;
	}

	try {
		size_t pos;
		argument = stoi(input, &pos);

		if (pos != input.length()) {
			cinFail();
			return 0;
		}
	}
	catch (const invalid_argument& e) {
		cinFail();
		return 0;
	}
	catch (const out_of_range& e) {
		cinFail();
		return 0;
	}
}

bool checkIndex(int indexes[], int size, int index) {
	for (int i = 0; i < size; i++) {
		if (indexes[i] == index) {
			return true;
		}
	}
	return false;
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

	void printUserList(int indexes[], int size) {
		Node* temp = head;
		int pos = 0;
		while (temp) {
			if (checkIndex(indexes, size, pos)) {
				cout << GREEN << temp->data << WHITE << " ";
			}
			else {
				cout << temp->data << " ";
			}
			pos++;
			temp = temp->next;
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

void deleteIndex(DoublyLinkedList& list, int index) {
	Node* temp = list.head;
	int pos = 0;

	while (temp) {
		if (pos == index) {
			if (temp->prev != NULL) temp->prev->next = temp->next;
			else list.head = temp->next;

			if (temp->next != NULL) temp->next->prev = temp->prev;
			else list.tail = temp->prev;

			delete temp;
			break;
		}
		pos++;
		temp = temp->next;
	}
}

void deleteNumber(DoublyLinkedList& list, int number) {
	Node* temp = list.head;

	while (temp) {
		if (temp->data == number) {
			if (temp->prev != NULL) temp->prev->next = temp->next;
			else list.head = temp->next;

			if (temp->next != NULL) temp->next->prev = temp->prev;
			else list.tail = temp->prev;

			delete temp;
			break;
		}
		temp = temp->next;
	}
}

void swapNumbers(DoublyLinkedList& list, int index1, int index2) {
	Node* temp = list.head;
	Node* save = temp;
	int data1;
	int data2;
	int pos = 0;
	int saveIndex;
	if (index1 > index2) {
		saveIndex = index1;
		index1 = index2;
		index2 = saveIndex;
	}

	while (temp) {
		if (pos == index1) {
			data1 = temp->data;
			save = temp;
		}
		if (pos == index2) {
			data2 = temp->data;
			temp->data = data1;
			save->data = data2;
			break;
		}
		pos++;
		temp = temp->next;
	}
}

int main() {
	DoublyLinkedList list;
	int* arr = 0;
	
	srand(time(NULL));
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	short numberOfCreatures = 0;
	while (true) {
		int userChoice;
		cout << "-----------------------------------------\n"
			<< ACTION_CREATE_LIST << " - Создать список с числами от 0 до 99\n"
			<< ACTION_CREATE_USER_LIST << " - Создать список со своими числами\n"
			<< ACTION_PRINT_LIST << " - Вывести текущий список\n"
			<< "-----------------------------------------\n"
			<< ACTION_ADD_NUMBER << " - Добавить элемент в список\n"
			<< ACTION_DELETE_NUMBER << " - Удалить элемент из списка\n"
			<< ACTION_SWAP_NUMBER << " - Поменять местами элементы в списке\n"
			<< ACTION_FIND_NUMBER << " - Найти элемент в списке\n"
			<< ACTION_TURN_OFF << " - Завершить работу\n"
			<< "-----------------------------------------\n"
			<< "Выборите действие: ";
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
			list.printUserList(arr, 0);
			list.deleteUserList();
			break;
		}
		case ACTION_CREATE_USER_LIST: {
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
				int len = number.length();
				if (checkNumber(number, len) == false) {
					cout << "\nОшибка ввода повторите ещё раз.\n";
					continue;
				}
				
				list.createNode(stoi(number));
				record(stoi(number));
			}

			list.printUserList(arr, 0);
			list.deleteUserList();
			break;
		}
		case ACTION_PRINT_LIST: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}
			int size = readList(list, numberOfCreatures);
			list.printUserList(arr, 0);
			cout << "\nКол-во элементов: " << size << endl;
			list.deleteUserList();
			break;
		}
		case ACTION_ADD_NUMBER: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}

			int size = readList(list, numberOfCreatures);
			int number = 0;
			int index = 0;

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
			int* indexes = &index;
			addNumber(list, index, number);
			extraRecord(list);

			list.printUserList(indexes, 1);
			list.deleteUserList();
			break;
		}
		case ACTION_DELETE_NUMBER: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}

			int size = readList(list, numberOfCreatures);

			cout << DELETE_BY_INDEX << " - Удалить по индексу\n"
				<< DELETE_BY_VALUE << " - Удалить по значению\n"
				<< ACTION_SECOND_TURN_OFF << " - Выход\n\n"
				<< "Выберите действие: ";
			int userChoiceCase5;
			if (!(rightInput(userChoiceCase5))) {
				list.deleteUserList();
				break;
			}
			system("cls");

			if (userChoiceCase5 == DELETE_BY_INDEX) {
				cout << "Введите индекс: ";
				int index = 0;
				if (!(rightInput(index))) {
					list.deleteUserList();
					break;
				}
				if (index > (size - 1) || index < 0) {
					cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
					list.deleteUserList();
					break;
				}
				int* indexes = &index;
				list.printUserList(indexes, 1);
				cout << endl;
				deleteIndex(list, index);
				extraRecord(list);

				list.printUserList(arr, 0);
			}
			if (userChoiceCase5 == DELETE_BY_VALUE) {
				cout << "Введите число: ";
				int count = 0, value = 0;

				if (!(rightInput(value))) {
					list.deleteUserList();
					break;
				}

				Node* temp = list.head;
				while (temp) {
					if (temp->data == value) {
						cout << GREEN << temp->data << WHITE << " ";
						count++;
					}
					else {
						cout << temp->data << " ";
					}
					temp = temp->next;
				}

				for (short i = 0; i < count; i++) deleteNumber(list, value);

				extraRecord(list);
				cout << endl << endl;
				list.printUserList(arr, 0);
			}

			list.deleteUserList();
			break;
		}
		case ACTION_SWAP_NUMBER: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}
			int size = readList(list, numberOfCreatures);
			int index1, index2;

			cout << "Введите индекс: ";
			

			if (!(rightInput(index1))) {
				list.deleteUserList();
				break;
			}
			if (index1 > (size - 1) || index1 < 0) {
				cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
				list.deleteUserList();
			}
			cout << "Введите индекс: ";
			if (!(rightInput(index2))) {
				list.deleteUserList();
				break;
			}
			if (index2 > (size - 1) || index2 < 0) {
				cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
				list.deleteUserList();
			}

			int* indexes = new int[2];
			*indexes = index1; 
			indexes++;
			*indexes = index2;
			indexes--;

			list.printUserList(indexes, 2);
			swapNumbers(list, index1, index2);
			extraRecord(list);
			cout << endl;
			list.printUserList(indexes, 2);
			list.deleteUserList();
			delete indexes;
			break;
		}
		case ACTION_FIND_NUMBER: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}
			int size = readList(list, numberOfCreatures);
			int userChoiceCase6;

			cout << FIND_BY_INDEX << " - Найти по индексу\n"
				<< FIND_BY_VALUE << " - Найти по значению\n"
				<< ACTION_SECOND_TURN_OFF << " - Назад\n\n"
				<< "Выберите действие: ";

			rightInput(userChoiceCase6);

			if (userChoiceCase6 == FIND_BY_INDEX) {
				system("cls");
				cout << "Введите индекс: ";
				int index = 0;

				if (!(rightInput(index))) {
					list.deleteUserList();
					break;
				}
				if (index > size) {
					system("cls");
					cout << "Элемент не найден.\n";
					list.deleteUserList();
					break;
				}

				Node* userNumber;
				auto start = high_resolution_clock::now();
				userNumber = getNumber(list, index, size);
				auto end = high_resolution_clock::now();
				auto time = duration_cast<nanoseconds>(end - start).count();

				int* indexes = &index;

				list.printUserList(indexes, 1);
				cout << "\nЭлемент с индексом " << index << ": " << GREEN << userNumber->data << WHITE << endl;
				cout << "Время на поиск: " << time << " наносекунд\n";
			}
			else if (userChoiceCase6 == FIND_BY_VALUE) {
				system("cls");
				cout << "Введите целое число: ";
				int userNumber;
				if (!(rightInput(userNumber))) {
					list.deleteUserList();
					break;
				}

				Node* temp = list.head->next;
				int mini = temp->prev->data, maxi = temp->prev->data;
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
				int currentIndex = 0, count = 0;
				int* index = new int[size];

				temp = list.head;

				auto start = high_resolution_clock::now();

				while (temp) {
					if (temp->data == userNumber) {
						*index = currentIndex;
						index++;
						count++;
					}
					else {
					}
					currentIndex++;
					temp = temp->next;
				}

				auto end = high_resolution_clock::now();
				auto time = duration_cast<nanoseconds>(end - start).count();
				
				if (count == 0) {
					system("cls");
					cout << "Элемент не найден.\n";
					list.deleteUserList();
					break;
				}
				index = index - count;
				list.printUserList(index, count);

				cout << "\nИндексы: ";
				for (int j = 0; j < count; j++) {
					cout << *(index + j) << " ";
				}
				cout << "\nВремя на поиск: " << time << " наносекунд\n";
				delete index;
			}
			else {
				system("cls");
			}

			list.deleteUserList();
			break;
		}
		case ACTION_TURN_OFF: {
			cout << "Работа завершена.";
			return false;
		}
		default:
			system("cls");
			cinFail();
		}
	}
	return 0;
}