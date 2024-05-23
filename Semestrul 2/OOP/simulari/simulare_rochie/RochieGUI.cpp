//
// Created by raulo on 5/23/2024.
//

#include "RochieGUI.h"
#include "validator.h"

void rochieGUI::init_gui() {
    this->setLayout(this->main_layout);

    // left
    this->left_layout->addWidget(this->lista_date);
    this->main_layout->addLayout(this->left_layout);

    // right
    this->right_layout->addWidget(this->inchiriere_buton);
    this->right_layout->addWidget(this->sort_marime_buton);
    this->right_layout->addWidget(this->sort_pret_buton);
    this->right_layout->addWidget(this->nesortat_buton);
    this->main_layout->addLayout(this->right_layout);
}

void rochieGUI::load_data(vector<Rochie>& vector_data) {
    this->lista_date->clear();

    for(auto const& item : vector_data) {
        auto* list_item = new QListWidgetItem{QString::fromStdString(item.rochieString())};

        if(item.isDisponibilitate())
            list_item->setBackground(QBrush(Qt::green));
        else
            list_item->setBackground(QBrush(Qt::red));

        list_item->setData(Qt::UserRole, QString::number(item.getCod()));

        this->lista_date->addItem(list_item);
    }
}

void rochieGUI::connect_buttons() {
    QObject::connect(this->inchiriere_buton, &QPushButton::clicked, this, [&](){
       auto selected = this->lista_date->selectedItems();
       if(!selected.isEmpty()) {
           auto selected_item = selected.at(0);
           int cod = selected_item->data(Qt::UserRole).toInt();

           auto m = this->service.set_disponibilitate_rochie(this->storage, cod);
           this->storage.save_to_file();
           this->load_data(this->storage.getListaRochii());

           QMessageBox qmb;
           qmb.setText(QString::fromStdString(m));
           qmb.exec();

       }
    });

    QObject::connect(this->sort_marime_buton, &QPushButton::clicked, this, &rochieGUI::sort_marime_gui);
    QObject::connect(this->sort_pret_buton, &QPushButton::clicked, this, &rochieGUI::sort_pret_gui);

    QObject::connect(this->nesortat_buton, &QPushButton::clicked, this, [&](){
       this->load_data(this->storage.getListaRochii());
    });
}

void rochieGUI::sort_marime_gui() {
    auto vec = this->service.generic_sort(this->storage, Validator::compare_marime);
    this->load_data(vec);
}

void rochieGUI::sort_pret_gui() {
    auto vec = this->service.generic_sort(this->storage, Validator::compare_pret);
    this->load_data(vec);
}
