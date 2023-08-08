#ifndef DESCRIPTIONDIALOG_H
#define DESCRIPTIONDIALOG_H

#include <QDialog>
#include "game.h"

namespace Ui {
class DescriptionDialog;
}

class DescriptionDialog : public QDialog {
    Q_OBJECT

public:
    explicit DescriptionDialog(Game* game, PasswordType pwdType, int towerId, QWidget *parent = nullptr);
    ~DescriptionDialog();

private:
    Ui::DescriptionDialog *ui;

};

#endif // DESCRIPTIONDIALOG_H
