#include <QApplication>
#include "mainwindow.h"
#include "createaccountwidget.h"
#include "updateaccountwidget.h"
#include "dbmanager.h"
#include "accountclientswidget.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    MainWindow mainwindow;
    mainwindow.show();

    return app.exec();
}
