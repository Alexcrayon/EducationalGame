/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include <QMouseEvent>
#include "gamescreenwidget.h"
#include "upgradedialog.h"
#include "towerenabledialog.h"
#include "passwordtowerfreeze.h"
#include "passwordtowerpeirce.h"
#include "passwordtowerreflecting.h"
#include "selectpassworddialog.h"
#include "descriptiondialog.h"
#include "malwaredialog.h"
/**
 * @brief GameScreenWidget::GameScreenWidget
 * The main game view for drawing object and simulating box2D physics
 * communicate with game class
 * @param parent
 */
GameScreenWidget::GameScreenWidget(QWidget *parent): QWidget(parent), timer(this)
{
    setMouseTracking(true);
    pathPercentIncrement = 0.0005;
    roundStarted = false;
    timer.start(10);
    stageBackground = QImage(":/sprites/GameImages/PathBackground.png");
    connect(&timer, &QTimer::timeout, this, &GameScreenWidget::updateWorld);
    connect(&attackerSpawnTimer, &QTimer::timeout, this, &GameScreenWidget::spawnNewAttacker);
    connect(&attackerMovementTimer, &QTimer::timeout, this, &GameScreenWidget::goToNextPercentagePoint);
}

/**
 * @brief GameScreenWidget::createGameWorld
 * setup on the starting of a new round
 */
void GameScreenWidget::createGameWorld()
{
    listener = new ContactListener();
    game->world->SetContactListener(listener);
    attackerSpawnTimer.start(game->attackerSpawningRate);
    attackerMovementTimer.start(16);
    emit startGame();
}

/**
 * @brief GameScreenWidget::paintEvent
 * paint every activated object on screen
 */
void GameScreenWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    backBounds = QRectF(29,9, 521, 471);
    painter.drawImage(backBounds, stageBackground);

    //paint attacker sprite
    foreach (auto attk, game->listOfAttackers) {
        b2Vec2 position = attk.second->attakBody->GetPosition();
        //end of path position, if passed this, stop drawing attacker sprite
        //Also don't draw attacker if they are dead
        if(!(position.x >= 557) && !(attk.second->isDead))
            painter.drawImage((int)position.x - attk.second->image.width()/2, (int)position.y - attk.second->image.height()/2, attk.second->image);
        else {
            if (!(attk.second->isAtEnd)&&!(attk.second->isDead)) {
                game->updateHealth(attk.second->getLivesTaken());
                attk.second->isAtEnd = true;
            }
        }
    }

    //paint a tower sprite following player cursor after one of the tower buttons was pressed
    if(game->towerOnCursor->getID() != 0){
        painter.drawImage(game->towerOnCursor->location.x(), game->towerOnCursor->location.y(), game->towerOnCursor->currentSprite);
    }
    foreach (auto t, game->listOfTowers) {
        if(!(game->isGameOver))
        {
            if(t.second->isActive)
                painter.drawImage(t.second->getPosition().x(),t.second->getPosition().y(), t.second->sprite);
            else
                painter.drawImage(t.second->getPosition().x(),t.second->getPosition().y(), t.second->disabledSprite);
        }
    }
    foreach (auto bullet, game->listOfBullets) {
        if(bullet->activated && game->isActiveRound)
            painter.drawImage(bullet->bulletBody->GetPosition().x,bullet->bulletBody->GetPosition().y, bullet->image);
    }
    painter.end();
}

/**
 * @brief GameScreenWidget::updateWorld
 * Update box2D physics and states for every attackers, towers and bullets in game
 */
void GameScreenWidget::updateWorld()
{
    float timeStep = 1.0/60.0;
    //Update attackers' position after round started
    if(game->isActiveRound){
        foreach(auto attacker, game->listOfAttackers)
        {
            if(attacker.second->isDead)
            {
                if (attacker.second->attakBody->IsActive())
                {
                    if (attacker.second->enemyType == keylog && !attacker.second->getFrozenState())
                    {
                        int randInt = 0;
                        if(game->listOfTowers.size() > 1)
                            randInt = rand() % game->listOfTowers.size();
                        if(game->listOfTowers.contains(randInt))
                            if(rand() % 2 == 1)
                                game->listOfTowers[randInt]->isActive = false;
                    }
                    if (attacker.second->enemyType == malware && !attacker.second->getFrozenState())
                    {
                        if(rand() % 2 == 1){
                            MalwareDialog malDialgo(game);
                            malDialgo.exec();
                        }
                    }
                    game->updatePoints(attacker.second->getCurrency());
                }
                attacker.second->attakBody->SetActive(false);
            }
            else
            {
                //get the next point in Path by percentage
                double nextPercentage = attacker.second->nextPercentPoint;
                if(nextPercentage < 1){
                    if(!attacker.second->getFrozenState())
                    {
                        QPoint nextPosition = game->path->getPosition(nextPercentage);
                        //calculate the length between current pos of attacker to the next point
                        b2Vec2 travelDist = b2Vec2(nextPosition.x(),nextPosition.y()) - attacker.second->attakBody->GetPosition();
                        //calculate the required velocity per timestep
                        float velocity = travelDist.Length() / timeStep;
                        travelDist *= velocity;
                        b2Vec2 newVelocity = travelDist;
                        attacker.second->attakBody->SetLinearVelocity(newVelocity);
                    }
                    else
                    {
                        attacker.second->attakBody->SetLinearVelocity(b2Vec2(0,0));
                    }
                }
                else{
                    attacker.second->attakBody->SetActive(false);
                    attacker.second->isDead = true;
                }
            }
        }
        //update towers
        foreach(auto tower, game->listOfTowers)
        {
            if(tower.second->isActive)
            {
                tower.second->findAttackersInRange(game->listOfAttackers);
                tower.second->currentTarget = game->acquireTargetAttacker(tower.second->inRangeTarget);
            }
        }
        //update bullets
        foreach (auto bullet, game->listOfBullets)
        {
            if(bullet->activated){
                 bullet->move();
                 bullet->bounce();
             }
        }
        game->world->Step(timeStep, 6, 2);

        bool attackersIsAlive = false;
        foreach (auto attacker, game->listOfAttackers)
            attackersIsAlive |= attacker.second->attakBody->IsActive();
        //end of the game
        if(game->isGameOver)
        {
            qDebug() << "Game Over";
            pathPercentIncrement = 0.0005;
            emit roundEnd();
            game->isActiveRound = false;
            timer.stop();
            attackerMovementTimer.stop();
            attackerSpawnTimer.stop();
            game->listOfAttackers.clear();
            game->listOfBullets.clear();
            game->listOfTowers.clear();

        }
        //end of the round
        if (game->isActiveRound&&!attackersIsAlive&&game->allAttackersSpawned)
        {
            qDebug() << "round end";
            pathPercentIncrement += 0.0001; //Increase velocity
            emit roundEnd();
            game->isActiveRound = false;
            upgradeMasterPassword();
        }
    }
    update();
}

/**
 * @brief GameScreenWidget::goToNextPercentagePoint
 * Update the percentage point in path
 */
void GameScreenWidget::goToNextPercentagePoint()
{
    foreach(auto attacker, game->listOfAttackers)
    {
        if(attacker.second->nextPercentPoint < 1 && !attacker.second->getFrozenState())
            attacker.second->nextPercentPoint += pathPercentIncrement;
    }
}

void GameScreenWidget::spawnNewAttacker()
{
    game->createAttackersByRound();
}

void GameScreenWidget::mousePressEvent(QMouseEvent* e)
{
    int x = e->pos().x();
    int y = e->pos().y();
    for (auto const [id, towerCategory] : game->listOfTowers)
    {
        int xDist = x - towerCategory->getPosition().x();
        int yDist = y - towerCategory->getPosition().y();
        if (xDist > 0 && xDist < 64 && yDist > 0 && yDist < 64)
        {
            if(game->listOfTowers[id]->isActive)
            {
                UpgradeDialog upgradeDialog(this->game, Tower, id);
                upgradeDialog.exec();
            }
            else if(game->points >= 30)
            {
                TowerEnableDialog enableTower(this->game, id);
                enableTower.exec();
            }
            return;
        }
    }
}

void GameScreenWidget::mouseMoveEvent(QMouseEvent* e)
{
    if(game->towerOnCursor->getID() != 0)
    {
        //TowerPlace* place = placer.second;
        game->towerOnCursor->goToMouse(e->pos().x(), e->pos().y());
    }
}

void GameScreenWidget::mouseReleaseEvent(QMouseEvent *e)
{
    int x = e->pos().x() - game->towerOnCursor->baseSprite.width()/2;
    int y = e->pos().y() - game->towerOnCursor->baseSprite.height()/2;;
    if (x < backBounds.x() || x > backBounds.x() + backBounds.width())
        return;
    if (y < backBounds.y() || y > backBounds.y() + backBounds.height())
        return;
    if (game->towerHeld && game->path->getPathDistance(QPoint(x, y)) > 30 && game->towerOnCursor->getID() != 0)
    {
        if (game->towerOnCursor->getID() == freeze)
        {
            if (game->points < PasswordTowerFreeze::cost)
            {
                return; //Don't actually place tower down
            }
            game->updatePoints(-(PasswordTowerFreeze::cost)); //Charge for tower
        }
        if (game->towerOnCursor->getID() == bounce)
        {
            if (game->points < PasswordTowerReflecting::cost)
            {
                return; //Don't actually place tower down
            }
            game->updatePoints(-(PasswordTowerReflecting::cost)); //Charge for tower
        }
        if (game->towerOnCursor->getID() == standard)
        {
            if (game->points < PasswordTowerPeirce::cost)
            {
                return; //Don't actually place tower down
            }
            game->updatePoints(-(PasswordTowerPeirce::cost)); //Charge for tower
        }
        emit placeDownTower();

        // Tower Password Prompt
        SelectPasswordDialog towerPwdPrompt(Tower, game->passwords);
        towerPwdPrompt.exec();

        PasswordTower* ptp = nullptr;
        QTimer* timer = new QTimer(this);
        //create a new timer for every new tower creation to control the fire rate
        if (game->towerOnCursor->getID() == standard)
        {
            ptp = new PasswordTowerPeirce(game->world, towerPwdPrompt.password, towerPwdPrompt.strength, x, y);
            timer->start(500);
            connect(timer,&QTimer::timeout, this, [source = game->dynamicIDTower, this](){
                 shoot(source);
            });
        }
        else if (game->towerOnCursor->getID() == bounce)
        {
            ptp = new PasswordTowerReflecting(game->world, towerPwdPrompt.password, towerPwdPrompt.strength, x, y);
            timer->start(2000);
            connect(timer,&QTimer::timeout, this, [source = game->dynamicIDTower, this](){
                 shoot(source);
            });
        }
        else if (game->towerOnCursor->getID() == freeze)
        {
            ptp = new PasswordTowerFreeze(game->world, towerPwdPrompt.password, towerPwdPrompt.strength, x, y);
            timer->start(5000);
            connect(timer,&QTimer::timeout, this, [source = game->dynamicIDTower, this](){
                 shoot(source);
            });
        }
        game->listOfTowers[game->dynamicIDTower] = ptp;
        QDialog* passDescription = new DescriptionDialog(game, Tower, game->dynamicIDTower);
        passDescription->exec();
        game->dynamicIDTower++;
        game->towerOnCursor->setID(0);
    }
}

void GameScreenWidget::upgradeMasterPassword()
{
    UpgradeDialog upgradeDialog(this->game, Master, 0);
    upgradeDialog.exec();
}

/**
 * @brief GameScreenWidget::shoot
 * Create a bullet on a tower's position, prepare it to shoot at target
 * @param sourceTower The towerID that bullet will shoot from
 */
void GameScreenWidget::shoot(int sourceTower)
{
    if (game->isGameOver)
    {
        return;
    }
    PasswordTower* tower = game->listOfTowers[sourceTower];

    Attacker* target = tower->currentTarget;
    if(target != nullptr)
    {
        if(tower->getID() == standard && tower->isActive)
        {
            Bullet* bullet = new Bullet(1, game->world, target->attakBody->GetPosition());
            bullet->bulletBody->SetTransform(b2Vec2(tower->getPosition().x() + tower->sprite.width()/2 - bullet->image.width()/2
                                                    ,tower->getPosition().y() + tower->sprite.height()/2 - bullet->image.height()/2), bullet->bulletBody->GetAngle());
            bullet->acquireTargetDirction();
            game->listOfBullets.push_back(bullet);
        }
        else if(tower->getID() == freeze && tower->isActive)
        {
            target->freeze();
        }
        else if(tower->getID() == bounce && tower->isActive)
        {
            Bullet* bullet = new Bullet(2, game->world, target->attakBody->GetPosition());
            bullet->bulletBody->SetTransform(b2Vec2(tower->getPosition().x() + tower->sprite.width()/2 - bullet->image.width()/2
                                                    ,tower->getPosition().y() + tower->sprite.height()/2 - bullet->image.height()/2), bullet->bulletBody->GetAngle());
            bullet->acquireTargetDirction();
            game->listOfBullets.push_back(bullet);
        }
    }
}

