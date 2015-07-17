#include "dateselectdialog.h"

DateSelectDialog::DateSelectDialog()
    : selectedDateLabel(new QLabel()),
      daySelector(new QCalendarWidget()),
      hourSpin(new QSpinBox()),
      minuteSpin(new QSpinBox()),
      okButton(new QPushButton(tr("OK"))),
      cancelButton(new QPushButton(tr("Cancel"))),
      requestObject(nullptr),
      selectedDate(Date())
{
    // Layout
    QHBoxLayout * timeSelectorLayout = new QHBoxLayout();
    timeSelectorLayout->addWidget(hourSpin);
    timeSelectorLayout->addWidget(minuteSpin);
    QHBoxLayout * dialogButtonsLayout = new QHBoxLayout();
    dialogButtonsLayout->addWidget(okButton);
    dialogButtonsLayout->addWidget(cancelButton);
    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->addWidget(selectedDateLabel);
    mainLayout->addWidget(daySelector);
    mainLayout->addLayout(timeSelectorLayout);
    mainLayout->addLayout(dialogButtonsLayout);
    this->setLayout(mainLayout);

    // UI
    //

    // Connections
    QObject::connect(daySelector, SIGNAL(selectionChanged()),
                     this, SLOT(setNewDay()));
    QObject::connect(hourSpin, SIGNAL(valueChanged(int)),
                     this, SLOT(setNewHour(int)));
    QObject::connect(minuteSpin, SIGNAL(valueChanged(int)),
                     this, SLOT(setNewMinute(int)));
    QObject::connect(okButton, SIGNAL(clicked(bool)),
                     this, SLOT(finishSelection()));
    QObject::connect(cancelButton, SIGNAL(clicked(bool)),
                     this, SLOT(reject()));
}

DateSelectDialog::~DateSelectDialog() {}

void DateSelectDialog::init() {
    requestObject = QObject::sender();
    daySelector->setSelectedDate(QDate(2015, 1, 1));
    hourSpin->setValue(0);
    minuteSpin->setValue(0);
    this->show();
}

void DateSelectDialog::setNewHour(int newHour) {
    selectedDate.setHour(newHour);
    selectedDateLabel->setText(Date::dateToString(selectedDate).c_str());
}

void DateSelectDialog::setNewMinute(int newMinute) {
    selectedDate.setMinute(newMinute);
    selectedDateLabel->setText(Date::dateToString(selectedDate).c_str());
}

void DateSelectDialog::setNewDay() {
    selectedDate.setYear(daySelector->selectedDate().year());
    selectedDate.setMonth(daySelector->selectedDate().month());
    selectedDate.setDay(daySelector->selectedDate().day());
    selectedDateLabel->setText(Date::dateToString(selectedDate).c_str());
}

void DateSelectDialog::finishSelection() {
    emit dateSelected(selectedDate, requestObject);
    this->accept();
}
