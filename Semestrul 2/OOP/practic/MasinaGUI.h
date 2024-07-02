//
// Created by raulo on 6/25/2024.
//

#ifndef PRACTIC_MASINAGUI_H
#define PRACTIC_MASINAGUI_H

#include "service.h"
#include "table_model.h"
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qboxlayout.h>

class MasinaGUI: public QWidget{
private:
    /** info utile */
    Service& service;
    RepoMasina& storage;

    /** functii */
    void init_gui();
    void load_data(std::vector<Masina>& vec);
    void connect_signals();

    /** elemente de ui */
    QHBoxLayout* main_layout = new QHBoxLayout;

    QTableView* table_view = new QTableView;
    CustomTableModel* table_model = new CustomTableModel(this);

    QVBoxLayout* right_layout = new QVBoxLayout;

    QHBoxLayout* btn_layout = new QHBoxLayout;
    QPushButton* btn_add = new QPushButton{"&+"};
    QPushButton* btn_sub = new QPushButton{"&-"};

    QPushButton* btn_delete = new QPushButton{"delete"};
    QPushButton* btn_undo = new QPushButton{"undo"};
    QPushButton* btn_redo = new QPushButton{"redo"};

public:
    /** constructor */
    MasinaGUI(Service& serv, RepoMasina& repo) : service(serv), storage(repo){
        this->init_gui();
        this->load_data(this->service.get_lista_sortata(this->storage));
        this->connect_signals();
    };
};

#endif //PRACTIC_MASINAGUI_H
