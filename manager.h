#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include "luhn.h"
#include "dataBase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Manager; }
QT_END_NAMESPACE

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    Manager(QWidget *parent = nullptr);
    ~Manager();
    void formatCardsTable (const int &capacity);
    void updateCardsTable (const std::vector <Luhn> &table);
    void getCard();
    void refreshTab();
    void deleteRow();
    void editCard();
    void editCardData(const int& index);
    void editRow();
    void changeData(const int& row_num);
private slots:
    void on_add_button_clicked();

    void on_delete_button_clicked();

    void on_edit_button_clicked();

    void on_close_button_clicked();

private:
    Ui::Manager *ui;
    DataBase cards;
};
#endif // MANAGER_H
