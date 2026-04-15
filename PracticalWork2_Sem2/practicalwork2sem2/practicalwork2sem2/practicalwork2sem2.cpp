#include <iostream>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <string>
#include <chrono>
#undef max

#define GREEN "\x1b[32m"
#define WHITE "\x1b[0m"

const int ACTION_PRINT_LIST_MENU = 0;
const int ACTION_TURN_OFF = 0;
const int ACTION_CREATE_LIST = 1;
const int ACTION_CREATE_USER_LIST = 2;
const int ACTION_PRINT_LIST = 3;
const int ACTION_ADD_NUMBER = 4;
const int ACTION_DELETE_NUMBER = 5;
const int ACTION_SWAP_NUMBER = 6;
const int ACTION_FIND_NUMBER = 7;
const int ACTION_SWAP_MENUS = 8;

const int DELETE_BY_INDEX = 1;
const int DELETE_BY_VALUE = 2;

const int FIND_BY_INDEX = 1;
const int FIND_BY_VALUE = 2;

const int ACTION_PRINT_ARRAY_MENU = 100;
const int ACTION_CREATE_ARRAY = 1;
const int ACTION_CREATE_USER_ARRAY = 2;
const int ACTION_PRINT_ARRAY = 3;

using namespace std;
using namespace chrono;

void error() {
	system("cls");
	cout << WHITE << "Ошибка ввода, повторите еще раз.\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool check_index(int indexes[], int size, int index) {
	for (int i = 0; i < size; i++) {
		if (indexes[i] == index) return true;
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

	Node* push_back(int value) {
		Node* new_node = new Node(value);
		if (!head) {
			head = tail = new_node;
		}
		else {
			tail->next = new_node;
			new_node->prev = tail;
			tail = new_node;
		}
		return new_node;
	}

	Node* push_front(int value) {
		Node* new_node = new Node(value);
		if (!head) {
			head = tail = new_node;
		}
		else {
			head->prev = new_node;
			new_node->next = head;
			head = new_node;
		}
		return new_node;
	}

	Node* get_number(int index) {
		Node* temp = head;
		int pos = 0;

		while (pos != index) {
			if (temp == NULL) return temp;

			temp = temp->next;
			pos++;
		}
		return temp;
	}

	Node* insert(int index, int value) {
		Node* right = get_number(index);
		if (right == NULL)
			return push_back(value);

		Node* left = right->prev;
		if (left == NULL)
			return push_front(value);

		Node* new_node = new Node(value);

		new_node->prev = left;
		new_node->next = right;
		left->next = new_node;
		right->prev = new_node;

		return new_node;
	}

	void print_list(int indexes[], int size) {
		Node* temp = head;
		int pos = 0;
		while (temp) {
			if (check_index(indexes, size, pos)) {
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

	void delete_list() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
	}
};

bool check_value(string value, int size) {
	string numbers = "0123456789";
	for (int i = 0; i < size; i++) {
		bool hit = false;

		for (int j = 0; j < 10; j++) {
			if (value[i] == numbers[j]) {
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


void delete_by_index(DoublyLinkedList& list, int index) {
	Node* temp = list.head;
	int pos = 0;

	while (temp) {
		if (pos == index) {
			if (temp->prev != NULL) {
				temp->prev->next = temp->next;
			}
			else {
				list.head = temp->next;
			}

			if (temp->next != NULL) {
				temp->next->prev = temp->prev;
			}
			else {
				list.tail = temp->prev;
			}

			delete temp;
			break;
		}
		pos++;
		temp = temp->next;
	}
}

void delete_by_value(DoublyLinkedList& list, int value) {
	Node* temp = list.head;

	while (temp) {
		if (temp->data == value) {
			if (temp->prev != NULL) {
				temp->prev->next = temp->next;
			}
			else {
				list.head = temp->next;
			}

			if (temp->next != NULL) {
				temp->next->prev = temp->prev;
			}
			else {
				list.tail = temp->prev;
			}

			delete temp;
			break;
		}
		temp = temp->next;
	}
}

void swap_values(DoublyLinkedList& list, int index1, int index2) {
	Node* temp = list.head;
	Node* save = temp;

	int saveData;
	int pos = 0;
	int saveIndex;
	if (index1 > index2) {
		saveIndex = index1;
		index1 = index2;
		index2 = saveIndex;
	}

	while (temp) {
		if (pos == index1) {
			save = temp;
		}
		if (pos == index2) {
			saveData = temp->data;
			temp->data = save->data;
			save->data = saveData;
			break;
		}
		pos++;
		temp = temp->next;
	}
}

int list_size(DoublyLinkedList& list) {
	Node* temp = list.head;
	int size = 0;
	while (temp) {
		size++;
		temp = temp->next;
	}
	return size;
}

void print_menus(int flag) {
	if (flag == ACTION_PRINT_LIST_MENU) {
		cout << "-----------------------------------------\n"
			<< ACTION_CREATE_LIST << " - Создать список с числами от 0 до 99\n"
			<< ACTION_CREATE_USER_LIST << " - Создать список со своими числами\n"
			<< ACTION_PRINT_LIST << " - Вывести текущий список\n"
			<< "-----------------------------------------\n"
			<< ACTION_ADD_NUMBER << " - Добавить элемент в список\n"
			<< ACTION_DELETE_NUMBER << " - Удалить элемент из списка\n"
			<< ACTION_SWAP_NUMBER << " - Поменять местами элементы в списке\n"
			<< ACTION_FIND_NUMBER << " - Найти элемент в списке\n"
			<< ACTION_SWAP_MENUS << " - Работа с массивом\n"
			<< ACTION_TURN_OFF << " - Завершить работу\n"
			<< "-----------------------------------------\n"
			<< "Выборите действие: ";
	}
	else if (flag == ACTION_DELETE_NUMBER) {
		cout << DELETE_BY_INDEX << " - Удалить по индексу\n"
			<< DELETE_BY_VALUE << " - Удалить по значению\n"
			<< ACTION_TURN_OFF << " - Назад\n\n"
			<< "Выберите действие: ";
	}
	else if (flag == ACTION_FIND_NUMBER) {
		cout << FIND_BY_INDEX << " - Найти по индексу\n"
			<< FIND_BY_VALUE << " - Найти по значению\n"
			<< ACTION_TURN_OFF << " - Назад\n\n"
			<< "Выберите действие: ";
	}
	else if (flag == ACTION_PRINT_ARRAY_MENU) {
		cout << "-----------------------------------------\n"
			<< ACTION_CREATE_ARRAY << " - Создать массив с числами от 0 до 99\n"
			<< ACTION_CREATE_USER_ARRAY << " - Создать массив со своими числами\n"
			<< ACTION_PRINT_ARRAY << " - Вывести текущий массив\n"
			<< "-----------------------------------------\n"
			<< ACTION_ADD_NUMBER << " - Добавить элемент в массив\n"
			<< ACTION_DELETE_NUMBER << " - Удалить элемент из массива\n"
			<< ACTION_SWAP_NUMBER << " - Поменять местами элементы в массиве\n"
			<< ACTION_FIND_NUMBER << " - Найти элемент в массиве\n"
			<< ACTION_TURN_OFF << " - Назад\n"
			<< "-----------------------------------------\n"
			<< "Выборите действие: ";
	}
}

// dynamic array

void print_array(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void fill_array(int*& arr, int& size) {
	cout << "e - выход\n"
		<< "enter - новый элемент\n";
	string value;

	while (true) {
		cout << "Введите элемент списка: ";
		cin >> value;
		if (value == "e" || value == "е") break;

		int length = value.length();
		if (check_value(value, length) == false) {
			cout << "\nОшибка ввода повторите ещё раз.\n";
			continue;
		}
		size++;

		int* new_arr = new int[size];
		for (int i = 0; i < size - 1; i++)
			new_arr[i] = arr[i];

		new_arr[size - 1] = stoi(value);
		delete[] arr;
		arr = new_arr;
	}
}

void fill_array_random(int*& arr, int& size) {
	int* new_arr = new int[size];

	for (int i = 0; i < size; i++) {
		new_arr[i] = rand() % 100;
	}
	delete[] arr;
	arr = new_arr;
}

bool dynamic_array() {
	int count_of_creatures = 0;
	int size = 0;
	int* arr = new int[size];
	while (true) {
		print_menus(ACTION_PRINT_ARRAY_MENU);
		int choice = 0;
		cin >> choice;
		switch (choice) {
		case ACTION_CREATE_ARRAY: {
			system("cls");
			if (count_of_creatures > 0) {
				delete[] arr;
				size = 0;
				int* new_arr = new int[size];
				arr = new_arr;
			}

			count_of_creatures++;
			cout << "Введите размер массива: ";

			while (!(cin >> size)) {
				error();
				cout << "Введите размер массива: ";
			}

			fill_array_random(arr, size);
			print_array(arr, size);

			break;
		}
		case ACTION_CREATE_USER_ARRAY: {
			system("cls");
			if (count_of_creatures > 0) {
				delete[] arr;
				size = 0;
				int* new_arr = new int[size];
				arr = new_arr;
			}

			count_of_creatures++;

			fill_array(arr, size);
			print_array(arr, size);
			break;
		}
		case ACTION_PRINT_ARRAY: {
			system("cls");
			print_array(arr, size);
			cout << "\nКол-во элементов: " << size << endl;
			break;
		}
		case ACTION_TURN_OFF: {
			system("cls");
			delete[] arr;
			return false;
		}
		default:
			system("cls");
		}

	}
}



int main() {
	DoublyLinkedList list;
	int* arr = 0;
	srand(time(NULL));
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	short number_of_creatures = 0;

	while (true) {
		int choice;
		print_menus(ACTION_PRINT_LIST_MENU);
		cin >> choice;
		switch (choice) {
		case ACTION_CREATE_LIST: {
			system("cls");
			if (number_of_creatures > 0) list.delete_list();

			number_of_creatures++;

			cout << "Введите размер списка: ";
			int size = 0;

			while (!(cin >> size)) {
				error();
				cout << "Введите размер списка: ";
			}

			system("cls");

			auto start = high_resolution_clock::now();

			for (int i = 0; i < size; i++)
				list.push_back((rand() % 100));

			auto end = high_resolution_clock::now();
			auto time = duration_cast<nanoseconds>(end - start).count();

			list.print_list(arr, 0);
			cout << "\nВремя создания: " << time << " наносекунд.\n";
			break;
		}
		case ACTION_CREATE_USER_LIST: {
			system("cls");
			if (number_of_creatures > 0)
				list.delete_list();

			number_of_creatures++;

			cout << "e - выход\n"
				<< "enter - новый элемент\n";
			string value;

			while (true) {
				cout << "Введите элемент списка: ";
				cin >> value;
				if (value == "e" || value == "е") {
					break;
				}
				int length = value.length();
				if (check_value(value, length) == false) {
					cout << "\nОшибка ввода повторите ещё раз.\n";
					continue;
				}

				list.push_back(stoi(value));
			}

			list.print_list(arr, 0);
			break;
		}
		case ACTION_PRINT_LIST: {
			system("cls");
			if (number_of_creatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}

			int size = list_size(list);
			list.print_list(arr, 0);
			cout << "\nКол-во элементов: " << size << endl;
			break;
		}
		case ACTION_ADD_NUMBER: {
			system("cls");
			if (number_of_creatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}

			int size = list_size(list);
			int value = 0;
			int index = 0;

			cout << "Введите индекс (0-" << size << "): ";
			while (!(cin >> index)) {
				error();
				cout << "Введите индекс (0-" << size << "): ";
			}
			if (index > size || index < 0) {
				system("cls");
				cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
				break;
			}

			cout << "\nВведите целое число: ";
			while (!(cin >> value)) {
				error();
				cout << "Введите целое число: ";
			}

			auto start = high_resolution_clock::now();
			list.insert(index, value);
			auto end = high_resolution_clock::now();
			auto time = duration_cast<nanoseconds>(end - start).count();

			list.print_list(&index, 1);
			cout << "\nВремя на вставку: " << time << " наносекунд.\n";
			break;
		}
		case ACTION_DELETE_NUMBER: {
			system("cls");
			if (number_of_creatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}

			int size = list_size(list);
			print_menus(ACTION_DELETE_NUMBER);

			int choice_action_del;
			while (!(cin >> choice_action_del)) {
				error();
				print_menus(ACTION_DELETE_NUMBER);
			}

			if (choice_action_del == DELETE_BY_INDEX) {
				cout << "Введите индекс (0-" << size - 1 << "): ";
				int index = 0;

				while (!(cin >> index)) {
					error();
					cout << "Введите индекс (0-" << size - 1 << "): ";
				}

				if (index > (size - 1) || index < 0) {
					cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
					break;
				}

				list.print_list(&index, 1);
				cout << endl;

				auto start = high_resolution_clock::now();
				delete_by_index(list, index);
				auto end = high_resolution_clock::now();
				auto time = duration_cast<nanoseconds>(end - start).count();

				list.print_list(arr, 0);
				cout << "\nВремя на удаление: " << time << " наносекунд.\n";
			}
			if (choice_action_del == DELETE_BY_VALUE) {
				cout << "Введите число: ";
				int count = 0, value = 0;

				while (!(cin >> value)) {
					error();
					cout << "Введите число: ";
				}

				Node* temp = list.head;
				while (temp) {
					if (temp->data == value) {
						cout << GREEN << temp->data << WHITE << " ";
						count++;
					}
					else
						cout << temp->data << " ";

					temp = temp->next;
				}

				auto start = high_resolution_clock::now();
				for (short i = 0; i < count; i++) delete_by_value(list, value);
				auto end = high_resolution_clock::now();
				auto time = duration_cast<nanoseconds>(end - start).count();

				cout << "\nВремя на удаление: " << time << " наносекунд.\n";
			}

			break;
		}
		case ACTION_SWAP_NUMBER: {
			system("cls");
			if (number_of_creatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}
			int size = list_size(list);
			int index1, index2;

			cout << "Введите индекс (0-" << size - 1 << "): ";

			while (!(cin >> index1)) {
				error();
				cout << "Введите индекс (0-" << size - 1 << "): ";
			}

			if (index1 > (size - 1) || index1 < 0) {
				cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
				break;
			}

			cout << "Введите индекс (0-" << size - 1 << "): ";

			while (!(cin >> index2)) {
				cout << "Введите индекс (0-" << size - 1 << "): ";
				error();
			}

			if (index2 > (size - 1) || index2 < 0) {
				cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
				break;
			}

			int* indexes = new int[2];
			indexes[0] = index1; indexes[1] = index2;

			list.print_list(indexes, 2);
			swap_values(list, index1, index2);
			cout << endl;
			list.print_list(indexes, 2);
			delete[] indexes;
			break;
		}
		case ACTION_FIND_NUMBER: {
			system("cls");
			if (number_of_creatures == 0) {
				cout << "Список не найден, попробуйте создать новый.\n";
				break;
			}
			int choice_action_find;
			int size = list_size(list);

			print_menus(ACTION_FIND_NUMBER);

			while (!(cin >> choice_action_find)) {
				error();
				print_menus(ACTION_FIND_NUMBER);
			}

			if (choice_action_find == FIND_BY_INDEX) {
				system("cls");
				cout << "Введите индекс (0-" << size - 1 << "): ";
				int index = 0;

				while (!(cin >> index)) {
					error();
					cout << "Введите индекс (0-" << size - 1 << "): ";
				}
				if (index >= size) {
					system("cls");
					cout << "Вы ввели неверный индекс, повторите ещё раз.\n";
					break;
				}

				Node* value;
				auto start = high_resolution_clock::now();
				value = list.get_number(index);
				auto end = high_resolution_clock::now();
				auto time = duration_cast<nanoseconds>(end - start).count();

				list.print_list(&index, 1);
				cout << "\nЭлемент с индексом " << index << ": " << GREEN << value->data << WHITE << endl;
				cout << "Время на поиск: " << time << " наносекунд\n";
			}
			else if (choice_action_find == FIND_BY_VALUE) {
				system("cls");
				cout << "Введите целое число: ";
				int userNumber = 0;

				while (!(cin >> userNumber)) {
					error();
					cout << "Введите целое число: ";
				}

				Node* temp = list.head;
				int currentIndex = 0, count = 0;
				int* indexes = new int[size];

				auto start = high_resolution_clock::now();

				while (temp) {
					if (temp->data == userNumber) {
						*indexes = currentIndex;
						indexes++;
						count++;
					}
					currentIndex++;
					temp = temp->next;
				}

				auto end = high_resolution_clock::now();
				auto time = duration_cast<nanoseconds>(end - start).count();

				if (count == 0) {
					system("cls");
					cout << "Элемент не найден.\n";
					delete[] indexes;
					break;
				}
				indexes = indexes - count;
				list.print_list(indexes, count);

				cout << "\nИндексы: ";
				for (int j = 0; j < count; j++) {
					cout << *(indexes + j) << " ";
				}
				cout << "\nВремя на поиск: " << time << " наносекунд\n";
				delete[] indexes;
			}
			else {
				system("cls");
			}

			break;
		}
		case ACTION_SWAP_MENUS: {
			system("cls");
			dynamic_array();
			break;
		}

		case ACTION_TURN_OFF: {
			cout << "Работа завершена.";
			list.delete_list();
			return false;
		}
		default:
			system("cls");
			error();
		}
	}
	return 0;
}