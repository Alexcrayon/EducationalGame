/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */

#include "towerplace.h"

/**
 * @brief TowerPlace::TowerPlace
 * Create a UI element showing what tower is being held and where it will be placed.
 * @param int ID
 */
TowerPlace::TowerPlace(int ID)
{
    this->ID = ID;
    baseSprite = QImage(":/sprites/GameImages/Tower_Pierce.png");
    freezeSprite = QImage(":/sprites/GameImages/Tower_Freeze.png");
    reflectSprite = QImage(":/sprites/GameImages/Tower_Bounce.png");

    currentSprite = baseSprite;
}

/**
 * @brief TowerPlace::goToMouse
 * Follow the mouse and adjust so its center is over the mouse.
 * @param x
 * @param y
 */
void TowerPlace::goToMouse(double x, double y)
{
    double xAdjust = currentSprite.width()/2;
    double yAdjust = currentSprite.height()/2;
    location = QPoint(x - xAdjust, y - yAdjust);
}

/**
 * @brief TowerPlace::setID
 * Set the type of tower being held by changing its ID and setting the correct image.
 * @param ID
 */
void TowerPlace::setID(int ID)
{
    this->ID = ID;
    switch(ID)
    {
    default:
        currentSprite = baseSprite;
        break;
    case 2:
        currentSprite = reflectSprite;
        break;
    case 3:
        currentSprite = freezeSprite;
        break;
    }
}

/**
 * @brief TowerPlace::getID
 * Get what ID the tower placer has so the correct tower can be placed down.
 * @return
 */
int TowerPlace::getID()
{
    return ID;
}
