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

	void printUserList(int index) {
		Node* current = head;
		int pos = 0;
		while (current) {
			if (pos == index) {cout << GREEN << current->data << WHITE << " ";}
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
	if (!record.is_open()) { cout << "Не получилось открыть файл."; }
	else {
		record << value << endl;
		record.close();
	}
}

int readList(DoublyLinkedList &list, int numberOfCretions) {
	ifstream file;
	string line;
	int n = 0;
	int number = 0;
	file.open("list.txt");
	if (!(file.is_open())) {
		cout << "Не удалось открыть файл.\n";
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

Node* getNumber(DoublyLinkedList &list, int index, int size) {
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

void bubbleSort(DoublyLinkedList &list) {
	bool flag;
	do {
		flag = false;
		Node* temp = list.head;

		while (temp->next) {
			if (temp->data > temp->next->data) {
				swap(temp->data, temp->next->data);
				flag = true;
			}
			temp = temp->next;
		}
	} while (flag);

}

void newNumber(DoublyLinkedList &list, int index, int value) {
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
			<< "1 - Создать список с числами от 0 до 99\n"
			<< "2 - Создать список со своими числами\n"
			<< "-----------------------------------------\n"
			<< "3 - Добавить элемент в список\n"
			<< "4 - Удалить элемент из списка\n"
			<< "5 - Поменять местами элементы в списке\n"
			<< "6 - Получить элемент с номером в списке N\n"
			<< "7 - Завершить работу\n"
			<< "-----------------------------------------\n"
			<< "Выбор: ";
		cin >> userChoice;
		switch (userChoice) {
		case 1: {
			system("cls");
			if (numberOfCreatures == 0 && readList(list, numberOfCreatures) == -1) { // if file not empty after programm closed
				remove("list.txt");
			}
			if (numberOfCreatures >= 1) { // user create new list
				remove("list.txt");
			}
			numberOfCreatures++;

			int value = 100;
			for (int i = 0; i < value; i++) {
				int random = rand() % 99;
				list.createNode(random);
				record(random);
			}
			list.printUserList(-1);
			list.deleteUserList();
			break;
		}
		case 2: {
			system("cls");
			list.printUserList(-1);
			list.deleteUserList();
			break;
		}
		case 3: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Создайте список";
				break;
			}
			
			int size = readList(list, numberOfCreatures);
			int index = 0, value = 0;
			cout << "Введите индекс: ";
			cin >> index;
			cout << "\nВведите целое число: ";
			cin >> value;

			newNumber(list, index, value);
			
			remove("list.txt");
			Node* temp = list.head;
			while (temp != NULL) {
				record(temp->data);
				temp = temp->next;
			}
			
			list.printUserList(-1);
			list.deleteUserList();
			break;
		}
		case 4: {
			system("cls");
			break;
		}
		case 5: {
			system("cls");
			break;
		}
		case 6: {
			system("cls");
			if (numberOfCreatures == 0) {
				cout << "Создайте список";
				break;
			}
			int size = readList(list, numberOfCreatures);
			int userChoiceCase6;
			
			cout << "1 - Найти по индексу\n"
				<< "2 - Найти по значению\n\n"
				<< "Выбор: ";

			if (!(cin >> userChoiceCase6)) return false;
			
			if (userChoiceCase6 == 1) {
				system("cls");
				cout << "Введите индекс: ";
				int index;
				Node* userNumber;

				cin >> index;
				auto time1 = high_resolution_clock::now();
				userNumber = getNumber(list, index, size);
				auto time2 = high_resolution_clock::now();
				auto end = duration_cast<nanoseconds>(time2 - time1).count();

				list.printUserList(index);
				cout << "\nЭлемент с индексом " << index << ": " << GREEN << userNumber->data << WHITE << endl;
				cout << "Время на поиск: " << end << " наносекунд\n";
				list.deleteUserList();
			}
			else if (userChoiceCase6 == 2) {
				system("cls");
				cout << "Введите целое число: ";
				int userNumber;
				cin >> userNumber;
				int i = 0, count = 0;
				int* index = new int[size];

				Node* temp = list.head;
				
				auto time1 = high_resolution_clock::now();
				
				while (temp) {
					if (temp->data == userNumber) {
						cout << GREEN << temp->data << WHITE << " ";
						*index = i;
						index++;
						count++;
					}
					else {
						cout << temp->data << " ";
					}
					i++;
					temp = temp->next;
				}

				auto time2 = high_resolution_clock::now();
				auto end = duration_cast<nanoseconds>(time2 - time1).count();
				cout << "\nИндексы: ";
				for (int j = 0; j < count; j++) {
					cout << *(index - count + j) << " ";
				}
				cout << "\nВремя на поиск: " << end << " наносекунд\n";
				index = index - count;
				delete index;
				list.deleteUserList();	
			}


			break;
		}
		case 7: {
			cout << "бб";
			return false;
		}
		default:
			system("cls");
		}

	}
	
	return 0;
}