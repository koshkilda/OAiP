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


void searchProductByPrice(const double& maxPrice) { //функция поиска продукта по цене
    ifstream inFile("products.txt");
    if (inFile.is_open()) {
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            size_t pos1 = line.find_first_of(',');
            size_t pos2 = line.find_last_of(',');
            double thatPrice = stod(line.substr(pos1 + 1, pos2 - pos1));
            if (thatPrice <= maxPrice) {
                cout << "Найдены продукты: " << line << endl;
                found = true;
            }
        }
        inFile.close();
        if (!found) {
            cout << "Продукты, цена которых меньше заданной, не найдены." << endl;
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
    double maxPrice;

    do {
        cout << "Меню:" << endl;
        cout << "1. Добавить продукт" << endl;
        cout << "2. Поиск продуктов по цене" << endl;
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
                cout << "Введите максимальную цену продукта для поиска: ";
                cin >> maxPrice;
                searchProductByPrice(maxPrice);
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
