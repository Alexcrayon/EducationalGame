#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>
#include <QPoint>
#include <QImage>
#include <Box2D/Box2D.h>
#include <map>
#include <ctime>
#include <vector>
#include "path.h"
#include "attacker.h"
#include "attackerkeylogger.h"
#include "attackermalware.h"
#include "attackermeltdown.h"
#include "passwordtower.h"
#include "towerplace.h"
#include "globals.h"
#include "bullet.h"

using std::vector;
using std::map;
using std::string;
/**
 * @brief Game::Game
 * A game object that stores all the required data and logic for the game
 *
 */
class Game : public QObject {
    Q_OBJECT
public:
    Game(QObject *parent = nullptr);
    map<int, vector<QString>*> passwords {
        {0, new vector<QString>()},
        {1, new vector<QString>()},
        {2, new vector<QString>()},
        {3, new vector<QString>()},
    };
    b2World* world;
    map<int, Attacker*> listOfAttackers;
    map<int, PasswordTower*> listOfTowers;
    map<int, Upgrade> upgrades;
    map<int, Upgrade> availableUpgrades;
    TowerPlace* towerOnCursor;
    QString masterPasswordPlainText;
    QString masterPassword;
    QString masterPasswordUpgrades;
    int masterPasswordStrength;
    int round;
    int points;
    Path* path;
    int healthPoint;
    int attackerSpawningRate;
    bool towerHeld;
    bool isActiveRound = false;
    bool allAttackersSpawned = false;
    bool isGameOver = false;
    int dynamicIDAttacker;
    int roundIndex;
    int dynamicIDTower;
    time_t seed;
    void createAttackersByRound();
    vector<Bullet*> listOfBullets;
    Attacker *acquireTargetAttacker(map<int, Attacker *> inRangeTarget);

signals:
    void towerPlaced();
    void updateCurrency(int newCurrency);
    void upgradedMasterPassword();
    void sendNewHealth(int newHealth);
    void updateGamePoints();

public slots:
    void startRound();
    void updatePoints(int pointIncrement);
    void updateHealth(int healthIncrement);
    void spawnTowerFollow(int towerType);
    void upgradePassword(Upgrade upgrade);
    void confirmUpgrade(Upgrade upgrade);
    void updatePoints();

private:

};

#endif // GAME_H
