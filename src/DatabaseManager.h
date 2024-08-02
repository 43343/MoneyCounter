#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
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
    QVector<PurchasesInfo> getAllPurchasesInfo();
private:
    QString hashPassword(const QString& password);
};