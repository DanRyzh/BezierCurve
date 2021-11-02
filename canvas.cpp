#include "canvas.h"

Canvas::Canvas(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Кривые Безье");
    setStyleSheet("background-color: black");
    setFixedSize(1200, 600);

    curve = new BezierCurve;
}

void Canvas::showInfo(QPainter& painter)
{    
    QString info[3] = {"Кривые Безье", "ЛКМ - новая точка", "ПКМ - удалить последнюю точку"};

    int textSize = 20;
    int textOffset = textSize + 15;
    QFont font("Arial", textSize, QFont::DemiBold);
    QFontMetrics metrics(font);

    painter.setPen(QColor(Qt::white));
    painter.setFont(font);

    painter.translate(QPoint(width()/2, height()/2 - (2*textOffset)));

    for(int i = 0; i < 3; i++)
    {
        int textWidth = metrics.width(info[i]);
        painter.drawText(-textWidth/2, i*textOffset, info[i]);
    }
}

void Canvas::closeEvent(QCloseEvent* event)
{
    emit closing();
    event->accept();
}

void Canvas::paintEvent(QPaintEvent*)
{

    QPainter painter;
    painter.begin(this);

    if(curve->empty())
        showInfo(painter);
    else
    {
        curve->drawLines(painter, Qt::white);
        curve->drawDots(painter, Qt::red);
        curve->drawBezierCurve(painter, Qt::blue, 0.0025);
    }

    painter.end();
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)  curve->add(event->pos());
    if (event->button() == Qt::RightButton) curve->deleteLast();
    update();
}

Canvas::~Canvas()
{
    delete curve;
}
