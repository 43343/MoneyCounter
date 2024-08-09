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


    //Drawing background
    QPixmap backgroundImage;
    void paintEvent(QPaintEvent* event) override;

    QVector<PurchasesInfo> purchasesVisible;
    QVector<PurchasesInfo> purchasesHistory;
    void updatePurchasesInfo(const QString& name, const qreal amount, const QDate& date);
    void updateCategoryInfo(const QString& name, const QString& colorHex);

    void updateChartSeries();
    void initializePurchasesVisible();
    QPieSeries* series;

    DatabaseManager& dbManager;
    Category& category;
    QGridLayout gridLayout;


    QDate currentDate;
    QPair<QDate, QDate> getWeekRange(const QDate& date);

    //Date animation
    QGraphicsOpacityEffect* opacityEffect;
    QPropertyAnimation* animation;
    void onFadeOutFinished();
    void onFadeInFinished();
    QPushButton* btnDate;
    bool animatingDateRunning = false;

    void changeTypeDate();
    TypeDate typeDate = TypeDate::Yearly;

    void autoSizeFont(QPushButton& btnLabelAutosize);

    void updateDateLabel();
};

