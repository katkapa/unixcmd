#include "DirectoryViewModel.h"


DirectoryViewModel::DirectoryViewModel(QObject* parent) : QAbstractTableModel(parent) {
}

int DirectoryViewModel::rowCount(const QModelIndex& parent) const {
    return 2;
}

int DirectoryViewModel::columnCount(const QModelIndex& parent) const {
    return 2;
}

QVariant DirectoryViewModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return QVariant("foo");

    return QVariant();
}
