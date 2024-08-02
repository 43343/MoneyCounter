#pragma once
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QStyle>

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