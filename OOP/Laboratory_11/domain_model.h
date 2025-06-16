#ifndef TRAVELPACKAGEMODEL_H
#define TRAVELPACKAGEMODEL_H

#include <QAbstractTableModel>
#include <qvector.h>
#include "domain.h"

class TravelPackageModel : public QAbstractTableModel {

private:

    QVector<Travel_Package> pachete;

public:

    TravelPackageModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setPachete(const QVector<Travel_Package>& lista) {

        beginResetModel();
        pachete = lista;
        endResetModel();
    }

    
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return static_cast<int>(pachete.size());
    }
   

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {

        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        const Travel_Package& p = pachete.at(index.row());

        switch (index.column()) {
        case 0: return p.get_id();
        case 1: return QString::fromStdString(p.get_name());
        case 2: return QString::fromStdString(p.get_destination());
        case 3: return QString::fromStdString(p.get_type());
        case 4: return p.get_price();
        default: return QVariant();
        }
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {

        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {

            switch (section) {
            case 0: return "ID";
            case 1: return "Name";
            case 2: return "Destination";
            case 3: return "Type";
            case 4: return "Price";
            default: return QVariant();
            }
        }

        return QVariant();
    }
};

#endif 
