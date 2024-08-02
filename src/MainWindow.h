#pragma once

#include <QWidget>
#include <QChartView>
#include <QPieSlice>
#include <QPieSeries>
#include <QColor>
#include <QVector>
#include <QString>
#include <QSqlError>
#include <QPushButton>
#include "AddExpenses.h"
#include "CategoryData.h"
#include "DatabaseManager.h"
#include "CategoryData.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QMetaEnum>




class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(Category* category, DatabaseManager* dbManager, QWidget* parent = (QWidget*)nullptr, Qt::WindowFlags f = {0});

    enum TypeDate {
        Daily,
        Weekly,
        Monthly,
        Yearly
    };
    Q_ENUM(TypeDate)
private:

    void addExpenses();
    void changeTypeDate();

    void setBackgroundImage(const QString& imagePath);
    QVector<PurchasesInfo> purchasesVisible;
    QVector<PurchasesInfo> purchasesHistory;
    void updatePurchasesInfo(const QString& name, qreal amount, const QDate& date);

    void updateChartSeries();
    void initializePurchasesVisible();
    QPieSeries* series;

    DatabaseManager& dbManager;
    Category& category;
    QGridLayout gridLayout;
    QPixmap backgroundImage;

    QDate currentDate;
    QPair<QDate, QDate> getWeekRange(const QDate& date);

    QGraphicsOpacityEffect* opacityEffect;
    QPropertyAnimation* animation;
    void onFadeOutFinished();
    void onFadeInFinished();
    QPushButton* btnDate;
    bool animatingDateRunning = false;
    TypeDate typeDate = TypeDate::Yearly;

    void autoSizeFont(QPushButton& btnLabelAutosize);

    void updateDateLabel();
};

