/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include "towerenabledialog.h"
#include "ui_towerenabledialog.h"

TowerEnableDialog::TowerEnableDialog(Game* game, int towerId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TowerEnableDialog)
{
    ui->setupUi(this);

    this->game = game;
    tower = game->listOfTowers[towerId];
}

TowerEnableDialog::~TowerEnableDialog()
{
    delete ui;
}

void TowerEnableDialog::on_confirm_clicked()
{
    game->updatePoints(-30);
    tower->isActive = true;
    optionClicked();
}

void TowerEnableDialog::on_cancel_clicked()
{
    optionClicked();
}

void TowerEnableDialog::optionClicked()
{
    this->close();
}
