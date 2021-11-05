#include "beziercurve.h"

#include <QDebug>

BezierCurve::BezierCurve(){}

void BezierCurve::add(const QPointF& point)
{
    points.push_back(point);
}

void BezierCurve::deleteLast()
{
    if(!points.isEmpty()) points.pop_back();
}

void BezierCurve::deletePoint(int pointPtr)
{
    for(int i = pointPtr; i<points.size() - 1; i++)
    {
        points[i].setX(points[i+1].x());
        points[i].setY(points[i+1].y());
    }

    points.pop_back();
}

void BezierCurve::editPoint(const QPointF& point)
{

    points[expectToEdit] = point;
}

int BezierCurve::checkPointClick(const QPointF& point)
{
    for(int i = 0; i<points.size(); i++)
    {
        if(point.x()+6 > points[i].x() && point.x()-6 < points[i].x()
                && point.y()+6 > points[i].y() && point.y()-6 < points[i].y())
        {
            return i;
        }
    }

    return -1;
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

void BezierCurve::drawLines(QPainter& painter, QColor color)
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


void BezierCurve::calcBezierDot(QVector<QPointF>& savedPoints, QVector<QPointF> copiedPoints, qreal step)
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
    calcBezierDot(savedPoints, std::move(copiedPoints), step);
}

void BezierCurve::drawBezierCurve(QPainter& painter, QColor color, qreal step)
{
    if(points.size()<3) return;

    QVector<QPointF> savedPoints;

    for (qreal i = 0; i <= 1.0; i += step)
    {
        calcBezierDot(savedPoints, points, i);
    }

    drawLines(painter, color, savedPoints);
}

QPointF BezierCurve::moveFromTo(QPointF p1, QPointF p2, qreal step)
{
    return {moveFromTo(p1.x(), p2.x(), step), moveFromTo(p1.y(), p2.y(), step)};
}


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

void BezierCurve::setOnEditPoint(int numb)
{
    expectToEdit = numb;
}

bool BezierCurve::editPointIsEmpty()
{
    return expectToEdit==-1;
}

BezierCurve::~BezierCurve(){}
