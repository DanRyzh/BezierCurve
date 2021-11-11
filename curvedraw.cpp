#include "curvedraw.h"

//defined using RGB
QColor colors[7] = {
   {148, 0, 211}, //Violet
   {75, 50, 130}, //Indigo
   {0, 0, 255},   //Blue
   {0, 255, 0},   //Green
   {255, 255, 0}, //Yellow
   {255, 127, 0}, //Orange
   {255, 0 , 0}   //Red
};

void drawPoints(QPainter& painter, QColor color, const QVector<QPointF>& points)
{
    if(points.size()==0) return;

    painter.setPen(QPen(color));
    painter.setBrush(QBrush(color));

    for(int i = 0; i<points.size(); i++)
    {
        painter.drawEllipse(points[i], 3, 3);
        painter.drawText(points[i].x(), points[i].y() - 5, "P" + QString::number(i+1));
    }
}

void drawLines(QPainter& painter, QColor color, const QVector<QPointF> &points)
{
    if(points.size()<2) return;

    painter.setPen(QPen(color));
    painter.setBrush(QBrush(color));

    for(int i = 0; i<points.size() - 1; i++)
    {
        QLineF line(points[i], points[i+1]);
        painter.drawLine(line);
    }
}
