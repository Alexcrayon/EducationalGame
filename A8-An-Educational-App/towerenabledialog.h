#ifndef TOWERENABLEDIALOG_H
#define TOWERENABLEDIALOG_H

#include <QDialog>
#include "passwordtower.h"
#include "game.h"

namespace Ui {
class TowerEnableDialog;
}

class TowerEnableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TowerEnableDialog(Game* game, int towerId, QWidget *parent = nullptr);
    ~TowerEnableDialog();

private slots:
    void on_confirm_clicked();
    void on_cancel_clicked();
    void optionClicked();

private:
    Ui::TowerEnableDialog *ui;
    Game* game;
    PasswordTower* tower;
};

#endif // TOWERENABLEDIALOG_H
