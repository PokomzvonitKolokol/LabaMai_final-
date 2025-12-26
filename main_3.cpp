#include <iostream>
#include <string>

int main() {
    std::string str, substr;

    std::cout << "Введите строку: ";
    std::getline(std::cin, str);

    std::cout << "Введите подстроку для поиска: ";
    std::getline(std::cin, substr);

    if (substr.empty()) {
        std::cout << "Подстрока пуста. Количество вхождений: 0" << std::endl;
        return 0;
    }

    int count = 0;
    size_t pos = 0;

    while ((pos = str.find(substr, pos)) != std::string::npos) {
        ++count;
        pos += 1; // сдвигаем позицию на 1, чтобы искать перекрывающиеся вхождения
    }

    std::cout << "Количество вхождений подстроки: " << count << std::endl;

    return 0;
}