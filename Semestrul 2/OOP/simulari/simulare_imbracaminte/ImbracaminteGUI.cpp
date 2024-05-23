//
// Created by raulo on 5/23/2024.
//

#include "ImbracaminteGUI.h"
#include "validator.h"

void ImbracaminteGUI::init_gui() {
    this->setLayout(this->main_layout);

    // left
    this->left_layout->addWidget(this->tabel_date);
    this->main_layout->addLayout(this->left_layout);

    // right
    this->right_layout->addWidget(this->tip_label);
    this->right_layout->addWidget(this->linie_tip);
    this->right_layout->addWidget(this->buton_filtrare);
    this->right_layout->addWidget(this->buton_sortare_tip);
    this->right_layout->addWidget(this->buton_sortare_pret);
    this->right_layout->addWidget(this->buton_nesortat);
    this->main_layout->addLayout(this->right_layout);
}

void ImbracaminteGUI::load_data(vector<Imbracaminte>& lista_date) {
    this->tabel_date->clear();

    this->tabel_date->setColumnCount(3);
    this->tabel_date->setRowCount(lista_date.size());
    this->tabel_date->setHorizontalHeaderItem(0, new QTableWidgetItem{"Tip"});
    this->tabel_date->setHorizontalHeaderItem(1, new QTableWidgetItem{"Culoare"});
    this->tabel_date->setHorizontalHeaderItem(2, new QTableWidgetItem{"Pret"});

    int nr_linii = 0;
    for(auto const& item : lista_date) {
        auto* col_tip = new QTableWidgetItem{QString::fromStdString(item.getTip())};
        auto* col_culoare = new QTableWidgetItem{QString::fromStdString(item.getCuloare())};
        auto* col_pret = new QTableWidgetItem{QString::number(item.getPret())};

        if(item.getCuloare() == "rosu") {
            // rosu
            col_tip->setBackground(QBrush(Qt::red));
            col_culoare->setBackground(QBrush(Qt::red));
            col_pret->setBackground(QBrush(Qt::red));
        }
        else if(item.getCuloare() == "albastru") {
            // albastru
            col_tip->setBackground(QBrush(Qt::blue));
            col_culoare->setBackground(QBrush(Qt::blue));
            col_pret->setBackground(QBrush(Qt::blue));
        }
        else if(item.getCuloare() == "verde") {
            // verde
            col_tip->setBackground(QBrush(Qt::green));
            col_culoare->setBackground(QBrush(Qt::green));
            col_pret->setBackground(QBrush(Qt::green));
        }
        else {
            //
            col_tip->setBackground(QBrush(Qt::yellow));
            col_culoare->setBackground(QBrush(Qt::yellow));
            col_pret->setBackground(QBrush(Qt::yellow));
        }

        this->tabel_date->setItem(nr_linii, 0, col_tip);
        this->tabel_date->setItem(nr_linii, 1, col_culoare);
        this->tabel_date->setItem(nr_linii, 2, col_pret);

        nr_linii++;
    }
}

void ImbracaminteGUI::connect_buttons() {
    QObject::connect(this->buton_filtrare, &QPushButton::clicked, this, &ImbracaminteGUI::filtreaza_dupa_tip);
    QObject::connect(this->buton_sortare_tip, &QPushButton::clicked, this, &ImbracaminteGUI::sort_tip_gui);
    QObject::connect(this->buton_sortare_pret, &QPushButton::clicked, this, &ImbracaminteGUI::sort_pret_gui);
    QObject::connect(this->buton_nesortat, &QPushButton::clicked, this, [&](){
       this->load_data(this->storage.getListaHaine());
    });
}

void ImbracaminteGUI::filtreaza_dupa_tip() {
    string tip = this->linie_tip->text().toStdString();
    if(tip.empty()) {
        string m = "Introdu un tip pentru a face filtrarea!";

        QMessageBox qmb;
        qmb.setText(QString::fromStdString(m));
        qmb.exec();

        return;
    }

    auto vector_haine = this->service.filtrare_dupa_tip(this->storage, tip);
    this->load_data(vector_haine);
}

void ImbracaminteGUI::sort_tip_gui() {
    auto vec = this->service.generic_sort(this->storage, Validator::compare_tip);
    this->load_data(vec);
}

void ImbracaminteGUI::sort_pret_gui() {
    auto vec = this->service.generic_sort(this->storage, Validator::compare_pret);
    this->load_data(vec);
}
