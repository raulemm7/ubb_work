//
// Created by raulo on 6/25/2024.
//

#include "MasinaGUI.h"
#include <QtWidgets/qmessagebox.h>

void MasinaGUI::init_gui() {
    this->setLayout(this->main_layout);

    this->table_view->setModel(this->table_model);
    this->table_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->table_view->setSelectionMode(QAbstractItemView::MultiSelection);
    this->main_layout->addWidget(this->table_view);

    this->btn_layout->addWidget(this->btn_add);
    this->btn_layout->addWidget(this->btn_sub);
    this->right_layout->addLayout(this->btn_layout);

    this->right_layout->addWidget(this->btn_delete);
    this->right_layout->addWidget(this->btn_undo);
    this->right_layout->addWidget(this->btn_redo);

    this->main_layout->addLayout(this->right_layout);
}

void MasinaGUI::load_data(std::vector<Masina> &vec) {
    this->table_model->setData(vec);
}

void MasinaGUI::connect_signals() {
    QObject::connect(this->btn_add, &QPushButton::clicked, this, [&](){
        // pentru fiecare masina din vector, incrementez anul de fabricatie cu 1
        auto& vec = this->service.get_lista_sortata(this->storage);
        for(auto& m : vec) {
            this->service.modifica_masina(this->storage, m.getNrInmatriculare(), 1);
        }
        this->load_data(vec);
    });

    QObject::connect(this->btn_sub, &QPushButton::clicked, this, [&](){
        // // pentru fiecare masina din vector, decrementez anul de fabricatie cu 1
        auto& vec = this->service.get_lista_sortata(this->storage);
        for(auto& m : vec) {
            this->service.modifica_masina(this->storage, m.getNrInmatriculare(), -1);
        }
        this->load_data(vec);
    });

    QObject::connect(this->btn_delete, &QPushButton::clicked, this, [&](){
        // iau elementele selectate din tabel
        auto elementeSelectate = this->table_view->selectionModel();
        // verific daca ceva a fost selectat
        if(elementeSelectate->hasSelection()){
            int k = 0; // pasul

            // iau fiecare rand selectat din tabel
            auto selectedRow = elementeSelectate->selectedRows();

            // sterg elementul din repo care se afla pe randul selectedRow in tabel
            auto& vec = this->storage.getListaMasina();
            for(auto singleRow : selectedRow){
                int poz_row = singleRow.row();
                auto& m = vec[poz_row + k];
                k++;

                this->service.sterge_masina(this->storage, m.getNrInmatriculare());
            }

            // dupa operatiile de stergere, salvez in fisier si updatez tabelul
            this->storage.save_to_file();
            this->load_data(this->service.get_lista_sortata(this->storage));
        }
    });

    QObject::connect(this->btn_undo, &QPushButton::clicked, this, [&](){
        std::string m = this->service.executa_undo(this->storage);
        // daca nu se mai poate face undo, afisez mesaj de atentionare
        if(m == "Nu se mai poate face undo!") {
            QMessageBox::information(nullptr, QString::fromStdString("eroare"), QString::fromStdString(m));
            return;
        }

        this->load_data(this->service.get_lista_sortata(this->storage));
        this->storage.save_to_file();
    });
}
