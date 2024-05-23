//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_ROCHIE_ROCHIEGUI_H
#define SIMULARE_ROCHIE_ROCHIEGUI_H

#include <QWidget>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qmessagebox.h>

#include "domain.h"
#include "repository.h"
#include "service.h"

class rochieGUI:public QWidget{
private:
    QHBoxLayout* main_layout = new QHBoxLayout;

    QVBoxLayout* left_layout = new QVBoxLayout;
    QListWidget* lista_date = new QListWidget;

    QVBoxLayout* right_layout = new QVBoxLayout;
    QPushButton* inchiriere_buton = new QPushButton{"&Inchiriaza"};
    QPushButton* sort_marime_buton = new QPushButton{"&Sorteaza dupa marime"};
    QPushButton* sort_pret_buton = new QPushButton{"&Sorteaza dupa pret"};
    QPushButton* nesortat_buton = new QPushButton{"&Nesortat"};

    void init_gui();
    void load_data(vector<Rochie>& vector_data);
    void connect_buttons();

    Repository& storage;
    Service& service;

    void sort_marime_gui();
    void sort_pret_gui();

public:
    rochieGUI(Repository& repo, Service& serv) : storage{repo}, service{serv}{
        this->init_gui();
        this->load_data(this->storage.getListaRochii());
        this->connect_buttons();
    };
};

#endif //SIMULARE_ROCHIE_ROCHIEGUI_H
