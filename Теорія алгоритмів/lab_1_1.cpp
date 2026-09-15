#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    cout << " СТЕК " << endl;
    cout << "Введіть кількість елементів стеку N: ";
    int n;
    cin >> n;

    int stack_main[100];
    int top_main = -1;

    for (int i = 0; i < n; i++) {
        top_main++;
        stack_main[top_main] = rand() % 100 - 50;
    }

    cout << "Початковий стек : ";
    for (int i = top_main; i >= 0; i--) {
        cout << stack_main[i] << " ";
    }
    cout << endl;

    int stack_temp[100];
    int top_temp = -1;

    while (top_main >= 0) {
        int val = stack_main[top_main];
        top_main--;

        if (val >= 0) {
            top_temp++;
            stack_temp[top_temp] = val;
        }
    }

    while (top_temp >= 0) {
        top_main++;
        stack_main[top_main] = stack_temp[top_temp];
        top_temp--;
    }

    cout << "Стек після видалення від'ємних елементів: ";
    if (top_main < 0) {
        cout << "Стек порожній";
    } else {
        for (int i = top_main; i >= 0; i--) {
            cout << stack_main[i] << " "; //так нне можна через і
        }
    }
    cout << endl;

    return 0;
}