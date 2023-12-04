#include "dataBase.h"
#include <string>
#include <regex>
#include <QMessageBox>


bool checkString(const std::string &chain);

int DataBase::ac_month = 0;
int DataBase::ac_year = 2000;
std::vector <std::string> DataBase::used_numbers = {"0"};

void DataBase::actualDate() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    ac_year = 1900 + ltm->tm_year;
    ac_month = 1 + ltm->tm_mon;
}

bool checkValidity(const int &month, const int &year) {
    if (year < DataBase::ac_year) return false;
    else if (year == DataBase::ac_year) {
        if (month <= DataBase::ac_month) return false;
        else return true;
    } else return true;
}

bool checkName (const std::string &name){
    std::regex name_pattern ("[A-Z][a-z]+");
    QMessageBox messageBox;
    if (name.length() > 100) {
        messageBox.critical(0,"Name error","Name is too length!");
        messageBox.setFixedSize(500,200);
        return true;
    } else if (!std::regex_match(name, name_pattern)) {
        messageBox.critical(0,"Name error","Forbidden signes used!");
        messageBox.setFixedSize(500,200);
        return true;
    }
    return false;
}

bool checkSurname (const std::string &surname){
    std::regex surname_pattern ("[A-Z][a-z]+");
    QMessageBox messageBox;
    if (surname.length() > 100) {
        messageBox.critical(0,"Surname error","Surname is too length!");
        messageBox.setFixedSize(500,200);
        return true;
    } else if (!std::regex_match(surname, surname_pattern)) {
        messageBox.critical(0,"Surname error","Forbidden signes used!");
        messageBox.setFixedSize(500,200);
        return true;}
    return false;
}

bool checkNumber (const std::string &number){
    QMessageBox messageBox;
    if (std::count(DataBase::used_numbers.begin(), DataBase::used_numbers.end(), number)) {
        messageBox.critical(0,"Number error","The number is used!");
        messageBox.setFixedSize(500,200);
        return true;
    } else if (!Luhn::test(number)) {
        messageBox.critical(0,"Number error","The number is wrong!");
        messageBox.setFixedSize(500,200);
        return true;
    }
    return false;
}

bool checkDate (const std::string &date){
    QMessageBox messageBox;
    const std::regex date_pattern("[0-1]*[0-9][/][2][0][0-4][0-9]");
    if (!std::regex_match(date, date_pattern)) {
        messageBox.critical(0,"Date error","Wrong date format (MM/RRRR)!");
        messageBox.setFixedSize(500,200);
        return true;
    }
    return false;
}

void DataBase::deleteCard(const int &choice){
    cards_data.erase(cards_data.begin() + choice);
    cards_data.shrink_to_fit();
}
