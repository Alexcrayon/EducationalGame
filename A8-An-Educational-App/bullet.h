#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <QImage>
#include <QtMath>
#include <QDebug>
#include <QRandomGenerator>
/**
 * @brief Bullet::Bullet
 * A bullet class that creates a bullet and its physics inside a b2World
 */
class Bullet : public QObject
{
    Q_OBJECT
public:
    Bullet(int type, b2World* world , b2Vec2 targetPos ,QObject *parent = nullptr);
    int bulletType = 0;
    QImage image;
    b2Body* bulletBody;
    b2BodyDef bulletBodyDef;

    bool activated;
    b2Vec2 target;
    b2Vec2 targetDirection;
    void acquireTargetDirction();

    bool isBouncing;
    int bounceDir;
public slots:
    void move();
    void destroyed();
    void bounce();
signals:

};

#endif // BULLET_H
