#ifndef PASSWORDTOWERREFLECTING_H
#define PASSWORDTOWERREFLECTING_H

#include "passwordtower.h"
#include <QObject>
/**
 * @brief PasswordTowerFreeze::PasswordTowerFreeze
 * Inherited from PasswordTower
 * A tower can shoot bouncing bullet, that bounce on first collision and continue to damage next few collided attackers, until it is off screen.
 */
class PasswordTowerReflecting : public PasswordTower {
public:
    explicit PasswordTowerReflecting(b2World* world, QString password, int passwordStrength, int x, int y, QObject *parent = nullptr);
    static const int cost = 100;

};

#endif // PASSWORDTOWERREFLECTING_H
