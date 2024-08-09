#include "AddExpenses.h"
#include <QFontDatabase>
#include <QFormLayout>
#include <QLabel>
#include <QWidget>
#include <QColorDialog>
#include <QRegularExpressionValidator>

AddExpenses::AddExpenses( Category* category, QWidget* parent) : QDialog(parent), m_category(*category) {
    
    QVBoxLayout* layout = new QVBoxLayout();
    amountEdit = new QLineEdit();
    QRegularExpression regex(R"(^\d{0,10}(\.\d{0,2})?$)");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex, amountEdit);

    formLayout = new QFormLayout();

    amountEdit = new QLineEdit();
    amountEdit->setValidator(validator);
    

    comboBox = new QComboBox();
    for (auto item : category->categoryList)
    {
        comboBox->addItem(item.name);
    }

    comboBox->addItem("New category");
    connect(comboBox, &QComboBox::currentIndexChanged, this, &AddExpenses::onCategoryChanged);

    dateEdit = new QDateEdit(this);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("dd.MM.yyyy");
    dateEdit->setDate(QDate::currentDate());

    newCategoryNameEdit = new QLineEdit();
    categoryColorEdit = new QPushButton();
    categoryColor = category->categoryList[0].colorHex;
    categoryColorEdit->setStyleSheet(QString("background-color: %1").arg(categoryColor));

    connect(categoryColorEdit, &QPushButton::clicked, this, &AddExpenses::showColorDialog);

    categoryNameLabel = new QLabel("Category Name:");

    formLayout->addRow("Enter amount:", amountEdit);
    formLayout->addRow("Select category:", comboBox);
    formLayout->addRow(categoryNameLabel, newCategoryNameEdit);
    formLayout->addRow("Category Color:", categoryColorEdit);
    formLayout->addRow("Purchase Date:", dateEdit);

    categoryNameLabel->setVisible(false);
    newCategoryNameEdit->setVisible(false);

    layout->addLayout(formLayout);

    QPushButton* okBtn = new QPushButton("OK");
    okBtn->setStyleSheet("background-color: #23A75D; color: white;");
    connect(okBtn, &QPushButton::clicked, this, &AddExpenses::accepted);
    layout->addWidget(okBtn);
    QPushButton* cancelBtn = new QPushButton(QStringLiteral("Cancel"));
    cancelBtn->setStyleSheet("background-color: #A72323; color: white;");
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    layout->addWidget(cancelBtn);



    setLayout(layout);
}

void AddExpenses::accepted() {
    if (isNewCategory) {
        if (!newCategoryNameEdit->text().isEmpty())
        {
            accept();
        }
    }
    else 
        accept();
}

void AddExpenses::showColorDialog() {
    QColor color = QColorDialog::getColor();

    categoryColor = color.name();

    if (color.isValid()) {
        categoryColorEdit->setStyleSheet(QString("background-color: %1").arg(categoryColor));
    }
}


void AddExpenses::onCategoryChanged(int index) {
    isNewCategory = comboBox->currentText() == "New category";

    categoryNameLabel->setVisible(isNewCategory);
    newCategoryNameEdit->setVisible(isNewCategory);
    for (auto item : m_category.categoryList)
    {
        if (comboBox->currentText() == item.name) {
            categoryColor = item.colorHex;
            categoryColorEdit->setStyleSheet(QString("background-color: %1").arg(categoryColor));
            break;
        }
    }
}

QString AddExpenses::getInput() const {
    return amountEdit->text();
}
QString AddExpenses::getCategory() const {
    if (isNewCategory) 
        return newCategoryNameEdit->text();
    else 
        return comboBox->currentText();
}
QDate AddExpenses::getDate() const {
    return dateEdit->date();
}
QString AddExpenses::getColor() const {
    return categoryColor;
}