/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include "startdialog.h"
#include "ui_startdialog.h"

startDialog::startDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    ui->setupUi(this);
    connect(ui->OkButton, &QPushButton::clicked, this, &startDialog::close);

    QPixmap passwordTower(":/sprites/GameImages/Tower_Pierce.png");
    ui->passwordTower->setPixmap(passwordTower.scaled(ui->passwordTower->width(), ui->passwordTower->height(), Qt::KeepAspectRatio));

    QPixmap passwordTowerFreeze(":/sprites/GameImages/Tower_Freeze.png");
    ui->passwordTower_2->setPixmap(passwordTowerFreeze.scaled(ui->passwordTower_2->width(), ui->passwordTower_2->height(), Qt::KeepAspectRatio));

    QPixmap passwordTowerReflecting(":/sprites/GameImages/Tower_Bounce.png");
    ui->passwordTower_3->setPixmap(passwordTowerReflecting.scaled(ui->passwordTower_3->width(), ui->passwordTower_3->height(), Qt::KeepAspectRatio));

    QPixmap attackerBase(":/sprites/GameImages/Attacker_Base.png");
    ui->passwordTower_4->setPixmap(attackerBase.scaled(ui->passwordTower_4->width(), ui->passwordTower_4->height(), Qt::KeepAspectRatio));

    QPixmap attackerKey(":/sprites/GameImages/Attacker_Keylogger.png");
    ui->passwordTower_5->setPixmap(attackerKey.scaled(ui->passwordTower_5->width(), ui->passwordTower_5->height(), Qt::KeepAspectRatio));

    QPixmap attackerMal(":/sprites/GameImages/Attacker_Adware.png");
    ui->passwordTower_6->setPixmap(attackerMal.scaled(ui->passwordTower_6->width(), ui->passwordTower_6->height(), Qt::KeepAspectRatio));

    QPixmap attackerMel(":/sprites/GameImages/Attacker_Meltdown.png");
    ui->passwordTower_7->setPixmap(attackerMel.scaled(ui->passwordTower_7->width(), ui->passwordTower_7->height(), Qt::KeepAspectRatio));
}

startDialog::~startDialog()
{
    delete ui;
}
