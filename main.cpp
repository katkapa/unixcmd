#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtPlugin>
#include <QtGlobal>

#include "src/UnixCmdWindow.h"

#ifdef BUILD_STATIC
    Q_IMPORT_PLUGIN(QtQmlPlugin)
    Q_IMPORT_PLUGIN(QtQmlModelsPlugin)
    Q_IMPORT_PLUGIN(QtQmlWorkerScriptPlugin)
    Q_IMPORT_PLUGIN(QtQuick2Plugin)
    Q_IMPORT_PLUGIN(QtQuickControls2Plugin)
    Q_IMPORT_PLUGIN(QtQuickLayoutsPlugin)
    Q_IMPORT_PLUGIN(QtQuickTemplates2Plugin)
    Q_IMPORT_PLUGIN(QtQuick2WindowPlugin)

    #ifdef IOS
        Q_IMPORT_PLUGIN(QIOSIntegrationPlugin)
    #endif
#endif


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    UnixCmdWindow window;

    window.show();

    return app.exec();
}
