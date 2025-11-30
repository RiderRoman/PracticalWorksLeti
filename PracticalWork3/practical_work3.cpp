/*

													*       ***    ****     ******
													*      *   *   *   *         *
													*      *****   ****     ******
													*      *   *   *   *         *
													*****  *   *   ****     ******                                                                                                                      */
#include <iostream>
#include <windows.h>

HANDLE hStdout;

using namespace std;
#undef max
#define BRIGHT_WHITE   "\033[97m"
#define BRIGHT_BLACK "\033[90m"

int yOffset = 0;
int xOffset = 0;

void problem() { // mistake cin
	system("cls");
	cout << "Неверный ввод. Попробуйте еще раз!\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return;
}

void print_num(int x, int y, int number) {
	COORD destCoord;

	destCoord.X = x * 4 + xOffset;
	destCoord.Y = y + yOffset;
	SetConsoleCursorPosition(hStdout, destCoord);
	Sleep(50);
	cout << number;
}

void print_num2(int x, int y, int number) {
	COORD destCoord;

	destCoord.X = x * 4 + xOffset;
	destCoord.Y = y + yOffset;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << number;
}

void print_word(int x, int y, char word) {
	COORD destCoord;

	destCoord.X = x * 3 + xOffset;
	destCoord.Y = y + yOffset;
	SetConsoleCursorPosition(hStdout, destCoord);

	cout << word;
}

void fill_massive(int* arr, int N, bool yesornot, bool yesornotfill, bool yesornotcolor, bool another_cout) {
	int* end = arr + N * N - 1;
	int j = 0;
	if (yesornotfill) for (int* ptr = arr, i = 0; ptr <= end; ptr++, i++) { *ptr = rand() % (N * N) + 1; }
	if (yesornot) for (int* ptr = arr, i = 0; ptr <= end; ptr++, i++) { print_num(i % N, i / N, *ptr); }
	if (another_cout) for (int* ptr = arr, i = 0; ptr <= end; ptr++, i++) { print_num2(i % N, i / N, *ptr); }
}

void snake_print(int* arr, int N) { // TASK1 option 2
	int* ptr = arr;
	xOffset = 20;
	yOffset = 0;
	short right_side = 0, count_for_ptr_up = -1;
	short for_count = 0; // счетчик форов

	while (for_count <= N * 2 - 1) {
		for (int k = 0; k < N; k++) { // вниз 
			print_num(N + count_for_ptr_up, k, *(ptr + right_side + N * k));
		}
		for_count += 2;
		count_for_ptr_up += 2;
		if (for_count >= N * 2 - 1) break;
		for (int k = N - 1; k >= 0; k--) { // наверх
			print_num(N + right_side, k, *(ptr + count_for_ptr_up + N * k));
		}
		for_count += 2;
		right_side += 2;
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n";
}

void spiral_print(int* arr, int N) { // TASK1 option 1
	int* ptr = arr;
	short for_count = 0;
	yOffset = 1;
	xOffset = 0;
	short count_one = 0, count_two_with_one = 1, count_right_one = -1, count_down = 2, ptr_dealer = 0;

	while (for_count <= N * N) {
		for (int k = 0, i = count_one; k < N - count_two_with_one; k++, i++) { // вправо
			print_num(k + count_one, count_right_one, *(ptr + N * ptr_dealer + i));
		}
		count_one++;
		int save = 0;
		for (int k = 1; k < N - (count_two_with_one - 1); k++) { // вниз
			print_num(N - count_one, k - count_down, *(ptr + (k + count_one - 1) * N - count_one));
			save = k;
		}

		for (int k = N - (count_two_with_one + 1), i = count_one; k >= 0; k--, i++) { // влево
			print_num(k + count_one, count_right_one + save, *(ptr + N * (N - (count_one - 1)) - i));
		}

		for (int k = N - count_one, i = 1; k >= count_one; k--, i++) { // наверх
			print_num(count_one - 1, (count_right_one + save) - i + 1, *(ptr + N * k + (count_one - 1)));
		}

		count_two_with_one += 2; count_right_one++; count_down--; ptr_dealer++;
		for_count += 4;
		if (for_count >= N * N) break;
	}
}

void rotate_blocks(int* arr, int* copyarr, int N) { // TASK2 option 1
	int* end = copyarr + N * N - 1;

	for (int* copyptr = copyarr, *ptr = arr; copyptr <= end; copyptr++, ptr++) { *copyptr = *ptr; }

	int count_N = 0;
	int* ptr = arr; int* copyptr = copyarr;


	for (int j = 0; j < N / 2; j++) {
		for (int k = 0; k < N / 2; k++) { // TOP RIGHT NUMBER -> TOP LEFT NUMBERS
			*(ptr + N / 2 + k + N * count_N) = *(copyptr + k + N * j);
		}
		count_N++;
	}
	count_N = 0;
	for (int j = 0; j < N / 2; j++) {
		for (int k = 0; k < N / 2; k++) { // BOTTOM LEFT NUMBERS -> BOTTOM RIGHT NUMBERS
			*(ptr + k + N * ((N - 1) - j)) = *(copyptr + k + N / 2 + N * (N - (j + 1)));
		}
	}

	for (int j = 0; j < N / 2; j++) {
		for (int k = 0; k < N / 2; k++) { // TOP LEFT NUMBERS -> BOTTOM LEFT NUMBERS
			*(ptr + k + N * j) = *(copyptr + k + (N * (N / 2) + N * j));
		}
	}
	for (int j = 0; j < N / 2; j++) {
		for (int k = 0; k < N / 2; k++) { // BOTTOM RIGHT NUMBERS -> TOP RIGHT NUMBERS
			*(ptr + k + N / 2 + N * (N - (N / 2 - j))) = *(copyptr + N / 2 + k + N * count_N);
		}
		count_N++;
	}
}

void from_bottom_to_top(int* copyarr, int* copyarr2, int N) { // TASK2 option 3
	int* end = copyarr2 + N * N - 1;

	for (int* copyptr2 = copyarr2, *copyptr = copyarr; copyptr2 <= end; copyptr2++, copyptr++) { *copyptr2 = *copyptr; }

	int* copyptr = copyarr; int* copyptr2 = copyarr2;

	for (int j = 0; j < N / 2; j++) { // BOTTOM NUMBERS -> TOP NUMBERS
		for (int k = 0; k < N / 2; k++) {
			*(copyptr + k + N * (N - (N / 2 - j))) = *(copyptr2 + k + N * j);
			*(copyptr + k + N / 2 + N * (N - (N / 2 - j))) = *(copyptr2 + k + N / 2 + N * j);
		}
	}

	for (int j = 0; j < N / 2; j++) { // TOP NUMBERS -> BOTTOM NUMBERS
		for (int k = 0; k < N / 2; k++) {
			*(copyptr + k + N * j) = *(copyptr2 + k + N * (N - (N / 2 - j)));
			*(copyptr + k + N / 2 + N * j) = *(copyptr2 + k + N / 2 + N * (N - (N / 2 - j)));
		}
	}
}

void arrows(int* copyarr2, int* copyarr3, int N) { // TASK2 option 2
	int* end = copyarr3 + N * N - 1;

	for (int* copyptr3 = copyarr3, *copyptr2 = copyarr2; copyptr3 <= end; copyptr3++, copyptr2++) { *copyptr3 = *copyptr2; }

	int* copyptr2 = copyarr2; int* copyptr3 = copyarr3;

	for (int j = 0; j < N / 2; j++) { // TOP LEFT NUMBERS <-> BOTTOM RIGHT NUMBERS
		for (int k = 0; k < N / 2; k++) {
			*(copyptr2 + k + N * j) = *(copyptr3 + k + N / 2 + (N * (N - (N / 2) + j)));
			*(copyptr2 + k + N / 2 + (N * (N - (N / 2) + j))) = *(copyptr3 + k + N * j);
		}
	}

	for (int j = 0; j < N / 2; j++) { // BOTTOM LEFT NUMBERS <-> TOP RIGHT NUMBERS
		for (int k = 0; k < N / 2; k++) {
			*(copyptr2 + k + (N * (N - (N / 2) + j))) = *(copyptr3 + k + N / 2 + N * j);
			*(copyptr2 + k + N / 2 + N * j) = *(copyptr3 + k + (N * (N - (N / 2) + j)));
		}
	}
}

void from_left_to_right(int* copyarr3, int* copyarr4, int N) { // TASK2 option 4
	int* end = copyarr4 + N * N - 1;

	for (int* copyptr4 = copyarr4, *copyptr3 = copyarr3; copyptr4 <= end; copyptr4++, copyptr3++) { *copyptr4 = *copyptr3; }

	int* copyptr3 = copyarr3; int* copyptr4 = copyarr4;

	for (int j = 0; j < N / 2; j++) {
		for (int k = 0; k < N / 2; k++) { // TOP NUMBERS left -> right
			*(copyptr3 + k + N * j) = *(copyptr4 + k + N / 2 + N * j);
			*(copyptr3 + k + N / 2 + N * j) = *(copyptr4 + k + N * j);
		}
	}

	for (int j = 0; j < N / 2; j++) { // BOTTOM NUMBERS left -> right
		for (int k = 0; k < N / 2; k++) {
			*(copyptr3 + k + N * (N - (N / 2) + j)) = *(copyptr4 + k + N / 2 + N * (N - (N / 2) + j));
			*(copyptr3 + k + N / 2 + N * (N - (N / 2) + j)) = *(copyptr4 + k + N * (N - (N / 2) + j));
		}
	}
}

void shaker_sort(int* arr, int N) { // TASK3
	int* left = arr;
	int* right = arr + N * N - 1;
	while (left <= right) {
		for (int* ptr = left; ptr < right; ptr++) {
			if (*(ptr) > *(ptr + 1)) swap(*(ptr), *(ptr + 1));
		}
		right--;
		for (int* ptr = right; ptr > left; ptr--) {
			if (*(ptr) < *(ptr - 1)) swap(*(ptr), *(ptr - 1));
		}
		left++;
	}
}

void bubble_sort(int* arr, int N) {
	int* end = arr + N * N - 1;
	for (int* ptr = arr; ptr <= end - 1; ptr++) {
		for (int* ptr2 = arr, i = 0; ptr2 <= end - i - 1; ptr2++) {
			if (*ptr2 > *(ptr2 + 1)) swap(*ptr2, *(ptr2 + 1));
		}
	}
}

//void proizvedenie(int* arr, int* copyarr, int* norm_arr, int N, int N_copy) {
//	int* end = arr + N * N - 1;
//	int* end_copy = copyarr + N * N - 1;
//	int summa = 0;
//	int* ptr = arr;
//	int* ptr2 = copyarr;
//	int* ptr3 = norm_arr;
//	for (int j = 0; j < N; j++) {
//		for (int k = 0; k < N; k++) {
//			for (int i = 0; i < N; i++) {
//				summa += *(ptr + i + N * k) * *(ptr2 + i + N * i);
//			}
//			*ptr3 = summa;
//			ptr3++;
//		}
//		
//	}
//	
//}

void moves_with_number(int* arr, int N, long long num, short choice) { // TASK4
	int* end = arr + N * N - 1;
	if (choice == 1) { for (int* ptr = arr; ptr <= end; ptr++) { *ptr = *ptr - num; } }
	else if (choice == 2) { for (int* ptr = arr; ptr <= end; ptr++) { *ptr = *ptr + num; } }
	else if (choice == 3) { for (int* ptr = arr; ptr <= end; ptr++) { *ptr = *ptr * num; } }
	else if (choice == 4) { for (int* ptr = arr; ptr <= end; ptr++) { *ptr = *ptr / num; } }
	else return;
}

void user_choice(int* arr, int N, long long num) {
	short choice = 0;
	cin >> choice;
	xOffset = 0; yOffset = 1;
	switch (choice) {
	case 1:
		system("cls");
		cout << "Было:\t\t\t\t" << "Стало:";
		fill_massive(arr, N, 0, 0, 0, 1);
		moves_with_number(arr, N, num, 1);
		xOffset = 40;
		fill_massive(arr, N, 0, 0, 0, 1);
		break;
	case 2:
		system("cls");
		cout << "Было:\t\t\t\t" << "Стало:";
		fill_massive(arr, N, 0, 0, 0, 1);
		moves_with_number(arr, N, num, 2);
		xOffset = 40;
		fill_massive(arr, N, 0, 0, 0, 1);
		break;
	case 3:
		system("cls");
		cout << "Было:\t\t\t\t" << "Стало:";
		fill_massive(arr, N, 0, 0, 0, 1);
		moves_with_number(arr, N, num, 3);
		xOffset = 40;
		fill_massive(arr, N, 0, 0, 0, 1);
		break;
	case 4:
		system("cls");
		cout << "Было:\t\t\t\t" << "Стало:";
		fill_massive(arr, N, 0, 0, 0, 1);
		moves_with_number(arr, N, num, 4);
		xOffset = 40;
		fill_massive(arr, N, 0, 0, 0, 1);
		break;
	default:
		problem();
		return;
	}
}

int main_menu(int* arr, int* copyarr, int* copyarr2, int* copyarr3, int* copyarr4, int N) { // arrays for task 2! ()
	short select = 0, n = 0, count = 0;
	while (true) {
		cout << "1 - Заполнить матрицу\t\t\t\t Размер:  " << N << "x" << N << endl
			<< "2 - Поменять местами блоки матрицы\n"
			<< "3 - Сортировка матрицы\n"
			<< "4 - Действия с числом\n"
			<< "5 - Завершить работу программы\n"
			<< "Выберите действие: ";
		cin >> select;
		switch (select) {
			case 1: {
				system("cls");
				fill_massive(arr, N, 0, 1, 0, 0);
				spiral_print(arr, N);
				snake_print(arr, N);
				break;
			}
			case 2: {
				system("cls");
				cout << "Исходная матрица:\t\t\t\t Изменённая: ";
				yOffset = 2; xOffset = 0;

				fill_massive(arr, N, 0, 0, 0, 1);

				rotate_blocks(arr, copyarr, N); // option a
				from_bottom_to_top(copyarr, copyarr2, N); // option c
				arrows(copyarr2, copyarr3, N); // option b
				from_left_to_right(copyarr3, copyarr4, N); // option d

				xOffset = 36;
				fill_massive(arr, N, 0, 0, 0, 1);
				print_word(N / 2, N, 'A');
				yOffset = 14;
				fill_massive(copyarr2, N, 0, 0, 0, 1);
				print_word(N / 2, N, 'B');

				yOffset = 2;
				xOffset = 68;
				fill_massive(copyarr, N, 0, 0, 0, 1);
				print_word(N / 2, N, 'C');
				yOffset = 14;
				fill_massive(copyarr3, N, 0, 0, 0, 1);
				print_word(N / 2, N, 'D');

				cout << "\n\n\n\n";
				break;
			}
			case 3:
				system("cls");
				cout << "Неотсортированная матрица:\t\t" << "Отсортированная матрица:";
				yOffset = 2; xOffset = 0;
				fill_massive(arr, N, 0, 0, 0, 1);
				bubble_sort(arr, N);
				xOffset = 40;
				fill_massive(arr, N, 0, 0, 0, 1);
				cout << "\n\n";
				break;
			case 4: {
				system("cls");
				xOffset = 0; yOffset = 0;
				cout << "Введите число: ";
				long long number;
				if (!(cin >> number)) problem();
				cout << "1 - Уменьшить каждый эл-т на число\n"
					<< "2 - Увеличить каждый эл-т на число\n"
					<< "3 - Умножить каждый эл-т на число\n"
					<< "4 - Разделить каждый эл-т на число\n\n"
					<< "Выберите действие: ";
				user_choice(arr, N, number);
				cout << "\n\n";
				break;
			}
			case 5: {
				cout << "Работа завершена\n";
				return false;
				break;
			}
			/*case 6:
				system("cls");
				
				xOffset = 0; yOffset = 0;

				fill_massive(arr, N, 1, 1, 0, 0);
				xOffset = 30; yOffset = 0;
				

				fill_massive(arr, N, 1,0, 0, 0);
				
				xOffset = 30; yOffset = 10;
				fill_massive(copyarr2, N, 0, 1, 0, 0);
				proizvedenie(arr, copyarr, copyarr2, N, N);
				fill_massive(copyarr2, N, 1, 0, 0, 0);

				break;*/
			default: {
				problem();
			}
		}
	}
}

int main() {
	srand(time(0));
	setlocale(LC_ALL, "RU");
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int altf4 = true;
	while (altf4) {
		int n;
		cout << "Перед началом работы программы необходимо ввести порядок матрицы! (Введите 6,8 или 10): ";
		cin >> n;
		if (n == 6) {
			system("cls");
			int const N = 6;
			int arr[N][N]; int copyarr[N][N]; int copyarr2[N][N]; int copyarr3[N][N]; int copyarr4[N][N];
			
			while (altf4) {
				altf4 = main_menu(&arr[0][0], &copyarr[0][0], &copyarr2[0][0], &copyarr3[0][0], &copyarr4[0][0], N);
			}
		}
		else if (n == 8) {
			system("cls");
			int const N = 8;
			int arr[N][N]; int copyarr[N][N]; int copyarr2[N][N]; int copyarr3[N][N]; int copyarr4[N][N];
			
			while (altf4) {
				altf4 = main_menu(&arr[0][0], &copyarr[0][0], &copyarr2[0][0], &copyarr3[0][0], &copyarr4[0][0], N);
			}
		}
		else if (n == 10) {
			system("cls");
			int const N = 10;
			int arr[N][N]; int copyarr[N][N]; int copyarr2[N][N]; int copyarr3[N][N]; int copyarr4[N][N];
			
			while (altf4) {
				altf4 = main_menu(&arr[0][0], &copyarr[0][0], &copyarr2[0][0], &copyarr3[0][0], &copyarr4[0][0], N);
			}
		}
		else {
			problem();
		}
	}
	return 0;
}