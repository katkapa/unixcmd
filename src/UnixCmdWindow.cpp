#include "UnixCmdWindow.h"
#include "DirectoryView.h"


UnixCmdWindow::UnixCmdWindow() {
    setWindowTitle("UnixCmd");
    setMinimumSize(800, 600);

    setCentralWidget(new DirectoryView);
}
