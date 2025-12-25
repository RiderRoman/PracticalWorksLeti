/*
												    *       ***    ****			******
                                                    *      *   *   *   *		     *
                                                    *      *****   ****			******
                                                    *      *   *   *   *		*	 
                                                    *****  *   *   ****			******																															*/


#include <iostream>
#include <chrono>
#include <limits>

using namespace std;
using namespace chrono;
void problem() { // mistake cin
    system("cls");
    cout << "Неверный ввод. Попробуйте еще раз!\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
}

void copy_array(int* arr, int* copyarr, int N) {
    for (int* ptr = arr, *ptr2 = copyarr; ptr <= arr + N - 1; ptr++, ptr2++) { *ptr = *ptr2; }

}

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
    short maxi = mas[99], mini = mas[0], count = 0, mid;
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
    while (mas[i] < A && i < n) {
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

int main() {
    setlocale(LC_ALL, "RU");
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