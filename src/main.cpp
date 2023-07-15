#include "ui/mainwindow.h"
#include "database/dbmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!DBManager::instance().openDB()) {
        return 1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
