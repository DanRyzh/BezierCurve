#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <QPointF>
#include <QPainter>
#include <QVector>
#include <algorithm>


class BezierCurve
{
    QVector<QPointF> points;
    QVector<QPointF>::iterator toEditPoint;

public:
    BezierCurve();
    ~BezierCurve();

    void drawLines(QPainter&, QColor);
    void drawLines(QPainter&, QColor, QVector<QPointF>&);
    void drawDots(QPainter&, QColor);
    void drawBezierCurve(QPainter&, QColor, qreal);

    void deleteLast();
    void deletePoint(QVector<QPointF>::iterator&);
    void add(const QPointF&);
    void editPoint(const QPointF&);

    bool empty();
    bool editPointIsEmpty();

    void setOnEditPoint(const QVector<QPointF>::iterator&);

    QVector<QPointF>::iterator checkClickToPoints(const QPointF&);
    QVector<QPointF>::iterator checkClickToLines(const QPointF&);
    bool checkClickToLine(const QPointF&, QVector<QPointF>::iterator);

    QVector<QPointF>::iterator end();

private:
    void calcBezierDots(QVector<QPointF>&, QVector<QPointF>, qreal);

    QPointF moveFromTo(QPointF, QPointF, qreal);
    qreal moveFromTo(qreal, qreal, qreal);
};

#endif // BEZIERCURVE_H
