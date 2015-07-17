#ifndef DATESELECTDIALOG_H
#define DATESELECTDIALOG_H

#include <QDialog>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QCalendarWidget>
#include <QDate>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../Core/Date.h"

class DateSelectDialog : public QDialog
{
    Q_OBJECT

public:
    DateSelectDialog();
    ~DateSelectDialog();
signals:
    void dateSelected(Date date, QObject * requester);
public slots:
    void init();
private slots:
    void setNewHour(int newHour);
    void setNewMinute(int newMinute);
    void setNewDay();
    void finishSelection();
private:
    QLabel * selectedDateLabel;
    QCalendarWidget * daySelector;
    QSpinBox * hourSpin;
    QSpinBox * minuteSpin;
    QPushButton * okButton;
    QPushButton * cancelButton;
    QObject * requestObject;
    Date selectedDate;
};

#endif // DATESELECTDIALOG_H
