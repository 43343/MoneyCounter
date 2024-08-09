#pragma once
#include <QDialog>
#include <QRadioButton>
#include <QButtonGroup>
#include <QString>

class ChangeTypeDate : public QDialog
{
	Q_OBJECT
public:
	explicit ChangeTypeDate(int& activeIndex, QWidget* parent = nullptr);

    QString getSelectedTypeDate();

private:
	QButtonGroup* buttonGroup;
	QRadioButton* radio1;
	QRadioButton* radio2;
	QRadioButton* radio3;
	QRadioButton* radio4;

};