#ifndef CREATEMEETINGDIALOG_H
#define CREATEMEETINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>
#include <list>
#include "../Core/AgendaService.h"
#include "dateselectdialog.h"
#include "../Core/User.h"
#include "notifybar.h"

class CreateMeetingDialog : public QDialog
{
    Q_OBJECT

public:
    CreateMeetingDialog();
    ~CreateMeetingDialog();
signals:
    void meetingCreated();
public slots:
    void startCreation(AgendaService * as, const QString & username);
    void finishCreation();
private slots:
    void newDateSelected(Date newDate, QObject * requester);
private:
    QLabel * titleLabel;
    QLineEdit * titleEdit;
    QLabel * sponsorLabel;
    QLabel * sponsorText;
    QLabel * participatorLabel;
    QComboBox * participatorCombo;
    QLabel * startDateLabel;
    QPushButton * startDateButton;
    QLabel * endDateLabel;
    QPushButton * endDateButton;
    QPushButton * okButton;
    QPushButton * cancelButton;
    NotifyBar * notifyBar;
    AgendaService * agendaService;
    QString mUsername;
    DateSelectDialog dateSelector;
};

#endif // CREATEMEETINGDIALOG_H
