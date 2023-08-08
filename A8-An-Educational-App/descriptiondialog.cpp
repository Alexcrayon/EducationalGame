/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include "descriptiondialog.h"
#include "ui_descriptiondialog.h"
#include "game.h"
#include "globals.h"

DescriptionDialog::DescriptionDialog(Game* game, PasswordType pwdType, int towerId, QWidget *parent) : QDialog(parent), ui(new Ui::DescriptionDialog) {
    ui->setupUi(this);
    if (pwdType == Master) {
        this->setWindowTitle("Master Password Description");
        this->ui->passLabel->setText(game->masterPassword);
        this->ui->descriptionLabel->setText(PASSWORD_STRENGTH_DESC.at(game->masterPasswordStrength));
    } else if (pwdType == Tower) {
        this->setWindowTitle("Tower Password Description");
        this->ui->passTitleLabel->setText("Your Tower Password");
        PasswordTower* tower = game->listOfTowers[towerId];
        this->ui->passLabel->setText(tower->basePassword);
        this->ui->descriptionLabel->setText(PASSWORD_STRENGTH_DESC.at(tower->passwordStrength));
    }

}

DescriptionDialog::~DescriptionDialog() {
    delete ui;
}
