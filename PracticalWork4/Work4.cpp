/*													*       ***    ****			*    *
													*      *   *   *   *		*    *
													*      *****   ****			******
													*      *   *   *   *			 *
													*****  *   *   ****				 *																															*/                  

#include <iostream>
#include <limits>
using namespace std;

void problem() { // mistake cin
	system("cls");
	cout << "Неверный ввод. Попробуйте еще раз!\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

#include <fstream>

void delete_symbol(char* arr, int index, int &N) {
	char* end = arr + N - 1;
	for (char* ptr = arr + index; ptr <= end; ptr++) { *ptr = *(ptr + 1); }
	N--;
}

int first_word(char* arr, int& N) {
	char* end = arr + N - 1;
	int index = 0;
	char* ptr = arr;
	while (ispunct(*ptr)) {
		index++;
		ptr++;
	}
	return index;
}

int count_words(char* arr, int N, int indexx, bool flag) {
	int count = 0, index = 0;
	char* end = arr + N - 1;
	if (flag) {
		for (char* ptr = arr; ptr <= end; ptr++) {
			if (ispunct(*ptr) || *ptr == ' ') {
				if (index > 0) {
					count++;
					index = 0;
				}
			}
			else index++;
		}
		return count;
	}
	else if (!flag) {
		for (char* ptr = arr + indexx; ptr <= end; ptr++) {
			if (ispunct(*ptr) || *ptr == ' ') {
				if (index > 0) {
					return index;
				}
			}
			else index++;
		}
	}
	
}

int fix_points(char* arr, int& N) {
	int index = first_word(arr, N);
	for (int i = 0 + index; i < N; i++) {
		if (arr[i] == '.') {
			int point = 1;
			int j = i + 1;
			while (arr[j] == '.') {
				point++;
				j++;
			}

			if (point == 3) {
				i += 2;
				continue;
			}
			else if ((point >= 4 || point == 2)) {
				int k = 1;
				for (int b = i + 1; b < i + point; b++) {
					arr[b] = arr[b + point - k];
					k++;
				}
				i--;
				continue;
			}
		}
	}
	return false;
}

void fix_all_text(char* arr, int &N) { 
	char* end = arr + N - 1;
	int index = 0;
	int first = first_word(arr, N);
	char* ptr2 = arr;
	*(arr + first) = toupper(*(arr + first));
	for (char* ptr = arr; ptr <= end; ptr++) {
		index = 0;
		if (ptr != arr && !ispunct(*ptr)) *ptr = tolower(*ptr);

		for (ptr2 = arr; ptr2 <= end; ptr2++) {
			++index;
			if (ispunct(*arr)) {
				delete_symbol(arr, 0, N);
				char* end = arr + N - 1;
			}
			if (ispunct(*ptr2) && ispunct(*(ptr2 + 1)) && *ptr2 != '.') {
				delete_symbol(arr, index, N);
				char* end = arr + N - 1;
			}
			if (*ptr2 == '.' && ispunct(*(ptr2 + 1)) && *(ptr2 + 1) != '.') {
				delete_symbol(arr, index, N);
				char* end = arr + N - 1;
			}
			
			if (*ptr2 == ' ' && *(ptr2 + 1) == ' ') {
				delete_symbol(arr, index, N);
				char* end = arr + N - 1;
			}
			
		}

	}
	end = arr + N - 1;
	if (*end != '.') {
		N++;
		end = arr + N - 1;
		*end = '.';
	}
}
//sdfsdf!!!!??? sdfsdf. hello world... qwe.
void letters(char* arr, int &N, bool flag) {
	int index = 0;
	char* end = arr + N - 1;
	char copyarr[10], first_letter;
	int stop = count_words(arr, N, 0, 1), count_for_stop = 0;
	*arr = tolower(*arr);
	int indexes[50], ind_count = 0, count_letter_words = 0;
	bool possible = true;
	for (char* ptr = arr; ptr <= end; ptr++) {
		
		if (ispunct(*ptr) || *ptr == ' ' || ptr == end) {
			if (index > 0) {
				possible = true;
				indexes[ind_count] = index;
				ind_count++; // size for indexes

				if (!flag) { // Task4
					for (int i = 0; i < index; i++) {
						cout << copyarr[i];
						if (i == index - 1) cout << " ";
					}
					count_for_stop++;

					if (count_for_stop == stop) {
						cout << endl;
						for (int i = 0; i < ind_count; i++) {
							cout << indexes[i];
							for (int k = 0; k < indexes[i]; k++) { cout << " "; }
						}
					}
				}

				if (flag) { // Task 3
					for (int i = 1; i < index; i++) {
						if (copyarr[i] == first_letter) {
							if (possible) {
								count_letter_words++;
								for (int k = 0; k < index; k++) { cout << copyarr[k]; }
								possible = false;
								cout << " ";
							}
							break;
						}
					}
				}
				
				index = 0;
			}
		}
		else {
			if (index == 0) first_letter = *ptr;
			copyarr[index] = *ptr;
			index++;
		}
	}
	if (flag) {
		cout << "\n\nКол-во таких слов: " << count_letter_words << "\n";
		cout << "Кол-во слов в исходной последовательности: " << stop << "\n";
	}
	*arr = toupper(*arr);
}

int linear_search(char* arr, char* pattern, int& N, int& M) {
	for (char* ptr = arr; ptr <= arr + N - 1; ptr++) {
		int j = 0;
		if (*ptr == pattern[j]) {
			while (j <= (M - 1) && ptr <= arr + N - 1  && *ptr == pattern[j]) {
				ptr++;
				j++;
			}
			if (j == M) return true;
		}
	}
	return false;
}

int est(char* pattern, int M, char c) {
	for (char* ptr = pattern; ptr <= pattern + M - 1; ptr++) { if (*ptr == c) return true; }
	return false;
}

int boyer_moore(char* arr, char* pattern, int &N, int &M) {
	char* end = arr + N - 1;
	int ALPH = 256;
	int* shift = new int[ALPH];
	int count_letters = 1;
	for (int c = 0; c < ALPH; ++c)
		shift[c] = M;

	for (int i = 0; i < M; ++i) {
		unsigned char c = static_cast<unsigned char>(pattern[i]);
		shift[c] = max(1, M - i - 1);
	}

	for (char* ptr = arr + M - 1; ptr <= end;) {

		if (*ptr == pattern[M - count_letters]) {
			int j = M - count_letters;

			while (j >= 0 && ptr >= arr && pattern[j] == *ptr) {
				ptr--;
				count_letters++;
				j = M - count_letters;
			}
			ptr = ptr + (count_letters - 1);
			if ((count_letters - 1) == M) {
				return ptr - arr - M + 1;
			}
			else {
				if (est(pattern, M, *ptr)) { ptr += shift[(unsigned char)*ptr];  }
				else ptr += M;
			}
			count_letters = 1;
		}

		else {
			for (char* ptr2 = pattern; ptr2 <= pattern + M - 1; ptr2++) {
				if (*ptr2 == *ptr) {
					ptr += shift[(unsigned char)*ptr];
					break;
				}
				else if (ptr2 == pattern + M - 1) ptr += M;
			}
		}
	}
	return -1;
}

int enter(char* arr, int &N, char* copyarr) {
	int select;
	char* end = arr + N - 1;
	char* ptr = arr;
	int size = 0;
	char* ptr2 = copyarr;

	while (true) {
		cout << "1 - Ввести последовательность с клавиатуры\n"
			<< "2 - Ввести последовательность с файла\n\n"
			<< "Выберите операцию: ";
		cin >> select;
		switch (select) {
		case 1: {
			system("cls");
			cout << "Введите текст: ";
			cin.ignore();
			char symbol;
			while (cin.get(symbol)) {
				if (symbol == '\n') break;
				size++;
				*ptr = symbol;
				*ptr2 = symbol;
				ptr++;
				ptr2++;
			}
			int words = count_words(arr, N, 0, 1);
			int letters = 0;
			if (words <= 50) {
				for (int i = 0; i < words; i++) {
					letters = count_words(arr, N, letters, 0);
					if (letters <= 10) continue;
					else {
						cout << "Вы превысили максимально допустимый размер слова!\n" << "Размер слова: \x1b[31m" << letters << "\x1b[0m\nМаксимально допустимый размер: \x1b[32m" << 10 << "\x1b[0m\n\n";
						return 0;
					}
				}
				return size;

			}
			else {
				cout << "Вы превысили максимально допустимое количество слов!\n" << "Количество слов: \x1b[31m" << words << "\x1b[0m\nМаксимально допустимое количество: \x1b[32m" << 50 << "\x1b[0m\n\n";
				return 0;
			}
		}
		case 2: {
			system("cls");
			cin.ignore();
			char filename[100];
			cout << "Введите название файла: ";
			cin.getline(filename, 100);

			ifstream file(filename);
			if (!file.is_open()) {
				cout << "Нет такого файла\n\n";
				problem();
			}

			file.getline(arr, 502);
			file.close();

			int size = strlen(arr);
			ptr = arr;
			for (ptr2 = copyarr; ptr2 <= copyarr + size - 1; ptr2++, ptr++) { *ptr2 = *ptr; }
			int words = count_words(arr, size, 0, 1);
			int letters = 0;
			if (words <= 50) {
				for (int i = 0; i < words; i++) {
					letters = count_words(arr, size, letters, 0);
					if (letters <= 10) continue;
					else {
						cout << "Вы превысили максимально допустимый размер слова!\n" << "Размер слова: \x1b[31m" << letters << "\x1b[0m\nМаксимально допустимый размер: \x1b[32m" << 10 << "\x1b[0m\n\n";
						return 0;
					}
				}
				return size;
			}
			else {
				cout << "Вы превысили максимально допустимое количество слов!\n" << "Количество слов: \x1b[31m" << words << "\x1b[0m\nМаксимально допустимое количество: \x1b[32m" << 50 << "\x1b[0m\n\n";
				return 0;
			}
			
		}
		default:
			system("cls");
			problem();
		}
	}
}

int chronosphere(char* arr, char* copyarr, int N) {
	int size = 0;
	char* end = copyarr + N - 1;
	for (char* ptr = copyarr, *ptr2 = arr; ptr <= end; ptr++, ptr2++) {
		*ptr2 = *ptr;
		size++;
	}
	return size;
}

int main() {
	setlocale(LC_ALL, "RU");
	int N = 1000;
	int select;
	char arr[1000];
	char copyarr[1000];
	int size = enter(arr, N, copyarr);
	if (!size) return false;
	int copysize = size;

	char* end = arr + size - 1;
	char* end2 = copyarr + size - 1;
	
	while (true) {
		cout << "1 - Отредактировать последовательность\n"
			<< "2 - Вывести на экран слова последовательности, в которых первая буква слова встречается в этом слове еще раз\n"
			<< "3 - Вывести на экран количество символов в каждом слове исходной последовательности\n"
			<< "4 - Найти подстроку в последовательности\n"
			<< "5 - Завершить работу\n\n"
			<< "Выберите операцию: ";
		cin >> select;
		switch (select) {
		case 1:
			system("cls");
			cout << "Исходная последовательность:\n";
			end = arr + size - 1;
			for (char* ptr = arr; ptr <= end; ptr++) { cout << *ptr; }
			

			fix_points(arr, size);
			fix_all_text(arr, size);

			cout << "\n\nИзменённая последовательность:\n";
			end = arr + size - 1;
			for (char* ptr = arr; ptr <= end; ptr++) { cout << *ptr; }
			cout << endl << endl;
			size = chronosphere(arr, copyarr, copysize);
			break;
		case 2:
			system("cls");
			fix_points(arr, size);
			fix_all_text(arr, size);
			letters(arr, size, 1);
			cout << endl << endl;
			size = chronosphere(arr, copyarr, copysize);
			break;
		case 3:
			system("cls");
			letters(arr, size, 0);
			cout << endl << endl;
			size = chronosphere(arr, copyarr, copysize);
			break;
		case 4: {
			system("cls");
			int M = 0;
			char pattern[1000];
			char* ptr_patt = pattern;
			cout << "Максимальный размер подстроки: " << "\x1b[32m" << size << "\x1b[0m\n"
				<< "Введите подстроку: ";
			cin.ignore();
			char pattern_symbol;
			while (cin.get(pattern_symbol)) {
				if (pattern_symbol == '\n') break;
				M++;
				*ptr_patt = pattern_symbol;
				ptr_patt++;
			}
			if (M >= size) {
				system("cls");
				cout << "Вы превысили максимально допустимый размер подстроки!\n" << "Размер подстроки: \x1b[31m" << M << "\x1b[0m\nМаксимально допустимый размер: \x1b[32m" << size << "\x1b[0m\n\n";
				break;
			}
			int index_pattern = boyer_moore(arr, pattern, size, M);
			if (index_pattern != -1) {
				cout << "\n\nПодстрока была найдена.\nИндекс: " << index_pattern << endl;
				for (char* ptr = arr; ptr <= arr + size - 1; ptr++) {
					if ((ptr - arr) == index_pattern) {
						for (int k = 0; k < M; k++) {
							cout << "\x1b[32m" << *ptr << "\x1b[0m";
							ptr++;
						}
					}
					cout << *ptr;

				}
				cout << "\n\n";
			}
			else cout << "\n\nТакой подстроки нету.\n\n";
			break;
		}
		case 5:
			return false;
		default:
			system("cls");
			problem();
		}
	}
}