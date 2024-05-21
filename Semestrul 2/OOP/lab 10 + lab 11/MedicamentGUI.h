//
// Created by raulo on 5/16/2024.
//

#ifndef LAB10_11_MEDICAMENTGUI_H
#define LAB10_11_MEDICAMENTGUI_H

#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qmessagebox.h>
#include "repository.h"
#include "service.h"

class MedicamentGUI:public QWidget {
private:
    QHBoxLayout* mainLayout = new QHBoxLayout;

    QVBoxLayout* leftLayout = new QVBoxLayout;
    QListWidget* listaMedicamente = new QListWidget;

    QHBoxLayout* butoaneFiltrare = new QHBoxLayout;
    QPushButton* filterByPrice = new QPushButton("&Filtreaza dupa pret");
    QPushButton* filterBySubstance = new QPushButton("&Filtreaza dupa substanta");
    QPushButton* quickadd = new QPushButton("&Adauga rapid");

    QHBoxLayout* butoaneSortare = new QHBoxLayout;
    QPushButton* sortByName = new QPushButton("&Sorteaza dupa denumire");
    QPushButton* sortByProd = new QPushButton("&Sorteaza dupa producator");
    QPushButton* sortBySubstAndPrice = new QPushButton("&Sorteaza dupa subst si pret");

    QVBoxLayout* rightLayout = new QVBoxLayout;

    QFormLayout* dataForm = new QFormLayout;
    QPushButton* addMed = new QPushButton("&Adauga");

    QHBoxLayout* butoane_del_mod_ser = new QHBoxLayout;
    QPushButton* deleteMed = new QPushButton("&Sterge");
    QPushButton* modifyMed = new QPushButton("&Modifica");
    QPushButton* searchMed = new QPushButton("&Cauta");

    QHBoxLayout* butoane_buc_rap_undo = new QHBoxLayout;
    QPushButton* bucket = new QPushButton("&Reteta");
    QPushButton* raport = new QPushButton("&Raport");
    QPushButton* undo = new QPushButton("&Undo");

    QLineEdit* id_med = new QLineEdit;
    QLineEdit* denumire = new QLineEdit;
    QLineEdit* pret = new QLineEdit;
    QLineEdit* producator = new QLineEdit;
    QLineEdit* subst = new QLineEdit;
    QLineEdit* oper = new QLineEdit;

    Service& serv;
    MedicamenteRepo& repo;

    void init_gui();

    void load_data(vector<Medicament>& meds);

    void connect_buttons();

    static void message_box(string& informatie);

    void gui_adauga_rapid();
    void gui_adauga_med();
    void gui_sterge_med();
    void gui_modifica_med();
    void gui_cauta_med();
    void gui_sort_denumrie();
    void gui_sort_producator();
    void gui_sort_price_and_subst();
    void gui_filtrare_dupa_substanta();
    void gui_filtrare_dupa_pret();
    void gui_undo();
public:
    MedicamentGUI(Service& service, MedicamenteRepo& storage):serv{service},repo{storage}{
        this->init_gui();
        this->load_data(this->repo.get_all());
        this->connect_buttons();
    };
};

#endif //LAB10_11_MEDICAMENTGUI_H
