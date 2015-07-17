#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QObject>
#include "../Core/AgendaService.h"
#include "notifybar.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(AgendaService * as, QWidget * parent = 0);
    ~LoginDialog();
signals:
    void loginSucceed(QString username, QString password);
public slots:
    void initMe();
    void loginButtonClicked();
    void showOrHideRegister();

private:
    QLabel * usernameLabel;
    QLineEdit * usernameEdit;
    QLabel * passwordLabel;
    QLineEdit * passwordEdit;
    QLabel * useremailLabel;
    QLineEdit * useremailEdit;
    QLabel * userphoneLabel;
    QLineEdit * userphoneEdit;
    QGridLayout * editLayout;
    QPushButton * registerTriggleButton;
    QPushButton * loginButton;
    QVBoxLayout * mainLayout;
    QVBoxLayout * registerLayout;
    NotifyBar * notifyBar;
    QVBoxLayout * bottomLayout;
//    MainWindow * mainWin;
    AgendaService * agendaService;
    bool isLogin;
    void adjustLayout();
    void userLogin();
    void userRegister();
};

#endif // LOGINDIALOG_H
