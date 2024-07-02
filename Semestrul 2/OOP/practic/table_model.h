//
// Created by raulo on 6/25/2024.
//

#ifndef PRACTIC_TABLE_MODEL_H
#define PRACTIC_TABLE_MODEL_H

#include <QAbstractTableModel>
#include "domain.h"

class CustomTableModel : public QAbstractTableModel{
private:
    std::vector<Masina> lista_masini;
public:
    /** constructor */
    explicit CustomTableModel(QObject* parent) : QAbstractTableModel(parent) {};

    /**
     * @param parent parintele in care este afisat modelul
     * @return nr de randuri din tabela
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    /**
     * @param parent parintele in care este afisat modelul
     * @return nr de coloane din tabela
     */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /**
     * seteaza informatiile in tabel
     * @param index index-ul din tabel
     * @param role rolul (afisare, colorare)
     * @return QVariant
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    /**
     * seteaza informatiile din header-ul tabelului
     * @param section sectiunea din header
     * @param orientation orientarea sectiunii
     * @param role rolul
     * @return
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    /**
     * seteaza informatiile in tabel
     * @param _masini_list vector cu informatii (masini)
     */
    void setData(const std::vector<Masina>& _masini_list);

    /** destructor */
    ~CustomTableModel() override = default;
};

#endif //PRACTIC_TABLE_MODEL_H
