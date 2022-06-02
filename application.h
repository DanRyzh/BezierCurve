#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "canvas.h"

class Application : public QApplication
{
    Q_OBJECT

    QScopedPointer<Canvas> canvas;

public:
    Application(int, char**);
};

#endif
