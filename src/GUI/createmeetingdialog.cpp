#include "createmeetingdialog.h"

CreateMeetingDialog::CreateMeetingDialog()
    : titleLabel(new QLabel(tr("Title"))),
      titleEdit(new QLineEdit()),
      sponsorLabel(new QLabel(tr("Sponsor"))),
      sponsorText(new QLabel(tr(""))),
      participatorLabel(new QLabel(tr(""))),
      participatorCombo(new QComboBox()),
      startDateLabel(new QLabel(tr("Start date"))),
      startDateButton(new QPushButton(tr("1000-01-01/00:00"))),
      endDateLabel(new QLabel(tr("End date"))),
      endDateButton(new QPushButton(tr("9999-12-31/23:59"))),
      okButton(new QPushButton(tr("OK"))),
      cancelButton(new QPushButton(tr("Cancel"))),
      notifyBar(new NotifyBar(tr("")))
{
    // Layout
    QGridLayout * gridLayout = new QGridLayout();
    gridLayout->addWidget(sponsorLabel, 0, 0);
    gridLayout->addWidget(sponsorText, 0, 1);
    gridLayout->addWidget(participatorLabel, 1, 0);
    gridLayout->addWidget(participatorCombo, 1, 1);
    gridLayout->addWidget(startDateLabel, 2, 0);
    gridLayout->addWidget(startDateButton, 2, 1);
    gridLayout->addWidget(endDateLabel, 3, 0);
    gridLayout->addWidget(endDateButton, 3, 1);
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);
    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(titleEdit);
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(notifyBar);
    this->setLayout(mainLayout);

    // Connections
    QObject::connect(startDateButton, SIGNAL(clicked(bool)),
                     &dateSelector, SLOT(init()));
    QObject::connect(endDateButton, SIGNAL(clicked(bool)),
                     &dateSelector, SLOT(init()));
    QObject::connect(okButton, SIGNAL(clicked(bool)),
                     this, SLOT(finishCreation()));
    QObject::connect(cancelButton, SIGNAL(clicked(bool)),
                     this, SLOT(reject()));
    QObject::connect(&dateSelector, SIGNAL(dateSelected(Date,QObject*)),
                     this, SLOT(newDateSelected(Date,QObject*)));
}

CreateMeetingDialog::~CreateMeetingDialog() {}

void CreateMeetingDialog::startCreation(AgendaService * as, const QString & username) {
    mUsername = username;
    agendaService = as;
    std::list<User> userList = agendaService->listAllUsers();
    titleEdit->setFocus();
    participatorCombo->clear();
    for (std::list<User>::const_iterator it = userList.begin(); it != userList.end(); ++it) {
        if (it->getName() != username.toStdString()) {
            participatorCombo->addItem(it->getName().c_str());
        }
    }
    this->show();
}

void CreateMeetingDialog::finishCreation() {
    if (agendaService->createMeeting(mUsername.toStdString(),
                                     titleEdit->text().toStdString(),
                                     participatorCombo->currentText().toStdString(),
                                     startDateButton->text().toStdString(),
                                     endDateButton->text().toStdString())) {
        emit meetingCreated();
        this->accept();
    } else {
        notifyBar->setTextColor(NotifyBar::TextRed);
        notifyBar->setText(tr("Create fail!"));
    }
}

void CreateMeetingDialog::newDateSelected(Date newDate, QObject *requester) {
    QPushButton * sender = dynamic_cast<QPushButton*>(requester);
    sender->setText(Date::dateToString(newDate).c_str());
}
