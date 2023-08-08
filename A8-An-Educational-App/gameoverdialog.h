#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>

namespace Ui {
class GameOverDialog;
}

class GameOverDialog : public QDialog
{
    Q_OBJECT

public:
    int points;
    int round;
    QString plain;
    QString upgraded;
    explicit GameOverDialog(QWidget *parent = nullptr, int points = 1, int round = 50, QString plain = "", QString upgraded = "");
    ~GameOverDialog();
public slots:
    void onButtonPressed();
signals:
    void gameCompleted();
private:
    Ui::GameOverDialog *ui;
};

#endif // GAMEOVERDIALOG_H
