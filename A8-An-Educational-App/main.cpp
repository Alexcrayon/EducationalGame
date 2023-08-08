/*******************************************************************************************************\
* Name: A8-An-Educational-App - Password Tower Defense                                                  *
* Created by: Team Cherry Bits - CS 3505                                                                *
* Team Members: Alex Cao, Jaran Holt, Sam Powel, Spencer Robinson, Camden Yates                         *
* Project completion: April 27, 2022                                                                    *
* Project Description: A cryptography tower defense game, with attackers and towers where you attempt   *
* to survive against enemies. Getting stronger towers depends on learning cybersecurity concepts. As    *
* you progress, you learn more advanced password security strategies that let you survive longer        *
* against the attackers and deal more damage. Collect points to build towers and use passwords to       *
* make the towers stronger.                                                                             *
\*******************************************************************************************************/

#include "mainwindow.h"
#include "gamescreenwidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Game* game = new Game();
    MainWindow w(game);
    return a.exec();
}
