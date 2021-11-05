#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <QPointF>
#include <QPainter>
#include <QVector>


class BezierCurve
{
    QVector<QPointF> points;
    int expectToEdit = -1;

public:
    BezierCurve();
    ~BezierCurve();
    void drawLines(QPainter&, QColor);
    void drawLines(QPainter&, QColor, QVector<QPointF>&);
    void drawDots(QPainter&, QColor);
    void drawBezierCurve(QPainter&, QColor, qreal);
    void add(const QPointF&);

    int checkPointClick(const QPointF&);

    void deleteLast();
    void deletePoint(int);

    void editPoint(const QPointF&);

    bool empty();
    bool editPointIsEmpty();

    void setOnEditPoint(int);

private:
    void calcBezierDot(QVector<QPointF>&, QVector<QPointF>, qreal);
    QPointF moveFromTo(QPointF, QPointF, qreal);
    qreal moveFromTo(qreal, qreal, qreal);
};

#endif // BEZIERCURVE_H
