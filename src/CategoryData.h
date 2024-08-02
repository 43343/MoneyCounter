#pragma once
#include <QString>
#include <QDate>
#include <QVector>

struct PurchasesInfo {
    int indexCategory;
    qreal amount;
    QDate date;
};
struct CategoryStr
{
    QString name;
    QString colorHex;
};

class Category {
public:
    Category();
    QVector<CategoryStr> categoryList;
};