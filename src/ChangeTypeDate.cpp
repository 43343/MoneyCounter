#include "ChangeTypeDate.h"

ChangeTypeDate::ChangeTypeDate(int& activeIndex, QWidget* parent) :
    QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    radio1 = new QRadioButton("Daily", this);
    radio2 = new QRadioButton("Weekly", this);
    radio3 = new QRadioButton("Monthly", this);
    radio4 = new QRadioButton("Yearly", this);

    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(radio1);
    buttonGroup->addButton(radio2);
    buttonGroup->addButton(radio3);
    buttonGroup->addButton(radio4);

    switch (activeIndex) {
    case 0:
        radio1->setChecked(true);
        break;
    case 1:
        radio2->setChecked(true);
        break;
    case 2:
        radio3->setChecked(true);
        break;
    case 3:
        radio4->setChecked(true);
        break;
    }

 
    layout->addWidget(radio1);
    layout->addWidget(radio2);
    layout->addWidget(radio3);
    layout->addWidget(radio4);


    QPushButton* okBtn = new QPushButton("OK");
    okBtn->setMinimumHeight(20);
    okBtn->setStyleSheet("background-color: #23A75D; color: white;");
    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(okBtn);
    QPushButton* cancelBtn = new QPushButton(QStringLiteral("Cancel"));
    cancelBtn->setMinimumHeight(20);
    cancelBtn->setStyleSheet("background-color: #A72323; color: white;");
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    layout->addWidget(cancelBtn);

    setLayout(layout);
}

QString ChangeTypeDate::getSelectedTypeDate() {
    if (buttonGroup->checkedButton() == radio1) {
        return "Daily";
    }
    else if (buttonGroup->checkedButton() == radio2) {
        return "Weekly";
    }
    else if (buttonGroup->checkedButton() == radio3) {
        return "Monthly";
    }
    else if (buttonGroup->checkedButton() == radio4) {
        return "Yearly";
    }
    return "None";
}