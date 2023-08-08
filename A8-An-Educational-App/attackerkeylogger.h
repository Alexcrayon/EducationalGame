#ifndef ATTACKERKEYLOGGER_H
#define ATTACKERKEYLOGGER_H

#include "attacker.h"
#include <Box2D/Box2D.h>

/**
 * @brief AttackerKeyLogger::AttackerKeyLogger
 * Keylogger attacker, inherit from Attacker class
 * enemyType 1, it is able to disable a tower on its death
 * disabled tower need to be repaired by clicking on it to be reactivated.
 */
class AttackerKeyLogger : public Attacker
{
public:
    AttackerKeyLogger(b2World* world, QObject *parent = nullptr);
    void loseHealth(double lostHealth);
    int getCurrency();
    int getLivesTaken();
private:
    int currencyGiven = 10;
    int livesTaken = -1;
};

#endif // ATTACKERKEYLOGGER_H
