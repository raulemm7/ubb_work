//
// Created by raulo on 5/24/2024.
//

#ifndef SIMULARE_OOP_PIXGUI_H
#define SIMULARE_OOP_PIXGUI_H

#include <QWidget>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>

#include "domain.h"
#include "repository.h"
#include "service.h"

class pixGUI : public QWidget {
private:
    QHBoxLayout* main_layout = new QHBoxLayout;

    QVBoxLayout* left_layout = new QVBoxLayout;
    /** lista pentru afisarea elementelor */
    QListWidget* lista_items = new QListWidget;

    QVBoxLayout* right_layout = new QVBoxLayout;
    /** form unde se afiseaza datele despre un item selectat din lista */
    QFormLayout* data_form = new QFormLayout;
    /** lineedits pt afisearea informatiilor unui item din lista */
    QLineEdit* line_brand = new QLineEdit;
    QLineEdit* line_culoare = new QLineEdit;
    QLineEdit* line_pret = new QLineEdit;

    /** butoane */
    QVBoxLayout* butoane_layout = new QVBoxLayout;
    QPushButton* buton_sortare_brand = new QPushButton{"&Sortare dupa brand (crescator)"};
    QPushButton* buton_sortare_pret = new QPushButton{"&Sortare dupa pret (descrescator)"};
    QPushButton* buton_nesortat = new QPushButton{"&Nesortat"};

    /** initializare interfata */
    void init_gui();
    /** populare lista cu date */
    void load_data(vector<Pix>& vector_data);
    /** conectare butoane */
    void connect_buttons();

    /** referinte la obiectele de repo si service */
    Repository& storage;
    Service& service;

    /** sortare dupa brand */
    void sort_brand_gui();
    /** sortare dupa pret */
    void sort_pret_gui();

public:
    /** constructor */
    pixGUI(Repository& repo, Service& serv) : storage{repo}, service{serv}{
        this->init_gui();
        this->load_data(repo.getListaPixuri());
        this->connect_buttons();
    };
};

#endif //SIMULARE_OOP_PIXGUI_H
