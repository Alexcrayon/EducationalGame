#ifndef ATTACKERMELTDOWN_H
#define ATTACKERMELTDOWN_H

#include "attacker.h"
#include <Box2D/Box2D.h>
/**
 * @brief AttackerMeltdown::AttackerMeltdown
 * Meltdown attacker, inherit from Attacker class
 * enemyType 3, powerful enemy that once reach end of the path,
 * reduce player's lives to zero and end the game.
 */
class AttackerMeltdown : public Attacker
{
public:
    AttackerMeltdown(b2World* world, QObject *parent = nullptr);
    void loseHealth(double lostHealth);
    int getCurrency();
    int getLivesTaken();
private:
    int currencyGiven = 20;
    int livesTaken = -2;
};

#endif // ATTACKERMELTDOWN_H
