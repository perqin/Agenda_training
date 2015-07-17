#include "GUI/mainwindow.h"
#include "GUI/logindialog.h"
#include "Core/AgendaService.h"
#include <QApplication>
#include <QDebug>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Perqin");
    app.setApplicationName("Agenda");

    AgendaService agendaService;
    agendaService.startAgenda();

    MainWindow mainWindow(&agendaService);
    //LoginDialog loginDialog(&mainWindow, &agendaService);
//    QObject::connect(&loginDialog, SIGNAL(loginSucceed(QString,QString)),
//                     &mainWindow, SLOT(getUserInfo(QString,QString)));
    //loginDialog.show();

    int runtime_error_code = app.exec();
    agendaService.quitAgenda();
    return runtime_error_code;
}
