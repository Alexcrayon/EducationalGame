/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include "attackerkeylogger.h"
/**
 * @brief AttackerKeyLogger::AttackerKeyLogger
 * Keylogger attacker, inherit from Attacker class
 * enemyType 1, it is able to disable a tower on its death
 * disabled tower need to be repaired by clicking on it to be reactivated.
 * @param world
 * @param parent
 */
AttackerKeyLogger::AttackerKeyLogger(b2World* world, QObject *parent) : Attacker{world,parent}
{
    QImage sprite (":/sprites/GameImages/Attacker_Keylogger.png");
    image = sprite;
    enemyType = 1;
    health = 7;
    isFrozen = false;
}

void AttackerKeyLogger::loseHealth(double lostHealth) {
    health = health - lostHealth;
    if (health <= 0)
        isDead = true;
        emit onDefeat(location, enemyID);
}

int AttackerKeyLogger::getCurrency() {
    return currencyGiven;
}

int AttackerKeyLogger::getLivesTaken() {
    return livesTaken;
}
