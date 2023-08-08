#include <algorithm>
#include <QIcon>
/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include "upgradedialog.h"
#include "ui_upgradedialog.h"
#include "globals.h"

using std::sort;

bool upgradeComparator(const Upgrade & up1, const Upgrade & up2) {
    return up1.complexityLevel < up2.complexityLevel;
}
/**
 * @brief UpgradeDialog::UpgradeDialog
 * Displaying upgrade content for the upgrade window
 * handle both masterpassword nad tower password upgrade
 * show 12 different types of upgrade in random order
 * as the game goes on, upgrade with more complexity will appear
 * @param game
 * @param pwdType
 * @param towerId
 * @param parent
 */
UpgradeDialog::UpgradeDialog(Game* game, PasswordType pwdType, int towerId, QWidget *parent)
    : QDialog(parent), ui(new Ui::UpgradeDialog) {
    ui->setupUi(this);
    this->game = game;
    this->upgrade = {"", -1};
    this->pwdType = pwdType;
    vector<Upgrade> upgradesList;
    setWindowTitle("Upgrade");
    if (pwdType == Master) {
        for (auto const& [id, upgrade] : game->availableUpgrades)
            upgradesList.push_back(upgrade);
        ui->plainTextLabelValue->setText(game->masterPasswordPlainText);
        ui->pointsLabel->setVisible(false);
        ui->pointsNumberText->setVisible(false);
    } else if (pwdType == Tower) {
        ui->pointsNumberText->setText(QString::number(game->points));
        tower = game->listOfTowers[towerId];
        for (auto const& [id, upgrade] : tower->availableUpgrades)
            upgradesList.push_back(upgrade);
        ui->plainTextLabelValue->setText(tower->basePassword);
        ui->label->setText("Upgrade Your Tower Password");
    }

    sort(upgradesList.begin(), upgradesList.end(), upgradeComparator);
    //Set text, icon and content for each button
    if(upgradesList.size()==1){
        ui->upgrade2Button->setVisible(false);
        ui->upgrade3Button->setVisible(false);
        up1 = upgradesList[0];
        ui->upgrade1Button->setText(up1.name);
        ui->upgrade1Button->setIcon(QIcon(up1.icon));
        if (game->points < up1.cost)
            ui->upgrade1Button->setDisabled(true);

        if (pwdType == Tower) {
            ui->passwordLabelValue->setText(tower->password);
            ui->upgradeLabelValue->setText(tower->passwordUpgrades);
            ui->upgrade1Button->setText(up1.name + "\n" + QString::number(up1.cost) + " Points");
        }
    }
    if(upgradesList.size()==2){
        ui->upgrade3Button->setVisible(false);
        up1 = upgradesList[0];
        up2 = upgradesList[1];

        ui->upgrade1Button->setText(up1.name);
        ui->upgrade2Button->setText(up2.name);
        ui->upgrade2Button->setIcon(QIcon(up2.icon));
        ui->upgrade1Button->setIcon(QIcon(up1.icon));

        if (game->points < up2.cost)
            ui->upgrade2Button->setDisabled(true);
        if (pwdType == Tower) {
                ui->passwordLabelValue->setText(tower->password);
                ui->upgradeLabelValue->setText(tower->passwordUpgrades);
                ui->upgrade1Button->setText(up1.name + "\n" + QString::number(up1.cost) + " Points");
                ui->upgrade2Button->setText(up2.name + "\n" + QString::number(up2.cost) + " Points");
            }
    }
    if(upgradesList.size()>=3){
        up1 = upgradesList[0];
        up2 = upgradesList[1];
        up3 = upgradesList[2];

        ui->upgrade1Button->setText(up1.name);
        ui->upgrade2Button->setText(up2.name);
        ui->upgrade3Button->setText(up3.name);
        ui->upgrade1Button->setIcon(QIcon(up1.icon));
        ui->upgrade2Button->setIcon(QIcon(up2.icon));
        ui->upgrade3Button->setIcon(QIcon(up3.icon));
        if (game->points < up3.cost)
            ui->upgrade3Button->setDisabled(true);
        if (pwdType == Tower) {
                ui->passwordLabelValue->setText(tower->password);
                ui->upgradeLabelValue->setText(tower->passwordUpgrades);
                ui->upgrade1Button->setText(up1.name + "\n" + QString::number(up1.cost) + " Points");
                ui->upgrade2Button->setText(up2.name + "\n" + QString::number(up2.cost) + " Points");
                ui->upgrade3Button->setText(up3.name + "\n" + QString::number(up3.cost) + " Points");
        }
    }
    if (pwdType == Master && up1.id != 1) {
        on_upgrade1Button_clicked();
    }
    if (pwdType == Tower) {
        ui->passwordLabelValue->setText(tower->password);
        ui->upgradeLabelValue->setText(tower->passwordUpgrades);
    }
}

UpgradeDialog::~UpgradeDialog() {
    delete ui;
}

void UpgradeDialog::on_upgrade1Button_clicked() {
    upgrade = up1;
    upgradeClicked();
}

void UpgradeDialog::on_upgrade2Button_clicked() {
    upgrade = up2;
    upgradeClicked();
}

void UpgradeDialog::on_upgrade3Button_clicked() {
    upgrade = up3;
    upgradeClicked();
}

void UpgradeDialog::upgradeClicked() {
    QString text;
    text.append("Description: \n");
    text.append(upgrade.description);
    text.append("\n\n");
    text.append("Pros: \n");
    text.append(upgrade.prosDescription);
    text.append("\n\n");
    text.append("Cons: \n");
    text.append(upgrade.consDescription);
    text.append("\n\n");
    text.append("Fact: \n");
    text.append(upgrade.funSecurityFact);
    ui->descriptionLabel->setText(text);
    if (pwdType == Master) {
        game->upgradePassword(upgrade);
        ui->passwordLabelValue->setText(game->masterPassword);
        ui->upgradeLabelValue->setText(game->masterPasswordUpgrades);
    } else if (pwdType == Tower) {
        tower->upgradePassword(upgrade);
        ui->passwordLabelValue->setText(tower->password);
        ui->upgradeLabelValue->setText(tower->passwordUpgrades);
    }

}

void UpgradeDialog::on_buttonBox_accepted() {
    if (upgrade.id != -1) {
        if (pwdType == Master) {
            game->confirmUpgrade(upgrade);
        }
        else if (pwdType == Tower) {
            game->points -= upgrade.cost;
            game->updatePoints();
            tower->confirmUpgrade(upgrade);
        }
    }
}

