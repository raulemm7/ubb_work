//
// Created by raulo on 5/23/2024.
//

#include "server_log_GUI.h"

void serverGUI::init_gui() {
    this->setLayout(this->main_layout);

    // left
    this->left_layout->addWidget(this->tabel_items);

    this->cbox_layout->addWidget(this->cbox_info);
    this->cbox_layout->addWidget(this->cbox_warning);
    this->cbox_layout->addWidget(this->cbox_error);
    this->cbox_layout->addWidget(this->cbox_critical);
    this->left_layout->addLayout(this->cbox_layout);
    this->main_layout->addLayout(this->left_layout);

    // right
    this->data_form->addRow("ID: ", this->line_id);
    this->data_form->addRow("content: ", this->line_content);
    this->data_form->addRow("PID: ", this->line_pid);
    this->data_form->addRow("level: ", this->line_level);
    this->right_layout->addLayout(this->data_form);

    this->butoane_layout->addWidget(this->add_button);
    this->right_layout->addLayout(this->butoane_layout);

    this->main_layout->addLayout(this->right_layout);
}

void serverGUI::load_data() {
    this->tabel_items->clear();

    this->tabel_items->setColumnCount(4);
    this->tabel_items->setRowCount(this->storage.getSize());

    this->tabel_items->setHorizontalHeaderItem(0, new QTableWidgetItem{"ID"});
    this->tabel_items->setHorizontalHeaderItem(1, new QTableWidgetItem{"Content"});
    this->tabel_items->setHorizontalHeaderItem(2, new QTableWidgetItem{"PID"});
    this->tabel_items->setHorizontalHeaderItem(3, new QTableWidgetItem{"Level"});

    int linie = 0;
    auto vector_logs = this->storage.getListaLogs();
    for(auto& log:vector_logs) {
        auto col_id = new QTableWidgetItem{QString::fromStdString(log.getId())};
        auto col_content = new QTableWidgetItem{QString::fromStdString(log.getContent())};
        auto col_pid = new QTableWidgetItem{QString::number(log.getPid())};
        auto col_level = new QTableWidgetItem{QString::fromStdString(log.getLevel())};

        if(log.getLevel() == "info") {
            // green
            col_id->setBackground(QBrush(Qt::green));
            col_content->setBackground(QBrush(Qt::green));
            col_pid->setBackground(QBrush(Qt::green));
            col_level->setBackground(QBrush(Qt::green));
        }
        else if(log.getLevel() == "warning") {
            // yellow
            col_id->setBackground(QBrush(Qt::yellow));
            col_content->setBackground(QBrush(Qt::yellow));
            col_pid->setBackground(QBrush(Qt::yellow));
            col_level->setBackground(QBrush(Qt::yellow));
        }
        else {
            // red
            col_id->setBackground(QBrush(Qt::red));
            col_content->setBackground(QBrush(Qt::red));
            col_pid->setBackground(QBrush(Qt::red));
            col_level->setBackground(QBrush(Qt::red));
        }

        this->tabel_items->setItem(linie, 0, col_id);
        this->tabel_items->setItem(linie, 1, col_content);
        this->tabel_items->setItem(linie, 2, col_pid);
        this->tabel_items->setItem(linie, 3, col_level);

        linie++;
    }
}

void serverGUI::connect_buttons() {
    QObject::connect(this->add_button, &QPushButton::clicked, this, &serverGUI::add_gui);
}

void serverGUI::add_gui() {
    auto id = this->line_id->text().toStdString();
    auto content = this->line_content->text().toStdString();
    auto pid = this->line_pid->text().toInt();
    auto level = this->line_level->text().toStdString();

    auto message = this->service.adaugare_log_nou(this->storage, id, content, pid, level);
    if(message == "Log inregistrat cu succes!"){
        this->storage.save_to_file();
        this->load_data();
    }


    QMessageBox qmsgbx;
    qmsgbx.setText(QString::fromStdString(message));
    qmsgbx.exec();
}
