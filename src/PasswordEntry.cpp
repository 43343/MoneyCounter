#include "PasswordEntry.h"

PasswordEntry::PasswordEntry(DatabaseManager* dbManager, QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f), dbManager(*dbManager)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* welcomePeople = new QLabel("Welcome, " + dbManager->getUsername(), this);
    welcomePeople->setStyleSheet("font-weight:bold; font-size:18px");
    welcomePeople->setAlignment(Qt::AlignCenter);
    layout->addWidget(welcomePeople);

    QLabel* enterYourPassword = new QLabel("Enter your password:", this);

    QHBoxLayout* passwordLayout = new QHBoxLayout();
    passwordField = new QLineEdit(this);
    passwordField->setEchoMode(QLineEdit::Password);


    passwordLayout->addWidget(enterYourPassword);
    passwordLayout->addWidget(passwordField);

    layout->addLayout(passwordLayout);

    QPushButton* loginButton = new QPushButton("Sign in", this);
    connect(loginButton, &QPushButton::clicked, this, &PasswordEntry::onSignInClicked);

    layout->addWidget(loginButton);
    setLayout(layout);
}

void PasswordEntry::onSignInClicked() {
    QString password = passwordField->text();
    if (dbManager.authenticateUser(dbManager.getUsername(), password)) {
        qDebug() << "Login successful";
        emit loginSuccessful();
    }
    else {
        passwordField->clear();
    }
}