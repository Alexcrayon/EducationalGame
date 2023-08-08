#include "gamescreenwidget.h"

GameScreenWidget::GameScreenWidget(QWidget *parent): QWidget(parent), world(b2Vec2(0.0f, 0.0f)), timer(this) {
    connect(&timer, &QTimer::timeout, this, &GameScreenWidget::updateWorld);
    timer.start(10);
}

void GameScreenWidget::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);

    //
    painter.end();

}

void GameScreenWidget::updateWorld() {

    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
}
