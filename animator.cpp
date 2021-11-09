#include "animator.h"

Animator::Animator(int ms, qreal _step): step(_step)
{
    frameGenerator = new QTimer;

    frameGenerator->setTimerType(Qt::PreciseTimer);
    frameGenerator->setInterval(ms);

    connect(frameGenerator,SIGNAL(timeout()),this, SLOT(drawFrame()));

    active = 0;
    paused = 0;
};

qreal Animator::getCurrentStep()
{
    return currentStep;
}

void Animator::pause()
{
    paused = 1;
    frameGenerator->stop();
}

void Animator::stop()
{
    frameGenerator->stop();
    currentStep = 0;
    active = 0;
    emit nextFrame();
}

void Animator::drawFrame()
{
    if(currentStep>=1.0) {stop(); return;}
    emit nextFrame();
    currentStep += step;
}

bool Animator::isActive()
{
    return active;
}

bool Animator::isPaused()
{
    return paused;
}

void Animator::start()
{
    if(!active)
        active = 1;
    if(paused)
        paused = 0;
    frameGenerator->start();
}

Animator::~Animator()
{
    if (frameGenerator->isActive())
        frameGenerator->stop();
    disconnect(frameGenerator,SIGNAL(timeout()),this, SLOT(drawFrame()));
    delete frameGenerator;
};


