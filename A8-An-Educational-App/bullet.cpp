/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include "bullet.h"
/**
 * @brief Bullet::Bullet
 * A bullet class that creates a bullet and its physics for the tower inside a b2World
 * @param type Types of bullet, type 1 is normal bullet, type 2 is the bounce bullet
 * @param world The box2DWorld it will be created in
 * @param targetPos The target posistion that this bullet need to reach
 */
Bullet::Bullet(int type, b2World* world, b2Vec2 targetPos, QObject *parent): QObject(parent){

    bulletType = type;
    isBouncing = false;
    QImage sprite (":/sprites/GameImages/Bullet.png");
    image = sprite;
    target = targetPos;

    //setup box2D body and fixture
    bulletBodyDef.type = b2_dynamicBody;
    bulletBodyDef.position.Set(0,0);
    bulletBody = world->CreateBody(&bulletBodyDef);
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(5.0f,5.0f);
    bulletBody->CreateFixture(&polygonShape, 1);
    bulletBody->SetUserData(this);

    //activate this bullet for drawing and physics simulation
    activated = true;
    //a random direction for bullet to bounce to
    bounceDir = (rand() > RAND_MAX/2) ? -1 : 1;
}

/**
 * @brief Bullet::acquireTargetDirction
 * Compute the vector that is required for the move direction of the bullet
 */
void Bullet::acquireTargetDirction(){
    targetDirection = target - bulletBody->GetPosition();
}

/**
 * @brief Bullet::move
 * Move a bullet toward a direction with max speed
 */
void Bullet::move()
{
    float velocity = (targetDirection.Length()) / (1.0/60.0);
    bulletBody->SetLinearVelocity(velocity *targetDirection );
}

/**
 * @brief Bullet::destroyed
 * Destroy the bullet when it hit an attacker
 * set it to inactive
 */
void Bullet::destroyed(){
    bulletBody->SetAwake(false);
    activated = false;
}
/**
 * @brief Bullet::bounce
 * Bounce the bullet to a perpendicular direction when it first hit an attacker
 */
void Bullet::bounce(){
    if(isBouncing){
        //velocity is maxed, 500 is just arbitrary number
        //bounce perpendicularly in both direction
        bulletBody->SetLinearVelocity(500 * bounceDir*targetDirection.Skew());
    }
}
