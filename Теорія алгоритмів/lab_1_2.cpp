#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int main() {
    srand(time(0));

    cout << " ЧЕРГА " << endl;
    cout << "Введіть кількість елементів черги N: ";
    int m;
    cin >> m;
    int queue[100];
    int head = 0;
    int tail = 0;
    for (int i = 0; i < m; i++) {
        queue[tail] = rand() % 100 - 50;
        tail++;
    }

    int temp_queue[100];
    int temp_head = 0;
    int temp_tail = 0;
    cout << "Елементи черги: ";
    while (head < tail) {
        int val = queue[head]; 
        head++; 
        cout << val << " ";
        temp_queue[temp_tail] = val;
        temp_tail++;
    }
    cout << endl;

    int sum_positive = 0;
    int sum_negative_abs = 0;

    while (temp_head < temp_tail) {
        int val = temp_queue[temp_head];
        temp_head++;

        if (val > 0) {
            sum_positive += val;
        } else if (val < 0) {
            sum_negative_abs += abs(val);
        }
    }
    cout << "Сума додатних елементів: " << sum_positive << endl;
    cout << "Сума модулів від'ємних елементів: " << sum_negative_abs << endl;

    if (sum_positive > sum_negative_abs) {
        cout << "Результат: Сума додатних елементів більша" << endl;
    } else if (sum_negative_abs > sum_positive) {
        cout << "Результат: Сума модулів від'ємних елементів більша" << endl;
    } else {
        cout << "Результат: Суми рівні" << endl;
    }

    return 0;
}