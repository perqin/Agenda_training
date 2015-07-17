#include "logindialog.h"

LoginDialog::LoginDialog(AgendaService * as, QWidget * parent)
    : QDialog(parent),
      usernameLabel(new QLabel(tr("User name"))), usernameEdit(new QLineEdit()),
      passwordLabel(new QLabel(tr("Password"))), passwordEdit(new QLineEdit()),
      useremailLabel(new QLabel(tr("E-mail"))), useremailEdit(new QLineEdit()),
      userphoneLabel(new QLabel(tr("Phone"))), userphoneEdit(new QLineEdit()),
      registerTriggleButton(new QPushButton(tr("+ Register"))), loginButton(new QPushButton(tr("Login"))),
      notifyBar(new NotifyBar(tr("Welcome to Agenda!"))),
      agendaService(as), isLogin(true) {
    // Manage layouts and UI
    editLayout = new QGridLayout;
    editLayout->addWidget(usernameLabel, 0, 0);
    editLayout->addWidget(usernameEdit, 0, 1);
    editLayout->addWidget(passwordLabel, 1, 0);
    editLayout->addWidget(passwordEdit, 1, 1);
    editLayout->addWidget(useremailLabel, 2, 0);
    editLayout->addWidget(useremailEdit, 2, 1);
    editLayout->addWidget(userphoneLabel, 3, 0);
    editLayout->addWidget(userphoneEdit, 3, 1);
    QHBoxLayout * buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(registerTriggleButton);
    buttonLayout->addWidget(loginButton);
    bottomLayout = new QVBoxLayout;
    bottomLayout->addLayout(buttonLayout);
    bottomLayout->addWidget(notifyBar);
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(editLayout);
    mainLayout->addLayout(bottomLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);
    passwordEdit->setEchoMode(QLineEdit::Password);
    adjustLayout();

    // Set default button
    registerTriggleButton->setDefault(false);
    loginButton->setDefault(true);

    // Connections
    connect(registerTriggleButton, SIGNAL(clicked(bool)), this, SLOT(showOrHideRegister()));
    connect(loginButton, SIGNAL(clicked(bool)), this, SLOT(loginButtonClicked()));
}

LoginDialog::~LoginDialog() {}

void LoginDialog::initMe() {
    usernameEdit->clear();
    passwordEdit->clear();
    usernameEdit->setFocus();
    show();
}

void LoginDialog::loginButtonClicked() {
    if (isLogin)
        userLogin();
    else
        userRegister();
}

void LoginDialog::showOrHideRegister() {
    isLogin = !isLogin;
    adjustLayout();
}

void LoginDialog::adjustLayout() {
    useremailLabel->setVisible(!isLogin);
    useremailEdit->setVisible(!isLogin);
    userphoneLabel->setVisible(!isLogin);
    userphoneEdit->setVisible(!isLogin);
    loginButton->setText(isLogin ? "Login" : "Register");
    registerTriggleButton->setText(isLogin ? "+ Register" : "- Register");
}

void LoginDialog::userLogin() {
    if (usernameEdit->text().isEmpty()){
        notifyBar->setTextColor(NotifyBar::TextRed);
        notifyBar->setText(tr("Username empty!"));
        usernameEdit->setFocus();
    } else if (passwordEdit->text().isEmpty()){
        notifyBar->setTextColor(NotifyBar::TextRed);
        notifyBar->setText(tr("Password empty!"));
        passwordEdit->setFocus();
    } else if (agendaService->userLogIn(usernameEdit->text().toStdString(), passwordEdit->text().toStdString())) {
        emit loginSucceed(usernameEdit->text(), passwordEdit->text());
        accept();
    } else {
        notifyBar->setTextColor(NotifyBar::TextRed);
        notifyBar->setText(tr("Login fail!"));
    }
}

void LoginDialog::userRegister() {
    if (usernameEdit->text().isEmpty()){
        notifyBar->setTextColor(NotifyBar::TextRed);
        notifyBar->setText(tr("Username empty!"));
        usernameEdit->setFocus();
    } else if (passwordEdit->text().isEmpty()){
        notifyBar->setTextColor(NotifyBar::TextRed);
        notifyBar->setText(tr("Password empty!"));
        passwordEdit->setFocus();
    } else if (useremailEdit->text().isEmpty()){
        notifyBar->setTextColor(NotifyBar::TextRed);
        notifyBar->setText(tr("Email empty!"));
        useremailEdit->setFocus();
    } else if (userphoneEdit->text().isEmpty()){
        notifyBar->setTextColor(NotifyBar::TextRed);
        notifyBar->setText(tr("Phone empty!"));
        userphoneEdit->setFocus();
    } else if (agendaService->userRegister(usernameEdit->text().toStdString(),
                                           passwordEdit->text().toStdString(),
                                           useremailEdit->text().toStdString(),
                                           userphoneEdit->text().toStdString())) {
        notifyBar->setTextColor(NotifyBar::TextGreen);
        notifyBar->setText(tr("Register succeed!"));
        showOrHideRegister();
    } else {
        notifyBar->setTextColor(NotifyBar::TextRed);
        notifyBar->setText(tr("Register fail!"));
    }
}
