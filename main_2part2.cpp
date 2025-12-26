#include <iostream>
using namespace std;

int main() {
    const int MAX_SIZE = 100; 
    int arr[MAX_SIZE];        
    int n;                             // количество элементов в  массиве

    // ввод кол-ва элементов
    
    cout << "введите кол-во чисел в списке: ";
    cin >> n;

    // проверка правильности ввода

    if (n <= 0 || n > MAX_SIZE) { 
        cout << "некорректное количество чисел." << endl;
        return 1;
    }

    // ввод элементов массива

    cout << "введите " << n << " целых чисел:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << endl << endl;

    
// отбор четных чисел

    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {                  // если число четное
            cout << arr[i] << endl;
        }
    }

    return 0;
}