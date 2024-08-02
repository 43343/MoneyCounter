#pragma once
#include <QDialog>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpressionValidator>
#include <QComboBox>
#include <QCalendarWidget>
#include <QDateEdit>
#include "CategoryData.h"

class AddExpenses : public QDialog {
    Q_OBJECT

public:
    explicit AddExpenses(Category* category = (Category*)nullptr, QWidget* parent = (QWidget*)nullptr);

    QString getInput() const;
    QString getCategory() const;
    QDate getDate() const;

signals:
    void applied();

private:
    QLineEdit* m_edit;
    QDateEdit* dateEdit;
    QComboBox* comboBox;
    Category& category;
};