#pragma once
#include <QSqlDatabase>
#include "CategoryData.h"
#include <QVector>

class DatabaseManager {
public:
    DatabaseManager();

    bool userExists();

    QString getUsername();

    bool registerUser(const QString& username, const QString& password);

    bool authenticateUser(const QString& username, const QString& password);

    void insertPurchasesInfo(const PurchasesInfo& data);
    void insertCategoryInfo(const QVector<CategoryStr>& data);
    QVector<PurchasesInfo> getAllPurchasesInfo();
    QVector<CategoryStr> getAllCategoriesInfo();
private:
    QString hashPassword(const QString& password);
    QSqlDatabase db;
};