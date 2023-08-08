/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */

#include "gameoverdialog.h"
#include "ui_gameoverdialog.h"

GameOverDialog::GameOverDialog(QWidget *parent, int points, int round, QString plain, QString upgraded) :
    QDialog(parent),
    points(points),
    round(round),
    plain(plain),
    upgraded(upgraded),
    ui(new Ui::GameOverDialog)
{
    ui->setupUi(this);
    ui->pointNumber->setText(QString::number(points));
    ui->roundNumber->setText(QString::number(round));
    ui->PlainPassword->setText(plain);
    ui->upgradedPassword->setText(upgraded);
    connect(ui->okButton, &QPushButton::clicked, this, &GameOverDialog::onButtonPressed);
}

void GameOverDialog::onButtonPressed() {
    this->close();
    emit gameCompleted();
}

GameOverDialog::~GameOverDialog()
{
    delete ui;
}
