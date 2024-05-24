//
// Created by raulo on 5/24/2024.
//

#include "pixGUI.h"
#include "validators.h"

void pixGUI::init_gui() {
    this->setLayout(this->main_layout);

    // left
    this->left_layout->addWidget(this->lista_items);
    this->main_layout->addLayout(this->left_layout);

    // right
    this->data_form->addRow("Brand: ", this->line_brand);
    this->data_form->addRow("Culoare: ", this->line_culoare);
    this->data_form->addRow("Pret: ", this->line_pret);
    this->right_layout->addLayout(this->data_form);

    this->butoane_layout->addWidget(this->buton_sortare_brand);
    this->butoane_layout->addWidget(this->buton_sortare_pret);
    this->butoane_layout->addWidget(this->buton_nesortat);
    this->right_layout->addLayout(this->butoane_layout);
    this->main_layout->addLayout(this->right_layout);
}

void pixGUI::load_data(vector<Pix> &vector_data) {
    this->lista_items->clear();

    for(auto const& pix : vector_data) {
        auto* linie_list = new QListWidgetItem{QString::fromStdString(pix.getPixString())};
        linie_list->setData(Qt::UserRole, QString::number(pix.getId()));

        if(pix.getCuloare() == "albastru") {
            linie_list->setBackground(QBrush(Qt::blue));
        }
        if(pix.getCuloare() == "rosu") {
            linie_list->setBackground(QBrush(Qt::red));
        }
        if(pix.getCuloare() == "galben") {
            linie_list->setBackground(QBrush(Qt::yellow));
        }
        if(pix.getCuloare() == "verde") {
            linie_list->setBackground(QBrush(Qt::green));
        }

        this->lista_items->addItem(linie_list);
    }
}

void pixGUI::connect_buttons() {
    // conectare hover lista
    QObject::connect(this->lista_items, &QListWidget::itemSelectionChanged, this, [&](){
       auto selected_widg = this->lista_items->selectedItems();
       if(selected_widg.isEmpty()) {
           this->line_brand->setText(QString::fromStdString(""));
           this->line_culoare->setText(QString::fromStdString(""));
           this->line_pret->setText(QString::fromStdString(""));
       }
       else {
           auto selected_item = selected_widg.at(0);
           int cod = selected_item->data(Qt::UserRole).toInt();

           auto item = this->storage.getPix(cod);
           this->line_brand->setText(QString::fromStdString(item.getBrand()));
           this->line_culoare->setText(QString::fromStdString(item.getCuloare()));
           this->line_pret->setText(QString::number(item.getPret()));
       }
    });

    // conectare butoane de sortare
    QObject::connect(this->buton_sortare_brand, &QPushButton::clicked, this, &pixGUI::sort_brand_gui);
    QObject::connect(this->buton_sortare_pret, &QPushButton::clicked, this, &pixGUI::sort_pret_gui);

    // conectare buton nesortat
    QObject::connect(this->buton_nesortat, &QPushButton::clicked, this, [&](){
        this->load_data(this->storage.getListaPixuri());
    });
}

void pixGUI::sort_brand_gui() {
    auto vect = this->service.generic_sort(this->storage, Validator::compara_dupa_brand_crescator);
    this->load_data(vect);
}

void pixGUI::sort_pret_gui() {
    auto vect = this->service.generic_sort(this->storage, Validator::compara_dupa_pret_descrescator);
    this->load_data(vect);
}
