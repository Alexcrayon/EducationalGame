/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include "contactlistener.h"
/**
 * @brief ContactListener::ContactListener
 * Contact listenter for the game, used for listening collision between attacker class and bullet class
 * @param parent
 */
ContactListener::ContactListener(QObject *parent):QObject(parent), b2ContactListener(){

}


/**
 * @brief ContactListener::BeginContact
 * Collision callback for handling collision between any attackers and bullets
 * @param contact the point of contact, contain two fixtures
 */
void ContactListener::BeginContact(b2Contact* contact) {

    b2Fixture* f1 = contact->GetFixtureA();
    b2Fixture* f2 = contact->GetFixtureB();

    b2Body* b1 = f1->GetBody();
    b2Body* b2 = f2->GetBody();

    QObject* o1 = static_cast<QObject*>(b1->GetUserData());
    QObject* o2 = static_cast<QObject*>(b2->GetUserData());

    //first contact object is attacker, the second is bullet
    if((QString)o1->metaObject()->className() == "Attacker" && (QString)o2->metaObject()->className() == "Bullet"){
        //qDebug()<<"scenario 1";
        Attacker* attacker = (Attacker*)(o1);
        Bullet* bullet = (Bullet*)o2;

        //normal bullet collision handle
        if(bullet->bulletType == 1 && bullet->activated){
            bullet->destroyed();
            attacker->loseHealth(1);
        }
        //bounce bullet collision handle
        if(bullet->bulletType == 2 && !bullet->isBouncing && bullet->activated){
            attacker->loseHealth(1);
            bullet->isBouncing = true;
        }
        if(bullet->bulletType == 2 && bullet->isBouncing && bullet->activated){
            attacker->loseHealth(1);
            //bullet->isBouncing = true;
        }

    }
    //first contact object is bullet, the second is attacker
    if((QString)o2->metaObject()->className() == "Attacker" && (QString)o1->metaObject()->className() == "Bullet"){
        //qDebug()<<"scenario 2";

        Bullet* bullet = (Bullet*)o1;
        Attacker* attacker = (Attacker*)(o2);

        //same as above
        if(bullet->bulletType == 1 && bullet->activated){
            bullet->destroyed();
            attacker->loseHealth(1);
        }

        if(bullet->bulletType == 2 && !bullet->isBouncing && bullet->activated){
            attacker->loseHealth(1);
            bullet->isBouncing = true;
        }
        if(bullet->bulletType == 2 && bullet->isBouncing && bullet->activated){
            attacker->loseHealth(1);
        }
    }
}

