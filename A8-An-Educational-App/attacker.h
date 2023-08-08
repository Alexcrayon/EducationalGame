#ifndef ATTACKER_H
#define ATTACKER_H

#include <QObject>
#include <QImage>
#include <Box2D/Box2D.h>
#include <path.h>
#include <QPoint>
#include <QTimer>

/**
 * @brief Attacker::Attacker
 * Parent class, create a attacker object that moving along a preloaded path
 */
class Attacker : public QObject
{
    Q_OBJECT
public:
    Attacker(b2World* world ,QObject *parent = nullptr);

    QImage image;
    b2Body* attakBody;
    b2BodyDef attakBodyDef;
    bool getFrozenState();
    void freeze();
    double health;
    double speed;
    bool isDead = false;
    bool isAtEnd = false;
    QPoint location; //Current location of a given attacker

    virtual void loseHealth(double lostHealth);
    virtual int getCurrency();
    virtual int getLivesTaken();

    double nextPercentPoint;
    int enemyID = 0;
    int enemyType;
signals:
    void onFinish();
    void onDefeat(QPoint location, int enemyID);
protected:
    bool isFrozen;
private:
    Path mainPath;
    double velocity;
    double percentVel;
    double currPos = 0;
    int currencyGiven = 5;
    int livesTaken = -1;

};

#endif // ATTACKER_H
