#include "AddExpenses.h"
#include <QFontDatabase>
#include <QFormLayout>

AddExpenses::AddExpenses(Category* category, QWidget* parent) : QDialog(parent), category(*category) {
    
    QVBoxLayout* layout = new QVBoxLayout();
    m_edit = new QLineEdit();
    QRegularExpression regex(R"(^\d{0,10}(\.\d{0,2})?$)");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex, m_edit);

    QFormLayout* formLayout = new QFormLayout();

    m_edit = new QLineEdit();
    m_edit->setValidator(validator);
    m_edit->setStyleSheet("background-color: #ED2442; color: white;");
    

    comboBox = new QComboBox();
    for (auto item : category->categoryList)
    {
        comboBox->addItem(item.name);
    }
    comboBox->setStyleSheet("background-color: #ED2442; color: white;");

    dateEdit = new QDateEdit(this);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("dd.MM.yyyy");
    dateEdit->setDate(QDate::currentDate());

    formLayout->addRow("Enter amount:", m_edit);
    formLayout->addRow("Select category:", comboBox);
    formLayout->addRow("Purchase Date:", dateEdit);

    layout->addLayout(formLayout);

    QPushButton* okBtn = new QPushButton("OK");
    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(okBtn);
    QPushButton* cancelBtn = new QPushButton(QStringLiteral("Cancel"));
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    layout->addWidget(cancelBtn);



    setLayout(layout);
}

QString AddExpenses::getInput() const {
    return m_edit->text();
}
QString AddExpenses::getCategory() const {
    return comboBox->currentText();
}
QDate AddExpenses::getDate() const {
    return dateEdit->date();
}