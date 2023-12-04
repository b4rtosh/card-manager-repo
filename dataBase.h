

#ifndef OBJ_FINAL_PROJ_DATABASE_H
#define OBJ_FINAL_PROJ_DATABASE_H

#include "luhn.h"
#include "qtmetamacros.h"
#include <iostream>
#include <algorithm>

class DataBase : public Luhn {
private:
    std::vector <Luhn> cards_data;

public:
    static std::vector <std::string> used_numbers;

    static int ac_month, ac_year;

    void actualDate();

    void addCard(Luhn card) {cards_data.emplace_back(card); }

    void loadData();

    void saveData();

    void emplaceNumber (const std::string &numb) { used_numbers.emplace_back(numb); }

    std::vector<Luhn> getTable() { return cards_data; }

    int getCapacity() { return cards_data.size(); }

    Luhn getVector(const int &n) { return cards_data[n]; };

    void deleteCard(const int &choice);
 //   Luhn getLastElement () {return cards_data[cards_data.capacity() - 1]; }

    long getLatestID() { return new_id; }

    void changeElement(const Luhn& element, const int& index){cards_data[index] = element;}
};

    bool checkName (const std::string &name);
    bool checkDate (const std::string &date);
     bool checkSurname (const std::string &surname);
    bool checkNumber (const std::string &number);

    bool checkValidity (const int &month, const int &year);

std::string getNumber();




#endif //OBJ_FINAL_PROJ_DATABASE_H
