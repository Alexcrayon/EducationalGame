/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */

#include "attacker.h"
/**
 * @brief Attacker::Attacker
 * Parent class, create a attacker object that moving along a preloaded path
 * @param world b2World
 * @param parent
 */
Attacker::Attacker(b2World* world , QObject *parent) : QObject{parent} {
    QImage sprite (":/sprites/GameImages/Attacker_Base.png");

    isFrozen = false;
    image = sprite;
    QPoint point = mainPath.getPosition(0);
    nextPercentPoint = 0;

    //setup box2D body and fixture
    attakBodyDef.type = b2_dynamicBody;
    attakBodyDef.position.Set((int)point.x(),(int) point.y());
    attakBody = world->CreateBody(&attakBodyDef);
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(9.0f,9.0f);
    attakBody->CreateFixture(&polygonShape, 1);
    attakBody->SetUserData(this);

    enemyType = 0;
    health = 5;
}

/**
 * @brief Attacker::loseHealth
 * attacker loses health by input amount,
 * it is considered dead when health <= 0
 * @param lostHealth
 */
void Attacker::loseHealth(double lostHealth) {
    health = health - lostHealth;
    if (health <= 0)
        isDead = true;
        emit onDefeat(location, enemyID);
}

/**
 * @brief Attacker::getCurrency
 * Return the currency it suppose to give on death
 * @return
 */
int Attacker::getCurrency() {
    return currencyGiven;
}

/**
 * @brief Attacker::getLivesTaken
 * Return the damage will cost to player's lives when it reach the end of the path
 * @return
 */
int Attacker::getLivesTaken() {
    return livesTaken;
}
/**
 * @brief Attacker::getFrozenState
 * @return whether attacker is frozen by freeze tower
 */
bool Attacker::getFrozenState()
{
    return isFrozen;
}

/**
 * @brief Attacker::freeze
 * Freeze the attacker
 */
void Attacker::freeze()
{
    isFrozen = true;
    QTimer::singleShot(4000, [this](){isFrozen = false;});
}
