#include "beziercurve.h"

//defined using RGB
static QColor colors[7] = {
    {148, 0, 211}, //Violet
    {75, 50, 130}, //Indigo
    {0, 0, 255},   //Blue
    {0, 255, 0},   //Green
    {255, 255, 0}, //Yellow
    {255, 127, 0}, //Orange
    {255, 0 , 0}   //Red
};

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

void BezierCurve::deletePoint(QVector<QPointF>::iterator& pIt)
{
    points.erase(pIt);
}

void BezierCurve::editPoint(const QPointF& point)
{
    *toEditPoint = point;
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

void BezierCurve::drawLines(QPainter& painter, QColor color, const QVector<QPointF> &points)
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

void BezierCurve::drawStep(QPainter& painter, qreal step, const QPointF& pos)
{
    if(points.size() < 3) return;

    int textSize = 20;

    QString text = "t=" + QString::number(step);

    QFont font("Arial", textSize, QFont::DemiBold);

    QFontMetrics metrics(font);
    int textWidth = metrics.width(text);

    painter.setPen(QColor(Qt::white));
    painter.setFont(font);

    painter.translate(pos);

    painter.drawText(-textWidth/2, -textSize, text);
}

//drawLines overload for accessing from canvas
void BezierCurve::drawLines(QPainter& painter, QColor color)
{
    drawLines(painter, color, points);
}

//Calculating supporting curve's dot with given step, saving it in array
void BezierCurve::calcBezierDot(QVector<QPointF>& bezierCurve, QVector<QPointF> curve, qreal step)
{
    if (curve.size() == 1)
    {
       bezierCurve.push_back(curve[0]);
       return;
    }

    for (int i = 0; i < curve.size() - 1; i++)
    {
        curve[i] = moveFromTo(curve[i], curve[i + 1], step);
    }

    curve.pop_back();
    calcBezierDot(bezierCurve, std::move(curve), step);
}

void BezierCurve::drawBezierCurve(QPainter& painter, QColor color, qreal step)
{
    if(points.size()<3) return;

    QVector<QPointF> curveCopied;
    curveCopied.reserve(static_cast<int>(1/step + 1));

    for (qreal i = 0; i <= 1.0; i += step)
    {
        calcBezierDot(curveCopied, points, i);
    }

    drawLines(painter, color, curveCopied);
}

//Calculating line's point with step
QPointF BezierCurve::moveFromTo(const QPointF &p1, const QPointF &p2, qreal step)
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

void BezierCurve::drawSupportLines(QPainter& painter, QVector<QPointF> curve, qreal step)
{
    if (curve.size() == 1)
    {
       painter.drawEllipse(curve[0], 5, 5);
       return;
    }

    for (int i = 0; i < curve.size() - 1; i++)
    {
        curve[i] = moveFromTo(curve[i], curve[i + 1], step);
    }

    curve.pop_back();
    drawLines(painter, colors[curve.size()%7], curve);
    drawSupportLines(painter, std::move(curve), step);
}

void BezierCurve::drawSupportLines(QPainter& painter,qreal step)
{
    if(points.size() < 3) return;

    drawSupportLines(painter, points, step);
}

BezierCurve::~BezierCurve(){}
