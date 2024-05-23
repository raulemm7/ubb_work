//
// Created by raulo on 5/22/2024.
//

#include "StockGUI.h"
#include "validators.h"

void StockGUI::init_gui() {
    this->setLayout(this->main_layout);

    // left part
    this->left_layout->addWidget(this->lista_stockuri);

    this->main_layout->addLayout(this->left_layout);

    // right part
    this->tabel_date->addRow("ID:", this->linie_id);
    this->tabel_date->addRow("Nume: ", this->linie_nume);
    this->tabel_date->addRow("Pret:", this->linie_pret);
    this->tabel_date->addRow("Change Ratio:", this->linie_change);
    this->right_layout->addLayout(this->tabel_date);

    this->butoane_layout->addWidget(this->buton_add);
    this->butoane_layout->addWidget(this->buton_delete);
    this->right_layout->addLayout(this->butoane_layout);

    this->main_layout->addLayout(this->right_layout);
}

void StockGUI::load_data(vector<StockObject> &vector_stocks) {
    this->lista_stockuri->clear();
    for(const auto& item:vector_stocks) {
        string data_list = item.getId();
        data_list += " " + std::to_string(item.getPret());

        auto* list_item = new QListWidgetItem(QString::fromStdString(data_list));
        list_item->setData(Qt::UserRole, QString::fromStdString(item.getNume()));

        if(item.getChangeRate() < 0) {
            // rosu
            list_item->setBackground(QBrush(Qt::red));
        }
        else {
            // verde
            list_item->setBackground(QBrush(Qt::green));
        }

        this->lista_stockuri->addItem(list_item);
    }
}

void StockGUI::connect_butoane() {
    QObject::connect(this->lista_stockuri, &QListWidget::itemSelectionChanged, [&](){
        auto selected = this->lista_stockuri->selectedItems();
        if(selected.isEmpty()){
            this->linie_id->setText("");
            this->linie_nume->setText("");
            this->linie_pret->setText("");
            this->linie_change->setText("");
        }
        else {
            auto selected_item = selected.at(0);
            string nume_stock = selected_item->data(Qt::UserRole).toString().toStdString();

            auto stk = this->storage.getStock(nume_stock);
            this->linie_id->setText(QString::fromStdString(stk.getId()));
            this->linie_nume->setText(QString::fromStdString(nume_stock));
            this->linie_pret->setText(QString::number(stk.getPret()));
            this->linie_change->setText(QString::number(stk.getChangeRate()));
        }
    });

    QObject::connect(this->buton_delete, &QPushButton::clicked, this, &StockGUI::sterge_gui);
}

void StockGUI::sterge_gui() {
    if(this->linie_nume->text().isEmpty()) {
        string m = "Introdu numele stockului pe care doresti sa il stergi!";

        QMessageBox msg_box;
        msg_box.setText(QString::fromStdString(m));
        msg_box.exec();

        return;
    }

    string nume = this->linie_nume->text().toStdString();

    // numele pe care l am bagat e inregistrat
    Validator vali;
    if(!vali.cautare_nume_in_storage(this->storage, nume)) {
        string m = "Numele nu a fost gasit in repo!";

        QMessageBox msg_box;
        msg_box.setText(QString::fromStdString(m));
        msg_box.exec();

        return;
    }

    auto exec_msg = this->service.sterge_stock_service(this->storage, nume);
    this->load_data(this->storage.getListaStocks());
    this->storage.save_to_file();

    QMessageBox msg_box;
    msg_box.setText(QString::fromStdString(exec_msg));
    msg_box.exec();
}
