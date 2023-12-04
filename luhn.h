//
// Created by p9bar on 20.04.2023.
//


#ifndef OBJ_FINAL_PROJ_LUHN_H
#define OBJ_FINAL_PROJ_LUHN_H

#include <string>
#include <utility>
#include <vector>

struct Date{
    int month{};
    int year {};
};

class Luhn {
protected:
    constexpr static char luhn_tab[10]{'0', '2', '4', '6', '8', '1', '3', '5', '7', '9'};
    std::string card_number{}, user_name{}, user_surname{}, card_brand{};
    long card_id{};
    static long new_id;
    bool card_validity {};
    Date card_date;
    static std::vector<std::string> brandNames;
public:
    void setNumber(std::string number) { card_number = std::move(number); }

    void setName(std::string name) { user_name = std::move(name); }

    void setSurname(std::string surname) { user_surname = std::move(surname); }

    void setBrand(std::string brand) { card_brand = std::move(brand); }

   // void addBrandName(const std::string& brand) { brandNames.push_back(brand); }

    void setValidity (bool validity) {card_validity = validity; }

    void setDate(int f_month, int f_year) { card_date.month = f_month; card_date.year = f_year;}

    void setID() {card_id = new_id++; }

    void addID(long ids) { new_id = ids; }

    Date getDate () const { return card_date; }

    bool getValidity () const { return card_validity; }
    std::string getNumber() const { return card_number; }

    std::string getName() const { return user_name; }

    std::string getSurname() const { return user_surname; }

    std::string getBrand() const { return card_brand; }

    long getID() const { return card_id; }

    std::string getVBrand(const int &n) const { return brandNames[n]; }

    static bool test(std::string number);

    Luhn (std::string number, std::string name, std::string surname, std::string brand, Date date) :
        card_id {new_id++}, card_number {number}, user_name {name}, user_surname {surname}, card_brand {brand}, card_date {date}
    {}

    explicit Luhn(long id) : card_id{id} {}

    Luhn () = default;
};


#endif //OBJ_FINAL_PROJ_LUHN_H
