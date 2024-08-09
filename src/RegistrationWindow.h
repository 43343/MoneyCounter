#pragma once
#include <QWidget>
#include <QLineEdit>
#include "DatabaseManager.h"

class RegistrationWindow : public QWidget
{
	Q_OBJECT
public:
	explicit RegistrationWindow(DatabaseManager* dbManager,  QWidget* parent = (QWidget*)nullptr, Qt::WindowFlags f = { 0 });
signals:
	void loginSuccessful();
private slots:
	void onSignInClicked();
private:
	QLineEdit* passwordField;
	QLineEdit* confirmPasswordField;
	QLineEdit* usernameField;
	DatabaseManager& dbManager;
};