#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>

#include <QMainWindow>
#include <QString>
#include <QObject>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QWidget>
#include <QHeaderView>
#include <QStringList>
#include <QStandardItemModel>
#include "modelgetter.h"
#include "../Core/AgendaService.h"
#include "logindialog.h"
#include "dateselectdialog.h"
#include "createmeetingdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AgendaService * as, QWidget *parent = 0);
    ~MainWindow();
signals:
    void loginRequired();
public slots:
    void performLogin();
    void performCreateMeeting();
    void performDeleteMeeting();
    void performDeleteAllMeetings();
    void performUnregister();
    void performLogout();
    void performAbout();
    void getUserInfo(QString username, QString password);
    void reloadMeetingsTable();
    void reloadMeetingsTableForTitleSearch();
    void reloadMeetingsTableForPeriodSearch();
    void reloadMeetingsTableForSelector(int index);
private slots:
    void newDateSelected(Date newDate, QObject * requester);
private:
    void activateSearch();
    void inactivateSearch();
    void loadUsersTable();
    LoginDialog mLoginDialog;
    AgendaService * mAgendaService;
    QString mUsername;
    QString mPassword;
    QComboBox * meetingListSelecter;
    QPushButton * createMeetingButton;
    QPushButton * deleteMeetingButton;
    QPushButton * deleteAllMeetingButton;
    QLabel * searchTitleLabel;
    QLineEdit * searchTitleEdit;
    QPushButton * searchTitleButton;
    QPushButton * startDateButton;
    QLabel * toLabel;
    QPushButton * endDateButton;
    QPushButton * searchPeriodButton;
    QTableView * meetingTable;
    QTableView * userTable;
    QPushButton * UnregisterButton;
    QPushButton * LogOutButton;
    QPushButton * AboutButton;
    QWidget * centralWidget;
    QVBoxLayout * mainLayout;
    QStandardItemModel * mUserModel;
    QStandardItemModel * mMeetingModel;
    CreateMeetingDialog createMeetingDialog;
    DateSelectDialog daySelector;
};

#endif // MAINWINDOW_H
