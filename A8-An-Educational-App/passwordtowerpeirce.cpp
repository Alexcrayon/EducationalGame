/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include "passwordtowerpeirce.h"
/**
 * @brief PasswordTowerFreeze::PasswordTowerFreeze
 * Inherited from PasswordTower
 * a basic tower that shoot bullet at attacker while they are in range
 * @param world
 * @param password
 * @param passwordStrength
 * @param x
 * @param y
 * @param parent
 */
PasswordTowerPeirce::PasswordTowerPeirce(b2World* world, QString password, int passwordStrength, int x, int y, QObject *parent): PasswordTower{world, password, passwordStrength, x, y, parent} {

    towerType = 1;

    if (passwordStrength == 3) {
        strength = 4;
        shootingDamage = 20;
        shootingRange = 175;
    } else if (passwordStrength == 2) {
        strength = 3;
        shootingDamage = 15;
        shootingRange = 125;
    }
    else if (passwordStrength == 1) {
        strength = 2;
        shootingDamage = 10;
        shootingRange = 100;
    } else {
        strength = 1;
        shootingDamage = 5;
        shootingRange = 75;
    }
    sprite = QImage(":/sprites/GameImages/Tower_Pierce.png");
    disabledSprite = QImage(":/sprites/GameImages/Tower_Pierce_Disabled.png");
}
