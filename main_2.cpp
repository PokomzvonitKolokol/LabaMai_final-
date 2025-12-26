#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a, b, c;

    cout << "Введите первый катет: ";
    cin >> a;
    cout << "Введите второй катет: ";
    cin >> b;

     if (a < 0 || b < 0) {
       cout << " значения не могут быть отрицательными." << endl;
        return 1; // Возврат с ошибкой

    c = sqrt(a * a + b * b);

    cout << "Гипотенуза = " << c << endl;

    return 0;
}