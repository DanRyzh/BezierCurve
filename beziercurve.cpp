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


void BezierCurve::drawDots(QPainter& painter, QColor color)
{
    if(empty()) return;

    painter.setPen(QPen(color));
    painter.setBrush(QBrush(color));

    for(int i = 0; i<points.size(); i++)
    {
        painter.drawEllipse(points[i], 2, 2);
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


void BezierCurve::drawBezierDot(QVector<QPointF>& savedPoints, QVector<QPointF> copiedPoints, qreal step)
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
    drawBezierDot(savedPoints, std::move(copiedPoints), step);
}

void BezierCurve::drawBezierCurve(QPainter& painter, QColor color, qreal step)
{
    if(points.size()<3) return;

    QVector<QPointF> savedPoints;

    for (qreal i = 0; i <= 1.0; i += step)
    {
        drawBezierDot(savedPoints, points, i);
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

BezierCurve::~BezierCurve(){}
