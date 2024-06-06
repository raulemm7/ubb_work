//
// Created by raulo on 6/5/2024.
//

#ifndef LAB10_11_TABLE_MODEL_H
#define LAB10_11_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "domain.h"

class TableModel : public QAbstractTableModel {
private:
    std::vector<Medicament> lista_meds;
public:
    /** constructor */
    explicit TableModel(QObject* parent) : QAbstractTableModel(parent) {};

    /**
     * @return numarul de linii al tabelei
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    /**
     * @return numarul de coloane al tabelei
     */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /**
     * scrie informatiile medicamentelor in tabel
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    /**
     * seteaza datele din header ul tabelului
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    /**
     * afiseaza in tabel informatiile unei liste cu medicamente
     * @param _med_list lista cu medicamente
     */
    void setList(const std::vector<Medicament>& _med_list);

    /** destructor */
    ~TableModel() override = default;
};

#endif //LAB10_11_TABLE_MODEL_H
