//
// Created by raulo on 5/29/2024.
//

#include "RetetaGUI_CRUD.h"

void RetetaCRUDGUI::init_gui() {
    this->setLayout(this->main_layout);

    this->main_layout->addWidget(this->lista_meds);

    this->main_layout->addWidget(this->reteta_meds);

    this->butoane_layout->addWidget(this->button_add);
    this->butoane_layout->addWidget(this->button_delete_all);
    this->butoane_layout->addWidget(this->line_info);
    this->butoane_layout->addWidget(this->button_generate);
    this->butoane_layout->addWidget(this->button_export);

    this->main_layout->addLayout(this->butoane_layout);
}

void RetetaCRUDGUI::load_data(vector<Medicament>& meds) {
    this->lista_meds->clear();
    for(auto const& item: meds) {
        auto* list_item = new QListWidgetItem(QString::fromStdString(item.get_denumire()));
        list_item->setData(Qt::UserRole, item.get_id());
        this->lista_meds->addItem(list_item);
    }
}

void RetetaCRUDGUI::connect_buttons() {
    QObject::connect(this->button_add, &QPushButton::clicked, this, [&](){
        auto selectedItems = this->lista_meds->selectedItems();
        if(selectedItems.isEmpty()) {
            auto* qmb = new QMessageBox;
            qmb->setText(QString::fromStdString("Selecteaza un medicament!"));
            qmb->exec();
            delete qmb;
        }
        else {
            auto item = selectedItems.at(0);
            int id = item->data(Qt::UserRole).toInt();

            const auto& med = this->storage_meds.get_med(id);

            this->service.adaugaMedicamentReteta(this->lista_meds_pt_reteta, med);
            this->reload_reteta(this->lista_meds_pt_reteta.get_all());
        }
    });

    QObject::connect(this->button_delete_all, &QPushButton::clicked, this, &RetetaCRUDGUI::delete_all_gui);
    QObject::connect(this->button_generate, &QPushButton::clicked, this, &RetetaCRUDGUI::genereaza_random_gui);
    QObject::connect(this->button_export, &QPushButton::clicked, this, &RetetaCRUDGUI::export_html_gui);
}

void RetetaCRUDGUI::reload_reteta(vector<Medicament> &meds) {
    this->reteta_meds->clear();
    for(auto const& item: meds) {
        auto* list_item = new QListWidgetItem(QString::fromStdString(item.get_denumire()));
        list_item->setData(Qt::UserRole, item.get_id());
        this->reteta_meds->addItem(list_item);
    }
}

void RetetaCRUDGUI::genereaza_random_gui() {
    if(this->line_info->text().isEmpty()) {
        QMessageBox::information(nullptr, "Error", QString::fromStdString("Introdu numarul de medicamente pe care doresti "
                                                                          "sa le generezi!"));
        return;
    }

    this->service.adaugareRandom(this->storage_meds, this->lista_meds_pt_reteta, this->line_info->text().toInt());
    this->reload_reteta(this->lista_meds_pt_reteta.get_all());

    QMessageBox::information(nullptr, "Succes", QString::fromStdString("Medicamente adaugate cu succes pe reteta!"));
}

void RetetaCRUDGUI::export_html_gui() {
    if(this->line_info->text().isEmpty()) {
        QMessageBox::information(nullptr, "Error", QString::fromStdString("Introdu un nume de fisier unde doresti sa"
                                                                          "exportezi reteta!"));
        return;
    }

    const string& file_name = this->line_info->text().toStdString();
    if(file_name.find(".html") == std::string::npos) {
        QMessageBox::information(nullptr, "Error", QString::fromStdString("Introdu extensia .html fisierului pentru a "
                                                                          "putea salva!"));
        return;
    }

    auto msg = this->service.exportDataInHTMLformat(this->lista_meds_pt_reteta, file_name, this->nr_reteta);

    this->nr_reteta++;
    QMessageBox::information(nullptr, "Succes", QString::fromStdString(msg));
}

void RetetaCRUDGUI::delete_all_gui() {
    auto str = this->service.stergeToateMedicamentele(this->lista_meds_pt_reteta);

    this->reload_reteta(this->lista_meds_pt_reteta.get_all());
    QMessageBox::information(nullptr, "Succes", QString::fromStdString(str));
}

