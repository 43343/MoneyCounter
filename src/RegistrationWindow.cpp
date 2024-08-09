#include "RegistrationWindow.h"
#include <QFormLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

RegistrationWindow::RegistrationWindow(DatabaseManager* dbManager,  QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f), dbManager(*dbManager)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* registration = new QLabel("Registration!", this);
    QFont font = registration->font();
    font.setBold(true);
    font.setPointSize(18);
    registration->setFont(font);
    registration->setAlignment(Qt::AlignCenter);
    layout->addWidget(registration);

    QFormLayout* formLayout = new QFormLayout();

    usernameField = new QLineEdit(this);
    passwordField = new QLineEdit(this);
    confirmPasswordField = new QLineEdit(this);

    passwordField->setEchoMode(QLineEdit::Password);
    confirmPasswordField->setEchoMode(QLineEdit::Password);

    usernameField->setFixedWidth(200);
    passwordField->setFixedWidth(200);
    confirmPasswordField->setFixedWidth(200);

    formLayout->addRow("Enter your username:", usernameField);
    formLayout->addRow("Enter your password:", passwordField);
    formLayout->addRow("Confirm your password:", confirmPasswordField);

    layout->addLayout(formLayout);

    QPushButton* registerButton = new QPushButton("Register", this);
    connect(registerButton, &QPushButton::clicked, this, &RegistrationWindow::onSignInClicked);

    layout->addWidget(registerButton);
    setLayout(layout);
}

void RegistrationWindow::onSignInClicked() {
    QString enteredUsername = usernameField->text();
    QString enteredPassword = passwordField->text();
    QString confirmedPassword = confirmPasswordField->text();
    if (enteredPassword == confirmedPassword && !enteredPassword.isEmpty() && !enteredUsername.isEmpty())
    {
        if (dbManager.registerUser(enteredUsername, enteredPassword))
        {
            emit loginSuccessful();
        }
        else
        {
            qDebug() << "Failed to save user to database";
        }
    }
    else
    {
        passwordField->clear();
        confirmPasswordField->clear();
    }
}