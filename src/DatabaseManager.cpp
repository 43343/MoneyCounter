#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
    }
    else {
        qDebug() << "Database: connection ok";
        QSqlQuery query;
        QString createTableQueryUser = "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT NOT NULL UNIQUE, "
            "password TEXT NOT NULL)";
        if (!query.exec(createTableQueryUser)) {
            qDebug() << "Unable to create table 'users':" << query.lastError().text();
        }
        QString createTableQueryPurchasesHistory = "CREATE TABLE IF NOT EXISTS PurchasesHistory ("
            "indexCategory INTEGER,"
            "amount REAL NOT NULL UNIQUE, "
            "date TEXT NOT NULL)";
        if (!query.exec(createTableQueryPurchasesHistory)) {
            qDebug() << "Unable to create table 'PurchasesHistory':" << query.lastError().text();
        }
        QString createTableQueryCategoryList = "CREATE TABLE IF NOT EXISTS CategoryList ("
            "name TEXT NOT NULL,"
            "colorHex TEXT NOT NULL)";
        if (!query.exec(createTableQueryCategoryList)) {
            qDebug() << "Unable to create table 'CategoryList':" << query.lastError().text();
        }
    }
}

bool DatabaseManager::userExists() {
    QSqlQuery query("SELECT COUNT(*) FROM users");
    if (query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

QString DatabaseManager::getUsername() {
    QSqlQuery query("SELECT username FROM users LIMIT 1");
    if (query.next()) {
        return query.value(0).toString();
    }
    return QString();
}

bool DatabaseManager::registerUser(const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashPassword(password));
    return query.exec();
}

bool DatabaseManager::authenticateUser(const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashPassword(password));
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

void DatabaseManager::insertPurchasesInfo(const PurchasesInfo& data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO PurchasesHistory (indexCategory, amount, date) "
        "VALUES (:indexCategory, :amount, :date)");
    query.bindValue(":indexCategory", data.indexCategory);
    query.bindValue(":amount", data.amount);
    query.bindValue(":date", data.date.toString(Qt::ISODate));

    if (!query.exec()) {
        qDebug() << "Failed to insert data:" << query.lastError();
    }
    
}

QVector<PurchasesInfo> DatabaseManager::getAllPurchasesInfo() {
    QVector<PurchasesInfo> data;

    QSqlQuery query("SELECT indexCategory, amount, date FROM PurchasesHistory");

    if (!query.exec() || query.size() == 0) {
        qDebug() << "Failed to retrieve data:" << query.lastError();
        return { };
    }

    while (query.next()) {
        PurchasesInfo item;
        item.indexCategory = query.value("indexCategory").toInt();
        item.amount = query.value("amount").toFloat();
        item.date = QDate::fromString(query.value("date").toString(), Qt::ISODate);

        data.append(item);
    }
    return data;
}

void DatabaseManager::insertCategoryInfo(const QVector<CategoryStr>& data) {
    QSqlQuery query(db);
    if (!query.exec("DELETE FROM CategoryList")) {
        qDebug() << "Unable to clear table 'CategoryList':" << query.lastError().text();
        return;
    }
    for (const auto& category : data) {
        query.prepare("INSERT INTO CategoryList (name, colorHex) VALUES (:name, :colorHex)");
        query.bindValue(":name", category.name);
        query.bindValue(":colorHex", category.colorHex);
        if (!query.exec()) {
            qDebug() << "Unable to insert into 'CategoryList':" << query.lastError().text();
        }
    }
}

QVector<CategoryStr> DatabaseManager::getAllCategoriesInfo() {
    QVector<CategoryStr> data;

    QSqlQuery query("SELECT name, colorHex FROM CategoryList");

    if (!query.exec() || query.size() == 0) {
        qDebug() << "Failed to retrieve data:" << query.lastError();
        return { };
    }

    while (query.next()) {
        CategoryStr item;
        item.name = query.value("name").toString();
        item.colorHex = query.value("colorHex").toString();

        data.append(item);
    }
    return data;
}


QString DatabaseManager::hashPassword(const QString& password) {
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashedPassword.toHex());
}