//
// Created by raulo on 6/5/2024.
//

#include "table_model.h"

int TableModel::rowCount(const QModelIndex &parent) const {
    return (int)lista_meds.size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case 0: return QString("Denumire");
                case 1: return QString("Pret");
                case 2: return QString("Producator");
                case 3: return QString("Substanta activa");

            }
            return QString("col %1").arg(section);
        }
        else {
            return QString("%1").arg(section);
        }
    }
    return {};
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    const int row = index.row();
    const int column = index.column();
    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
            case 0: return QString::fromStdString(this->lista_meds.at(row).get_denumire());
            case 1: return QString::number(this->lista_meds.at(row).get_pret());
            case 2: return QString::fromStdString(this->lista_meds.at(row).get_producator());
            case 3: return QString::fromStdString(this->lista_meds.at(row).get_subst_activa());
        }
        return QString("R%1, C%2").arg(index.row() + 1).arg(index.column() + 1);
    }
    return {};
}

void TableModel::setList(const std::vector<Medicament> &_med_list) {
    this->lista_meds = _med_list;
    const QModelIndex topLeft = createIndex(0, 0);
    const QModelIndex bottomRight = createIndex(rowCount(), columnCount());
    dataChanged(topLeft, bottomRight);
    layoutChanged();
}
