#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <QPointF>
#include <QPainter>
#include <QVector>
#include <algorithm>

/*todo:
  divide the drawing
  and calculating logic*/
class BezierCurve
{
    QVector<QPointF> points;
    QVector<QPointF>::iterator toEditPoint;

public:
    BezierCurve();
    ~BezierCurve();

    void drawLines(QPainter&, QColor);
    void drawDots(QPainter&, QColor);
    void drawBezierCurve(QPainter&, QColor, qreal);
    void drawStep(QPainter&, qreal, const QPointF&);
    void drawSupportLines(QPainter&, qreal);

    void deleteLast();
    void deletePoint(QVector<QPointF>::iterator&);

    void add(const QPointF&);
    void editPoint(const QPointF&);

    bool empty();
    bool editPointIsEmpty();

    void setOnEditPoint(const QVector<QPointF>::iterator&);

    QVector<QPointF>::iterator checkClickToPoints(const QPointF&);
    QVector<QPointF>::iterator checkClickToLines(const QPointF&);

    QVector<QPointF>::iterator end();

private:
    void calcBezierDot(QVector<QPointF>&, QVector<QPointF>, qreal);

    void drawLines(QPainter&, QColor, const QVector<QPointF>&);

    bool checkClickToLine(const QPointF&, const QVector<QPointF>::iterator&);

    void drawSupportLines(QVector<QPointF>&, QPainter&, QVector<QPointF>, qreal);

    QPointF moveFromTo(const QPointF&, const QPointF&, qreal);
    qreal moveFromTo(qreal, qreal, qreal);
};

#endif // BEZIERCURVE_H
