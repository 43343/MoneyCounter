#include "Square.h"


Square::Square(QPieSlice& slice, QPieSeries& pieSeries, QWidget* parent) : QWidget(parent), m_activePieSlice(slice), m_pieSeries(pieSeries)
{
    setFixedSize(rectWidth + 1, rectHeight + 1);
    connect(&m_activePieSlice, &QPieSlice::hovered, this, &Square::pieScliceActive);
}

void Square::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    QPen pen;

    if (isHovered)
    {
        pen.setColor(Qt::white);
    }
    else
    {
        pen.setColor(Qt::black);
    }
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawRect(0, 0, rectWidth, rectHeight);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(*color);
    painter.drawRect(10, (rectHeight - squareSize) / 2, squareSize, squareSize);
    painter.setPen(Qt::white);
    painter.drawText(10 + squareSize + textOffset, rectHeight / 2 + 5, *textDraw);
 
}

void Square::enterEvent(QEnterEvent* event)  {
    isHovered = true;
    m_pieSeries.chart()->setAnimationOptions(QChart::AnimationOption::NoAnimation);
    m_activePieSlice.setExploded(true);
    update(); 
}

void Square::pieScliceActive(bool state) {
    isHovered = state;
    m_pieSeries.chart()->setAnimationOptions(QChart::AnimationOption::NoAnimation);
    m_activePieSlice.setExploded(state);
    update();
}

void Square::leaveEvent(QEvent* event)  {
    isHovered = false;
    m_activePieSlice.setExploded(false);
    update(); 
}
void Square::setColor(QString& hexColor) {
    color = new QColor(hexColor);
    update();
}
void Square::setText(QString& text) {
    textDraw = &text;
    update();
}

