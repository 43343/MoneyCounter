#include "MainWindow.h"
#include "Square.h"
#include "ChangeTypeDate.h"
#include <QDate>
#include <QFontMetrics>

MainWindow::MainWindow(Category* category, DatabaseManager* dbManager, QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f), dbManager(*dbManager), category(*category) {
    purchasesHistory = dbManager->getAllPurchasesInfo();
  
    currentDate = QDate::currentDate();
    
    series = new QPieSeries();
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setPlotAreaBackgroundVisible(false); 
    chart->setBackgroundBrush(Qt::NoBrush); 
    chart->setBackgroundPen(Qt::NoPen);
    chart->createDefaultAxes();

    initializePurchasesVisible();
    updateChartSeries();


    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(this);
    chartView->setGeometry(30, 50, 600, 400);
    chartView->setBackgroundBrush(Qt::NoBrush); 
    chartView->setFrameStyle(QFrame::NoFrame);

    
    gridLayout.setAlignment(Qt::AlignCenter);
    //layout->setGeometry();
    QWidget* container = new QWidget(this);
    container->setLayout(&gridLayout);
    container->setGeometry(0, 25, 650, 100);


    QPushButton* btn = new QPushButton("Add expense", this);
    btn->setGeometry(230, 420, 200, 100);
    btn->setStyleSheet("background-color: #ED2442; color: white; font-weight: bold; font: 14pt");
    connect(btn, &QPushButton::clicked, this, &MainWindow::addExpenses);

    btnDate = new QPushButton(currentDate.toString("yyyy"), this);
    btnDate->setGeometry(15, 220, 85, 70);
    btnDate->setStyleSheet("background-color: transparent; border: none; color: white; font-weight: bold;");
    opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(1);
    btnDate->setGraphicsEffect(opacityEffect);
    animation = new QPropertyAnimation(opacityEffect, "opacity");
    animation->setDuration(400);
    connect(btnDate, &QPushButton::clicked, this, &MainWindow::changeTypeDate);
    autoSizeFont(*btnDate);

    QPushButton* btnUp = new QPushButton(this);
    btnUp->setIcon(QIcon(":/images/arrowUp.png")); 
    btnUp->setIconSize(QSize(32, 32)); 
    btnUp->setGeometry(41, 120, 30, 30);
    btnUp->setStyleSheet("background-color: transparent; border: none;");
    connect(btnUp, &QPushButton::clicked, this, [this] {
        if (typeDate == TypeDate::Daily) currentDate = currentDate.addDays(1);
        if (typeDate == TypeDate::Weekly) currentDate = currentDate.addDays(7);
        if (typeDate == TypeDate::Monthly) currentDate = currentDate.addMonths(1);
        if (typeDate == TypeDate::Yearly) currentDate = currentDate.addYears(1);
        updateDateLabel();
    });
    QPushButton* btnDown = new QPushButton(this);
    btnDown->setIcon(QIcon(":/images/arrowDown.png")); 
    btnDown->setIconSize(QSize(32, 32)); 
    btnDown->setGeometry(41, 350, 30, 30);
    btnDown->setStyleSheet("background-color: transparent; border: none;");
    connect(btnDown, &QPushButton::clicked, this, [this] {
        if (typeDate == TypeDate::Daily) currentDate = currentDate.addDays(-1);
        if (typeDate == TypeDate::Yearly) currentDate = currentDate.addYears(-1);
        if (typeDate == TypeDate::Weekly) currentDate = currentDate.addDays(-7);
        if (typeDate == TypeDate::Monthly) currentDate = currentDate.addMonths(-1);
        updateDateLabel();
    });
    setBackgroundImage(":/4015db3053c401bf5c6d3eef84d7c583.jpg");
        
}

void MainWindow::updateDateLabel() {
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    connect(animation, &QPropertyAnimation::finished, this, &MainWindow::onFadeOutFinished);
    animation->start();
    initializePurchasesVisible();
    updateChartSeries();
}

void MainWindow::autoSizeFont(QPushButton& btnAutoSizeFont) {
    int buttonWidth = btnAutoSizeFont.width();
    int buttonHeight = btnAutoSizeFont.height();

    
    int fontSize = 1;
    QFont font = btnAutoSizeFont.font();

    
    while (true) {
        QFont testFont = font;
        testFont.setPointSize(fontSize);
        QFontMetrics fm(testFont);
        QRect textRect = fm.boundingRect(rect(), Qt::AlignCenter, btnAutoSizeFont.text());

        if (textRect.width() > buttonWidth || textRect.height() > buttonHeight) {
            break;
        }

        fontSize++;
    }

    
    font.setPointSize(fontSize - 1);
    btnAutoSizeFont.setFont(font);
}

void MainWindow::onFadeOutFinished() {
    
    if (typeDate == TypeDate::Daily) btnDate->setText(currentDate.toString("d MMM. yyyy"));
    if (typeDate == TypeDate::Monthly) btnDate->setText(currentDate.toString("MMMM yyyy"));
    if (typeDate == TypeDate::Weekly)
    {
        QPair<QDate, QDate> weekRange = getWeekRange(currentDate);
        QString weekText = QString("%1 - %2 %3")
            .arg(weekRange.first.toString("d MMM"))
            .arg(weekRange.second.toString("d MMM"))
            .arg(currentDate.year());
        btnDate->setText(weekText);
    }
    if (typeDate == TypeDate::Yearly) btnDate->setText(currentDate.toString("yyyy"));
    autoSizeFont(*btnDate);

    
    disconnect(animation, &QPropertyAnimation::finished, this, &MainWindow::onFadeOutFinished);

    connect(animation, &QPropertyAnimation::finished, this, &MainWindow::onFadeInFinished);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start();
}

void MainWindow::onFadeInFinished() {
    disconnect(animation, &QPropertyAnimation::finished, this, &MainWindow::onFadeInFinished);
}

void MainWindow::setBackgroundImage(const QString& imagePath) {
    QPixmap bkgnd(imagePath);

    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}

QPair<QDate, QDate> MainWindow::getWeekRange(const QDate& date) {
    QDate startOfWeek = date.addDays(-(date.dayOfWeek() - 1)); 
    QDate endOfWeek = startOfWeek.addDays(6); 
    return qMakePair(startOfWeek, endOfWeek);
}


void MainWindow::addExpenses() {
    AddExpenses dlg(&category,this);
    dlg.setFixedSize(250, 150);
    switch (dlg.exec()) {
    case QDialog::Accepted:
        qDebug() << "Accepted";
        updatePurchasesInfo(dlg.getCategory(), dlg.getInput().toDouble(), dlg.getDate());
        break;
    case QDialog::Rejected:
        qDebug() << "Rejected";
        break;
    default:
        qDebug() << "Unexpected";
    }
}

void MainWindow::changeTypeDate() {
    int typeDateId = static_cast<int>(typeDate);
    ChangeTypeDate dlg (typeDateId, this);
    dlg.setFixedSize(250, 150);
    switch (dlg.exec()) {
    case QDialog::Accepted:
        qDebug() << "Accepted";
        TypeDate typeCurrentDate;
        if (dlg.getSelectedTypeDate() == "Daily") typeCurrentDate = TypeDate::Daily;
        if (dlg.getSelectedTypeDate() == "Weekly") typeCurrentDate = TypeDate::Weekly;
        if (dlg.getSelectedTypeDate() == "Monthly") typeCurrentDate = TypeDate::Monthly;
        if (dlg.getSelectedTypeDate() == "Yearly") typeCurrentDate = TypeDate::Yearly;
        if (typeCurrentDate != typeDate)
        {
            typeDate = typeCurrentDate;
            currentDate = QDate::currentDate();
            updateDateLabel();
        }
        break;
    case QDialog::Rejected:
        qDebug() << "Rejected";
        break;
    default:
        qDebug() << "Unexpected";
    }
}

void MainWindow::updatePurchasesInfo(const QString& name, qreal amount, const QDate& date) {
    int index = 0;
    for (int i = 0; i < category.categoryList.size(); i++) {
        if (category.categoryList[i].name == name) {
            index = i;
            break;
        }
    }
    PurchasesInfo purchasesInfo;
    purchasesInfo.indexCategory = index;
    purchasesInfo.amount = amount;
    purchasesInfo.date = date;
    purchasesHistory.append(purchasesInfo);
    initializePurchasesVisible();

    dbManager.insertPurchasesInfo(purchasesInfo);
    QPair<QDate, QDate> weekRange = getWeekRange(currentDate);

    if ((typeDate == TypeDate::Daily && date == currentDate) ||
        (typeDate == TypeDate::Weekly && date >= weekRange.first && date <= weekRange.second) ||
        (typeDate == TypeDate::Monthly && date.year() == currentDate.year() && date.month() == currentDate.month()) ||
        (typeDate == TypeDate::Yearly && date.year() == currentDate.year()))
    {
        updateChartSeries();
    }
}

void MainWindow::updateChartSeries() {
    int columns = 5;
    series->clear();
    series->chart()->setAnimationOptions(QChart::AnimationOption::SeriesAnimations);
    while (QLayoutItem* item = gridLayout.takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater(); 
        }
        delete item; 
    }
    qreal totalSpend = std::accumulate(purchasesVisible.begin(), purchasesVisible.end(), 0.0,
                                        [](qreal total, const PurchasesInfo& item) {
                                        return total + item.amount;
                                        });
    for (int i = 0; i < purchasesVisible.size(); i++) {
        if (i < 6) {
            if (purchasesVisible[i].amount != 0)
            {
                QPieSlice* slice = series->append(QString::asprintf("%0.2f", purchasesVisible[i].amount / totalSpend * 100) + "%", purchasesVisible[i].amount);
                QString colorHex = category.categoryList[purchasesVisible[i].indexCategory].colorHex;
                slice->setBrush(QColor(colorHex));
                slice->setPen(QPen(Qt::black, 2)); // Устанавливаем черный цвет линии границы и толщину 2
                if (purchasesVisible[i].amount / totalSpend * 100 > 8) slice->setLabelVisible();
                //slice->setLabelArmLengthFactor(3);
                slice->setLabelColor(QColor("#FFFFFF"));
                slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
                Square* square = new Square(*slice, *series);
                square->setColor(colorHex);
                square->setText(category.categoryList[purchasesVisible[i].indexCategory].name);
                int row = i / columns;
                int column = i % columns;
                gridLayout.addWidget(square, row, column);
            }
            else break;
        }
        else if (series->count() > 0) {
            qreal otherPercentage = std::accumulate(purchasesVisible.begin() + 5, purchasesVisible.end(), 0.0,
                                    [](qreal total, const PurchasesInfo& item) {
                                        return total + item.amount;
                                    });
            QPieSlice* slice = series->append(QString::asprintf("%0.2f", otherPercentage / totalSpend * 100) + "%", otherPercentage);
            QString* grayHexColor = new QString("#808080");
            QString* other = new QString("Other");
            slice->setBrush(QColor(*grayHexColor));
            slice->setPen(QPen(Qt::black, 2)); 
            if(otherPercentage / totalSpend * 100 > 8) slice->setLabelVisible();
            //slice->setLabelArmLengthFactor(0);
            slice->setLabelColor(QColor("#FFFFFF"));
            slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
            Square* square = new Square(*slice, *series);
            square->setColor(*grayHexColor);
            square->setText(*other);
            int row = i / columns;
            int column = i % columns;
            gridLayout.addWidget(square, row, column);
            break;
        }
    }

    if (series->count() == 0)
    {
        qDebug() << "Количество PieSlice равно нулю.";
        QPieSlice* slice = series->append("", 10);
        slice->setBrush(QColor("#036B6B"));
    }
}

void MainWindow::initializePurchasesVisible() {
    purchasesVisible = {};
    QPair<QDate, QDate> weekRange = getWeekRange(currentDate);
    for (int i = 0; i < category.categoryList.size(); i++)
    {
        PurchasesInfo purchasesInfo;
        purchasesInfo.indexCategory = i;
        purchasesInfo.amount = 0;
        purchasesVisible.append(purchasesInfo);
        qDebug() << purchasesVisible[i].indexCategory;
    }
    for (int i = 0; i < purchasesVisible.size(); i++)
    {
        for (int j = 0; j < purchasesHistory.size(); j++)
        {
            if (purchasesHistory[j].indexCategory == i && ((typeDate == TypeDate::Daily && purchasesHistory[j].date == currentDate) ||
                (typeDate == TypeDate::Weekly && purchasesHistory[j].date >= weekRange.first && purchasesHistory[j].date <= weekRange.second) ||
                (typeDate == TypeDate::Monthly && purchasesHistory[j].date.year() == currentDate.year() && purchasesHistory[j].date.month() == currentDate.month()) ||
                (typeDate == TypeDate::Yearly && purchasesHistory[j].date.year() == currentDate.year())))
            {
                purchasesVisible[i].amount += purchasesHistory[j].amount;
            }
        }
    }
    std::sort(purchasesVisible.begin(), purchasesVisible.end(), [](const PurchasesInfo& a, const PurchasesInfo& b) {
        return a.amount > b.amount;
        });
}


