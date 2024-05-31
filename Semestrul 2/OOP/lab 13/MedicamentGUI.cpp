//
// Created by raulo on 5/16/2024.
//

#include "MedicamentGUI.h"
#include <vector>
#include <string>
#include "service.h"
#include "repository.h"

void MedicamentGUI::init_gui() {
    this->setLayout(this->mainLayout);

    // left layout
    this->layout_infos->addWidget(this->listaMedicamente);
    this->layout_infos->addWidget(this->tableMeds);
    this->leftLayout->addLayout(this->layout_infos);

    this->butoaneFiltrare->addWidget(this->filterByPrice);
    this->butoaneFiltrare->addWidget(this->filterBySubstance);
    this->butoaneFiltrare->addWidget(this->nesortat_button);
    this->leftLayout->addLayout(this->butoaneFiltrare);

    this->butoaneSortare->addWidget(this->sortByName);
    this->butoaneSortare->addWidget(this->sortByProd);
    this->butoaneSortare->addWidget(this->sortBySubstAndPrice);
    this->leftLayout->addLayout(this->butoaneSortare);

    this->mainLayout->addLayout(this->leftLayout);

    // right layout
    this->dataForm->addRow("ID: ", this->id_med);
    this->dataForm->addRow("Denumire: ", this->denumire);
    this->dataForm->addRow("Pret: ", this->pret);
    this->dataForm->addRow("Producator: ", this->producator);
    this->dataForm->addRow("Substanta activa: ", this->subst);
    this->dataForm->addRow("Operator: ", this->oper);
    this->dataForm->addRow("Numar random: ", this->generate_number_line);
    this->rightLayout->addLayout(this->dataForm);

    this->rightLayout->addWidget(this->generate_button);

    this->butoane_sus->addWidget(this->addMed);
    this->butoane_sus->addWidget(this->deleteMed);
    this->butoane_sus->addWidget(this->searchMed);
    this->butoane_sus->addWidget(this->modifyMed);
    this->rightLayout->addLayout(this->butoane_sus);

    this->butoane_jos->addWidget(this->reteta_CRUD);
    this->butoane_jos->addWidget(this->reteta_READ_ONLY);
    this->butoane_jos->addWidget(this->raport);
    this->butoane_jos->addWidget(this->undo);
    this->rightLayout->addLayout(this->butoane_jos);

    this->mainLayout->addLayout(this->rightLayout);

    this->mainLayout->addLayout(this->ly_butoane_automate);
}

void MedicamentGUI::load_data_in_list(vector<Medicament>& meds) {
    this->listaMedicamente->clear();
    for(auto const& item: meds) {
        auto* list_item = new QListWidgetItem(QString::fromStdString(item.get_denumire()));
        list_item->setData(Qt::UserRole, item.get_id());
        this->listaMedicamente->addItem(list_item);
    }
}

void MedicamentGUI::load_data_in_table(vector<Medicament> &meds) {
    this->tableMeds->clear();
    this->tableMeds->setColumnCount(4);
    this->tableMeds->setRowCount((int)meds.size());

    this->tableMeds->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromStdString("Denumire")));
    this->tableMeds->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromStdString("Pret")));
    this->tableMeds->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromStdString("Producator")));
    this->tableMeds->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromStdString("Substanta activa")));

    int nr_linii = 0;
    for(const auto& item: meds) {
        this->tableMeds->setItem(nr_linii, 0, new QTableWidgetItem(QString::fromStdString(item.get_denumire())));
        this->tableMeds->setItem(nr_linii, 1, new QTableWidgetItem(QString::number(item.get_pret())));
        this->tableMeds->setItem(nr_linii, 2, new QTableWidgetItem(QString::fromStdString(item.get_producator())));
        this->tableMeds->setItem(nr_linii, 3, new QTableWidgetItem(QString::fromStdString(item.get_subst_activa())));

        nr_linii++;
    }
}


void MedicamentGUI::connect_buttons() {
    QObject::connect(this->listaMedicamente, &QListWidget::itemSelectionChanged, [&](){
       auto selected = this->listaMedicamente->selectedItems();
       if(selected.isEmpty()){
           this->id_med->setText("");
           this->denumire->setText("");
           this->pret->setText("");
           this->producator->setText("");
           this->subst->setText("");
       }
       else{
           auto selectedItem = selected.at(0);
           this->denumire->setText(selectedItem->text());
           int id = selectedItem->data(Qt::UserRole).toInt();

           const auto& med = this->storage.get_med(id);
           this->id_med->setText(QString::number(id));
           this->pret->setText(QString::number(med.get_pret()));
           this->producator->setText(QString::fromStdString(med.get_producator()));
           this->subst->setText(QString::fromStdString(med.get_subst_activa()));
       }
    });

    QObject::connect(this->nesortat_button, &QPushButton::clicked, this, [&](){
        this->load_data_in_list(this->storage.get_all());
        this->load_data_in_table(this->storage.get_all());
    });

    // right
    QObject::connect(this->generate_button, &QPushButton::clicked, this, &MedicamentGUI::genereaza_random_gui);

    QObject::connect(this->addMed, &QPushButton::clicked, this, &MedicamentGUI::gui_adauga_med);
    QObject::connect(this->deleteMed, &QPushButton::clicked, this, &MedicamentGUI::gui_sterge_med);
    QObject::connect(this->searchMed, &QPushButton::clicked, this, &MedicamentGUI::gui_cauta_med);
    QObject::connect(this->raport, &QPushButton::clicked, this, &MedicamentGUI::raport_gui);
    QObject::connect(this->modifyMed, &QPushButton::clicked, this, &MedicamentGUI::gui_modifica_med);
    QObject::connect(this->undo, &QPushButton::clicked, this, &MedicamentGUI::gui_undo);
    QObject::connect(this->reteta_CRUD, &QPushButton::clicked, this, [&](){
        auto* reteta = new RetetaCRUDGUI(this->storage, this->serv, this->lista_reteta);
        reteta->show();
    });
    QObject::connect(this->reteta_READ_ONLY, &QPushButton::clicked, this, [&](){
        auto reteta_ro = new RetetaReadOnlyGUI(this->serv, this->lista_reteta);
        reteta_ro->show();
    });

    // left
    QObject::connect(this->sortByName, &QPushButton::clicked, this, &MedicamentGUI::gui_sort_denumrie);
    QObject::connect(this->sortByProd, &QPushButton::clicked, this, &MedicamentGUI::gui_sort_producator);
    QObject::connect(this->sortBySubstAndPrice, &QPushButton::clicked, this, &MedicamentGUI::gui_sort_price_and_subst);
    QObject::connect(this->filterBySubstance, &QPushButton::clicked, this, &MedicamentGUI::gui_filtrare_dupa_substanta);
    QObject::connect(this->filterByPrice, &QPushButton::clicked, this, &MedicamentGUI::gui_filtrare_dupa_pret);
}

void MedicamentGUI::message_box(string& informatie) {
    QMessageBox qmsg;
    qmsg.setText(QString::fromStdString(informatie));
    qmsg.exec();
}

void MedicamentGUI::gui_adauga_med() {
    if(this->denumire->text().isEmpty() or
       this->pret->text().isEmpty() or
       this->producator->text().isEmpty() or
       this->subst->text().isEmpty()) {
        string m = "Introdu o denumire, un pret, un producator si o substanta activa pentru a putea adauga un medicament!";
        MedicamentGUI::message_box(m);
        return;
    }

    string name = this->denumire->text().toStdString();
    int price = this->pret->text().toInt();
    string prod = this->producator->text().toStdString();
    string act_subst = this->subst->text().toStdString();

    int idmed = this->storage.get_last_id();

    Medicament med(idmed, name, price, prod, act_subst);
    auto msg = this->serv.adaugaMedicament(storage, med);
    MedicamentGUI::message_box(msg);

    this->load_data_in_list(this->storage.get_all());
    this->load_data_in_table(this->storage.get_all());
    this->storage.save_to_file();
    this->butoane_dinamic();
}

void MedicamentGUI::gui_sterge_med() {
    string msg;

    if(this->id_med->text().isEmpty() or this->id_med->text().toInt() >= this->storage.get_last_id()){
        msg = "ID invalid!";
    }
    else {
        int id = this->id_med->text().toInt();
        if (id < this->storage.get_last_id()) {
            msg = this->serv.stergeMedicament(storage, id);

            this->load_data_in_list(this->storage.get_all());
            this->load_data_in_table(this->storage.get_all());
            this->storage.save_to_file();
            this->butoane_dinamic();
        }
    }

    MedicamentGUI::message_box(msg);
}

void MedicamentGUI::gui_modifica_med() {
    if(this->id_med->text().isEmpty() or
       this->pret->text().isEmpty() or
       this->subst->text().isEmpty()) {
        string m = "Introdu un id, un pret nou si o substanta activa noua pentru a putea modifica un medicament!";
        MedicamentGUI::message_box(m);
        return;
    }

    int id = this->id_med->text().toInt();
    int new_price = this->pret->text().toInt();
    const string new_subst = this->subst->text().toStdString();

    string msg = this->serv.modificaMedicament(this->storage, id, new_price, new_subst);

    this->storage.save_to_file();
    this->load_data_in_table(this->storage.get_all());
    this->butoane_dinamic();

    MedicamentGUI::message_box(msg);
}

void MedicamentGUI::gui_cauta_med() {
    const string& name = this->denumire->text().toStdString();
    if(name.empty()) {
        string m = "Introdu o denumire!";
        MedicamentGUI::message_box(m);
        return;
    }

    int id = this->serv.cautaMedicament(this->storage, name);

    string msg;
    if(id == -1) {
        msg = "Nu s-a gasit medicamentul cautat!";
    }
    else {
        auto med = this->storage.get_med(id);
        msg = "ID: " + std::to_string(med.get_id()) + "\n";
        msg += "Denumire: " + med.get_denumire() + "\n";
        msg += "Pret: " + std::to_string(med.get_pret()) + "\n";
        msg += "Producator: " + med.get_producator() + "\n";
        msg += "Substanta act: " + med.get_subst_activa();
    }
    MedicamentGUI::message_box(msg);
}

void MedicamentGUI::gui_sort_denumrie() {
    auto meds = this->serv.sortare_generica(this->storage, &Validator::compare_denumire);

    this->load_data_in_list(meds);
    this->load_data_in_table(meds);
}

void MedicamentGUI::gui_sort_producator() {
    auto meds = this->serv.sortare_generica(this->storage, &Validator::compare_producator);

    this->load_data_in_list(meds);
    this->load_data_in_table(meds);
}

void MedicamentGUI::gui_sort_price_and_subst() {
    auto meds = this->serv.sortare_generica(this->storage, &Validator::compare_subst_activa_and_pret);

    this->load_data_in_list(meds);
    this->load_data_in_table(meds);
}

void MedicamentGUI::gui_filtrare_dupa_substanta() {
    if(this->subst->text().isEmpty()) {
        string m = "Introdu o substanta activa dupa care doresti sa faci filtrarea!";
        MedicamentGUI::message_box(m);
        return;
    }

    auto meds = this->serv.filtrare_dupa_substanta(this->storage, this->subst->text().toStdString());

    this->load_data_in_list(meds);
    this->load_data_in_table(meds);
}

void MedicamentGUI::gui_filtrare_dupa_pret() {
    if(this->oper->text().isEmpty() or this->oper->text().length() > 1){
        string m = "Introdu un operator valid!";
        MedicamentGUI::message_box(m);
        return;
    }
    char op = this->oper->text().toStdString()[0];
    if(op != '=' and op != '>' and op != '<') {
        string m = "Introdu un operator valid!";
        MedicamentGUI::message_box(m);
        return;
    }
    if(this->pret->text().isEmpty()) {
        string m = "Introdu un pret dupa care doresti sa faci filtrarea!";
        MedicamentGUI::message_box(m);
        return;
    }

    auto meds = this->serv.filtrare_dupa_pret(this->storage, this->pret->text().toInt(), op);

    this->load_data_in_list(meds);
    this->load_data_in_table(meds);
}

void MedicamentGUI::gui_undo() {
    string m = this->serv.executa_undo(this->storage);
    MedicamentGUI::message_box(m);

    this->load_data_in_list(this->storage.get_all());
    this->load_data_in_table(this->storage.get_all());
    this->storage.save_to_file();
    this->butoane_dinamic();
}

void MedicamentGUI::raport_gui() {
    const auto& raport_substante = this->serv.generareRaport(this->storage);

    string msg;

    for(auto const& item : raport_substante) {
        auto med_dto = item.second;

        msg += med_dto.substanta_activa + ": " + std::to_string(med_dto.nr_meds) + '\n';
    }

    MedicamentGUI::message_box(msg);
}

void MedicamentGUI::butoane_dinamic() {
    // eliberez memoria folosita de butoanele vechi
    for(auto btn: vector_butoane)
        delete btn;

    // eliberez vectorul de butoane
    vector_butoane.clear();

    // completez noile butoane cu informatii
    const auto& raport_substante = this->serv.generareRaport(this->storage);
    for(auto const& item : raport_substante) {
        auto* btn = new QPushButton{QString::fromStdString(item.first)};
        vector_butoane.push_back(btn);

        QObject::connect(btn, &QPushButton::clicked, this, [item](){
                QMessageBox::information(nullptr, QString::fromStdString(item.first),
                                         QString::fromStdString("Numar medicamente: " + std::to_string(item.second.nr_meds)));
        });

        this->ly_butoane_automate->addWidget(btn);
    }
}

void MedicamentGUI::genereaza_random_gui() {
    if(this->generate_number_line->text().isEmpty()) {
        string m = "Introdu numarul de medicamente pe care doresti sa il generezi!";
        MedicamentGUI::message_box(m);
        return;
    }

    int nr_adaugari = this->generate_number_line->text().toInt();

    this->serv.adaugareRandom(this->storage, this->lista_reteta, nr_adaugari);
}

