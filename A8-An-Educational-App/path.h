#ifndef PATH_H
#define PATH_H

#include <string>
#include <vector>
#include <QPoint>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
using std::vector;
using std::string;

/**
 * @brief Path::Path
 * The path class. Used to know where in the world the path is when having attackers follow it and towers not get too close to it.
 */
class Path : public QObject {
    Q_OBJECT
public:
    Path(QObject *parent = nullptr);
    QPoint getPosition(double percent);
    double getPathDistance(QPoint location);

    vector<QPoint> getAllPoints();
signals:
    void loadPath();

private:
    QFile pathToFollow;
    //QTextStream in;
    string readLine;
    vector<QPoint> points;
    void showDebugOutput();
    double getLength();
    double getDistanceForPoint(QPoint pointA, QPoint pointB);

};

#endif // PATH_H
