#include <QApplication>
#include "MainWindow.h"
#include "PasswordEntry.h"
#include "RegistrationWindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>

#include "DatabaseManager.h"
#include "CategoryData.h"



int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    DatabaseManager dbManager;
    Category category;
    PasswordEntry* entry = new PasswordEntry(&dbManager);
    RegistrationWindow* registrationWindow = new RegistrationWindow(&dbManager);
    MainWindow* mainWindow = new MainWindow(&category,&dbManager);
    registrationWindow->setFixedSize(350, 150);
    entry->setFixedSize(300, 150);
    mainWindow->setFixedSize(660, 700);
    if (dbManager.userExists())
    {
        QObject::connect(entry, &PasswordEntry::loginSuccessful, [&]() {
            entry->deleteLater();
            mainWindow->show();
            });
        entry->show();
    }
    else
    {

        QObject::connect(registrationWindow, &RegistrationWindow::loginSuccessful, [&]() {
            registrationWindow->deleteLater();
            mainWindow->show();
            });
        registrationWindow->show();
    }
    return a.exec();
}