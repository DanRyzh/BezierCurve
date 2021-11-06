#include "beziercurve.h"

#include <QDebug>

BezierCurve::BezierCurve()
{
    toEditPoint = end();
}

void BezierCurve::add(const QPointF& point)
{
    points.push_back(point);
}

void BezierCurve::deleteLast()
{
    if(!points.isEmpty()) points.pop_back();
}

//Moving given point to the end, then deleting it
void BezierCurve::deletePoint(QVector<QPointF>::iterator& pIt)
{
    for(;pIt!= points.end() - 1; pIt++) std::iter_swap(pIt, pIt+1);
    points.pop_back();
}

void BezierCurve::editPoint(const QPointF& point)
{
    *toEditPoint = point;
}

/*Calculating if given point lies between p1 and p1+1 (lies on line(p1, p1+1))
  todo:
  change the implementation of calc,
  some bugs occuring*/
bool BezierCurve::checkClickToLine(const QPointF& point, QVector<QPointF>::iterator p1)
{
    QVector<QPointF>::iterator p2 = p1 + 1;
    qreal expr1 = (point.x() - p1->x())/(p2->x() - p1->x());
    qreal expr2 = (point.y() - p1->y())/(p2->y() - p1->y());
    return (abs(expr1 - expr2) <= 0.05);
}

//Checking if point lies on some curves's line (at least 1 line required)
//if point lies, includes point and returns its iterator
/*todo:
  change the implementation, some disaster with iterators*/
QVector<QPointF>::iterator BezierCurve::checkClickToLines(const QPointF& point)
{
    if(points.size()<2) return end();

    for(auto pIt = points.begin(); pIt!=points.end() - 1; pIt++)
    {
        if(checkClickToLine(point, pIt))
        {
            points.insert(++pIt, point);
            return pIt;
        }
    }

    return end();
}

/*Checking if point lies on some point in curve (at least 1 line required)
  if point matches returns its iterator
  +-6 means the ability to get to the point by clicking*/
QVector<QPointF>::iterator BezierCurve::checkClickToPoints(const QPointF& point)
{
    auto p = points.begin();

    for(;p!=points.end(); p++)
    {
        if(point.x() + 6 > p->x() && point.x()-6 < p->x()
                && point.y()+6 > p->y() && point.y()-6 < p->y())
            break;

    }

    return p;
}

void BezierCurve::drawDots(QPainter& painter, QColor color)
{
    painter.setPen(QPen(color));
    painter.setBrush(QBrush(color));

    for(int i = 0; i<points.size(); i++)
    {
        painter.drawEllipse(points[i], 3, 3);
        painter.drawText(points[i].x(), points[i].y() - 5, "P" + QString::number(i+1));
    }
}

void BezierCurve::drawLines(QPainter& painter, QColor color, QVector<QPointF>& points)
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

//drawLines overload for accessing from canvas
void BezierCurve::drawLines(QPainter& painter, QColor color)
{
    drawLines(painter, color, points);
}

//Calculating supporting curve's dot with given step, saving it in array
void BezierCurve::calcBezierDots(QVector<QPointF>& savedPoints, QVector<QPointF> copiedPoints, qreal step)
{
    if (copiedPoints.size() == 1)
    {
       savedPoints.push_back(copiedPoints[0]);
       return;
    }

    for (int i = 0; i < copiedPoints.size() - 1; i++)
    {
        copiedPoints[i] = moveFromTo(copiedPoints[i], copiedPoints[i + 1], step);
    }

    copiedPoints.pop_back();
    calcBezierDots(savedPoints, std::move(copiedPoints), step);
}

void BezierCurve::drawBezierCurve(QPainter& painter, QColor color, qreal step)
{
    if(points.size()<3) return;

    QVector<QPointF> savedPoints;

    for (qreal i = 0; i <= 1.0; i += step)
    {
        calcBezierDots(savedPoints, points, i);
    }

    drawLines(painter, color, savedPoints);
}

//Calculating line's point with step
QPointF BezierCurve::moveFromTo(QPointF p1, QPointF p2, qreal step)
{
    return {moveFromTo(p1.x(), p2.x(), step), moveFromTo(p1.y(), p2.y(), step)};
}

//moveFromTo overload for coordinates separately
qreal BezierCurve::moveFromTo(qreal p1, qreal p2, qreal step)
{
    if(p1<p2)
        return (p2 - p1) * step + fmin(p1, p2);
    else
        return (p2 - p1) * step + fmax(p1, p2);
}

bool BezierCurve::empty()
{
    return points.isEmpty();
}

void BezierCurve::setOnEditPoint(const QVector<QPointF>::iterator& pIt)
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

BezierCurve::~BezierCurve(){}
