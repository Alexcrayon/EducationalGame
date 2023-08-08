#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <game.h>
/**
 * @brief ContactListener::ContactListener contact listenter for the game, used for listening collision between attacker class and bullet class
 * @param parent
 */
class ContactListener:  public QObject, public b2ContactListener
{
    //Q_OBJECT
public:
    ContactListener(QObject *parent = nullptr);

    virtual void BeginContact(b2Contact* cp) override;
};

#endif // CONTACTLISTENER_H
