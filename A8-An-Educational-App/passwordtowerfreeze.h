#ifndef PASSWORDTOWERFREEZE_H
#define PASSWORDTOWERFREEZE_H

#include <QObject>
#include "passwordtower.h"
#include "attacker.h"
/**
 * @brief PasswordTowerFreeze::PasswordTowerFreeze
 * Inherit from PasswordTower class
 * Create a freeze tower that is able to stop attacker moving for short period of time
 */
class PasswordTowerFreeze : public PasswordTower {
public:
    explicit PasswordTowerFreeze(b2World* world, QString password, int passwordStrength, int x, int y, QObject *parent = nullptr);
    static const int cost = 150;
};

#endif // PASSWORDTOWERFREEZE_H
