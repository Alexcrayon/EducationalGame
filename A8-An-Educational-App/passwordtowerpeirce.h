#ifndef PASSWORDTOWERPEIRCE_H
#define PASSWORDTOWERPEIRCE_H

#include "passwordtower.h"
#include <QObject>

/**
 * @brief PasswordTowerFreeze::PasswordTowerFreeze
 * Inherited from PasswordTower
 * a basic tower that shoot bullet at attacker while they are in range
 */
class PasswordTowerPeirce : public PasswordTower {
public:
    explicit PasswordTowerPeirce(b2World* world, QString password, int passwordStrength, int x, int y, QObject *parent = nullptr);
    static const int cost = 50;
};

#endif // PASSWORDTOWERPEIRCE_H
