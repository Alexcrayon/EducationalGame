#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QShowEvent>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief MainWindow::MainWindow
 * Main view outside the game screen to display and control other UI elements
 *
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(Game* game, QWidget *parent = nullptr);
    ~MainWindow();
    Game* game;

private slots:
    void on_startGame_clicked();
    void setUpHeldTower();
    void reactivateButtons();
    void on_round_end();
    void on_currency_change(int newCurrency);
    void onPasswordUpgrade();
    void on_lives_change(int newLives);
    void gameClose();
    void updatePointsValue();

public slots:

signals:
    void gameStart();

private:
    Ui::MainWindow *ui;
    void onGameOver();

};
#endif // MAINWINDOW_H
