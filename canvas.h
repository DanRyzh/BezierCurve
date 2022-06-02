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

    QScopedPointer<BezierCurve> curve;
    QScopedPointer<Animator> animator;

public:
    Canvas(QWidget* parent = 0);
    ~Canvas();
private:
    void showInfo(QPainter&);
protected:
    void paintEvent(QPaintEvent*) override;
    void closeEvent(QCloseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
signals:
    void closing();
};

#endif // CANVAS_H
