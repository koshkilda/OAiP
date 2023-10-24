#include <iostream>
#include <cstring>

using namespace std; 

float sum(float *mas, int n) { // функция для получения суммы элементов массива
    float sum = 0;

    for (int i = 0; i < n; i++) {
        sum = sum + mas[i];
    }

    return sum;
}

int main() {
    // ввод данных
    int number_of_items_sold; // ввод количества проданных товаров
    cout << "Введите количество проданных товаров:";
    cin >> number_of_items_sold;

    string *name = new string[number_of_items_sold]; // определение массива
    int *number_of_units_sold = new int[number_of_items_sold];
    float *price = new float[number_of_items_sold];

    for (int i = 0; i < number_of_items_sold; i++) { // заполнение массива
        cout << "Введите название товара " << i + 1 << ": ";
        cin >> name[i];

        cout << "Введите количество проданных единиц товара " << name[i] << ": ";
        cin >> number_of_units_sold[i];

        cout << "Введите цену за единицу товара " << name[i] << ": ";
        cin >> price[i];
    }



    // сортируем данные по алфавиту
    string tstr; // вводим переменные для замены в дальнейшем
    int tk;
    float tp;

    for (int i = 0; i < number_of_items_sold - 1; i++) { 
        if (name[i + 1] > name[i]) {
            tstr = name[i]; // сортируем имена
            name[i] = name[i + 1];
            name[i + 1] = tstr; 

            tk = number_of_units_sold[i]; // сортируем количество проданного товара вслед за именем
            number_of_units_sold[i] = number_of_units_sold[i + 1];
            number_of_units_sold[i + 1] = tk;

            tp = price[i]; // сортируем цену вслед за именем
            price[i] = price[i + 1];
            price[i + 1] = tp;
        }
    }

    for (int i = 0; i < number_of_items_sold; i++) { // выводим отсортированный массив
        cout << "Название товара " << i + 1 << ": " << name[i] << endl;
        cout << "Количество проданных единиц товара: " << number_of_units_sold[i] << endl;
        cout << "Цена за единицу товара: " << price[i] << endl;
    }
    


    // расчет средней цены товара
    float avarage_price; 
    avarage_price = sum(price, number_of_items_sold) / number_of_items_sold;
    cout << "Средняя цена за единицу товара: " << avarage_price << endl;



    // расчет общей суммы продаж
    float sum = 0;
    for (int i = 0; i < number_of_items_sold; i++) {   
        sum = sum + number_of_units_sold[i] * price[i];
    }
    cout << "Общая сумма продаж: " << sum << endl;



    // освобождаем память
    delete[] name; 
    delete[] number_of_units_sold;
    delete[] price; 

    return 0;
}