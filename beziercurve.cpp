#include "beziercurve.h"

BezierCurve::BezierCurve()
{
    toEditPoint = end();
}

/*Calculating if given point lies between p1 and p1+1 (lies on line(p1, p1+1))
  with 4 px allowance*/
bool BezierCurve::checkClickToLine(const QPointF& point, const QVector<QPointF>::iterator &p1)
{
    QVector<QPointF>::iterator p2 = p1 + 1;

    int pxAllowance = 4;

    QPointF A(p1->x() + pxAllowance, p1->y() + pxAllowance);
    QPointF B(p1->x() - pxAllowance, p1->y() - pxAllowance);
    QPointF C(p2->x() - pxAllowance, p2->y() - pxAllowance);
    QPointF D(p2->x() + pxAllowance, p2->y() + pxAllowance);

    QPolygonF polygon({A, B, C, D});

    return polygon.containsPoint(point, Qt::OddEvenFill);
}

//Checking if point lies on some curves's line (at least 1 line required)
//if point lies, includes point and returns its iterator
QVector<QPointF>::iterator BezierCurve::checkClickToLines(const QPointF& point)
{
    if(points.size()<2) return end();

    for(auto pIt = points.begin(); pIt!=points.end() - 1; pIt++)
        if(checkClickToLine(point, pIt))
           return points.insert(++pIt, point);

    return end();
}

/*Checking if point lies on some point in curve (at least 1 line required)
  if point matches returns its iterator
  +-6 means the ability to get to the point by clicking*/
QVector<QPointF>::iterator BezierCurve::checkClickToPoints(const QPointF& point)
{
    auto p = points.begin();

    for(;p!=points.end(); p++)
        if(point.x() + 6 > p->x() && point.x()-6 < p->x()
                && point.y()+6 > p->y() && point.y()-6 < p->y())
            break;

    return p;
}

void BezierCurve::drawCurve(QPainter& painter, QColor pointColor, QColor lineColor)
{
    drawPoints(painter, pointColor, points);
    drawLines(painter, lineColor, points);
}

void BezierCurve::drawBezierCurve(QPainter& painter, QColor color, qreal step)
{
    if(points.size()<3) return;

    QVector<QPointF> curveCopied;
    curveCopied.reserve(static_cast<int>(1/step + 1));

    for (qreal i = 0; i <= 1.0; i += step)
        calcBezierDot(curveCopied, points, i);

    drawLines(painter, color, curveCopied);
}

void BezierCurve::animateAlgorithm(QPainter& painter, qreal step, QPointF pos)
{
    if(points.size()<3) return;

    drawBearingLines(painter, points, step);
    drawStep(painter, step, pos);
}

bool BezierCurve::empty()
{
    return points.isEmpty();
}

void BezierCurve::setEditPoint(const QVector<QPointF>::iterator& pIt)
{
    toEditPoint = pIt;
}

QVector<QPointF>::iterator BezierCurve::end()
{
    return points.end();
}

bool BezierCurve::editPointIsEmpty()
{
    return toEditPoint == points.end();
}

void BezierCurve::add(const QPointF& point)
{
    points.push_back(point);
}

void BezierCurve::deleteLast()
{
    if(!points.isEmpty()) points.pop_back();
}

void BezierCurve::deletePoint(QVector<QPointF>::iterator& pIt)
{
    points.erase(pIt);
}

void BezierCurve::editPoint(const QPointF& point)
{
    *toEditPoint = point;
}
