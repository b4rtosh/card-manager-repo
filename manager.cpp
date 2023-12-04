#include "manager.h"
#include "./ui_manager.h"
#include "ui_addDialog.h"
#include "ui_deleteFirstDialog.h"
#include "ui_deleteDialog.h"
#include <string>
#include "ui_editDialog.h"

Manager::Manager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Manager)
{
    cards.actualDate();
    cards.loadData();
    ui->setupUi(this);
    formatCardsTable(cards.getCapacity());
    updateCardsTable(cards.getTable());
}

Manager::~Manager()
{
    delete ui;
}

void Manager::formatCardsTable (const int &capacity){
    ui->cards_table->clear();
    ui->cards_table->setColumnCount(6);
    ui->cards_table->setRowCount(4);
    ui->cards_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // rozszerzanie tabeli
    ui->cards_table->setHorizontalHeaderItem(0, new QTableWidgetItem("Brand"));
    ui->cards_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
    ui->cards_table->setHorizontalHeaderItem(2, new QTableWidgetItem("Surname"));
    ui->cards_table->setHorizontalHeaderItem(3, new QTableWidgetItem("Number"));
    ui->cards_table->setHorizontalHeaderItem(4, new QTableWidgetItem("Date"));
    ui->cards_table->setHorizontalHeaderItem(5, new QTableWidgetItem("Valiadity"));
    ui->cards_table->setEditTriggers(QAbstractItemView::NoEditTriggers); }

void Manager::updateCardsTable (const std::vector <Luhn> &table) {
    for (int i = 0; i < table.capacity(); ++i){
        ui->cards_table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(table[i].getBrand())));

        ui->cards_table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(table[i].getName())));

        ui->cards_table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(table[i].getSurname())));

        ui->cards_table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(table[i].getNumber())));

        ui->cards_table->setItem(i, 4, new QTableWidgetItem
                                (QString::number(table[i].getDate().month)+'/'+QString::number(table[i].getDate().year)));

        ui->cards_table->setItem(i, 5, new QTableWidgetItem(table[i].getValidity() ? "Yes" : "No"));
    }
}

void Manager::getCard(){
    QDialog addCard;
    Ui::AddDialog ui;
    ui.setupUi(&addCard);
    //connect(ui.buttonBox, SIGNAL(accepted()),this,SLOT(confirmedCard()));
    //connect(this,SIGNAL(addedCard(bool)),this,SLOT(refreshTab(bool)));

    ui.brand_combo->addItem(QString("Visa"));
    ui.brand_combo->addItem(QString("MasterCard"));
    std::string s_name, s_surname, s_number, s_brand, s_date;
    bool b_name{}, b_surname{}, b_number{}, b_date{};
    QString name, surname, number, date, brand;

    while (true){
        if(b_name)ui.name_edit->clear();
        if(b_surname)ui.surname_edit->clear();
        if(b_number)ui.number_edit->clear();
        if(b_date)ui.date_edit->clear();

        if(addCard.exec())
        {
            name = ui.name_edit->text();
            surname = ui.surname_edit->text();
            number = ui.number_edit->text();
            date = ui.date_edit->text();
            brand = ui.brand_combo->currentText();

            s_name = name.toStdString();
            s_surname = surname.toStdString();
            s_number = number.toStdString();
            s_date = date.toStdString();
            s_brand = brand.toStdString();

            b_name = checkName(s_name);
            b_surname = checkSurname(s_surname);
            b_number = checkNumber(s_number);
            b_date = checkDate (s_date);

            if (b_name || b_surname || b_number || b_date)continue;

        }
        break;
    }
    cards.emplaceNumber(s_number);
    int pos = s_date.find('/', 0);
    int i_month = std::stoi(s_date.substr(0,pos));
    int i_year = std::stoi(s_date.substr(pos+1,4));
    Date d_date {i_month, i_year};
    Luhn new_card(s_number, s_name, s_surname, s_brand, d_date);
    cards.addCard(new_card);
    refreshTab();
}

void Manager::refreshTab (){
    //int new_row = cards.getCapacity();
    int new_row = ui->cards_table->rowCount();
    //formatCardsTable(manager.getCapacity());
    //updateCardsTable(manager.getTable());
    qDebug() << new_row;

   ui->cards_table->insertRow(new_row);
    ui->cards_table->setItem(new_row, 0, new QTableWidgetItem(QString::fromStdString(cards.getVector(new_row).getBrand())));

    ui->cards_table->setItem(new_row, 1, new QTableWidgetItem(QString::fromStdString(cards.getVector(new_row).getName())));

    ui->cards_table->setItem(new_row, 2, new QTableWidgetItem(QString::fromStdString(cards.getVector(new_row).getSurname())));

    ui->cards_table->setItem(new_row, 3, new QTableWidgetItem(QString::fromStdString(cards.getVector(new_row).getNumber())));

    ui->cards_table->setItem(new_row, 4, new QTableWidgetItem
                            (QString::number(cards.getVector(new_row).getDate().month)+'/'
                            +QString::number(cards.getVector(new_row).getDate().year)));

    ui->cards_table->setItem(new_row, 5, new QTableWidgetItem(cards.getVector(new_row).getValidity() ? "Yes" : "No"));
}

void Manager::on_add_button_clicked()
{
    getCard();
}

void Manager::deleteRow(){
    int row_num = ui->cards_table->currentRow();
   /* if(row_num == 0){
        QDialog deleteCardDialog;
        Ui::FirstDialog ui;
        ui.setupUi(&deleteCardDialog);
        if(deleteCardDialog.exec()){

            Manager::ui->cards_table->removeRow(row_num);
        }
    }
*/
        QDialog deleteCardDialog;
        Ui::DeleteDialog ui;
        ui.setupUi(&deleteCardDialog);
        for(int i = 1; i <= cards.getCapacity(); ++i){
            ui.delete_combo->addItem(QString::number(i));
        }
         ui.delete_combo->setCurrentIndex(row_num);
        if(deleteCardDialog.exec()){
            cards.used_numbers.erase(cards.used_numbers.begin()+(ui.delete_combo->currentIndex())+1);
            Manager::ui->cards_table->removeRow((ui.delete_combo->currentIndex()));
        }
}

void Manager::on_delete_button_clicked()
{
    deleteRow();
}

void Manager::editRow(){
    int row_num = ui->cards_table->currentRow();
    QDialog editCardDialog;
    Ui::EditDialog ui;
    ui.setupUi(&editCardDialog);
    for(int i = 1; i <= cards.getCapacity(); ++i){
            ui.edit_combo->addItem(QString::number(i));
    }
    ui.edit_combo->setCurrentIndex(row_num);
    if(editCardDialog.exec()){
            editCardData(ui.edit_combo->currentIndex());
    }
}

void Manager::changeData(const int& row_num){
    ui->cards_table->setItem(row_num, 0, new QTableWidgetItem(QString::fromStdString(cards.getVector(row_num).getBrand())));

    ui->cards_table->setItem(row_num, 1, new QTableWidgetItem(QString::fromStdString(cards.getVector(row_num).getName())));

    ui->cards_table->setItem(row_num, 2, new QTableWidgetItem(QString::fromStdString(cards.getVector(row_num).getSurname())));

    ui->cards_table->setItem(row_num, 3, new QTableWidgetItem(QString::fromStdString(cards.getVector(row_num).getNumber())));

    ui->cards_table->setItem(row_num, 4, new QTableWidgetItem
                             (QString::number(cards.getVector(row_num).getDate().month)+'/'+
                                QString::number(cards.getVector(row_num).getDate().year)));

    ui->cards_table->setItem(row_num, 5, new QTableWidgetItem(cards.getVector(row_num).getValidity() ? "Yes" : "No"));
}

void Manager::editCardData(const int& index){
    QDialog editDialog;
    Ui::AddDialog ui;
    ui.setupUi(&editDialog);
    ui.brand_combo->addItem(QString("Visa"));
    ui.brand_combo->addItem(QString("MasterCard"));
    std::string s_name, s_surname, s_number, s_brand, s_date;
    bool b_name{}, b_surname{}, b_number{}, b_date{};
    QString name, surname, number, date, brand;

    ui.name_edit->insert(QString::fromStdString(cards.getVector(index).getName()));
    ui.surname_edit->insert(QString::fromStdString(cards.getVector(index).getSurname()));
    ui.number_edit->insert(QString::fromStdString(cards.getVector(index).getNumber()));
    ui.date_edit->insert(QString::number(cards.getVector(index).getDate().month)+'/'+QString::number(cards.getVector(index).getDate().year));
    while (true){
            if(b_name)ui.name_edit->clear();
            if(b_surname)ui.surname_edit->clear();
            if(b_number)ui.number_edit->clear();
            if(b_date)ui.date_edit->clear();

            if(editDialog.exec())
            {
            name = ui.name_edit->text();
            surname = ui.surname_edit->text();
            number = ui.number_edit->text();
            date = ui.date_edit->text();
            brand = ui.brand_combo->currentText();

            s_name = name.toStdString();
            s_surname = surname.toStdString();
            s_number = number.toStdString();
            s_date = date.toStdString();
            s_brand = brand.toStdString();

            b_name = checkName(s_name);
            b_surname = checkSurname(s_surname);
            if(s_number != cards.getVector(index).getNumber())
                b_number = checkNumber(s_number);
            b_date = checkDate (s_date);

            if (b_name || b_surname || b_number || b_date)continue;

            }
            break;
    }
    int pos = s_date.find('/', 0);
    int i_month = std::stoi(s_date.substr(0,pos));
    int i_year = std::stoi(s_date.substr(pos+1,4));
    Luhn new_card(cards.getVector(index).getID());
    new_card.setName(s_name);
    new_card.setSurname(s_surname);
    new_card.setDate(i_month, i_year);
    new_card.setNumber(s_number);
    new_card.setBrand(s_brand);
    cards.used_numbers[index+1] = s_number;
    /*
    cards.getVector(index).setName(s_name);
    cards.getVector(index).setSurname(s_surname);
    cards.getVector(index).setNumber(s_number);
    cards.getVector(index).setDate(i_month,i_year);
    cards.getVector(index).setValidity(checkValidity(i_month,i_year));
    cards.getVector(index).setBrand(s_brand);
*/
    cards.changeElement(new_card,index);
    changeData(index);
}


void Manager::on_edit_button_clicked()
{
    editRow();
}


void Manager::on_close_button_clicked()
{
    cards.saveData();
    this->close();
}

