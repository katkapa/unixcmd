#pragma once

#include <QAbstractTableModel>

class DirectoryViewModel : public QAbstractTableModel {
    Q_OBJECT

public:
    DirectoryViewModel(QObject* parent = nullptr);
    virtual ~DirectoryViewModel() = default;

public:
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
};
