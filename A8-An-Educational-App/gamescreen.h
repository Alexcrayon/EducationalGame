#ifndef GAMESCREENWIDGET_H
#define GAMESCREENWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <Box2D/Box2D.h>

class GameScreenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameScreenWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

public slots:
    void updateWorld();

private:
     b2World world;
     QTimer timer;
     //QImage image;
signals:

};

#endif // GAMESCREENWIDGET_H
