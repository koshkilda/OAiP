#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Product{ //создаем структуру для продуктов, компоненты -- название, цена и количество 
    string name;
    double price;
    int number;
};


void addProductToFile(const Product& product) { //функция добавления продукта в файл
    ofstream outFile("products.txt", ios::app); //ios::app -- запись происходит в конец файла
    if (outFile.is_open()) {
        outFile << product.name << "," << product.price << "," << product.number << endl;
        outFile.close();
        cout << "Продукт успешно добавлен." << endl;
    } else {
        cerr << "Не удалось открыть файл для записи." << endl;
    }
}


void searchProductByName(const string& name) { //функция поиска продукта по имени
    ifstream inFile("products.txt");
    if (inFile.is_open()) {
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            size_t pos = line.find(',');
            string fullName = line.substr(0, pos);
            if (fullName == name) {
                cout << "Найден продукт: " << line << endl;
                found = true;
                break;
            }
        }
        inFile.close();
        if (!found) {
            cout << "Продукт с таким именем не найден." << endl;
        }
    } else {
        cerr << "Не удалось открыть файл для чтения." << endl;
    }
}


void sortProductbyNumber() {
    ifstream inFile("products.txt");
    if (inFile.is_open()) {
        // Чтение данных и сортировка (пузырьковая сортировка)
        string lines[100]; // Предполагаем, что не более 100 продуктов
        int count = 0;
        string line;

        while (getline(inFile, line)) {
            lines[count] = line;
            count++;
        }
        inFile.close();

        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                // преобразовываем конец строки(количество) из string в int для сравнения
                size_t pos1 = lines[j].find_last_of(','); //find_last_of() позволяет найти индекс последнего символа "," в строке:
                size_t pos2 = lines[j + 1].find_last_of(',');

                int Par1 = stoi(lines[j].substr(pos1 + 1)); //stoi -- преобразовывает string в int
                int Par2 = stoi(lines[j + 1].substr(pos2 + 1));

                if (Par1 > Par2) {
                    swap(lines[j], lines[j + 1]);
                }
            }
        }

        // Запись отсортированных данных обратно в файл
        ofstream outFile("products.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << endl;
            }
            outFile.close();
            cout << "Продукты отсортированы по количеству." << endl;
        } else {
            cerr << "Не удалось открыть файл для записи." << endl;
        }
    } else {
        cerr << "Не удалось открыть файл для чтения." << endl;
    }
}


int main() {
    int choice;
    string name;

    do {
        cout << "Меню:" << endl;
        cout << "1. Добавить продукт" << endl;
        cout << "2. Поиск продукта по названию" << endl;
        cout << "3. Сортировать продукты по цене" << endl;
        cout << "0. Выйти" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore();
                string name;
                double price;
                int number;

                cout << "Введите название продукта: ";
                getline(cin, name);
                if (name.empty()) {
                    cout << "Ввод прерван." << endl;
                    break;
                }
                cout << "Введите цену продукта: ";
                cin >> price;
                cout << "Введите количество продукта: ";
                cin >> number;

                Product newProduct = {name, price, number};
                addProductToFile(newProduct);
                break;
            }
            case 2: {
                cin.ignore();
                cout << "Введите название продукта для поиска: ";
                getline(cin, name);
                searchProductByName(name);
                break;
            }
            case 3: {
                sortProductbyNumber();
                break;
            }
            case 0: {
                cout << "Программа завершена." << endl;
                break;
            }
            default: {
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}