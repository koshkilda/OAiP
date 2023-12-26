#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T1, typename T2>
class Pair {
public:
    Pair() {}
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

    void displayPair() const {
        cout << first << ": " << second << endl;
    }

    void savePairToFile(ofstream& outFile) const {
        outFile << first << " " << second << " ";
    }

private:
    T1 first;
    T2 second;
};

class Product {
public:
    Product(const string& name, const double& price, const int& quanity)
        : name(name), price(price), quanity(quanity) {}

    ~Product() {}

    const string& getName() const { //геттеры
        return name;
    }

    const double& getPrice() const {
        return price;
    }

    const int& getQuanity() const {
        return quanity;
    }

    void setName(const string& newName) { //сеттеры
        name = newName;
    }

    void setPrice(const double& newPrice) {
        price = newPrice;
    }

    void setQuanity(const int& newQuanity) {
        quanity = newQuanity;
    }

    virtual void displayInfo() const { //вывод информации о продукте
        cout << "Продукт: " << name << ", цена: " << price << ", количество: " << quanity << endl;
        // grades.displayGrades();
    }

    /* void inputGrades() {
        grades.inputGrades();
    } */

    void saveToFile(ofstream& outFile) const {
        outFile << name << " " << price << " " << quanity << " ";
        // grades.saveGradesToFile(outFile);
    }

    static bool compareByPrice(const Product* product1, const Product* product2) {
        return product1->getPrice() < product2->getPrice();
    }

private:
    string name;
    double price;
    int quanity;
    //Grades<int> grades;  // Изменил на Grades<int> для использования целочисленных оценок
};

class Meal : public Product //наследуемый класс
{
public:
    void displayInfo() const override {
        cout << "Осталось дней до истечения срока годности: " << expirationDate << endl;
    }

private:
    int expirationDate;
};

void modifyProduct(Product* product) { //метод изменения продукта
    cout << "Продукт найден. Что вы хотите изменить?" << endl;
    cout << "1. Название" << endl;
    cout << "2. Цена" << endl;
    cout << "3. Количество" << endl;
    // cout << "4. Оценки" << endl;

    int choice;
    cout << "Введите ваш выбор: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            string newName;
            cout << "Введите новое название: ";
            cin >> newName;
            product->setName(newName);
            break;
        }
        case 2: {
            double newPrice;
            cout << "Введите новую цену: ";
            cin >> newPrice;
            product->setPrice(newPrice);
            break;
        }
        case 3: {
            int newQuanity;
            cout << "Введите новое количество: ";
            cin >> newQuanity;
            product->setQuanity(newQuanity);
            break;
        }
        /* case 4:
            student->inputGrades();
            break; */

        default:
            cout << "Неверный выбор." << endl;
    }
}

void saveProductsToFile(const vector<Product*>& products, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Ошибка открытия файла для записи." << endl;
        return;
    }

    for (const auto* product : products) {
        product->saveToFile(outFile);
    }

    outFile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Product*> products;

    int choice;
    string filename;

    do {
        cout << "Меню:" << endl;
        cout << "1. Добавить продукт" << endl;
        cout << "2. Изменить данные о продукте" << endl;
        cout << "3. Удалить продукт" << endl;
        cout << "4. Найти продукт" << endl;
        cout << "5. Вывести список продуктов" << endl;
        cout << "6. Сохранить в файл" << endl;
        cout << "7. Сортировать по цене" << endl;
        cout << "8. Выход" << endl;

        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                double price;
                int quanity;

                cout << "Введите данные продукта:" << endl;
                cout << "Название: ";
                cin >> name;
                cout << "Цена: ";
                cin >> price;
                cout << "Количество: ";
                cin >> quanity;

                products.push_back(new Product(name, price, quanity));
                // products.back()->inputGrades();

                break;
            }
            case 2: {
                string name;

                cout << "Введите название продукта для изменения:" << endl;
                cin >> name;

                auto it = find_if(products.begin(), products.end(), [&](const Product* product) {
                    return product->getName() == name;
                });

                if (it != products.end()) {
                    modifyProduct(*it);
                } else {
                    cout << "Продукт не найден." << endl;
                }

                break;
            }
            case 3: {
                string name;
                
                cout << "Введите название продукта для удаления:" << endl;
                cin >> name;

                auto it = find_if(products.begin(), products.end(), [&](const Product* product) {
                    return product->getName() == name;
                });

                if (it != products.end()) {
                    delete *it;
                    products.erase(it);
                    cout << "Продукт удален." << endl;
                } else {
                    cout << "Продукт не найден." << endl;
                }

                break;
            }
            case 4: {
                string name;

                cout << "Введите название продукта для поиска:" << endl;
                cin >> name;

                auto it = find_if(products.begin(), products.end(), [&](const Product* product) {
                    return product->getName() == name;
                });

                if (it != products.end()) {
                    (*it)->displayInfo();
                } else {
                    cout << "Продукт не найден." << endl;
                }

                break;
            }
            case 5: {
                cout << "Список продуктов:" << endl;
                for (const auto* product : products) {
                    product->displayInfo();
                }
                break;
            }
            case 6: {
                cout << "Введите имя файла для сохранения данных: ";
                cin >> filename;
                saveProductsToFile(products, filename);
                break;
            }
            case 7: {
                sort(products.begin(), products.end(), Product::compareByPrice);
                cout << "Список продуктов отсортирован по цене." << endl;
                break;
            }
            case 8:
                cout << "Выход." << endl;
                break;
            default:
                cout << "Неверный выбор." << endl;
        }
    } while (choice != 8);

    for (const auto* product: products) {
        delete product;
    }

    return 0;
}