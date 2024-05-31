//
// Created by raulo on 5/29/2024.
//

#ifndef LAB10_11_RETETAGUI_CRUD_H
#define LAB10_11_RETETAGUI_CRUD_H

#include "Observer.h"
#include "file_repository.h"
#include "service.h"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qtablewidget.h>

class RetetaCRUDGUI : public QWidget, public Observer{
public:
    /**
     * constructor
     * @param repo repo cu medicamente inregistrate
     * @param serv service pentru a efectua operatii
     * @param lista_repo repo in care se vor stoca medicamentele de pe reteta
     */
    RetetaCRUDGUI(FileRepo& repo, Service& serv, MedicamenteRepo& lista_repo) : storage_meds{repo}, service{serv},
        lista_meds_pt_reteta{lista_repo}, nr_reteta{0}{
        this->service.addObserver(this);
        this->init_gui();
        this->load_data(storage_meds.get_all());
        this->reload_reteta(lista_repo.get_all());
        this->connect_buttons();
    };

    /**
     * destructor
     */
    ~RetetaCRUDGUI() override{
        this->service.removeObserver(this);
    }
private:
    /** elemente de UI */
    QHBoxLayout* main_layout = new QHBoxLayout;

    QListWidget* lista_meds = new QListWidget;

    QListWidget* reteta_meds = new QListWidget;

    QVBoxLayout* butoane_layout = new QVBoxLayout;
    QPushButton* button_add = new QPushButton{"&Adauga"};
    QPushButton* button_delete_all = new QPushButton{"&Sterge toate"};
    QLineEdit* line_info = new QLineEdit;
    QPushButton* button_generate = new QPushButton{"&Genereaza random"};
    QPushButton* button_export = new QPushButton{"&Export"};

    Service& service;
    FileRepo& storage_meds;
    MedicamenteRepo& lista_meds_pt_reteta;
    int nr_reteta;

    /** functii pentru operatiile aplicatie */
    void init_gui();
    void load_data(vector<Medicament>& meds);
    void connect_buttons();
    void reload_reteta(vector<Medicament> &meds);

    void genereaza_random_gui();
    void export_html_gui();
    void delete_all_gui();


    /** functia update() al clasei Observer */
    void update() override {
        this->reload_reteta(this->lista_meds_pt_reteta.get_all());
    }
};

#endif //LAB10_11_RETETAGUI_CRUD_H
