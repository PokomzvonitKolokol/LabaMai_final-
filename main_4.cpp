#include <iostream>
#include <cstring>  // cstring - строки типа С , подробнее о них : https://stackoverflow.com/questions/12203339/c-string-definition-in-c-c 
using namespace std;

enum Priority {  // enum - позволяет определить новый тип , подробнее о нем : https://www.youtube.com/watch?v=BMmbQ81lQd0
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3      // задали три возможных значения приоритета для заметок
};

struct Note {
    int id;   // номер заметки , "айдишник" (id) присваивается автоматически (для различие заметок )
    char text[256]; // массив из 256 символов
    int length; // длина тексат в символах
    Priority priority; // приоритет
};

const int MAX_NOTES = 100; // выделяем память под мааксимум 100 заметок

                                                                             // средняя длина по приоритетам
void averageLlengthbypriority(Note notes[], int n) {    // массивы sum и count хранят сумму длин и количество заметок для каждого приоритета

    double sum[4] = {0};                                                     // индексы 1,2,3 — под LOW, MEDIUM, HIGH (1, 2, 3 соответствуют LOW, MEDIUM, HIGH)
    int count[4] = {0};

    for (int i = 0; i < n; i++) {                               // проходим по заметкам реобразуем Priority в число (static_cast<int>), чтобы использовать как индекс
        int p = static_cast<int>(notes[i].priority);
        sum[p] += notes[i].length;
        count[p]++;
    }

    cout << "Средняя длина:\n";                                          // вводим значение средней длины
    if (count[LOW] > 0)    cout << "Низкий:    " << sum[LOW] / count[LOW] << endl;
    if (count[MEDIUM] > 0) cout << "Средний:   " << sum[MEDIUM] / count[MEDIUM] << endl;  // выводим среднюю длину для каждого приоритета, но только если такие заметки есть

    if (count[HIGH] > 0)   cout << "Высокий:   " << sum[HIGH] / count[HIGH] << endl;
}

// Фильтр по минимальному приоритету и диапазону длины
void filterbypriorityandlength (Note notes[], int n, Priority minPriority, int minLen, int maxLen) {  // функция: фильтр по приоритету и длине
    cout << "\nФильтр (приоритет >= " << minPriority
         << ", длина от " << minLen << " до " << maxLen << "):\n";
    bool found = false;
    for (int i = 0; i < n; i++) {                            // вывожит только те заметки у которых приоритет не ниже minPriority
        if (notes[i].priority >= minPriority &&                  
            notes[i].length >= minLen &&
            notes[i].length <= maxLen) {
            cout << "ID: " << notes[i].id
                 << " | Приоритет: " << notes[i].priority
                 << " | Длина: " << notes[i].length
                 << " | Текст: " << notes[i].text << endl;
            found = true;
        }
    }
    if (!found) cout << "(ничего не найдено)\n";
}

// Поиск подстроки (регистр учитывается)
bool contains(const char* str, const char* substr) {           // функция: проверка наличия подстроки
    if (strlen(substr) == 0) return true;                    // ищет substr внутри str
    int len1 = strlen(str);                      // если подстрока пуста - возвращает true
    int len2 = strlen(substr);                                    // возвращяет true , если нашла совпадение
    for (int i = 0; i <= len1 - len2; i++) {
        bool ok = true;
        for (int j = 0; j < len2; j++) {
            if (str[i + j] != substr[j]) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
    }
    return false;
}

void searchsubstring(Note notes[], int n, char substr[]) {        // поиск подстроки в заметках , проходит по всем заметкам и вызывает contains          
    cout << "\nПоиск подстроки '" << substr << "':\n";       // выводит все заметки , в тексте которых есть указанная подстрока
    bool found = false;
    for (int i = 0; i < n; i++) {                       // bool - https://otvet.mail.ru/question/191548747?ysclid=mj26b5mvph983047688
        if (contains(notes[i].text, substr)) {
            cout << "ID: " << notes[i].id << " | Текст: " << notes[i].text << endl;
            found = true;
        }
    }
    if (!found) cout << "(ничего не найдено)\n";
}

// Сортировка: сначала по приоритету (по убыванию), потом по длине (по возрастанию)
void sortnotes(Note notes[], int n) {                           // сортирует заметки
    for (int i = 0; i < n - 1; i++) {                    // сначала по приоритету по убыванию 
        for (int j = i + 1; j < n; j++) {             // если приоритеты равны - по длине по возрастанию 
            if (notes[i].priority < notes[j].priority ||
                (notes[i].priority == notes[j].priority && notes[i].length > notes[j].length)) {      // это условие говорит нам что нужно поменять местами если i-заметка меньше j-й по нашему правилу
                Note temp = notes[i];
                notes[i] = notes[j];
                notes[j] = temp;
            }
        }
    }
}

// Вывод всех заметок (для проверки)
void printall(Note notes[], int n) {          // просто печатает всю информацию по каждой заметке
    cout << "\nВсе заметки:\n";
    for (int i = 0; i < n; i++) {
        cout << "ID: " << notes[i].id
             << " | Приоритет: " << notes[i].priority
             << " | Длина: " << notes[i].length
             << " | Текст: " << notes[i].text << endl;
    }
}

int main() {                      // запрашивает , сколько заметок введет пользователь
    Note notes[MAX_NOTES];
    int n;
                                // cin.ignore() - убирает символ новой строки (\n)  чтобы  getline работал правильно
    cout << "Сколько заметок ввести? (<=100): ";
    cin >> n;
    cin.ignore(); // съедаем \n

    for (int i = 0; i < n; i++) {     // заполняем каждую заметку id - просто номер по порядку 
        notes[i].id = i + 1;
        cout << "Текст заметки " << i + 1 << ": ";
        cin.getline(notes[i].text, 256);       // getline (https://www.geeksforgeeks.org/cpp/getline-string-c/?ysclid=mj25aezykj947709061) 
        notes[i].length = strlen(notes[i].text); // strlen (https://www.geeksforgeeks.org/cpp/5-different-methods-to-find-length-of-a-string-in-cpp/?ysclid=mj25fht7lj926158574)
        cout << "Приоритет (1=низкий, 2=средний, 3=высокий): ";
        int p;
        cin >> p;
        notes[i].priority = static_cast<Priority>(p);
        cin.ignore();
    }

    // Выполняем все пункты задачи
    averageLlengthbypriority (notes, n);

    filterbypriorityandlength(notes, n, MEDIUM, 5, 30); // пример

    char substr[50];
    cout << "\nВведите подстроку для поиска: ";
    cin.getline(substr, 50);
    searchsubstring(notes, n, substr);

    cout << "\nСортировка (приоритет ↓, длина ↑):";
    sortnotes(notes, n);
    printall(notes, n);

    return 0;
}