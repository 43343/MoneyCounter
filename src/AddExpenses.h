#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>
#include <QFormLayout>
#include <QLabel>
#include "DatabaseManager.h"
#include "CategoryData.h"

class AddExpenses : public QDialog {
    Q_OBJECT

public:
    explicit AddExpenses(Category* category = (Category*)nullptr, QWidget* parent = (QWidget*)nullptr);

    //Get information about expense
    QString getInput() const;
    QString getCategory() const;
    QDate getDate() const;
    QString getColor() const;

private:
    QFormLayout* formLayout; 

    QLineEdit* amountEdit;

    QComboBox* comboBox;
    void onCategoryChanged(int index);
    Category& m_category;

    QLineEdit* newCategoryNameEdit;
    bool isNewCategory = false;
    QLabel* categoryNameLabel;
    QPushButton* categoryColorEdit;
    QString categoryColor;
    void showColorDialog();

    QDateEdit* dateEdit;
    
    void accepted();
};
