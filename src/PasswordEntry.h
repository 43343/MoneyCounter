#pragma once
#include <QWidget>
#include <QLineEdit>

#include "DatabaseManager.h"

class PasswordEntry : public QWidget
{
	Q_OBJECT
public:
	explicit PasswordEntry(DatabaseManager* dbManager, QWidget* parent = (QWidget*)nullptr, Qt::WindowFlags f = { 0 });
signals:
	void loginSuccessful();
private slots:
	void onSignInClicked();
private:
	QLineEdit* passwordField;
	DatabaseManager& dbManager;
};