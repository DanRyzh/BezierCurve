#ifndef CURVEDRAW_H
#define CURVEDRAW_H

#include <QPainter>

extern QColor colors[7];

void drawPoints(QPainter&, QColor, const QVector<QPointF>&);

void drawLines(QPainter&, QColor, const QVector<QPointF>&);

#endif // CURVEDRAW_H
