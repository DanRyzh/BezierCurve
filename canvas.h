#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include "animator.h"
#include "beziercurve.h"

class Canvas : public QWidget
{
    Q_OBJECT

    BezierCurve* curve;
    Animator* animator;

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
    void keyPressEvent(QKeyEvent *);
signals:
    void closing();
};

#endif // CANVAS_H
