//
// Created by raulo on 5/30/2024.
//

#ifndef LAB10_11_RETETAGUI_READ_ONLY_H
#define LAB10_11_RETETAGUI_READ_ONLY_H

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
#include <QPainter>

class RetetaReadOnlyGUI : public QWidget, public Observer {
public:
    /**
     * constructor
     * @param serv service pentru a putea face operatii
     * @param lista_repo lista cu medicamente de pe reteta
     */
    RetetaReadOnlyGUI(Service& serv, MedicamenteRepo& lista_repo) : service{serv}, lista_meds_reteta{lista_repo},
    nr_meds{(int)lista_repo.get_all().size()}{
        this->service.addObserver(this);
        this->load_data();

        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        startTimer(1000);
    };

    /** rescrierea functiei paintEvent() a clasei QWidget */
    void paintEvent(QPaintEvent* ev) override;

    /** rescrierea functiei update() a clasei Observer */
    void update() override {
        this->load_data();
        this->repaint();
    }

    /** destructor */
    ~RetetaReadOnlyGUI() override {
        this->service.removeObserver(this);
    }

private:
    Service& service;
    MedicamenteRepo& lista_meds_reteta;
    int nr_meds;

    QColor culoareRandom();

    void load_data(){
        this->nr_meds = (int)this->lista_meds_reteta.get_all().size();
    }
};

#endif //LAB10_11_RETETAGUI_READ_ONLY_H
