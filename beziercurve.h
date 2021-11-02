#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <QPointF>
#include <QPainter>
#include <QVector>


class BezierCurve
{
    QVector<QPointF> points;

public:
    BezierCurve();
    ~BezierCurve();
    void drawLines(QPainter&, QColor);
    void drawDots(QPainter&, QColor);
    void drawBezierCurve(QPainter&, QColor, qreal);
    void add(const QPointF&);
    void deleteLast();

    bool empty();
private:
    void drawBezierDot(QPainter&, QVector<QPointF>, qreal);
    QPointF moveFromTo(QPointF, QPointF, qreal);
    qreal moveFromTo(qreal, qreal, qreal);
};

#endif // BEZIERCURVE_H
