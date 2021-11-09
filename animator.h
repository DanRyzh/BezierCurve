#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include "beziercurve.h"

class Animator : public QWidget
{
    Q_OBJECT

    qreal step = 0;
    qreal currentStep = 0;
    QPainter* painter;
    QTimer* frameGenerator;
    bool active;
    bool paused;

public:
    Animator(int = 25, qreal = 0.01);
    ~Animator();

    bool isActive();
    bool isPaused();
    void start();
    void stop();
    void pause();
    void continueAnim();
    qreal getCurrentStep();

protected slots:
    void drawFrame();
signals:
    void nextFrame();
};

#endif // ANIMATOR_H