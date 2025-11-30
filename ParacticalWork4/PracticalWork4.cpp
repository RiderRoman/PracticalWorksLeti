#include <iostream>
#include <windows.h>

using namespace std;

void remove_space(char* arr, int& N, int index) {
	if (index < 0 || index >= N) return;
	char* end = arr + N - 1;
	for (char* ptr = arr + index; ptr <= end; ptr++) {
		*ptr = *(ptr + 1);
	}
	N--;
}

int search_punc(int* arr, int &N, int num) {
	int* end = arr + N - 1;
	for (int* ptr = arr; ptr <= end; ptr++) {
		if (num == *ptr) {
			return *ptr;
		}
	}
	return -1;
}

int search_register(int* arr, int N, int num, bool flag) {
	int* end = arr + N - 1;
	if (flag) { // if yes -> A - Z
		for (int* ptr = arr; ptr <= end - N / 2; ptr++) {
			if (num == *ptr) { return *ptr; }
		}
	}
	else {
		for (int* ptr = arr + N / 2 - 1; ptr <= end; ptr++) {
			if (num == *ptr) { return *ptr; }
		}
	}
	return -1;

}

void check_punctuation(char* arr, int* arr_punc, int &N, int N_punc) {
	char* end = arr + N - 1;
	
	for (char* ptr1 = arr; ptr1 <= end; ptr1++) {
		for (char* ptr2 = arr; ptr2 <= end; ptr2++) {
			int same_ASCII1 = static_cast<char>(*ptr2);
			int same_ASCII2 = static_cast<char>(*(ptr2 + 1));

			if (same_ASCII1 == search_punc(arr_punc, N_punc, same_ASCII1) && same_ASCII2 == search_punc(arr_punc, N_punc, same_ASCII2)) {
				remove_space(arr, N, (ptr2 - arr) + 1);
			}
			
		}
	}
}

void check_register(char* arr, int* arr_reg, int& N, int N_reg) {
	char* end = arr + N - 1;
	int first_symbol = static_cast<char>(*arr);
	int search_first_symbol = search_register(arr_reg, N_reg, first_symbol, 0);

	if (first_symbol == search_first_symbol) { *arr = static_cast<int>(first_symbol - 32); }

	for (char* ptr1 = arr + 1; ptr1 <= end; ptr1++) {
		for (char* ptr2 = arr + 1; ptr2 <= end; ptr2++) {
			int same_ASCII = static_cast<char>(*ptr2);
			int search_ASCII = search_register(arr_reg, N_reg, same_ASCII, 1);
			if (same_ASCII == search_ASCII) {
				*ptr2 = static_cast<int>(same_ASCII + 32);
			}
		}
	}
}

void check_space(char* arr, int& N) {
	char* end = arr + N - 1;
	for (char* ptr1 = arr; ptr1 <= end; ptr1++) {
		for (char* ptr = arr; ptr < end; ptr++) {
			if (*ptr == ' ' && *(ptr + 1) == ' ') {
				remove_space(arr, N, (ptr - arr) + 1);
				end = arr + N - 1;
			}
		}
	}

}




int main() {
	setlocale(LC_ALL, "RU");

	char PUNCT_CHARS[] = {' ', ',', ':','&', '.'};
	/*if (isupper(c)) c = tolower(c);*/

	int const N_punc = 32;
	int arr_punc[N_punc]; // fill punctuation array
	int* end_punc = arr_punc + N_punc - 1;
	for (int* ptr = arr_punc, i = 33; ptr <= end_punc; ptr++, i++) {
		*ptr = i;
	}

	int const N_reg = 52;
	int arr_reg[N_reg];
	int* end_reg = arr_reg + N_reg - 1;
	for (int* ptr = arr_reg, i = 65; ptr <= end_reg; ptr++, i++) {
		if (i <= 90) *ptr = i;
		else *ptr = i + 6;
	}

	int N = 1000; 
	char symbol; 
	char* arr = new char[N];
	char* ptr = arr;
	int i = 0;
	cout << "Введите текст: ";

	while (cin.get(symbol)) { // fill array
		if (symbol == '\n') break;
		i++;
		*ptr = symbol;
		ptr++;
	}


	check_register(arr, arr_reg, i, N_reg);
	check_space(arr, i);
	check_punctuation(arr, arr_punc, i, N_punc);

	char* end = arr + i - 1;
	cout << "\nВывод текста:\n\n";
	for (char* ptr = arr; ptr <= end; ptr++) {
		cout << *ptr;
	}
	return 0;
}