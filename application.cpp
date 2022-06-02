#include "application.h"

Application::Application(int argc, char** argv) : QApplication(argc,argv), canvas(new Canvas)
{
    canvas->show();
}
