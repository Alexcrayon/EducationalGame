/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>
#include <QCryptographicHash>
#include "passwordtower.h"
#include "globals.h"

using std::map;
using std::vector;
using std::erase;
using std::count;
using std::time;
using std::shuffle;
using std::default_random_engine;
/**
 * @brief PasswordTower::PasswordTower
 * A parent tower class that create a tower object with a password
 * Store the type of tower, the current target that it is looking at, upgrades
 * all attackers within its shooting range
 *
 * @param world
 * @param password The set password on placing this tower
 * @param passwordStrength Strength decided by the set password
 * @param x X position of the tower on screen
 * @param y Y position of the tower on screen
 * @param parent
 */
PasswordTower::PasswordTower(b2World* world, QString password, int passwordStrength, int x, int y, QObject *parent)
    : QObject{parent} {
    this->world = world;
    this->basePassword = password;
    this->password = password;
    this->passwordStrength = passwordStrength;
    this->passwordUpgrades = "password";
    position.setX(x);
    position.setY(y);
    currentTarget = nullptr;
    seed = time(0);
    availableUpgrades = {
        {0, length}, {1, symbols}, {2, numbers}, {3, randomize},
        {4, sha1}, {5, md5}, {6, md5TripleHash}, {7, sha1TripleHash},
        {8, basicSalt}, {9, basicPepper}, {10, bcryptHash}, {11, argon2idHash},
    };
    isActive = true;
}

QPoint PasswordTower::getPosition(){
    return position;
}

int PasswordTower::getID() {
    return towerType;
}

/**
 * @brief PasswordTower::upgradePassword
 * Upgrade tower's password by the selected upgrade
 * @param upgrade
 */
void PasswordTower::upgradePassword(Upgrade upgrade) {
    passwordUpgrades = "password";
    password = basePassword;
    if (upgrade.id == 0 || upgrades.count(0)) { // length
        passwordUpgrades.append("|len");
        password.append("nfVi");
    }
    if (upgrade.id == 1 || upgrades.count(1)) { // symbols
        passwordUpgrades.append("|syms");
        password.append("$!&?&");
    }
    if (upgrade.id == 2 || upgrades.count(2)) { // numbers
        passwordUpgrades.append("|nums");
        password.append("63254");
    }
    if (upgrade.id == 3 || upgrades.count(3)) { // random
        passwordUpgrades.append("|rand");
        string temp = password.toStdString();
        shuffle(temp.begin(), temp.end(), default_random_engine(seed));
        password = QString::fromStdString(temp);
    }
    if (upgrade.id == 4 || upgrades.count(4)) { // sha-1
        passwordUpgrades.prepend("sha1(").append(")");
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha1).toHex()));
    }
    if (upgrade.id == 5 || upgrades.count(5)) { // md5
        passwordUpgrades.prepend("md5(").append(")");
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Md5).toHex()));
    }
    if (upgrade.id == 6 || upgrades.count(6)) { // triplemd5
        passwordUpgrades.prepend("md5(md5(md5(").append(")))");
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Md5).toHex()));
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Md5).toHex()));
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Md5).toHex()));
    }
    if (upgrade.id == 7 || upgrades.count(7)) { // triple sha1
        passwordUpgrades.prepend("sha1(sha1(sha1(").append(")))");
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha1).toHex()));
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha1).toHex()));
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha1).toHex()));
    }
    if (upgrade.id == 8 || upgrades.count(8)) { // salt
        QStringList list = passwordUpgrades.split("password");
        passwordUpgrades = list[0] + "saltValue+password" + list[1];
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha1).toHex()));
    }
    if (upgrade.id == 9 || upgrades.count(9)) { // pepper
        QStringList list = passwordUpgrades.split("password");
        passwordUpgrades = list[0] + "pepperValue+password" + list[1];
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha1).toHex()));
    }
    if (upgrade.id == 10 || upgrades.count(10)) { // bcrypt
        passwordUpgrades.prepend("bcrypt(").append(")");
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Blake2b_256).toHex()));
    }
    if (upgrade.id == 11 || upgrades.count(11)) { // argonid
        passwordUpgrades.prepend("argonid2(").append(")");
        password = QString("%1").arg(QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Blake2b_384).toHex()));
    }
}

/**
 * @brief PasswordTower::confirmUpgrade
 * Apply the upgrade by increasing tower's damage and range
 * @param upgrade type of upgrade
 */
void PasswordTower::confirmUpgrade(Upgrade upgrade) {
    // remove from available, add to upgrades
    upgrades[upgrade.id] = upgrade;
    availableUpgrades.erase(upgrade.id);
    shootingDamage += upgrade.damageIncrease;
    shootingRange += upgrade.rangeIncrease;
}

/**
 * @brief PasswordTower::findAttackersInRange
 * Search all the attackers within the current tower shooting range
 * store they to inRangeTarget map, once one leaves the range, remove it from the map
 * @param attackersMap
 */
void PasswordTower::findAttackersInRange(map<int, Attacker*> attackersMap){
    foreach (auto attacker, attackersMap) {
        float distance = (b2Vec2(getPosition().x(),getPosition().y()) - attacker.second->attakBody->GetPosition()).Length();
        //remove from the target map if attacker is dead
        if(attacker.second->isDead){
            inRangeTarget.erase(attacker.first);
            continue;
        }
        //in-range
        if (distance < shootingRange)
            inRangeTarget[attacker.first] = attacker.second;
        else //out-of-range
            if(inRangeTarget.contains(attacker.first))
                inRangeTarget.erase(attacker.first);
    }
}
