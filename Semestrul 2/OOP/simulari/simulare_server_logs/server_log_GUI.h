//
// Created by raulo on 5/23/2024.
//

#ifndef SIMULARE_LOGS_SERVER_LOG_GUI_H
#define SIMULARE_LOGS_SERVER_LOG_GUI_H

#include "repository.h"
#include "service.h"

#include <QWidget>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qcheckbox.h>

class serverGUI:public QWidget{
private:
    QHBoxLayout* main_layout = new QHBoxLayout;

    QVBoxLayout* left_layout = new QVBoxLayout;
    QTableWidget* tabel_items = new QTableWidget;

    QVBoxLayout* right_layout = new QVBoxLayout;
    QFormLayout* data_form = new QFormLayout;

    QHBoxLayout* butoane_layout = new QHBoxLayout;
    QPushButton* add_button = new QPushButton{"&Adauga"};

    QLineEdit* line_id = new QLineEdit;
    QLineEdit* line_content = new QLineEdit;
    QLineEdit* line_pid = new QLineEdit;
    QLineEdit* line_level = new QLineEdit;

    QHBoxLayout* cbox_layout = new QHBoxLayout;
    QCheckBox* cbox_info = new QCheckBox{"info"};
    QCheckBox* cbox_warning = new QCheckBox{"warning"};
    QCheckBox* cbox_error = new QCheckBox{"error"};
    QCheckBox* cbox_critical = new QCheckBox{"critical"};

    void init_gui();
    void load_data();
    void connect_buttons();

    repository& storage;
    Service& service;

    void add_gui();

public:
    serverGUI(repository& repo, Service& serv):storage{repo},service{serv}{
        this->init_gui();
        this->load_data();
        this->connect_buttons();
    };
};

#endif //SIMULARE_LOGS_SERVER_LOG_GUI_H
