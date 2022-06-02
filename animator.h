#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QWidget>
#include <QTimer>
#include <QPointer>

class Animator : public QWidget
{
    Q_OBJECT

    qreal step = 0;
    qreal currentStep = 0;
    QScopedPointer<QTimer> frameGenerator;
    bool active = false;
    bool paused = false;

public:
    Animator(int = 25, qreal = 0.01);
    ~Animator();

    bool isActive();
    bool isPaused();
    void start();
    void stop();
    void pause();
    qreal getCurrentStep();

protected slots:
    void drawFrame();
signals:
    void nextFrame();
};

#endif // ANIMATOR_H
