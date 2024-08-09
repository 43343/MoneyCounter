#pragma once
#include <QWidget>
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QColor>
#include <QPieSlice>
#include <QPieSeries>
#include <QChart>


class Square : public QWidget {
    Q_OBJECT

public:
    explicit Square(QPieSlice& slice, QPieSeries& pieSeries , QWidget* parent = nullptr);

    //Set up parammeter
    void setColor(QString& hexColor); 
    void setText(QString& text);
private:
    void paintEvent(QPaintEvent* event) override;
    bool isHovered = false;
    QColor* color;
    QString* textDraw;
    QPieSlice& m_activePieSlice;
    QPieSeries& m_pieSeries;
    int rectWidth = 120;
    int rectHeight = 30;
    int squareSize = 20;
    int textOffset = 10;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void pieScliceActive(bool state);
};
