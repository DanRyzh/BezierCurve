#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QCloseEvent>
#include <QMouseEvent>
#include "beziercurve.h"

class Canvas : public QWidget
{
    Q_OBJECT

    BezierCurve* curve;

public:
    Canvas(QWidget* parent = 0);
    ~Canvas();
private:
    void showInfo(QPainter&);
protected:
   void paintEvent(QPaintEvent*);
    void closeEvent(QCloseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
signals:
    void closing();
};

#endif // CANVAS_H
