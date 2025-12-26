#include <iostream>
#include <cstdint>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <limits>
#include <windows.h>

HANDLE hStdout;


#undef max
#undef bind
#define BRIGHT_WHITE   "\033[97m"
#define BRIGHT_BLACK "\033[90m"

int yOffset = 0;
int xOffset = 0;

using namespace std;
using namespace chrono;

union BinF {
    uint32_t int_form;
    float number;
};
BinF binf;

union BinD {
    uint64_t int_form;
    double number;
};
BinD binD;

void problem() { // mistake cin
    system("cls");
    cout << "Неверный ввод. Попробуйте еще раз!\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
}

void PrintBinInt(int num) { // TASK2 WORK1
    cout << "\nРезультат: ";
    uint32_t mask = 1 << sizeof(int) * 8 - 1;
    for (int i = 0; i < sizeof(int) * 8; i++) {
        cout << ((num & mask) ? '1' : '0');
        if (i == 0 || i == 7) cout << " ";
        if (i > 7) {
            if ((i - 7) % 8 == 0) cout << " ";
        }
        mask >>= 1;
    }
    cout << "\n           ^ SIGN\n\n";
}

void PrintBinFloat(float num) { // TASK3 WORK1
    binf.number = num;
    cout << "\nРезультат: ";
    uint32_t mask = 1 << sizeof(float) * 8 - 1;
    for (int i = 0; i < sizeof(float) * 8; i++) {
        cout << ((binf.int_form & mask) ? '1' : '0');
        if (i == 0 || i == 8) cout << " ";
        if (i > 8) {
            if ((i - 8) % 8 == 0) cout << " ";
        }
        mask >>= 1;
    }
    cout << endl << setw(13) << "(S)" << "(---E--)" << " " << "(" << setfill('-') << setw(12) << "M" << setw(12) << ")" << setfill(' ') << "\n\n\n";
}

void PrintBinDouble(double num) { // TASK4 WORK1
    binD.number = num;
    cout << "\nРезультат: ";
    uint64_t mask = 1ULL << 63;
    for (int i = 0; i < 64; i++) {
        cout << ((binD.int_form & mask) ? '1' : '0');
        if (i == 0 || i == 11) cout << " ";
        if (i > 11) {
            if ((i + 1) % 8 == 0) cout << " ";
        }
        mask >>= 1;
    }
    cout << endl << setw(13) << "(S)" << "(----E----) " << "(" << setfill('-') << setw(29) << "M" << setw(28) << ")" << setfill(' ') << "\n\n\n";
}

void ReplaceBitsDouble() { //TASK5 WORK1
    short pos;
    bool bitVal;
    cout << "Введите позицию бита (0-63): ";
    cin >> pos;
    cout << "Введите значение бита (0-1): ";
    cin >> bitVal;

    if (bitVal) binD.int_form |= (1ULL << pos);
    else binD.int_form &= ~(1ULL << pos);

    PrintBinDouble(binD.number);
    cout << "Новое число: " << binD.number << endl << endl;
}

void ReplaceBitsFloat() { //TASK5 WORK1
    short pos;
    bool bitVal;
    cout << "Введите позицию бита (0-31): ";
    cin >> pos;
    cout << "Введите значение бита (0-1): ";
    cin >> bitVal;

    if (bitVal) binf.int_form |= (1 << pos);
    else binf.int_form &= ~(1 << pos);

    PrintBinFloat(binf.number);
    cout << "Новое число: " << binf.number << endl << endl;
}

void ReplaceBitsInt(int num) { //TASK5 WORK1
    short pos;
    bool bitVal;
    cout << "Введите позицию бита (0-31): ";
    cin >> pos;
    cout << "Введите значение бита (0-1): ";
    cin >> bitVal;

    if (bitVal) num |= (1 << pos);
    else num &= ~(1 << pos);

    PrintBinInt(num);
    cout << "Новое число: " << num << endl << endl;
}

bool MenuForReplace() { //menu
    short select = 0;
    while (true) {
        cout << "1 - Изменить двоичное представление\n"
            << "2 -" << "\x1b[32m" << " Готово" << "\x1b[0m\n\n"
            << "Выберите действие: ";
        cin >> select;
        /*if (problem() == 0) continue;*/
        switch (select) {
        case 1:
            return 1;
            break;
        case 2:
            system("cls");
            return false;
        default:
            problem();
        }
    }
}

int PracticalWork1() {
    short select = 0;
    int num_int = 0;
    double num_double = 0;
    float num_float = 0;
    while (true) {
        cout << "1 - Типы данных\n"
            << "2 - Двоичное представление int\n"
            << "3 - Двоичное представление float\n"
            << "4 - Двоичое представление double\n"
            << "5 - Назад\n"
            << "Выберите операцию: ";
        if (!(cin >> select)) problem();
        switch (select) {
        case 1:
            system("cls"); // задание 1
            cout << "int: " << sizeof(int) << " байт\n\n"
                << "short int: " << sizeof(short int) << " байт\n\n"
                << "long int: " << sizeof(long int) << " байт\n\n"
                << "float: " << sizeof(float) << " байт\n\n"
                << "double: " << sizeof(double) << " байт\n\n"
                << "long double: " << sizeof(long double) << " байт\n\n"
                << "char: " << sizeof(char) << " байт\n\n"
                << "bool: " << sizeof(bool) << " байт\n\n";
            break;
        case 2:
            system("cls");
            cout << "Введите целое число: ";
            if (!(cin >> num_int)) {
                problem();
                continue;
            }

            PrintBinInt(num_int);
            while (MenuForReplace() == 1) {
                ReplaceBitsInt(num_int);
            }
            break;
        case 3:
            system("cls");
            cout << "Введите число: ";
            if (!(cin >> num_float)) {
                problem();
                continue;
            }

            PrintBinFloat(num_float);
            while (MenuForReplace() == 1) {
                ReplaceBitsFloat();
            }
            break;
        case 4:
            system("cls");
            cout << "Введите число: ";
            if (!(cin >> num_double)) {
                problem();
                continue;
            }

            PrintBinDouble(num_double);
            while (MenuForReplace() == 1) {
                ReplaceBitsDouble();
            }
            break;
        case 5:
            system("cls");
            return false;
        default:
            system("cls");
            break;
        }
    }
}

void copy_array(int* arr, int* copyarr, int N) { for (int* ptr = arr, *ptr2 = copyarr; ptr <= arr + N - 1; ptr++, ptr2++) { *ptr = *ptr2; } }

int bubble_sort(int mas[], int n, bool yesornot) { // TASK2 WORK2
    auto time1 = high_resolution_clock::now();
    for (int t = 0; t < n - 1; t++) {
        for (int i = 0; i < n - t - 1; i++) { if (mas[i] > mas[i + 1]) swap(mas[i], mas[i + 1]); }
    }
    auto time2 = high_resolution_clock::now();
    auto end = duration_cast<nanoseconds>(time2 - time1).count();
    if (yesornot) for (int i = 0; i < 100; i++) { cout << mas[i] << " "; }
    return end;
}

int shaker_sort(int mas[], int n, bool yesornot) {
    auto time1 = high_resolution_clock::now();
    int left = 0, right = n - 1;
    while (left <= right) {
        for (int i = left; i < right; i++) {
            if (mas[i] > mas[i + 1]) swap(mas[i], mas[i + 1]);
        }
        right--;
        for (int i = right; i > left; i--) {
            if (mas[i] < mas[i - 1]) swap(mas[i], mas[i - 1]);
        }
        left++;
    }
    auto time2 = high_resolution_clock::now();
    auto end = duration_cast<nanoseconds>(time2 - time1).count();
    if (yesornot) for (int i = 0; i < n; i++) { cout << mas[i] << " "; }
    return end;
}

int insert_sort(int* mas, int n, int yesornot) {
    auto time1 = high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        int key = mas[i];
        int j = i - 1;
        while (j >= 0 && mas[j] > key) {
            mas[j + 1] = mas[j];
            j--;
        }
        mas[j + 1] = key;
    }
    auto time2 = high_resolution_clock::now();
    auto end = duration_cast<nanoseconds>(time2 - time1).count();
    if (yesornot) for (int i = 0; i < n; i++) { cout << mas[i] << " "; }
    return end;
}

int selection_sort(int* arr, int n, bool yesornot) {
    auto time1 = high_resolution_clock::now();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
    auto time2 = high_resolution_clock::now();
    auto end = duration_cast<nanoseconds>(time2 - time1).count();
    if (yesornot) for (int i = 0; i < n; i++) { cout << arr[i] << " "; }
    return end;
}

void quick_sort(int* arr, int begin, int end) {
    if (begin >= end) return;

    int left = begin;
    int right = end;
    int mid = arr[(left + right) / 2];

    while (left <= right) {
        while (arr[left] < mid) left++;
        while (arr[right] > mid) right--;

        if (left <= right) {
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    if (begin < right) quick_sort(arr, begin, right);
    if (left < end) quick_sort(arr, left, end);
}

int max_min(int mas[], int n, bool yesornot, bool sorted) { // TASK3 WORK2
    short maxi = mas[0], mini = mas[0];
    auto time1 = high_resolution_clock::now();
    if (!sorted) {
        for (short i = 1; i < n; i++) {
            if (mas[i] > maxi) maxi = mas[i];
            else if (mas[i] < mini) mini = mas[i];
        }
    }
    else {
        maxi = mas[n - 1];
        mini = mas[0];
    }
    auto time2 = high_resolution_clock::now();
    auto end = duration_cast<nanoseconds>(time2 - time1).count();
    if (yesornot == 1) {
        cout << "Минимальный элемент: " << mini << " Максимальный элемент: " << maxi << endl;
    }
    return end;
}

void mid(int mas[], int n) { // TASK4 WORK2
    bubble_sort(mas, n, 0);
    short maxi = mas[n - 1], mini = mas[0], count = 0, mid;
    mid = (maxi + mini) / 2;
    auto time1 = high_resolution_clock::now();
    for (short i = 0; i < n; i++) {
        if (mas[i] == mid) {
            count++;
            cout << "Индекс: " << i << " ";
        }
    }
    auto time2 = high_resolution_clock::now();
    auto end = duration_cast<nanoseconds>(time2 - time1).count();
    cout << "\nЧисло: " << mid;
    cout << "\n\nКол-во чисел равных среднему значению макс/мин: " << count;
    cout << "\n\nЗатраченное время на поиск: " << end << " наносекунд\n\n";
}

void user_min_num(int mas[], int n, int A) { // TASK5 WORK2
    bubble_sort(mas, n, 0);
    int i = 0;
    while (mas[i] < A) {
        i++;
    }
    cout << "\n\nКоличество элементов меньших вашему числу: " << "\x1b[32m" << i << "\x1b[0m" << endl;
}

void user_max_num(int mas[], int n, int B) { // TASK6 WORK2
    bubble_sort(mas, n, 0);
    int i = 99, count = 0;
    while (mas[i] > B) {
        count++;
        i--;
    }
    cout << "\n\nКоличество элементов больших вашему числу: " << "\x1b[32m" << count << "\x1b[0m" << endl;
}

int common_search(int mas[], int num, int n) { // TASK7 WORK2
    short find = 0;
    for (short i = 0; i < n; i++) {
        if (mas[i] == num) {
            find = mas[i];
            break;
        }
    }
    return find;
}

int binary_search(int mas[], int num, int i1, int i2) { // TASK7  WORK2
    if (i2 >= i1) {
        int i_mid = i1 + (i2 - i1) / 2;
        if (mas[i_mid] == num) return i_mid;
        if (mas[i_mid] > num) return binary_search(mas, num, i1, i_mid - 1);
        else return binary_search(mas, num, i_mid + 1, i2);
    }
    return -1;
}

void replace_index(int mas[], int n, int index1, int index2) { // TASK8 WORK2
    int count1 = 0;
    cout << "Было:\n";
    for (short i = 0; i < n; i++) {
        if (i == index1 || i == index2) {
            if (count1 < 2) {
                cout << "\x1b[32m" << mas[i] << "\x1b[0m" << " ";
                count1++;
            }
            else cout << mas[i] << " ";
        }
        else cout << mas[i] << " ";
    }
    count1 = 0;
    cout << "\n\nСтало:\n";

    auto time1 = high_resolution_clock::now();
    swap(mas[index1], mas[index2]);
    auto time2 = high_resolution_clock::now();
    auto end = duration_cast<nanoseconds>(time2 - time1).count();

    for (short i = 0; i < n; i++) {
        if (i == index1 || i == index2) {
            if (count1 < 2) {
                cout << "\x1b[32m" << mas[i] << "\x1b[0m" << " ";
                count1++;
            }
            else cout << mas[i] << " ";
        }
        else cout << mas[i] << " ";
    }
    cout << "\n\nВремя затраченное на обмен: " << end << " наносекунд\n\n";
}

int PracticalWork2() { //WORK2
    short select = 0, index1, index2;
    short const n = 100;
    int mas[n], copyMas[n];
    int* end = mas + n - 1;
    int* end_copy = copyMas + n - 1;
    short count = 0;
    int user_num_A, user_num_B, user_num_7, num_in_mas;

    while (true) {
        cout << "1 - Создать массив (обязательно)" << endl
            << "2 - Отсортировать массив (от меньшего к большему)" << endl
            << "3 - Найти максимальный и минимальный элемент массива" << endl
            << "4 - Среднее значение максимального и минимального эл-та массива" << endl
            << "5 - Количество элементов в отсортированном массиве меньшие вашего числа" << endl
            << "6 - Количество элементов в отсортированном массиве большие вашего числа" << endl
            << "7 - Найти своё число в массиве" << endl
            << "8 - Поменять местами числа в массиве" << endl
            << "9 - Назад" << endl
            << "Выберите действие: ";
        if (!(cin >> select)) { problem(); }
        switch (select) {
        case 1: {
            system("cls");
            for (int* ptr = mas; ptr <= end; ptr++) { *ptr = rand() % 199 - 99; }

            for (int* ptr = mas; ptr <= end; ptr++) { cout << *ptr << " "; }
            cout << "\n\n";

            for (int* ptr2 = copyMas, *ptr = mas; ptr2 <= end_copy; ptr2++, ptr++) *ptr2 = *ptr;
            break;
        }
        case 2: {
            system("cls");
            int time;
            time = bubble_sort(mas, n, 1);
            copy_array(mas, copyMas, n);
            cout << "\n\nЗатраченное время на сортировку:\n\n";
            cout << "Bubble sort: " << time << " наносекунд\n";
            time = shaker_sort(mas, n, 0);
            copy_array(mas, copyMas, n);
            cout << "Shaker sort: " << time << " наносекунд\n";
            time = insert_sort(mas, n, 0);
            copy_array(mas, copyMas, n);
            cout << "Insert sort: " << time << " наносекунд\n";
            time = selection_sort(mas, n, 0);
            copy_array(mas, copyMas, n);
            cout << "Selection sort: " << time << " наносекунд\n";
            auto time1 = high_resolution_clock::now();
            quick_sort(mas, 0, n - 1);
            auto time2 = high_resolution_clock::now();
            auto end1 = duration_cast<nanoseconds>(time2 - time1).count();
            cout << "Quick sort: " << end1 << " наносекунд\n\n";
            break;
        }
        case 3: {
            system("cls");
            int time1, time2, prost;
            time1 = max_min(copyMas, n, 0, 0); // неотсортированный массив                  
            prost = bubble_sort(mas, n, 0); // отсортированный массив 
            time2 = max_min(mas, n, 1, 1);

            cout << "Затраченное время в Неотсортированном массиве: " << time1 << " наносекунд\n\n";
            cout << "Затраченное время в Отсортированном массиве: " << time2 << " наносекунд\n\n";

            break;
        }
        case 4:
            system("cls");
            bubble_sort(mas, n, 0);
            cout << "Неотсортированный массив:\n";
            mid(copyMas, n);
            cout << "Отсортированный массив!\n";
            mid(mas, n);
            break;
        case 5:
            system("cls");
            cout << "Введите число: ";
            if (!(cin >> user_num_A)) {
                problem();
                continue;
            }

            user_min_num(mas, n, user_num_A);
            break;
        case 6:
            system("cls");
            cout << "Введите число: ";
            if (!(cin >> user_num_B)) {
                problem();
                continue;
            }

            user_max_num(mas, n, user_num_B);
            break;
        case 7: {
            system("cls");
            bubble_sort(mas, n, 0);
            cout << "Введите число: ";
            if (!(cin >> user_num_7)) {
                problem();
                continue;
            }

            auto time1 = high_resolution_clock::now();
            num_in_mas = common_search(mas, user_num_7, n);
            auto time2 = high_resolution_clock::now();
            auto end1 = duration_cast<nanoseconds>(time2 - time1).count();

            auto time11 = high_resolution_clock::now();
            num_in_mas = binary_search(mas, user_num_7, 0, n - 1);
            auto time22 = high_resolution_clock::now();
            auto end2 = duration_cast<nanoseconds>(time22 - time11).count();
            if (num_in_mas == -1) cout << "Такого элемента нету\n\n";
            else {
                for (int i = 0; i < n; i++) {
                    if (mas[i] == mas[num_in_mas]) {
                        if (count < 1) {
                            cout << "\x1b[32m" << mas[i] << "\x1b[0m" << " ";
                            count++;
                        }
                        else cout << mas[i] << " ";
                    }
                    else cout << mas[i] << " ";
                }
                count = 0;
                cout << "\n\nЭлемент находится по индексу: " << num_in_mas << "\n\n"
                    << "Время затраченное на поиск перебором: " << end1 << " наносекунд\n\n"
                    << "Время затраченное на поиск бинарным поиском: " << end2 << " наносекунд\n\n";
            }
            break;
        }
        case 8:
            system("cls");
            cout << "Введите первый индекс: ";
            if (!(cin >> index1)) {
                problem();
                continue;
            }

            cout << "\nВведите второй индекс: ";
            if (!(cin >> index2)) {
                problem();
                continue;
            }

            cout << endl;
            replace_index(mas, n, index1, index2);
            break;
        case 9:
            system("cls");
            return false;
            break;
        }
    }
    return 0;
}

void print_num(int x, int y, int number) {
    COORD destCoord;

    destCoord.X = x * 3 + xOffset;
    destCoord.Y = y + yOffset;
    SetConsoleCursorPosition(hStdout, destCoord);
    Sleep(20);
    cout << number;
}

void print_num2(int x, int y, int number) {
    COORD destCoord;

    destCoord.X = x * 3 + xOffset;
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

void fill_massive(int* arr, int N, bool yesornot, bool yesornotfill, bool another_cout) {
    int* end = arr + N * N - 1;
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
    short count_one = 0, count_two = 0, count_two_with_one = 1, count_right_one = -1, count_down = 2, count_two_left = 2, ptr_dealer = 0;

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

        for (int k = N - count_two_left, i = count_one; k >= 0; k--, i++) { // влево
            print_num(k + count_one, count_right_one + save, *(ptr + N * (N - (count_one - 1)) - i));
        }

        for (int k = N - count_one, i = 1; k >= count_one; k--, i++) { // наверх
            print_num(count_one - 1, (count_right_one + save) - i + 1, *(ptr + N * k + (count_one - 1)));
        }

        count_two_with_one += 2; count_right_one++; count_down--; count_two_left += 2; ptr_dealer++;
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

void shaker_sort_Work3(int* arr, int N) { // TASK3
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
    if (!(cin >> choice)) problem();
    xOffset = 0; yOffset = 1;
    switch (choice) {
    case 1:
        system("cls");
        cout << "Было:\t\t\t\t" << "Стало:";
        fill_massive(arr, N, 0, 0, 1);
        moves_with_number(arr, N, num, 1);
        xOffset = 40;
        fill_massive(arr, N, 0, 0, 1);
        break;
    case 2:
        system("cls");
        cout << "Было:\t\t\t\t" << "Стало:";
        fill_massive(arr, N, 0, 0, 1);
        moves_with_number(arr, N, num, 2);
        xOffset = 40;
        fill_massive(arr, N, 0, 0, 1);
        break;
    case 3:
        system("cls");
        cout << "Было:\t\t\t\t" << "Стало:";
        fill_massive(arr, N, 0, 0, 1);
        moves_with_number(arr, N, num, 3);
        xOffset = 40;
        fill_massive(arr, N, 0, 0, 1);
        break;
    case 4:
        system("cls");
        cout << "Было:\t\t\t\t" << "Стало:";
        fill_massive(arr, N, 0, 0, 1);
        moves_with_number(arr, N, num, 4);
        xOffset = 40;
        fill_massive(arr, N, 0, 0, 1);
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
            << "5 - Назад\n"
            << "Выберите действие: ";
        cin >> select;
        switch (select) {
        case 1: {
            system("cls");
            fill_massive(arr, N, 0, 1, 0);
            spiral_print(arr, N);
            snake_print(arr, N);
            break;
        }
        case 2: {
            system("cls");
            cout << "Исходная матрица:\t\t\t\t Изменённая: ";
            yOffset = 2; xOffset = 0;

            fill_massive(arr, N, 0, 0, 1);

            rotate_blocks(arr, copyarr, N); // option a
            from_bottom_to_top(copyarr, copyarr2, N); // option c
            arrows(copyarr2, copyarr3, N); // option b
            from_left_to_right(copyarr3, copyarr4, N); // option d

            xOffset = 36;
            fill_massive(arr, N, 0, 0, 1);
            print_word(N / 2, N, 'A');
            yOffset = 14;
            fill_massive(copyarr2, N, 0, 0, 1);
            print_word(N / 2, N, 'B');

            yOffset = 2;
            xOffset = 68;
            fill_massive(copyarr, N, 0, 0, 1);
            print_word(N / 2, N, 'C');
            yOffset = 14;
            fill_massive(copyarr3, N, 0, 0, 1);
            print_word(N / 2, N, 'D');

            cout << "\n\n\n\n";
            break;
        }
        case 3:
            system("cls");
            cout << "Неотсортированная матрица:\t\t" << "Отсортированная матрица:";
            yOffset = 2; xOffset = 0;
            fill_massive(arr, N, 0, 0, 1);
            shaker_sort_Work3(arr, N);
            xOffset = 40;
            fill_massive(arr, N, 0, 0, 1);
            cout << "\n\n";
            break;
        case 4: {
            system("cls");
            xOffset = 0; yOffset = 0;
            cout << "Введите число: ";
            long long number;
            if (!(cin >> number)) {
                problem();
                continue;
            }
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
            system("cls");
            return false;
        }
        default: {
            problem();
        }
        }
    }
}

int PracticalWork3() {
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int altf4 = true;
    while (altf4) {
        int n;
        cout << "0 - Назад.\n"
            << "Перед началом работы этого пункта необходимо ввести порядок матрицы! (Введите 6,8 или 10): ";
        if (!(cin >> n)) {
            problem();
            continue;
        }
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
            int altf4 = true;
            while (altf4) {
                altf4 = main_menu(&arr[0][0], &copyarr[0][0], &copyarr2[0][0], &copyarr3[0][0], &copyarr4[0][0], N);
            }
        }
        else if (n == 10) {
            system("cls");
            int const N = 10;
            int arr[N][N]; int copyarr[N][N]; int copyarr2[N][N]; int copyarr3[N][N]; int copyarr4[N][N];
            int altf4 = true;
            while (altf4) {
                altf4 = main_menu(&arr[0][0], &copyarr[0][0], &copyarr2[0][0], &copyarr3[0][0], &copyarr4[0][0], N);
            }
        }
        else if (n == 0) {
            system("cls");
            return false;
        }
        else {
            problem();
        }
    }
    return 0;
}

#include <fstream>

void delete_symbol(char* arr, int index, int& N) {
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
            if (ispunct(*ptr) || *ptr == ' ' || *ptr == '\0') {
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

void fix_all_text(char* arr, int& N) {
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
                end = arr + N - 1;
            }
            if (ispunct(*ptr2) && ispunct(*(ptr2 + 1)) && *ptr2 != '.') {
                delete_symbol(arr, index, N);
                end = arr + N - 1;
            }
            if (*ptr2 == '.' && ispunct(*(ptr2 + 1)) && *(ptr2 + 1) != '.') {
                delete_symbol(arr, index, N);
                end = arr + N - 1;
            }

            if (*ptr2 == ' ' && *(ptr2 + 1) == ' ') {
                delete_symbol(arr, index, N);
                end = arr + N - 1;
            }
            if (*ptr2 == ' ' && ispunct(*(ptr2 + 1))) {
                delete_symbol(arr, index, N);
                end = arr + N - 1;
            }

        }

    }
    if (*end != '.') {
        N++;
        end = arr + N - 1;
        *end = '.';
    }
}

void letters(char* arr, int& N, bool flag) {
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
            while (j < M && ptr <= (arr + N - 1) && *ptr == pattern[j]) {
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

int boyer_moore(char* arr, char* pattern, int& N, int& M) {
    char* end = arr + N - 1;

    int const ALPH = 256;
    int shift[ALPH];
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

            while (pattern[j] == *ptr && j >= 0 && ptr >= arr) {
                ptr--;
                count_letters++;
                j = M - count_letters;
            }
            ptr = ptr + (count_letters - 1);
            if ((count_letters - 1) == M) {
                return ptr - arr - M + 1;
            }
            else {
                if (est(pattern, M, *ptr)) { ptr += shift[(unsigned char)*ptr]; }
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

int enter(char* arr, int& N, char* copyarr) {
    int select;
    char* end = arr + N - 1;
    char* ptr = arr;
    int size = 0;
    char* ptr2 = copyarr;

    while (true) {
        cout << "1 - Ввести последовательность с клавиатуры\n"
            << "2 - Ввести последовательность с файла\n"
            << "3 - Назад\n\n"
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
        case 3:
            system("cls");
            return false;
        default:
            system("cls");
            problem();
            return false;
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

int PracticalWork4() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
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
            << "5 - Назад\n\n"
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
            if (M > size) {
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
                    if (ptr - 1 == end) break;
                    else cout << *ptr;

                }
                cout << "\n\n";
            }
            else cout << "\n\nТакой подстроки нету.\n\n";
            break;
        
        }
        case 5:
            system("cls");  
            return false;
        default:
            system("cls");
            problem();
        }
    }
}


int main() {
    srand(time(0));
    setlocale(LC_ALL, "RU");

    short Userchoice = 0;
    while (true) {
        cout << "===============Курсовая работа===============\n"
            << "1 - ТИПЫ ДАННЫХ И ИХ ВНУТРЕННЕЕ ПРЕДСТАВЛЕНИЕ В ПАМЯТИ\n"
            << "2 - ОДНОМЕРНЫЕ СТАТИЧЕСКИЕ МАССИВЫ\n"
            << "3 - ДВУМЕРНЫЕ СТАТИЧЕСКИЕ МАССИВЫ. УКАЗАТЕЛИ\n"
            << "4 - СТРОКИ\n"
            << "5 - Завершить работу\n\n"
            << "Выберите действие: ";
        if (!(cin >> Userchoice)) {
            problem();
            continue;
        }
        switch (Userchoice) {
        case 1:
            system("cls");
            PracticalWork1();
            break;
        case 2:
            system("cls");
            PracticalWork2();
            break;
        case 3:
            system("cls");
            PracticalWork3();
            break;
        case 4:
            system("cls");
            PracticalWork4();
            break;
        case 5:
            cout << "\nРабота завершена";
            return false;
        case 228: // :D
            system("cls");
            cout << "______________________________________________________\n"
                << "| Critical error                            [-][ ][x] |\n"
                << "|_____________________________________________________|\n"
                << "|                                                     |\n"
                << "| Windows has detected that your penis is so small    |\n"
                << "| Is that true ?                                      |\n"
                << "|  ________       _________           _________       |\n"
                << "|  | Yes  |       | maybe |           | Help  |       |\n"
                << "|  |______|       |_______|           |_______|       |\n"
                << "|_____________________________________________________|\n";
            return false;
            break;
        default:
            problem();
        }
    }
    return 0;
}