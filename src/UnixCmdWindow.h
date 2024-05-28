#pragma once


#include <QMainWindow>

class UnixCmdWindow : public QMainWindow {
    Q_OBJECT

public:
    UnixCmdWindow();
    virtual ~UnixCmdWindow() = default;
};
