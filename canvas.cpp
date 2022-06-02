#include "canvas.h"

Canvas::Canvas(QWidget* parent) : QWidget(parent), curve(new BezierCurve), animator(new Animator)
{
    setWindowTitle("Bezier curves");
    setStyleSheet("background-color: black");
    setFixedSize(1200, 600);

    connect(animator.data(), &Animator::nextFrame, this, static_cast<void (QWidget::*)()>(&QWidget::update));
}

//Displaying user info
void Canvas::showInfo(QPainter& painter)
{    
    QString info[4] = {
        "Bezier curves",
        "LMB - new point/edit point by dragging",
        "RMB - delete selected/last point",
        "Key A - algorithm animation/pause"
    };

    int textSize = 20;
    int textOffset = textSize + 15;

    QFont font("Arial", textSize, QFont::DemiBold);
    QFontMetrics metrics(font);

    painter.setPen(QColor(Qt::white));
    painter.setFont(font);

    painter.translate(QPoint(width()/2, height()/2 - (2*textOffset)));

    for(int i = 0; i < 4; i++)
    {
        int textWidth = metrics.width(info[i]);
        painter.drawText(-textWidth/2, i*textOffset, info[i]);
    }
}

void Canvas::closeEvent(QCloseEvent* event)
{
    emit closing();
    event->accept();
}

/*Drawing points/dots/curve if it exist
  else displaying user info*/
void Canvas::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter;
    painter.begin(this);

    if(curve->empty())
        showInfo(painter);
    else
    {
        curve->drawCurve(painter, Qt::red, Qt::white);
        curve->drawBezierCurve(painter, Qt::blue, 0.0025);
        if(animator->isActive())
            curve->animateAlgorithm(painter, animator->getCurrentStep(), QPoint(width()/2, height()));
    }
    painter.end();
}

/*Checking if some points/lines were edited
  else adding new point*/
void Canvas::mousePressEvent(QMouseEvent* event)
{
    auto pointIt = curve->checkClickToPoints(event->pos());

    if (event->button() == Qt::LeftButton)
    {
        if(pointIt == curve -> end())
        {
            pointIt = curve->checkClickToLines(event->pos());
            if(pointIt == curve -> end())
            {
                curve->add(event->pos());
                pointIt = curve->end() - 1;
            }
        }

        if(pointIt != curve -> end())
        {
            setCursor(QCursor(Qt::ClosedHandCursor));
            curve->setEditPoint(pointIt);
        }
    }

    if (event->button() == Qt::RightButton)
    {
        if(pointIt == curve -> end())
            curve->deleteLast();
        else
            curve->deletePoint(pointIt);
    }
    update();
}

//Changing point if it was dragged
void Canvas::mouseMoveEvent(QMouseEvent* event)
{
    if(!curve->editPointIsEmpty())
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        curve->editPoint(event->pos());
        update();
    }
}

//Releasing dragged point, changing cursor
void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event)

    setCursor(QCursor(Qt::ArrowCursor));
    curve->setEditPoint(curve -> end());
}
void Canvas::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_A)
    {
        if(!animator->isActive() || animator->isPaused())
            animator->start();
        else animator->pause();
    }
}

Canvas::~Canvas()
{
    if(animator->isActive())
        animator->stop();
    disconnect(animator.data(), &Animator::nextFrame, this, static_cast<void (QWidget::*)()>(&QWidget::update));
}
