/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include <vector>
#include <algorithm>
#include <map>
#include <QShowEvent>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "descriptiondialog.h"
#include "selectpassworddialog.h"
#include "gameoverdialog.h"
#include "globals.h"
#include "startdialog.h"

using std::erase;
using std::count;
using std::vector;
using std::map;
/**
 * @brief MainWindow::MainWindow
 * Main view outside the game screen to display and control other UI elements
 *
 * @param game
 * @param parent
 */
MainWindow::MainWindow(Game* game, QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->widget->show();
    this->game = game;

    setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
    ui->startGame->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));

    ui->widget->game = game;
    ui->widget->setMouseTracking(true);
    ui->baseTower->setIcon(QIcon(":/sprites/GameImages/Tower_Pierce.png"));
    ui->bounceTower->setIcon(QIcon(":/sprites/GameImages/Tower_Bounce.png"));
    ui->freezeTower->setIcon(QIcon(":/sprites/GameImages/Tower_Freeze.png"));

    connect(this, &MainWindow::gameStart, ui->widget, &GameScreenWidget::createGameWorld);
    connect(ui->widget, &GameScreenWidget::startGame, game, &Game::startRound);
    connect(ui->baseTower, &QPushButton::clicked, game, [this, game](){game->spawnTowerFollow(1);});
    connect(ui->baseTower, &QPushButton::clicked, this, &MainWindow::setUpHeldTower);
    connect(ui->bounceTower, &QPushButton::clicked, game, [this, game](){game->spawnTowerFollow(2);});
    connect(ui->bounceTower, &QPushButton::clicked, this, &MainWindow::setUpHeldTower);
    connect(ui->freezeTower, &QPushButton::clicked, game, [this, game](){game->spawnTowerFollow(3);});
    connect(ui->freezeTower, &QPushButton::clicked, this, &MainWindow::setUpHeldTower);
    connect(ui->widget, &GameScreenWidget::placeDownTower, this, &MainWindow::reactivateButtons);
    connect(ui->widget, &GameScreenWidget::roundEnd, this, &MainWindow::on_round_end);
    connect(game, &Game::updateCurrency, this, &MainWindow::on_currency_change);
    connect(game, &Game::updateGamePoints, this, &MainWindow::updatePointsValue);
    connect(game, &Game::sendNewHealth, this, &MainWindow::on_lives_change);
    connect(game, &Game::upgradedMasterPassword, this, &MainWindow::onPasswordUpgrade);

    this->show();

    //Start Menu
    startDialog start(this);
    start.exec();

    // Master Password Prompt
    SelectPasswordDialog masterPwdPrompt(Master, game->passwords);
    masterPwdPrompt.exec();
    game->masterPasswordPlainText = masterPwdPrompt.password;
    game->masterPassword = masterPwdPrompt.password;
    game->masterPasswordStrength = masterPwdPrompt.strength;
    game->healthPoint = (game->masterPassword.length() * (game->masterPasswordStrength+1));
    ui->plainTextMasterLabelValue->setText(game->masterPasswordPlainText);
    ui->masterPasswordLabelValue->setText(game->masterPassword);
    ui->masterUpgradeLabelValue->setText(game->masterPasswordUpgrades);

    // Master Password Description
    QDialog* masterPassDescription = new DescriptionDialog(game, Master, 0);
    masterPassDescription->exec();

    //Set starting health
    ui->healthNumberText->setText(QString::number(game->healthPoint));
    ui->pointsNumberText->setText(QString::number(game->points));

}

MainWindow::~MainWindow() {
    delete ui;
}

//startbutton clicked
void MainWindow::on_startGame_clicked() {
    if(ui->startGame->text() == "Cancel") {
        reactivateButtons();
        game->towerOnCursor->setID(0);
        ui->startGame->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    }
    else {
        emit gameStart();
        ui->startGame->setEnabled(false);
    }
}

//when clicks on tower, turn in placing tower phase
//disable other tower buttons, start button turn into a cancel button
void MainWindow::setUpHeldTower() {
    ui->baseTower->setEnabled(false);
    ui->freezeTower->setEnabled(false);
    ui->bounceTower->setEnabled(false);
    ui->startGame->setEnabled(true); //Make sure cancel can be pressed
    ui->startGame->setStyleSheet( QString("QPushButton {background-color: rgb(200,50,50);} QPushButton:pressed {background-color: rgb(255,150,150);}"));
    ui->startGame->setText("Cancel");
}

//disable start button after round start, enable all tower buttons
void MainWindow::reactivateButtons() {
    ui->baseTower->setEnabled(true);
    ui->freezeTower->setEnabled(true);
    ui->bounceTower->setEnabled(true);
    ui->startGame->setText("Start");
    ui->startGame->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    if (game->isActiveRound == true) {
        ui->startGame->setEnabled(false);
    }
}

void MainWindow::on_round_end() {
    ui->startGame->setEnabled(true);
    ui->roundNumberLabel->setText(QString::number(game->round+1));
    game->updatePoints(100); //Get 100 points. Subject to change
    ui->roundDesc->setText(ROUND_DESCRIPTIONS.at(game->round+1));
    if(game->round >= 16)
    {
        onGameOver();
    }
}
//update the text of the points currency on change
void MainWindow::on_currency_change(int newCurrency) {
    ui->pointsNumberText->setText(QString::number(newCurrency));
}
//update the text of the masterpassword
void MainWindow::onPasswordUpgrade() {
    ui->masterUpgradeLabelValue->setText(game->masterPasswordUpgrades);
    ui->masterPasswordLabelValue->setText(game->masterPassword);
}

//update lives, determine end game state
void MainWindow::on_lives_change(int newLives) {
    ui->healthNumberText->setText(QString::number(newLives));
    if (newLives <= 0)
        onGameOver();
}

//display game over window on defeat
void MainWindow::onGameOver() {
    game->isGameOver = true;
    GameOverDialog* gameOver = new GameOverDialog(this, game->points, game->round, game->masterPasswordPlainText, game->masterPassword);
    connect(gameOver, &GameOverDialog::gameCompleted, this, &MainWindow::gameClose);
    gameOver->exec();
}

void MainWindow::gameClose() {
    exit(0);
}

//update the text display of the points currency
void MainWindow::updatePointsValue() {
     ui->pointsNumberText->setText(QString::number(game->points));
}

