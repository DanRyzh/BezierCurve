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

    QString message = "Информация";
    QFont font("Arial", 20, QFont::DemiBold);
    QFontMetrics metrics(font);
    int textWidth = metrics.width(message);

    painter.setPen(QColor(Qt::white));
    painter.setFont(font);

    int h = height();
    int w = width();

    painter.translate(QPoint(w/2, h/2));
    painter.drawText(-textWidth/2, 0, message);
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
