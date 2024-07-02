//
// Created by raulo on 6/25/2024.
//

#include "table_model.h"
#include <QColor>

int CustomTableModel::rowCount(const QModelIndex &parent) const {
    return (int)this->lista_masini.size();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const {
    const int row = index.row();
    const int column = index.column();
    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
            case 0: return QString::fromStdString(this->lista_masini.at(row).getNrInmatriculare());
            case 1: return QString::fromStdString(this->lista_masini.at(row).getDenumire());
            case 2: return QString::number(this->lista_masini.at(row).getAnFabricatie());
            case 3: return QString::fromStdString(this->lista_masini.at(row).getTip());
        }
        return QString("R%1, C%2").arg(index.row() + 1).arg(index.column() + 1);
    }
    /** pentru colorare */
    else if(role == Qt::BackgroundRole) {
        auto m = this->lista_masini.at(row);
        if(m.getTip() == "sedan") {
            // albastru
            switch(column) {
                case 0: return QColor(Qt::blue);
                case 1: return QColor(Qt::blue);
                case 2: return QColor(Qt::blue);
                case 3: return QColor(Qt::blue);
            }
        }
        if(m.getTip() == "hatch") {
            // cyan
            switch(column) {
                case 0: return QColor(Qt::cyan);
                case 1: return QColor(Qt::cyan);
                case 2: return QColor(Qt::cyan);
                case 3: return QColor(Qt::cyan);
            }
        }
        if(m.getTip() == "suv") {
            // rosu
            switch(column) {
                case 0: return QColor(Qt::red);
                case 1: return QColor(Qt::red);
                case 2: return QColor(Qt::red);
                case 3: return QColor(Qt::red);
            }
        }
        if(m.getTip() == "van") {
            // verde
            switch(column) {
                case 0: return QColor(Qt::green);
                case 1: return QColor(Qt::green);
                case 2: return QColor(Qt::green);
                case 3: return QColor(Qt::green);
            }
        }
    }
    return {};

}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case 0: return QString("NR INMATRICULARE");
                case 1: return QString("DENUMIRE");
                case 2: return QString("AN FABRICATIE");
                case 3: return QString("TIP");
            }
            return QString("col %1").arg(section);
        }
        else {
            return QString("%1").arg(section);
        }
    }
    return {};
}

void CustomTableModel::setData(const std::vector<Masina> &_masini_list) {
    this->lista_masini = _masini_list;

    const QModelIndex topLeft = createIndex(0, 0);
    const QModelIndex bottomRight = createIndex(rowCount(), columnCount());
    dataChanged(topLeft, bottomRight);
    layoutChanged();
}


