//
// Created by raulo on 5/16/2024.
//

#include "MedicamentGUI.h"
#include <utility>
#include <vector>
#include <string>
#include "service.h"
#include "repository.h"

void MedicamentGUI::init_gui() {
    this->setLayout(this->mainLayout);

    // left layout
    this->leftLayout->addWidget(this->listaMedicamente);

    this->butoaneFiltrare->addWidget(this->filterByPrice);
    this->butoaneFiltrare->addWidget(this->filterBySubstance);
    this->butoaneFiltrare->addWidget(this->quickadd);
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
    this->rightLayout->addLayout(this->dataForm);

    this->rightLayout->addWidget(this->addMed);

    this->butoane_del_mod_ser->addWidget(this->deleteMed);
    this->butoane_del_mod_ser->addWidget(this->searchMed);
    this->butoane_del_mod_ser->addWidget(this->modifyMed);
    this->rightLayout->addLayout(this->butoane_del_mod_ser);

    this->butoane_buc_rap_undo->addWidget(this->bucket);
    this->butoane_buc_rap_undo->addWidget(this->raport);
    this->butoane_buc_rap_undo->addWidget(this->undo);
    this->rightLayout->addLayout(this->butoane_buc_rap_undo);

    this->mainLayout->addLayout(this->rightLayout);
}

void MedicamentGUI::load_data(vector<Medicament>& meds) {
    this->listaMedicamente->clear();
    for(auto const& item: meds) {
        auto* list_item = new QListWidgetItem(QString::fromStdString(item.get_denumire()));
        list_item->setData(Qt::UserRole, item.get_id());
        this->listaMedicamente->addItem(list_item);
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

           auto med = this->repo.get_med(id);
           this->id_med->setText(QString::number(id));
           this->pret->setText(QString::number(med.get_pret()));
           this->producator->setText(QString::fromStdString(med.get_producator()));
           this->subst->setText(QString::fromStdString(med.get_subst_activa()));
       }
    });

    QObject::connect(this->quickadd, &QPushButton::clicked, this, &MedicamentGUI::gui_adauga_rapid);

    // right
    QObject::connect(this->addMed, &QPushButton::clicked, this, &MedicamentGUI::gui_adauga_med);
    QObject::connect(this->deleteMed, &QPushButton::clicked, this, &MedicamentGUI::gui_sterge_med);
    QObject::connect(this->searchMed, &QPushButton::clicked, this, &MedicamentGUI::gui_cauta_med);
    QObject::connect(this->modifyMed, &QPushButton::clicked, this, &MedicamentGUI::gui_modifica_med);
    QObject::connect(this->undo, &QPushButton::clicked, this, &MedicamentGUI::gui_undo);

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

void MedicamentGUI::gui_adauga_rapid() {
    this->serv.adaugaMedicamenteRapid(this->repo);
    this->load_data(this->repo.get_all());
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

    int idmed = this->repo.get_last_id();

    Medicament med(idmed, name, price, prod, act_subst);
    auto msg = this->serv.adaugaMedicament(repo, med);
    MedicamentGUI::message_box(msg);

    this->load_data(this->repo.get_all());
}

void MedicamentGUI::gui_sterge_med() {
    string msg;

    if(this->id_med->text().isEmpty() or this->id_med->text().toInt() >= this->repo.get_last_id()){
        msg = "ID invalid!";
    }
    else {
        int id = this->id_med->text().toInt();
        if (id < this->repo.get_last_id()) {
            msg = this->serv.stergeMedicament(repo, id);
            this->load_data(this->repo.get_all());
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

    string msg = this->serv.modificaMedicament(this->repo, id, new_price, new_subst);
    MedicamentGUI::message_box(msg);
}

void MedicamentGUI::gui_cauta_med() {
    const string& name = this->denumire->text().toStdString();
    if(name.empty()) {
        string m = "Introdu o denumire!";
        MedicamentGUI::message_box(m);
        return;
    }

    int id = this->serv.cautaMedicament(this->repo, name);

    string msg;
    if(id == -1) {
        msg = "Nu s-a gasit medicamentul cautat!";
    }
    else {
        auto med = this->repo.get_med(id);
        msg = "ID: " + std::to_string(med.get_id()) + "\n";
        msg += "Denumire: " + med.get_denumire() + "\n";
        msg += "Pret: " + std::to_string(med.get_pret()) + "\n";
        msg += "Producator: " + med.get_producator() + "\n";
        msg += "Substanta act: " + med.get_subst_activa();
    }
    MedicamentGUI::message_box(msg);
}

void MedicamentGUI::gui_sort_denumrie() {
    auto meds = this->serv.sortare_generica(this->repo, &Validator::compare_denumire);
    while(this->repo.get_last_id()) {
        this->repo.sterge_medicament(0);
        this->repo.set_id_correctly();
    }
    for(auto& med: meds){
        med.set_id(this->repo.get_last_id());
        this->serv.adaugaMedicament(this->repo, med);
    }
    this->load_data(this->repo.get_all());
}

void MedicamentGUI::gui_sort_producator() {
    auto meds = this->serv.sortare_generica(this->repo, &Validator::compare_producator);
    while(this->repo.get_last_id()) {
        this->repo.sterge_medicament(0);
        this->repo.set_id_correctly();
    }
    for(auto& med: meds){
        med.set_id(this->repo.get_last_id());
        this->serv.adaugaMedicament(this->repo, med);
    }
    this->load_data(this->repo.get_all());
}

void MedicamentGUI::gui_sort_price_and_subst() {
    auto meds = this->serv.sortare_generica(this->repo, &Validator::compare_subst_activa_and_pret);
    while(this->repo.get_last_id()) {
        this->repo.sterge_medicament(0);
        this->repo.set_id_correctly();
    }
    for(auto& med: meds){
        med.set_id(this->repo.get_last_id());
        this->serv.adaugaMedicament(this->repo, med);
    }
    this->load_data(this->repo.get_all());
}

void MedicamentGUI::gui_filtrare_dupa_substanta() {
    if(this->subst->text().isEmpty()) {
        string m = "Introdu o substanta activa dupa care doresti sa faci filtrarea!";
        MedicamentGUI::message_box(m);
        return;
    }

    auto meds = this->serv.filtrare_dupa_substanta(this->repo, this->subst->text().toStdString());

    this->load_data(meds);
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

    auto meds = this->serv.filtrare_dupa_pret(this->repo, this->pret->text().toInt(), op);

    this->load_data(meds);
}

void MedicamentGUI::gui_undo() {
    string m = this->serv.executa_undo(this->repo);
    MedicamentGUI::message_box(m);

    this->load_data(this->repo.get_all());
}

