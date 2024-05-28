#pragma once


#include <QTableView>


class DirectoryView : public QTableView {
    Q_OBJECT

public:
    DirectoryView();
    virtual ~DirectoryView() = default;
};
