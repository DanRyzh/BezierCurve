#include "decasteljau.h"

//Calculating supporting bezier dot with given step using de casteljau algo, saving it in array
void calcBezierDot(QVector<QPointF>& bezierCurve, QVector<QPointF> curve, qreal step)
{
    if (curve.size() == 1)
    {
       bezierCurve.push_back(curve[0]);
       return;
    }

    for (int i = 0; i < curve.size() - 1; i++)
        curve[i] = moveFromTo(curve[i], curve[i + 1], step);

    curve.pop_back();
    calcBezierDot(bezierCurve, std::move(curve), step);
}

//Calculating line's point with step
QPointF moveFromTo(const QPointF &p1, const QPointF &p2, qreal step)
{
    return {moveFromTo(p1.x(), p2.x(), step), moveFromTo(p1.y(), p2.y(), step)};
}

//moveFromTo overload for coordinates separately
qreal moveFromTo(qreal p1, qreal p2, qreal step)
{
    if(p1<p2)
        return (p2 - p1) * step + fmin(p1, p2);
    else
        return (p2 - p1) * step + fmax(p1, p2);
}

//Displaying supporting lines and dot using de casteljau algo
void drawBearingLines(QPainter& painter, QVector<QPointF> curve, qreal step)
{
    if (curve.size() == 1)
    {
       painter.drawEllipse(curve[0], 5, 5);
       return;
    }

    for (int i = 0; i < curve.size() - 1; i++)
        curve[i] = moveFromTo(curve[i], curve[i + 1], step);

    curve.pop_back();
    drawLines(painter, colors[curve.size()%7], curve);
    drawBearingLines(painter, std::move(curve), step);
}

//Displaying the current step of algo
void drawStep(QPainter& painter, qreal step, const QPointF& pos)
{

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

