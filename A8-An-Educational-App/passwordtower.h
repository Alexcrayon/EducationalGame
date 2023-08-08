#ifndef PASSWORDTOWER_H
#define PASSWORDTOWER_H

#include <QObject>
#include <QPoint>
#include <cmath>
#include <QTimer>
#include <map>
#include "globals.h"
#include "attacker.h"

using std::map;
using std::vector;

/**
 * @brief PasswordTower::PasswordTower
 * A parent tower class that create a tower object with a password
 * Store the type of tower, the current target that it is looking at, upgrades
 * all attackers within its shooting range
 *
 */
class PasswordTower : public QObject {
    Q_OBJECT

public:
    static const int cost = 50;
    explicit PasswordTower(b2World* world, QString password, int passwordStrength, int x, int y, QObject *parent = nullptr);
    QImage sprite;
    QImage disabledSprite;
    double shootingDamage;
    double shootingRange;
    double rateOfFire;
    QString basePassword;
    QString password;
    QString passwordUpgrades;
    map<int, Upgrade> upgrades;
    map<int, Upgrade> availableUpgrades;
    QTimer* timer;
    bool enabled;
    double strength;
    b2World* world;
    QPoint getPosition();
    Attacker* currentTarget;
    int getID();
    void upgradePassword(Upgrade upgrade);
    void confirmUpgrade(Upgrade upgrade);
    int seed;
    map<int, Attacker*> inRangeTarget;
    void findAttackersInRange(map<int,Attacker*>);
    bool isActive;
    QPoint position;
    int passwordStrength;

signals:
    void sendNewHealth(int);

protected:
    int towerType;
};

#endif // PASSWORDTOWER_H
