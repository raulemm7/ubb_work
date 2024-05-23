//
// Created by raulo on 5/22/2024.
//

#ifndef SIMULARE_STOCKS_STOCKGUI_H
#define SIMULARE_STOCKS_STOCKGUI_H

#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qmessagebox.h>

#include "repository.h"
#include "service.h"

class StockGUI:public QWidget {
private:
    QHBoxLayout* main_layout = new QHBoxLayout;

    QVBoxLayout* left_layout = new QVBoxLayout;
    QListWidget* lista_stockuri = new QListWidget;

    QVBoxLayout* right_layout = new QVBoxLayout;
    QFormLayout* tabel_date = new QFormLayout;
    QLineEdit* linie_id = new QLineEdit;
    QLineEdit* linie_nume = new QLineEdit;
    QLineEdit* linie_pret = new QLineEdit;
    QLineEdit* linie_change = new QLineEdit;

    QHBoxLayout* butoane_layout = new QHBoxLayout;
    QPushButton* buton_add = new QPushButton("&Adauga");
    QPushButton* buton_delete = new QPushButton("&Sterge");

    RepoObject& storage;
    Service& service;

    void init_gui();
    void load_data(vector<StockObject>& vector_stocks);
    void connect_butoane();

    void sterge_gui();
public:
    StockGUI(RepoObject& repo, Service& serv):storage{repo}, service{serv}{
        this->init_gui();
        this->load_data(repo.getListaStocks());
        this->connect_butoane();
    };
};

#endif //SIMULARE_STOCKS_STOCKGUI_H
