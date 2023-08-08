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
#include <QRandomGenerator>
#include <QCryptographicHash>
#include "game.h"
#include "globals.h"

using std::map;
using std::vector;
using std::erase;
using std::count;
using std::time;
using std::shuffle;
using std::default_random_engine;

/**
 * @brief Game::Game
 * A game object that stores all the required data and logic for the game
 *
 */
Game::Game(QObject *parent) : QObject(parent) {
    //create a box2D world with zero gravity
    world = new b2World(b2Vec2(0.0f, 0.0f));

    //create path
    Path* pathFromFile = new Path();
    this->path = pathFromFile;

    round = 0;
    //starting currency for player in round1:TBD
    points = 100;

    dynamicIDAttacker= 0;
    dynamicIDTower = 0;
    attackerSpawningRate = 2000; //every 2 secs
    towerHeld = false;
    towerOnCursor = new TowerPlace(0);

    // create subset of passwords for game
    QRandomGenerator rng(time(0));
    map<int, vector<QString>*> pwdCollection;
    for (int i = 0; i < 4; i++)
        pwdCollection[i] = new vector<QString>(PASSWORDS_COLLECTION.at(i));
    int pwdIndex;
    QString pwdValue;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4 - i; j++) {
            pwdIndex = rng.bounded((int)(pwdCollection.at(i)->size()-1));
            pwdValue = pwdCollection.at(i)->at(pwdIndex);
            erase(*pwdCollection.at(i), pwdValue);
            this->passwords.at(i)->push_back(pwdValue);
        }
    masterPasswordUpgrades = "password";
    seed = time(0);
    // init available upgrades
    availableUpgrades = {
        {0, length}, {1, symbols}, {2, numbers}, {3, randomize},
        {4, sha1}, {5, md5}, {6, md5TripleHash}, {7, sha1TripleHash},
        {8, basicSalt}, {9, basicPepper}, {10, bcryptHash}, {11, argon2idHash},
    };
}
/**
 * @brief Game::spawnTowerFollow
 * Decide which towertype is selected to be placed
 * @param towerType
 */
void Game::spawnTowerFollow(int towerType)
{
    towerHeld = true;
        towerOnCursor->setID(towerType);
}

/**
 * @brief Game::startRound public slot to start the next round of game
 * spawn the attackers to follow the path
 */
void Game::startRound(){
    round++;
    isActiveRound = true;
    allAttackersSpawned = false;
    listOfAttackers.clear();
    listOfBullets.clear();
    foreach(auto tower, listOfTowers)
        tower.second->inRangeTarget.clear();
    dynamicIDAttacker = 0;
    roundIndex = 0;
    createAttackersByRound();
}

/**
 * @brief Game::createAttackersByRound
 * Spawning waves of attackers by the number of round
 * as the round increase, different types of attackers will be spawned
 * and diffcult will also increase
 */
void Game::createAttackersByRound(){
    //Round 1: Just five basic enemies
    if(round == 1 && roundIndex < 5){
        Attacker *attacker = new Attacker(world);
        attacker->enemyID = dynamicIDAttacker;
        listOfAttackers[dynamicIDAttacker] = attacker;
        dynamicIDAttacker++;
        roundIndex++;
        if (roundIndex == 5) {
            allAttackersSpawned = true;
        }
    }
    //Round 2: 10 enemies: 5 basic and 5 keylogger
    if(round == 2 && roundIndex < 12) {
        if(roundIndex < 5) {
            Attacker *attacker = new Attacker(world);
            attacker->enemyID = dynamicIDAttacker;
            attacker->health = 10;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 7 && roundIndex >= 5)
            roundIndex++; //Delay
        if(roundIndex >= 7) {
            AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 12)
                allAttackersSpawned = true;
        }
    }
    //Round 3: 15 enemies: 5 basic, 5 keylogger, 5 malware
    if(round == 3 && roundIndex < 18) {
        if(roundIndex < 5) {
            Attacker *attacker = new Attacker(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            attacker->health = 15;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 7 && roundIndex >= 5)
            roundIndex++; //Delay
        if(roundIndex < 11 && roundIndex >= 7) {
            AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 13 && roundIndex >= 11)
            roundIndex++; //Delay
        if(roundIndex >= 13) {
            AttackerMalware *attacker = new AttackerMalware(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 18)
                allAttackersSpawned = true;
        }
    }
    //Round 4: First Boss Wave, 20 enemies: 4 basic, 8 keylogger, 7 malware, 1 meltdown
    if (round == 4 && roundIndex < 26) {
        if(roundIndex < 4) {
            Attacker *attacker = new Attacker(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            attacker->health = 20;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 6 && roundIndex >= 4)
            roundIndex++; //Delay
        if(roundIndex < 14 && roundIndex >= 6) {
            AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 16 && roundIndex >= 14)
            roundIndex++; //Delay
        if(roundIndex < 23 && roundIndex >= 16) {
            AttackerMalware *attacker = new AttackerMalware(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 25 && roundIndex >= 23)
            roundIndex++; //Delay
        if(roundIndex >= 25) {
            AttackerMeltdown *attacker = new AttackerMeltdown(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 26)
                allAttackersSpawned = true;
        }
    }
    //Round 5: First Mixed Wave, 25 enemies: 10 random, 5 ranom, 10 random
    if (round == 5 && roundIndex < 29) {
        std::random_device randomDevice; //Used to intilize engine
        std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
        std::uniform_int_distribution<int> range(0, 2);
        if (roundIndex < 10) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                attacker->health = 25;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 12 && roundIndex >= 10)
            roundIndex++; //Delay
        if (roundIndex < 17 && roundIndex >= 12) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 19 && roundIndex >= 17)
            roundIndex++; //Delay
        if (roundIndex < 29 && roundIndex >= 19) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 29) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 29) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 29) {
                    allAttackersSpawned = true;
                }
            }
        }
    }
    //Round 6: Mixed Wave, 30 enemies: 10 random, 10 random, 10 random
    if (round == 6 && roundIndex < 34) {
        std::random_device randomDevice; //Used to intilize engine
        std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
        std::uniform_int_distribution<int> range(0, 2);
        if (roundIndex < 10) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                attacker->health = 25;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 12 && roundIndex >= 10)
            roundIndex++; //Delay
        if (roundIndex < 22 && roundIndex >= 12) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 24 && roundIndex >= 22)
            roundIndex++; //Delay
        if (roundIndex < 34 && roundIndex >= 24) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 34) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 34) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 34) {
                    allAttackersSpawned = true;
                }
            }
        }
        //Round 7: No Delay Random Wave, 35 enemies: 35 random
        if (round == 7 && roundIndex < 35) {
            std::random_device randomDevice; //Used to intilize engine
            std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
            std::uniform_int_distribution<int> range(0, 2);
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                attacker->health = 25;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
        }
    }
    //Round 7: First No Delay Random Wave, 35 enemies: 35 random
    if(round == 7 && roundIndex < 35) {
        std::random_device randomDevice; //Used to intilize engine
        std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
        std::uniform_int_distribution<int> range(0, 2);
        int enemyChosen = range(rng);
        if (enemyChosen == 0) {
            Attacker *attacker = new Attacker(world);
            attacker->enemyID = dynamicIDAttacker;
            attacker->health = 25;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 35) {
                allAttackersSpawned = true;
            }
        }
        if (enemyChosen == 1) {
            AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 35) {
                allAttackersSpawned = true;
            }
        }
        if (enemyChosen == 2) {
            AttackerMalware *attacker = new AttackerMalware(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 35) {
                allAttackersSpawned = true;
            }
        }
    }
    //Round 8: Second Boss Wave, 40 enemies: 10 basic, 13 keyloggers, 15 malware, 2 meltdown
    if (round == 8 && roundIndex < 46) {
        if(roundIndex < 10) {
            Attacker *attacker = new Attacker(world);
            attacker->enemyID = dynamicIDAttacker;
            attacker->health = 25;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 12 && roundIndex >= 10)
            roundIndex++; //Delay
        if(roundIndex < 25 && roundIndex >= 12) {
            AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 27 && roundIndex >= 25)
            roundIndex++; //Delay
        if(roundIndex < 42 && roundIndex >= 27) {
            AttackerMalware *attacker = new AttackerMalware(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 44 && roundIndex >= 42)
            roundIndex++; //Delay
        if(roundIndex >= 44) {
            AttackerMeltdown *attacker = new AttackerMeltdown(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 46)
                allAttackersSpawned = true;
        }
    }
    //Round 9: Mixed Wave, 45 enemies: 20 random, 5 random, 20 random
    if (round == 9 && roundIndex < 49) {
        std::random_device randomDevice; //Used to intilize engine
        std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
        std::uniform_int_distribution<int> range(0, 2);
        if (roundIndex < 20) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                attacker->health = 25;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 22 && roundIndex >= 20)
            roundIndex++; //Delay
        if (roundIndex < 27 && roundIndex >= 22) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 39 && roundIndex >= 37)
            roundIndex++; //Delay
        if (roundIndex < 49 && roundIndex >= 39) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 49) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 49) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 49) {
                    allAttackersSpawned = true;
                }
            }
        }
        if (round == 7 && roundIndex < 35) {
            std::random_device randomDevice; //Used to intilize engine
            std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
            std::uniform_int_distribution<int> range(0, 2);
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
        }
    }
    //Round 10: Mixed Wave, 50 enemies: 10 random, 20 random, 20 random
    if (round == 10 && roundIndex < 54) {
        std::random_device randomDevice; //Used to intilize engine
        std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
        std::uniform_int_distribution<int> range(0, 2);
        if (roundIndex < 10) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                attacker->health = 25;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 12 && roundIndex >= 10)
            roundIndex++; //Delay
        if (roundIndex < 32 && roundIndex >= 12) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 34 && roundIndex >= 32)
            roundIndex++; //Delay
        if (roundIndex < 54 && roundIndex >= 34) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 54) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 54) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 54) {
                    allAttackersSpawned = true;
                }
            }
        }
        if (round == 7 && roundIndex < 35) {
            std::random_device randomDevice; //Used to intilize engine
            std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
            std::uniform_int_distribution<int> range(0, 2);
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
        }
    }
    //Round 11: Mixed Wave, 55 enemies: 15 random, 20 random, 20 random
    if (round == 11 && roundIndex < 59) {
        std::random_device randomDevice; //Used to intilize engine
        std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
        std::uniform_int_distribution<int> range(0, 2);
        if (roundIndex < 15) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 17 && roundIndex >= 15)
            roundIndex++; //Delay
        if (roundIndex < 37 && roundIndex >= 17) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 39 && roundIndex >= 37)
            roundIndex++; //Delay
        if (roundIndex < 59 && roundIndex >= 39) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 59) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 59) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 59) {
                    allAttackersSpawned = true;
                }
            }
        }
        if (round == 7 && roundIndex < 35) {
            std::random_device randomDevice; //Used to intilize engine
            std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
            std::uniform_int_distribution<int> range(0, 2);
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
        }
    }
    //Round 12: Third Boss Wave, 60 enemies: 10 basic, 20 keyloggers, 25 malware, 5 meltdown
    if (round == 12 && roundIndex < 66) {
        if(roundIndex < 10) {
            Attacker *attacker = new Attacker(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 12 && roundIndex >= 10)
            roundIndex++; //Delay
        if(roundIndex < 32 && roundIndex >= 12) {
            AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 34 && roundIndex >= 32)
            roundIndex++; //Delay
        if(roundIndex < 59 && roundIndex >= 34) {
            AttackerMalware *attacker = new AttackerMalware(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 61 && roundIndex >= 59)
            roundIndex++; //Delay
        if(roundIndex >= 61) {
            AttackerMeltdown *attacker = new AttackerMeltdown(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 66)
                allAttackersSpawned = true;
        }
    }
    //Round 13: Final Mixed Wave, 65 enemies: 5 random, 30 random, 30 random
    if (round == 13 && roundIndex < 69) {
        std::random_device randomDevice; //Used to intilize engine
        std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
        std::uniform_int_distribution<int> range(0, 2);
        if (roundIndex < 5) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 7 && roundIndex >= 5)
            roundIndex++; //Delay
        if (roundIndex < 37 && roundIndex >= 7) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
            }
        }
        if (roundIndex < 39 && roundIndex >= 37)
            roundIndex++; //Delay
        if (roundIndex < 59 && roundIndex >= 39) {
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 59) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 59) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 59) {
                    allAttackersSpawned = true;
                }
            }
        }
        if (round == 7 && roundIndex < 35) {
            std::random_device randomDevice; //Used to intilize engine
            std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
            std::uniform_int_distribution<int> range(0, 2);
            int enemyChosen = range(rng);
            if (enemyChosen == 0) {
                Attacker *attacker = new Attacker(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 1) {
                AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
            if (enemyChosen == 2) {
                AttackerMalware *attacker = new AttackerMalware(world);
                attacker->enemyID = dynamicIDAttacker;
                listOfAttackers[dynamicIDAttacker] = attacker;
                dynamicIDAttacker++;
                roundIndex++;
                if (roundIndex == 35) {
                    allAttackersSpawned = true;
                }
            }
        }
    }
    //Round 14: Final No Delay Random Wave, 70 enemies: 70 random
    if (round == 14 && roundIndex < 70) {
        std::random_device randomDevice; //Used to intilize engine
        std::mt19937 rng(randomDevice()); //Mersenne-Twister engine
        std::uniform_int_distribution<int> range(0, 2);
        int enemyChosen = range(rng);
        if (enemyChosen == 0) {
            Attacker *attacker = new Attacker(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 70) {
                allAttackersSpawned = true;
            }
        }
        if (enemyChosen == 1) {
            AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 70) {
                allAttackersSpawned = true;
            }
        }
        if (enemyChosen == 2) {
            AttackerMalware *attacker = new AttackerMalware(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 70) {
                allAttackersSpawned = true;
            }
        }
    }
    //Round 15: Final Boss Wave, 100 enemies: 30 basic, 30 keyloggers, 30 malware, 10 meltdown
    if (round == 15 && roundIndex < 106) {
        if(roundIndex < 30) {
            Attacker *attacker = new Attacker(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 32 && roundIndex >= 30)
            roundIndex++; //Delay
        if(roundIndex < 62 && roundIndex >= 32) {
            AttackerKeyLogger *attacker = new AttackerKeyLogger(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 64 && roundIndex >= 62)
            roundIndex++; //Delay
        if(roundIndex < 94 && roundIndex >= 64) {
            AttackerMalware *attacker = new AttackerMalware(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
        }
        if(roundIndex < 96 && roundIndex >= 94)
            roundIndex++; //Delay
        if(roundIndex >= 96) {
            AttackerMeltdown *attacker = new AttackerMeltdown(world);
            attacker->enemyID = dynamicIDAttacker;
            listOfAttackers[dynamicIDAttacker] = attacker;
            dynamicIDAttacker++;
            roundIndex++;
            if (roundIndex == 106)
                allAttackersSpawned = true;
        }
    }
}

/**
 * @brief Game::acquireTargetAttacker acquire the first attacker from the map containing all the in-range attackers
 * @param inRangeTarget
 * @return
 */
Attacker* Game::acquireTargetAttacker(map<int,Attacker*> inRangeTarget){
    if(!inRangeTarget.empty())
        return inRangeTarget.begin()->second;
    else
        return nullptr;
}

/**
 * @brief Game::updatePoints
 * pulic slot update player's currency in game through
 * defeating attackers or buying new tower
 */
void Game::updatePoints(int pointIncrement){
    points += pointIncrement;
    emit updateCurrency(points);
}
/**
 * @brief Game::updateHealth
 * public slot to adjust player's health by how many attacker pass through the level
 */
void Game::updateHealth(int healthIncrement){
    healthPoint += healthIncrement;
    emit sendNewHealth(healthPoint);
}

/**
 * @brief Game::upgradePassword
 * Update the masterpassword by the upgrade,
 * convert to a new password by which hashing upgrade is chosen
 * also changes the text in display
 * @param upgrade
 */
void Game::upgradePassword(Upgrade upgrade) {
    masterPasswordUpgrades = "password";
    masterPassword = masterPasswordPlainText;
    if (upgrade.id == 0 || upgrades.count(0)) { // length
        masterPasswordUpgrades.append("|len");
        masterPassword.append("nfVi");
    }
    if (upgrade.id == 1 || upgrades.count(1)) { // symbols
        masterPasswordUpgrades.append("|syms");
        masterPassword.append("$!&?&");
    }
    if (upgrade.id == 2 || upgrades.count(2)) { // numbers
        masterPasswordUpgrades.append("|nums");
        masterPassword.append("63254");
    }
    if (upgrade.id == 3 || upgrades.count(3)) { // random
        masterPasswordUpgrades.append("|rand");
        string temp = masterPassword.toStdString();
        shuffle(temp.begin(), temp.end(), default_random_engine(seed));
        masterPassword = QString::fromStdString(temp);
    }
    if (upgrade.id == 4 || upgrades.count(4)) { // sha-1
        masterPasswordUpgrades.prepend("sha1(").append(")");
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Sha1).toHex()));
    }
    if (upgrade.id == 5 || upgrades.count(5)) { // md5
        masterPasswordUpgrades.prepend("md5(").append(")");
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Md5).toHex()));
    }
    if (upgrade.id == 6 || upgrades.count(6)) { // triplemd5
        masterPasswordUpgrades.prepend("md5(md5(md5(").append(")))");
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Md5).toHex()));
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Md5).toHex()));
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Md5).toHex()));
    }
    if (upgrade.id == 7 || upgrades.count(7)) { // triple sha1
        masterPasswordUpgrades.prepend("sha1(sha1(sha1(").append(")))");
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Sha1).toHex()));
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Sha1).toHex()));
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Sha1).toHex()));
    }
    if (upgrade.id == 8 || upgrades.count(8)) { // salt
        QStringList list = masterPasswordUpgrades.split("password");
        masterPasswordUpgrades = list[0] + "saltValue+password" + list[1];
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Sha1).toHex()));
    }
    if (upgrade.id == 9 || upgrades.count(9)) { // pepper
        QStringList list = masterPasswordUpgrades.split("password");
        masterPasswordUpgrades = list[0] + "pepperValue+password" + list[1];
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Sha1).toHex()));
    }
    if (upgrade.id == 10 || upgrades.count(10)) { // bcrypt
        masterPasswordUpgrades.prepend("bcrypt(").append(")");
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Blake2b_256).toHex()));
    }
    if (upgrade.id == 11 || upgrades.count(11)) { // argonid
        masterPasswordUpgrades.prepend("argonid2(").append(")");
        masterPassword = QString("%1").arg(QString(QCryptographicHash::hash(masterPassword.toUtf8(),QCryptographicHash::Blake2b_384).toHex()));
    }
}

/**
 * @brief Game::confirmUpgrade
 * apply chosen upgrade to increase player's lives accordingly
 * @param upgrade
 */
void Game::confirmUpgrade(Upgrade upgrade) {
    // remove from available, add to upgrades
    upgrades[upgrade.id] = upgrade;
    availableUpgrades.erase(upgrade.id);
    updateHealth(upgrade.lifeIncrease);
    emit upgradedMasterPassword();
}

void Game::updatePoints() {
    emit updateGamePoints();
}

