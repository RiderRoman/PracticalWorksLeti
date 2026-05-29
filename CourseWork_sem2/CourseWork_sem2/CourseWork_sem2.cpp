#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <chrono>
#undef max

using namespace std;
using namespace chrono;

#define MAIN_MENU 1
#define MANAGEMENT_MENU 2
#define BYPASS_MENU 3

#define ACTION_TURN_OFF 0
#define ACTION_CREATE_TREE 1
#define ACTION_CREATE_USER_TREE 2
#define ACTION_CREATE_FILE_TREE 3
#define ACTION_PRINT_TREE 4
#define ACTION_MANAGEMENT_TREE 5
#define ACTION_BYPASS_TREE 6
#define ACTION_GENERATE_TASK 7

#define ACTION_INSERT_NUMBER 1
#define ACTION_DELETE_NUMBER 2
#define ACTION_FIND_NUMBER 3

#define ACTION_STRAIGHT_BYPASS 1
#define ACTION_REVERSE_BYPASS 2
#define ACTION_WIDTH_BYPASS 3

class binary_tree {
private:
	struct Tree {
		int data;
		Tree* left;
		Tree* right;

		Tree(int value) : data(value), left(nullptr), right(nullptr) {}
	};

	Tree* root;

	Tree* insert_node(Tree* node, int value) {
		if (node == nullptr) {
			return new Tree(value);
		}
		if (value < node->data) {
			node->left = insert_node(node->left, value);
		}
		else if (value > node->data) {
			node->right = insert_node(node->right, value);
		}
		return node;
	}

	void print_tree_rec(Tree* node, int space, ostream& out) {
		if (node == nullptr) {
			return;
		}

		space += 3;
		print_tree_rec(node->right, space, out);

		for (int i = 3; i < space; i++) out << "   ";

		if (space > 3) out << ".--> " << node->data << "\n";
		else out << "Корень: " << node->data << "\n";
		
		print_tree_rec(node->left, space, out);
	}

	Tree* find_min(Tree* node) {
		while (node && node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	bool find_node(Tree* node, int value) {
		if (node == nullptr) return false;
		
		if (value == node->data) {
			cout << "Элемент найден.\n";
			return true;
		}
		if (value < node->data) {
			return find_node(node->left, value);
		}
		return find_node(node->right, value);
	}

	Tree* delete_node(Tree* node, int value, bool& success) {
		if (node == nullptr) {
			success = false;
			return nullptr;
		}

		if (value < node->data) {
			node->left = delete_node(node->left, value, success);
		}
		else if (value > node->data) {
			node->right = delete_node(node->right, value, success);
		}
		else {
			success = true;

			if (node->left == nullptr) {
				Tree* temp = node->right;
				delete node;
				return temp;
			}
			else if (node->right == nullptr) {
				Tree* temp = node->left;
				delete node;
				return temp;
			}

			Tree* temp = find_min(node->right);
			node->data = temp->data;
			node->right = delete_node(node->right, temp->data, success);
		}
		return node;
	}

	void straight_bypass_rec(Tree* node) {
		if (node == nullptr) return;
		cout << node->data << " ";
		straight_bypass_rec(node->left);
		straight_bypass_rec(node->right);
	}

	void reverse_bypass_rec(Tree* node) {
		if (node == nullptr) return;
		reverse_bypass_rec(node->left);
		reverse_bypass_rec(node->right);
		cout << node->data << " ";
	}

	void destroy_tree(Tree* node) {
		if (node != nullptr) {
			destroy_tree(node->left);
			destroy_tree(node->right);
			delete node;
		}
	}

public:
	binary_tree() : root(nullptr) {}

	~binary_tree() {
		clear();
	}

	void clear() {
		destroy_tree(root);
		root = nullptr;
	}

	void insert(int value) {
		root = insert_node(root, value);
	}

	void print_tree() {
		if (root == nullptr) {
			cout << "Дерево пустое.\n\n";
			return;
		}

		print_tree_rec(root, 0, cout);
		cout << "\n";

		ofstream file("tree.txt");
		if (file.is_open()) {
			print_tree_rec(root, 0, file);
			file.close();
		}
		else cout << "Не удалось открыть файл.\n\n";
	}

	bool create_tree_from_file(const string& filename) {
		ifstream file(filename);

		if (!file.is_open()) {
			cout << "Не удалось открыть файл \"" << filename << "\".\n";
			return false;
		}

		clear();

		int value;
		int count = 0;

		while (file >> value) {
			insert(value);
			count++;
		}

		if (!file.eof()) {
			cout << "Ошибка при чтении файла.\n";
			clear();
			file.close();
			return false;
		}

		file.close();

		if (count == 0) {
			cout << "Файл \"" << filename << "\" не содержит элементов.\n";
			return false;
		}

		cout << "Дерево успешно создано из " << count << " элементов.\n\n";
		return true;
	}

	void create_random_tree(int count) {
		clear();
		auto start = high_resolution_clock::now();
		for (int i = 0; i < count; i++) {
			int random_value = (rand() % 199) - 99;
			insert(random_value);
		}
		auto end = high_resolution_clock::now();
		auto time = duration_cast<nanoseconds>(end - start).count();
		cout << "Дерево успешно создано из " << count << " элементов.\n";
		cout << "Время потраченное на создание: " << time << " наносекунд.\n";
	}

	bool create_user_tree(const string& input_str) {
		if (input_str.empty()) {
			cout << "Ошибка ввода, пустая строка.\n";
			return false;
		}

		stringstream ss(input_str);
		vector<int> numbers;
		int number;

		while (ss >> number) {
			numbers.push_back(number);
		}

		if (!ss.eof()) {
			cout << "Ошибка ввода, повторите ещё раз.\n";
			return false;
		}

		if (numbers.empty()) {
			cout << "Ошибка ввода, не найдено ни одного числа для создания дерева.\n";
			return false;
		}

		clear();
		auto start = high_resolution_clock::now();
		for (int val : numbers) {
			insert(val);
		}
		auto end = high_resolution_clock::now();
		auto time = duration_cast<nanoseconds>(end - start).count();

		cout << "Дерево успешно создано из " << numbers.size() << " элементов.\n";
		cout << "Время потраченное на создание: " << time << " наносекунд.\n";
		return true;
	}

	bool find(int value) {
		return find_node(root, value);
	}

	bool remove(int value) {
		bool success = false;

		auto start = high_resolution_clock::now();
		root = delete_node(root, value, success);
		auto end = high_resolution_clock::now();
		auto time = duration_cast<nanoseconds>(end - start).count();

		cout << "Время потраченное на удаление: " << time << " наносекунд.\n";
		return success;
	}

	void straight_bypass() {
		if (root == nullptr) {
			cout << "Дерево пустое.\n";
			return;
		}
		straight_bypass_rec(root);
		cout << "\n";
	}

	void reverse_bypass() {
		if (root == nullptr) {
			cout << "Дерево пустое.\n";
			return;
		}
		reverse_bypass_rec(root);
		cout << "\n";
	}

	void width_bypass() {
		if (root == nullptr) {
			cout << "Дерево пустое.\n";
			return;
		}

		queue<Tree*> q;
		q.push(root);

		while (!q.empty()) {
			Tree* current = q.front();
			q.pop();

			cout << current->data << " ";

			if (current->left != nullptr) {
				q.push(current->left);
			}
			if (current->right != nullptr) {
				q.push(current->right);
			}
		}
		cout << "\n";
	}

	void generate_task_system() {
		clear();

		const int task_size = 7;
		vector<int> task_numbers;
		for (int i = 0; i < task_size; i++) {
			int val = (rand() % 199) - 99;
			task_numbers.push_back(val);
			insert(val);
		}

		ofstream task_file("outputTask.txt");
		if (task_file.is_open()) {
			task_file << "Постройте бинарное дерево поиска из следующих чисел:\n";
			for (int val : task_numbers) {
				task_file << val << " ";
			}
			task_file << "\n\n2. Выполните прямой обход полученного дерева.\n";
			task_file.close();
		}

		stringstream correct_stream;

		struct Local {
			static void get_straight(Tree* node,  stringstream& ss) {
				if (node == nullptr) return;
				ss << node->data << " ";
				get_straight(node->left, ss);
				get_straight(node->right, ss);
			}
		};
		Local::get_straight(root, correct_stream);
		string correct_answer = correct_stream.str();

		ofstream key_file("outputKey.txt");
		if (key_file.is_open()) {
			key_file << correct_answer;
			key_file.close();
		}

		cout << "Числа для построения дерева: ";
		for (int val : task_numbers) cout << val << " ";
		cout << "\nВведите через пробел результат прямого обхода дерева:\n";

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		string user_answer;
		getline(cin, user_answer);
		if (!user_answer.empty() && user_answer.back() != ' ') {
			user_answer += " ";
		}

		ofstream ans_file("outputAns.txt");
		if (ans_file.is_open()) {
			ans_file << user_answer;
			ans_file.close();
			cout << "\nВаш ответ был успешно записан.\n";
		}

		if (user_answer == correct_answer) {
			cout << "Ответ верный.\n\n";
		}
		else {
			cout << "Ответ неверный.\n";
			cout << "Правильный ответ: " << correct_answer << "\n\n";
		}
	}


};

void clear_screen() {
#ifdef _WIN32
	 system("cls");
#else
	 system("clear");
#endif
}

void error() {
	clear_screen();
	cout << "Ошибка ввода, повторите ещё раз.\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return;
}

void print_menus(int variant) {
	if (variant == MAIN_MENU) {
		cout << ACTION_CREATE_TREE << " - Создать дерево\n"
			<< ACTION_CREATE_USER_TREE << " - Создать дерево со своими числами\n"
			<< ACTION_CREATE_FILE_TREE << " - Создать дерево с помощью файла\n"
			<< ACTION_PRINT_TREE << " - Вывести дерево\n"
			<< ACTION_MANAGEMENT_TREE << " - Взаимодейтсвие с элементами (вставка, удаление и поиск)\n"
			<< ACTION_BYPASS_TREE << " - Обход дерева\n"
			<< ACTION_GENERATE_TASK << " - Случайное задание\n"
			<< ACTION_TURN_OFF << " - Завершить работу\n\n"
			<< "Выберите действие: ";
	}
	if (variant == MANAGEMENT_MENU) {
		cout << ACTION_INSERT_NUMBER << " - Вставить элемент в дереве\n"
			<< ACTION_DELETE_NUMBER << " - Удалить элемент из дерева\n"
			<< ACTION_FIND_NUMBER << " - Найти элемент в дереве\n"
			<< ACTION_TURN_OFF << " - Назад\n\n"
			<< "Выберите действие: ";
	}
	if (variant == BYPASS_MENU) {
		cout << ACTION_STRAIGHT_BYPASS << " - Прямой обход\n"
			<< ACTION_REVERSE_BYPASS << " - Обратный обход\n"
			<< ACTION_WIDTH_BYPASS << " - Обход в ширину\n"
			<< ACTION_TURN_OFF << " - Назад\n\n"
			<< "Выберите действие: ";
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RU");
	srand(time(NULL));

	int choice = 0;
	int count_of_creatures = 0;
	binary_tree tree;

	while (true) {
		print_menus(MAIN_MENU);

		while (!(cin >> choice) || choice > 7 || choice < 0) {
			error();
			print_menus(MAIN_MENU);
		}

		switch (choice) {
			case ACTION_CREATE_TREE: {
				
				clear_screen();
				int count = 0;
				cout << "Введите количество элементов: ";

				while (!(cin >> count) || count < 0) {
					error();
					cout << "Введите количество элементов: ";
				}
				tree.create_random_tree(count);
				count_of_creatures++;
				break;
			}
			case ACTION_CREATE_USER_TREE: {
				clear_screen();
				string input;
				cout << "Введите числа через пробел: ";
				getline(cin >> ws, input);

				if (!(tree.create_user_tree(input))) {
					break;
				}

				system("pause");
				clear_screen();
				count_of_creatures++;
				break;
			}
			case ACTION_CREATE_FILE_TREE: {
				clear_screen();
				string input;
				cout << "Введите путь к файлу (элементы в файле должны идти строго через перевод строки): ";
				getline(cin >> ws, input);

				tree.create_tree_from_file(input);

				system("pause");
				clear_screen();
				count_of_creatures++;
				break;
			}
			case ACTION_PRINT_TREE: {
				if (count_of_creatures < 1) {
					cout << "Создайте дерево\n";
					system("pause");
					clear_screen();
					break;
				}
				clear_screen();

				tree.print_tree();
				break;
			}
			case ACTION_MANAGEMENT_TREE: {
				if (count_of_creatures < 1) {
					cout << "Создайте дерево\n";
					system("pause");
					clear_screen();
					break;
				}
				clear_screen();

				while (true) {
					int management_choice = 0;
					print_menus(MANAGEMENT_MENU);

					while (!(cin >> management_choice) || management_choice > 3 || management_choice < 0) {
						error();
						print_menus(MANAGEMENT_MENU);
					}

					if (management_choice == 0) {
						clear_screen();
						break;
					}

					switch (management_choice) {
						case ACTION_INSERT_NUMBER: {
							clear_screen();
							cout << "Введите число: ";
							int number = 0;
							while (!(cin >> number)) {
								error();
								cout << "Введите число: ";
							}

							auto start = high_resolution_clock::now();
							tree.insert(number);
							auto end = high_resolution_clock::now();
							auto time = duration_cast<nanoseconds>(end - start).count();

							cout << "Время потраченное на удаление: " << time << " наносекунд.\n";
							tree.print_tree();
							system("pause");
							clear_screen();
							break;
						}
						case ACTION_DELETE_NUMBER: {
							clear_screen();
							cout << "Введите число: ";
							int number = 0;
							while (!(cin >> number)) {
								error();
								cout << "Введите число: ";
							}

							tree.remove(number);
							tree.print_tree();

							system("pause");
							clear_screen();
							break;
						}
						case ACTION_FIND_NUMBER: {
							clear_screen();
							cout << "Введите число: ";
							int number = 0;
							while (!(cin >> number)) {
								error();
								cout << "Введите число: ";
							}

							auto start = high_resolution_clock::now();							
							tree.find(number);
							auto end = high_resolution_clock::now();
							auto time = duration_cast<nanoseconds>(end - start).count();
							cout << "Время потраченное на поиск: " << time << " наносекунд.\n";
							tree.print_tree();

							system("pause");
							clear_screen();
							break;
						}
					}
				}
				break;
			}
			case ACTION_BYPASS_TREE: {
				if (count_of_creatures < 1) {
					cout << "Создайте дерево\n";
					system("pause");
					clear_screen();
					break;
				}
				clear_screen();

				while (true) {
					int bypass_choice = 0;
					print_menus(BYPASS_MENU);

					while (!(cin >> bypass_choice) || bypass_choice > 3 || bypass_choice < 0) {
						error();
						print_menus(BYPASS_MENU);
					}

					if (bypass_choice == 0) {
						clear_screen();
						break;
					}

					switch (bypass_choice) {
						case ACTION_STRAIGHT_BYPASS: {
							clear_screen();
							cout << "Прямой обход:\n";
							tree.straight_bypass();
							cout << "\n";
							system("pause");
							clear_screen();
							break;
						}
						case ACTION_REVERSE_BYPASS: {
							clear_screen();
							cout << "Обратный обход:\n";
							tree.reverse_bypass();
							cout << "\n";
							system("pause");
							clear_screen();
							break;
						}
						case ACTION_WIDTH_BYPASS: {
							clear_screen();
							cout << "Обход в ширину:\n";
							tree.width_bypass();
							cout << "\n";
							 system("pause");
							clear_screen();
							break;
						}
					}
				}
				break;
			}
			case ACTION_GENERATE_TASK: {
				clear_screen();

				tree.generate_task_system();
				system("pause");
				clear_screen();
				break;
			}
			case ACTION_TURN_OFF: {
				return false;
			}
			default:
				error();
				break;
		}
	}
}