#ifndef DECASTELJAU_H
#define DECASTELJAU_H

#include <QPainter>
#include <QVector>
#include "curvedraw.h"

void calcBezierDot(QVector<QPointF>&, QVector<QPointF>, qreal);

QPointF moveFromTo(const QPointF&, const QPointF&, qreal);

qreal moveFromTo(qreal, qreal, qreal);

void drawBearingLines(QPainter&, QVector<QPointF>, qreal);

void drawStep(QPainter&, qreal, const QPointF&);

#endif // DECASTELJAU_H
