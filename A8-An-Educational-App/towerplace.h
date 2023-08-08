#ifndef TOWERPLACE_H
#define TOWERPLACE_H

#include <QObject>
#include <QWidget>
#include <QImage>

/**
 * @brief TowerPlace::TowerPlace
 * The tower place class. Controls the UI elements present for visuals when placing a tower.
 */
class TowerPlace : public QObject
{
    Q_OBJECT
public:
    QImage baseSprite;
    QImage freezeSprite;
    QImage reflectSprite;
    QImage currentSprite;
    QPoint location;
    TowerPlace(int ID);
    int getID();
    void setID(int ID);
public slots:
    void goToMouse(double x, double y);
private:
    int ID;
};

#endif // TOWERPLACE_H
