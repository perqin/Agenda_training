#include "mainwindow.h"

MainWindow::MainWindow(AgendaService * as, QWidget * parent)
    : QMainWindow(parent),
      mLoginDialog(as), mAgendaService(as), mUsername(""), mPassword(""),
      meetingListSelecter(new QComboBox()),
      createMeetingButton(new QPushButton(tr("Create meeting"))),
      deleteMeetingButton(new QPushButton(tr("Delete meeting"))),
      deleteAllMeetingButton(new QPushButton(tr("Clear meetings"))),
      searchTitleLabel(new QLabel(tr("Title"))),
      searchTitleEdit(new QLineEdit()),
      searchTitleButton(new QPushButton(tr("Search title"))),
      startDateButton(new QPushButton("1000-01-01/00:00")),
      toLabel(new QLabel(tr(" ~ "))),
      endDateButton(new QPushButton("9999-12-31/23:59")),
      searchPeriodButton(new QPushButton(tr("Search period"))),
      meetingTable(new QTableView()),
      userTable(new QTableView()),
      UnregisterButton(new QPushButton(tr("Unregister me"))),
      LogOutButton(new QPushButton(tr("Log out"))),
      AboutButton(new QPushButton(tr("About"))),
      mUserModel(new QStandardItemModel(this)),
      mMeetingModel(new QStandardItemModel(this))
{
    // Layout
    QHBoxLayout * meetingManageLayout = new QHBoxLayout();
    meetingManageLayout->addWidget(meetingListSelecter);
    meetingManageLayout->addWidget(createMeetingButton);
    meetingManageLayout->addWidget(deleteMeetingButton);
    meetingManageLayout->addWidget(deleteAllMeetingButton);
    QHBoxLayout * meetingSearchLayout = new QHBoxLayout();
    meetingSearchLayout->addWidget(searchTitleLabel);
    meetingSearchLayout->addWidget(searchTitleEdit);
    meetingSearchLayout->addWidget(searchTitleButton);
    meetingSearchLayout->addWidget(startDateButton);
    meetingSearchLayout->addWidget(toLabel);
    meetingSearchLayout->addWidget(endDateButton);
    meetingSearchLayout->addWidget(searchPeriodButton);
    QVBoxLayout * MeetingGroupLayout = new QVBoxLayout();
    MeetingGroupLayout->addLayout(meetingManageLayout);
    MeetingGroupLayout->addLayout(meetingSearchLayout);
    MeetingGroupLayout->addWidget(meetingTable);
    QGroupBox * MeetingGroupBox = new QGroupBox(tr("Meetings"));
    MeetingGroupBox->setLayout(MeetingGroupLayout);
    QVBoxLayout * UserButtonsLayout = new QVBoxLayout();
    UserButtonsLayout->addWidget(UnregisterButton);
    UserButtonsLayout->addWidget(LogOutButton);
    UserButtonsLayout->addWidget(AboutButton);
    QHBoxLayout * UserGroupLayout = new QHBoxLayout();
    UserGroupLayout->addWidget(userTable);
    UserGroupLayout->addLayout(UserButtonsLayout);
    QGroupBox * UserGroupBox = new QGroupBox(tr("Users"));
    UserGroupBox->setLayout(UserGroupLayout);
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(MeetingGroupBox);
    mainLayout->addWidget(UserGroupBox);

    // UI
    meetingListSelecter->addItem(tr("List all meetings"));
    meetingListSelecter->addItem(tr("List sponsor meetings"));
    meetingListSelecter->addItem(tr("List paticipate meetings"));
    meetingListSelecter->addItem(tr("Search result"));
    mMeetingModel->setColumnCount(5);
    mMeetingModel->setHorizontalHeaderLabels(QStringList() << tr("Title") << tr("Sponsor") << tr("Participator") << tr("Start date") << tr("End date"));
    mUserModel->setColumnCount(3);
    mUserModel->setHorizontalHeaderLabels(QStringList() << tr("Username") << tr("Email") << tr("Phone number"));
    meetingTable->setModel(mMeetingModel);
    meetingTable->setColumnWidth(3, 112);
    meetingTable->setColumnWidth(4, 112);
    userTable->setModel(mUserModel);
//    userTable->setColumnWidth();

    // Signals and slots connections
    QObject::connect(this, SIGNAL(loginRequired()),
                     this, SLOT(performLogin()));
    QObject::connect(&mLoginDialog, SIGNAL(loginSucceed(QString,QString)),
                     this, SLOT(getUserInfo(QString,QString)));
    QObject::connect(meetingListSelecter, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(reloadMeetingsTableForSelector(int)));
    QObject::connect(createMeetingButton, SIGNAL(clicked(bool)),
                     this, SLOT(performCreateMeeting()));
    QObject::connect(&createMeetingDialog, SIGNAL(meetingCreated()),
                     this, SLOT(reloadMeetingsTable()));
    QObject::connect(deleteMeetingButton, SIGNAL(clicked(bool)),
                     this, SLOT(performDeleteMeeting()));
    QObject::connect(deleteAllMeetingButton, SIGNAL(clicked(bool)),
                     this, SLOT(performDeleteAllMeetings()));
    QObject::connect(UnregisterButton, SIGNAL(clicked(bool)),
                     this, SLOT(performUnregister()));
    QObject::connect(LogOutButton, SIGNAL(clicked(bool)),
                     this, SLOT(performLogout()));
    QObject::connect(AboutButton, SIGNAL(clicked(bool)),
                     this, SLOT(performAbout()));
    QObject::connect(startDateButton, SIGNAL(clicked(bool)),
                     &daySelector, SLOT(init()));
    QObject::connect(endDateButton, SIGNAL(clicked(bool)),
                     &daySelector, SLOT(init()));
    QObject::connect(&daySelector, SIGNAL(dateSelected(Date,QObject*)),
                     this, SLOT(newDateSelected(Date,QObject*)));
    QObject::connect(searchTitleButton, SIGNAL(clicked(bool)),
                     this, SLOT(reloadMeetingsTableForTitleSearch()));
    QObject::connect(searchPeriodButton, SIGNAL(clicked(bool)),
                     this, SLOT(reloadMeetingsTableForPeriodSearch()));

    // Emit login signal
    emit loginRequired();
}

MainWindow::~MainWindow() {}

void MainWindow::performLogin() {
    this->setVisible(false);
    mLoginDialog.initMe();
}

void MainWindow::performCreateMeeting() {
    createMeetingDialog.startCreation(mAgendaService, mUsername);
}

void MainWindow::performDeleteMeeting() {
    bool ok;
    QString title = QInputDialog::getText(this, tr("Delete meeting"), tr("Title"), QLineEdit::Normal, "", &ok);
    if (ok && !title.isEmpty())
        mAgendaService->deleteMeeting(mUsername.toStdString(), title.toStdString());
}

void MainWindow::performDeleteAllMeetings() {
    QMessageBox promptBox;
    promptBox.setInformativeText(tr("Are you sure to clear your meetings?"));
    promptBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    promptBox.setDefaultButton(QMessageBox::Cancel);
    if (promptBox.exec() == QMessageBox::Ok) {
        mAgendaService->deleteAllMeetings(mUsername.toStdString());
    }
}

void MainWindow::performUnregister() {
    QMessageBox promptBox;
    promptBox.setInformativeText(tr("Are you sure to delete your account?"));
    promptBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    promptBox.setDefaultButton(QMessageBox::Cancel);
    if (promptBox.exec() == QMessageBox::Ok) {
        mAgendaService->deleteUser(mUsername.toStdString(), mPassword.toStdString());
    }
}

void MainWindow::performLogout() {
    QMessageBox promptBox;
    promptBox.setInformativeText(tr("Are you sure to log out?"));
    promptBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    promptBox.setDefaultButton(QMessageBox::Cancel);
    if (promptBox.exec() == QMessageBox::Ok) {
        mUsername.clear();
        mPassword.clear();
        emit loginRequired();
    }
}

void MainWindow::performAbout() {
    QMessageBox promptBox;
    promptBox.setText(tr("Agenda 0.0.3"));
    promptBox.setInformativeText(tr("Agenda is a lite agenda client. You can manage your meeting timtable with this handy but powerful tools. :P\nAgenda GUI 0.0.3 released on 20150701 by Perqin\nFeedback : perqin@yeah.net || perqinxie@gmail.com"));
    promptBox.setStandardButtons(QMessageBox::Ok);
    promptBox.setDefaultButton(QMessageBox::Ok);
    promptBox.exec();
}

void MainWindow::getUserInfo(QString username, QString password) {
    mUsername = username;
    mPassword = password;
    setVisible(true);
    emit meetingListSelecter->currentIndexChanged(0);
    loadUsersTable();
}

void MainWindow::reloadMeetingsTable() {
    reloadMeetingsTableForSelector(meetingListSelecter->currentIndex());
}

void MainWindow::reloadMeetingsTableForTitleSearch() {
    ModelGetter::getIt(mAgendaService->meetingQuery(mUsername.toStdString(), searchTitleEdit->text().toStdString()), mMeetingModel);
}

void MainWindow::reloadMeetingsTableForPeriodSearch() {
    ModelGetter::getIt(mAgendaService->meetingQuery(mUsername.toStdString(), startDateButton->text().toStdString(), endDateButton->text().toStdString()), mMeetingModel);
}

void MainWindow::reloadMeetingsTableForSelector(int index) {
    switch (index) {
    case 0: // List all
        inactivateSearch();
        ModelGetter::getIt(mAgendaService->listAllMeetings(mUsername.toStdString()), mMeetingModel);
        break;
    case 1: // List sponsor
        inactivateSearch();
        ModelGetter::getIt(mAgendaService->listAllSponsorMeetings(mUsername.toStdString()), mMeetingModel);
        break;
    case 2: // List participate
        inactivateSearch();
        ModelGetter::getIt(mAgendaService->listAllParticipateMeetings(mUsername.toStdString()), mMeetingModel);
        break;
    case 3: // Search
        activateSearch();
        break;
    default:
        break;
    }
}

void MainWindow::newDateSelected(Date newDate, QObject *requester) {
    QPushButton * sender = dynamic_cast<QPushButton*>(requester);
    sender->setText(Date::dateToString(newDate).c_str());
}

void MainWindow::activateSearch() {
    searchTitleLabel->setVisible(true);
    searchTitleEdit->setVisible(true);
    searchTitleButton->setVisible(true);
    startDateButton->setVisible(true);
    toLabel->setVisible(true);
    endDateButton->setVisible(true);
    searchPeriodButton->setVisible(true);
    searchTitleEdit->clear();
    searchTitleEdit->setFocus();
    startDateButton->setText("1000-01-01/00:00");
    endDateButton->setText("9999-12-31/23:59");
}

void MainWindow::inactivateSearch() {
    searchTitleLabel->setVisible(false);
    searchTitleEdit->setVisible(false);
    searchTitleButton->setVisible(false);
    startDateButton->setVisible(false);
    toLabel->setVisible(false);
    endDateButton->setVisible(false);
    searchPeriodButton->setVisible(false);
    meetingListSelecter->setFocus();
}

void MainWindow::loadUsersTable() {
    ModelGetter::getIt(mAgendaService->listAllUsers(), mUserModel);
}
