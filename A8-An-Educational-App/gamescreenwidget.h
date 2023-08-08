#ifndef GAMESCREENWIDGET_H
#define GAMESCREENWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QImage>
#include <Box2D/Box2D.h>
#include "game.h"
#include "contactlistener.h"
#include <random>

/**
 * @brief GameScreenWidget::GameScreenWidget
 * The main game view for drawing object and simulating box2D physics
 * communicate with game class
 */
class GameScreenWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameScreenWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    Game* game;

public slots:
    void updateWorld();
    void createGameWorld();
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
    void goToNextPercentagePoint();
    void spawnNewAttacker();
    void upgradeMasterPassword();
    void shoot(int sourceTower);

private:
    QTimer timer;
    QTimer attackerMovementTimer;
    QTimer attackerSpawnTimer;
    QImage stageBackground;
    QRectF backBounds;
    b2World* gameWorld;
    bool roundStarted;
    double pathPercentIncrement;
    ContactListener* listener;
    enum towerCategory{nonePresent, standard, bounce, freeze};
    enum attackerCategory{basic, keylog, malware, meltdown};
    map<QTimer*,int> listOfTimer;

signals:
    void startGame();
    void placeDownTower();
    void roundEnd();
};

#endif // GAMESCREENWIDGET_H
