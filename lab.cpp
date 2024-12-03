#include <iostream>
#include <fstream>
#include <string>


using namespace std;

// Структура для збереження інформації про маршрут
struct Route {
    string startPoint; // Початкова точка маршруту
    string endPoint; // Кінцева точка маршруту
    int routeNumber; // Номер маршруту
};

// Функція для відображення списку маршрутів із файлу
void displayRoutes(const std::string& fileName) {
    ifstream file(fileName); // Відкриваємо файл для читання

    if (!file.is_open()) { // Перевіряємо, чи файл відкрився
        std::cerr << "File could not be opened" << fileName << ".\n"; // Виводимо повідомлення про помилку
        return;
    }

    string startPoint, endPoint; // Змінні для зчитування даних
    int routeNumber;
    bool isEmpty = true; // Прапорець, що показує, чи є дані у файлі

    cout << "List of routes:\n";

    // Читаємо дані з файлу рядок за рядком
    while (file >> startPoint >> endPoint >> routeNumber) {
        cout << "Starting point: " << startPoint
            << ", The end point: " << endPoint
            << ", Route number: " << routeNumber << "\n";
        isEmpty = false; // Файл не порожній
    }

    if (isEmpty) { // Якщо файл порожній
        cout << "The file is empty or the data format is incorrect.\n";
    }

    file.close(); // Закриваємо файл
}


// Функція для пошуку маршруту за номером
bool findRouteByNumber(const string& fileName, int routeNumber, Route& foundRoute) {
    ifstream file(fileName); // Відкриваємо файл для читання

    if (!file.is_open()) { // Перевіряємо, чи файл відкрився
        cerr << "File could not be opened " << fileName << ".\n";
        return false;
    }

    string startPoint, endPoint; // Змінні для зчитування даних
    int number;

    // Пошук маршруту у файлі
    while (file >> startPoint >> endPoint >> number) {
        if (number == routeNumber) { // Якщо маршрут знайдено
            foundRoute.startPoint = startPoint;
            foundRoute.endPoint = endPoint;
            foundRoute.routeNumber = number;
            file.close(); // Закриваємо файл
            return true;
        }
    }

    file.close(); // Закриваємо файл
    return false; // Маршрут не знайдено
}

// Функція для додавання нового маршруту до файлу
void addRouteToFile(const string& fileName) {
    ofstream file(fileName, ios::app); // Відкриваємо файл для запису (додаємо дані в кінець файлу)

    if (!file.is_open()) { // Перевіряємо, чи файл відкрився
        cerr << "File could not be opened " << fileName << ".\n";
        return;
    }

    Route newRoute; // Новий маршрут
    cout << "Enter the starting point: ";
    cin >> newRoute.startPoint; // Зчитуємо початкову точку
    cout << "Enter the destination: ";
    cin >> newRoute.endPoint;  // Зчитуємо кінцеву точку
    cout << "Enter the route number: ";

    // Перевірка правильності введення номера маршруту
    while (!(cin >> newRoute.routeNumber) || newRoute.routeNumber <= 0) {
        cout << "Error! Enter the correct route number: ";
        cin.clear();  // Очищаємо помилку вводу
        cin.ignore(1000, '\n'); // Пропускаємо некоректний ввід
    }

    // Записуємо маршрут у файл
    file << newRoute.startPoint << " " << newRoute.endPoint << " " << newRoute.routeNumber << "\n";
    cout << "The route has been successfully added to the file.\n";

    file.close(); // Закриваємо файл
}

// Функція для відображення меню
void showMenu() {
    cout << "\nMenu:\n";
    cout << "1. Display the list of routes\n"; // Показати список маршрутів
    cout << "2. Add a new route\n";             // Додати новий маршрут
    cout << "3. Find a route by number\n";      // Знайти маршрут за номером
    cout << "4. Exit\n";                        // Вийти з програми
    cout << "Your choice: ";
}

int main() {

    string fileName; // Змінна для імені файлу
    cout << "Enter a file name: ";
    cin >> fileName; // Зчитуємо ім'я файлу

    int choice; // Змінна для збереження вибору користувача

    // Основний цикл програми
    do {
        showMenu(); // Показуємо меню

        // Перевірка правильності вводу пункту меню
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Error! Enter the correct menu item: ";
            cin.clear();  // Очищаємо помилку вводу
            cin.ignore(1000, '\n'); // Пропускаємо некоректний ввід
        }

        // Виконуємо дію, залежно від вибору користувача
        switch (choice) {
        case 1:
            displayRoutes(fileName); // Показати список маршрутів
            break;
        case 2:
            addRouteToFile(fileName); // Додати новий маршрут
            break;
        case 3: {
            int searchNumber;
            cout << "Enter the route number to search for: ";

            // Перевірка правильності вводу номера маршруту
            while (!(cin >> searchNumber) || searchNumber <= 0) {
                cout << "Error! Enter the correct number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            Route foundRoute; // Змінна для збереження знайденого маршруту

            // Пошук маршруту за номером
            if (findRouteByNumber(fileName, searchNumber, foundRoute)) { 

                cout << "The route has been found:\n";
                cout << "Starting point: " << foundRoute.startPoint << "\n";
                cout << "The end point: " << foundRoute.endPoint << "\n";
                cout << "Route number: " << foundRoute.routeNumber << "\n";
            }
            else {
                cout << "Route with number " << searchNumber << " not found.\n";
            }
            break;
        }
        case 4:
            cout << "Exit the program.\n"; // Вихід з програми
            break;
        }
    } while (choice != 4); // Цикл працює, поки не вибрано пункт 4

    return 0;
}
// C:\Users\yande\source\repos\11.3\x64\Debug\test.txt