#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MusicalInstrument
{
public:
    MusicalInstrument(string p_name, string p_material) { //конструктор
        name = p_name;
        material = p_material;
        cout << "Musical Instrument has been created" << endl;
    }

    ~MusicalInstrument() { //деструктор
        
    }
    virtual void display() const {
        cout << "Name: " << name << endl;
        cout << "Material: " << material << endl;
    }

    void change_data(string p_name, string p_material) {
        name = p_name;
        material = p_material;
    }

private:
    string name;
    string material;
    
};


class StringInstrument : public MusicalInstrument
{
public:
    StringInstrument(string p_name, string p_material, int p_number_of_strings) : MusicalInstrument(p_name, p_material)
    {
        number_of_strings = p_number_of_strings;
        cout << "String Instrument has been created" << endl;
    }

    ~StringInstrument(){ //деструктор
        
    }

    void display() const {
        MusicalInstrument::display();
        cout << "Amount of strings: " << number_of_strings << endl;
    }

private:
    int number_of_strings;
};


class BrassInstrument : public MusicalInstrument
{
public:
    BrassInstrument(string p_name, string p_material, string p_brass_type) : MusicalInstrument(p_name, p_material)
    {
        brass_type = p_brass_type;
        cout << "Brass Instrument has been created" << endl;
    }

    ~BrassInstrument(){ //деструктор
        
    }

    void display() const {
        MusicalInstrument::display();
        cout << "Brass type: " << brass_type << endl;
    }
private:
    string brass_type;
};

void change_info(MusicalInstrument *instr, string new_name, string new_material)
{
    instr->change_data(new_name, new_material);
}

main()
{
    StringInstrument guitar      {(string)"guitar", "oak", 6};
    StringInstrument rock_guitar {"rock-guitar", "ash", 8};
    BrassInstrument  saxophone   {"saxophone", "brass", "yellow"};
    

    vector<MusicalInstrument *> instruments = {&guitar, &rock_guitar, &saxophone};

    cout << "\nInstruments:\n" << endl;
    for (size_t i = 0; i < instruments.size(); i++) {
        instruments[i]->display();
        cout << endl;
    }

    change_info(&rock_guitar, "metal-guitar", "birch");
    rock_guitar.display();
}