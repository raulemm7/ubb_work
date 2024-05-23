//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_IMBRACAMINTE_IMBRACAMINTEGUI_H
#define SIMULARE_IMBRACAMINTE_IMBRACAMINTEGUI_H

#include <QWidget>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qmessagebox.h>

#include "repository.h"
#include "service.h"
#include "domain.h"

class ImbracaminteGUI : public QWidget{
private:
    QHBoxLayout* main_layout = new QHBoxLayout;

    QVBoxLayout* left_layout = new QVBoxLayout;
    QTableWidget* tabel_date = new QTableWidget;

    QVBoxLayout* right_layout = new QVBoxLayout;
    QLabel* tip_label = new QLabel{"Introdu tipul pentru filtrare:"};
    QLineEdit* linie_tip = new QLineEdit;
    QPushButton* buton_filtrare = new QPushButton{"&Filtreaza"};
    QPushButton* buton_sortare_tip = new QPushButton{"&Sorteaza dupa tip"};
    QPushButton* buton_sortare_pret = new QPushButton{"&Sorteaza dupa pret"};
    QPushButton* buton_nesortat = new QPushButton{"&Nesortat"};

    void init_gui();
    void load_data(vector<Imbracaminte>& lista_date);
    void connect_buttons();

    Repository& storage;
    Service& service;

    void filtreaza_dupa_tip();
    void sort_tip_gui();
    void sort_pret_gui();
public:
    ImbracaminteGUI(Repository& repo, Service& serv) : storage{repo}, service{serv}{
        this->init_gui();
        this->load_data(repo.getListaHaine());
        this->connect_buttons();
    };
};

#endif //SIMULARE_IMBRACAMINTE_IMBRACAMINTEGUI_H
