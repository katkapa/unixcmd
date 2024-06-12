#pragma once


#include <QTableView>
#include <QTimer>
#include "DirectoryViewModel.h"

class DirectoryView : public QTableView {
    Q_OBJECT

public:
    DirectoryView();
    virtual ~DirectoryView() = default;
private:
    DirectoryViewModel* m_directoryViewModel;
    QTimer m_timer = QTimer(this);
};
