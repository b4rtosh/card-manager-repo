#include "dataBase.h"
#include "qdebug.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <QFile>


void DataBase::loadData() {

    QFile file ("C:/Users/Public/Documents/bazadanych.txt");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }
        std::string line;
        unsigned int semicolon1{}, semicolon2{};
        while (!file.atEnd())  {
        line = file.readLine();
            semicolon2 = line.find(';');
            Luhn card(std::stol(line.substr(0, semicolon2)));
            Luhn::addID(card.getID() + 1);

            semicolon1 = line.find(';', semicolon2 + 1);
            card.setName(line.substr(semicolon2 + 1, semicolon1 - semicolon2 - 1));

            semicolon2 = line.find(';', semicolon1 + 1);
            card.setSurname(line.substr(semicolon1 + 1, semicolon2 - semicolon1 - 1));

            semicolon1 = line.find(';', semicolon2 + 1);
            card.setBrand(line.substr(semicolon2 + 1, semicolon1 - semicolon2 - 1));

            semicolon2 = line.find(';', semicolon1 + 1);
            card.setNumber(line.substr(semicolon1 + 1, semicolon2 - semicolon1 - 1));

            semicolon1 = line.find(';', semicolon2 + 1);
            card.setDate(std::stoi(line.substr(semicolon2 + 1,semicolon1 - semicolon2 - 1)),
                         std::stoi(line.substr(semicolon1 + 1, 4)));

            card.setValidity(checkValidity(card.getDate().month, card.getDate().year));

            used_numbers.emplace_back(card.getNumber());
            cards_data.push_back(card);
        }

}

void DataBase::saveData(){
        QFile file ("C:/Users/Public/Documents/bazadanych.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.resize(0);
            QTextStream out(&file);
            QString line;
            for (int i = 0; i < cards_data.capacity(); i++) {
                line = QString::number(cards_data[i].getID());
                line.append(';'+cards_data[i].getName()+';'+cards_data[i].getSurname()+';'+cards_data[i].getBrand()+';'
                            +cards_data[i].getNumber()+';');
                line.append(QString::number(cards_data[i].getDate().month));
                line.append(';');
                line.append(QString::number(cards_data[i].getDate().year));
                line.append('\n');
                out << line;
            }
        }
}
/*
 void DataBase::saveData() {
    std::ofstream inFile;
    inFile.open(R"(C:\Users\Public\Documents\bazadanych.txt)", std::ios::trunc); // otworzenie czystego pliku na dane
    std::cout << std::setfill('0') << std::setw(2);
    if (inFile.is_open()) // zapisywanie bazy danych do pliku pod warunkiem otwarcia pliku
    {
        for (int i = 0; i < cards_data.capacity(); i++) {
            inFile << cards_data[i].getID() << ';' << cards_data[i].getName() << ';' << cards_data[i].getSurname()
                   << ';' << cards_data[i].getBrand() << ';' << cards_data[i].getNumber() << ';'
                   << cards_data[i].getDate().month << ';' << cards_data[i].getDate().year << '\n';
        }
    } else
        std::cout << "Plik otwarty niepoprawnie.\n"; // informacja o niepowodzeniu w otwarciu pliku
    inFile.close();
}

*/
