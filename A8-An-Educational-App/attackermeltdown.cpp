/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include "attackermeltdown.h"
/**
 * @brief AttackerMeltdown::AttackerMeltdown
 * Meltdown attacker, inherit from Attacker class
 * enemyType 3, powerful enemy that once reach end of the path,
 * reduce player's lives to zero and end the game.
 * @param world
 * @param parent
 */
AttackerMeltdown::AttackerMeltdown(b2World* world, QObject *parent) : Attacker{world, parent}
{
    QImage sprite (":/sprites/GameImages/Attacker_Meltdown.png");
    image = sprite;
    enemyType = 3;
    health = 20;
    livesTaken = -999999;
    isFrozen = false;
}

void AttackerMeltdown::loseHealth(double lostHealth) {
    health = health - lostHealth;
    if (health <= 0)
        isDead = true;
        emit onDefeat(location, enemyID);
}

int AttackerMeltdown::getCurrency() {
    return currencyGiven;
}

int AttackerMeltdown::getLivesTaken() {
    return livesTaken;
}
