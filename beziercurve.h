#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <QPointF>
#include <QPainter>
#include <QVector>
#include <algorithm>

#include "curvedraw.h"
#include "decasteljau.h"

/*todo:
  split the drawing
  and calculating logic*/
class BezierCurve
{
    QVector<QPointF> points;
    QVector<QPointF>::iterator toEditPoint;

public:
    BezierCurve();

    void drawCurve(QPainter&, QColor, QColor);
    void drawBezierCurve(QPainter&, QColor, qreal);
    void animateAlgorithm(QPainter&, qreal, QPointF);

    void deleteLast();
    void deletePoint(QVector<QPointF>::iterator&);

    void add(const QPointF&);
    void editPoint(const QPointF&);

    bool empty();
    bool editPointIsEmpty();

    void setEditPoint(const QVector<QPointF>::iterator&);

    QVector<QPointF>::iterator checkClickToPoints(const QPointF&);
    QVector<QPointF>::iterator checkClickToLines(const QPointF&);

    QVector<QPointF>::iterator end();

private:
    bool checkClickToLine(const QPointF&, const QVector<QPointF>::iterator&);
};

#endif // BEZIERCURVE_H
