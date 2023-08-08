/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include "passwordtowerfreeze.h"

/**
 * @brief PasswordTowerFreeze::PasswordTowerFreeze
 * Inherit from PasswordTower class
 * Create a freeze tower that is able to stop attacker moving for short period of time
 * @param world
 * @param password
 * @param passwordStrength
 * @param x
 * @param y
 * @param parent
 */
PasswordTowerFreeze::PasswordTowerFreeze(b2World* world, QString password, int passwordStrength, int x, int y, QObject *parent): PasswordTower{world, password, passwordStrength, x, y, parent}{

    enabled = true;
    towerType = 3;

    if (passwordStrength == 3) {
        strength = 4;
        shootingDamage = 20;
        shootingRange = 125;
        rateOfFire = 1;
    } else if (passwordStrength == 2) {
        strength = 3;
        shootingDamage = 15;
        shootingRange = 100;
        rateOfFire = 2;
    } else if (passwordStrength == 1) {
        strength = 2;
        shootingDamage = 10;
        shootingRange = 75;
        rateOfFire = 3;
    } else {
        strength = 1;
        shootingDamage = 5;
        shootingRange = 50;
        rateOfFire = 4;
    }

    sprite = QImage(":/sprites/GameImages/Tower_Freeze.png");
    disabledSprite = QImage(":/sprites/GameImages/Tower_Freeze_Disabled.png");
}


