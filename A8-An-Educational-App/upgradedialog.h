#ifndef UPGRADEDIALOG_H
#define UPGRADEDIALOG_H

#include <QDialog>
#include "game.h"
#include "globals.h"
#include "passwordtower.h"

namespace Ui {
/**
 * @brief UpgradeDialog::UpgradeDialog
 * Displaying upgrade content for the upgrade window
 * handle both masterpassword nad tower password upgrade
 * show 12 different types of upgrade in random order
 * as the game goes on, upgrade with more complexity will appear
 */
class UpgradeDialog;
}

class UpgradeDialog : public QDialog {
    Q_OBJECT

public:
    explicit UpgradeDialog(Game* game, PasswordType pwdType, int towerId, QWidget *parent = nullptr);
    ~UpgradeDialog();

private slots:
    void on_upgrade1Button_clicked();
    void on_upgrade2Button_clicked();
    void on_upgrade3Button_clicked();
    void on_buttonBox_accepted();
    void upgradeClicked();

private:
    Ui::UpgradeDialog *ui;
    Upgrade upgrade, up1, up2, up3;
    Game* game;
    PasswordTower* tower;
    PasswordType pwdType;
};

#endif // UPGRADEDIALOG_H
