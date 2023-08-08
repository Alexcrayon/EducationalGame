/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include <QPoint>
#include "path.h"

/**
 * @brief Path::Path
 * Grabs a path from a .txt file and uses it to determine what path the attackers follow.
 * Also used by the towers to know where the should not be placed.
 * @param parent
 */
Path::Path(QObject *parent) : QObject(parent) {
    pathToFollow.setFileName(":/File/GameResources/NewPath.txt");
    if (!pathToFollow.open(QIODevice::ReadOnly)){
        qDebug() << "fail to read";
        qDebug() << pathToFollow.errorString();
    }
    QTextStream in(&pathToFollow);
    while (!in.atEnd()) {
        QString line = in.readLine();
        string readLine = line.toStdString();
        int spacePlace = readLine.find(" ", 0);
        int x = stoi(readLine.substr(0, spacePlace));
        int y = stoi(readLine.substr(spacePlace, readLine.length() - 1));
        points.push_back(QPoint(x, y));
    }
}

/**
 * @brief Path::getLength
 * Gets the length of the path as a whole. Used to know how far along it is percentage wise.
 * @return
 */
double Path::getLength() {
    double xLength = 0;
    double yLength = 0;
    double length = 0;
    for (size_t i = 1; i < points.size(); i++) {
        xLength = points[i].x() - points[i-1].x();
        yLength = points[i].y() - points[i-1].y();
        length += sqrt((xLength * xLength) + (yLength * yLength));
    }
    return length;
}

/**
 * @brief Path::getPosition
 * Gets exactly where it should be in the world based on the percent travelled along the path.
 * @param percent
 * @return
 */
QPoint Path::getPosition(double percent) {
    // Get what the distance travelled is for each segment.
    double distance = getLength() * percent;
    vector<double> lengthOfSegments;
    for(size_t i = 1; i < points.size(); i++) {
        double xPos = points[i].x() - points[i-1].x();
        double yPos = points[i].y() - points[i-1].y();
        double segLength = sqrt((xPos * xPos) + (yPos * yPos));
        lengthOfSegments.push_back(segLength);
    }

    // Check how many segments have been fully crossed.
    double lengthSegSum = 0;
    int section = 0;
    while (lengthSegSum + lengthOfSegments[section] <= distance) {
        lengthSegSum += lengthOfSegments[section];
        if (lengthSegSum < distance)
            section++;
    }

    // Check how far along its current segment it is.
    double distAlongSeg = distance - lengthSegSum;
    if(section == 0)
        section++;
    double percentAlongSeg = distAlongSeg / lengthOfSegments[section];
    int attackerX = (int) ((points[section - 1].x() * (1-percentAlongSeg)) + (points[section].x() * (percentAlongSeg)));
    int attackerY = (int) ((points[section - 1].y() * (1-percentAlongSeg)) + (points[section].y() * (percentAlongSeg)));
    return QPoint(attackerX, attackerY);
}

/**
 * @brief Path::getAllPoints
 * Gets every point on the path used to mark where it is.
 * @return
 */
vector<QPoint> Path::getAllPoints(){
    return points;
}

/**
 * @brief Path::getPathDistance
 * Gets how far any point is from the closest point on the path. Use for tower placement to determine if the tower is
 * too close to the path at the moment.
 * @param location
 * @return
 */
double Path::getPathDistance(QPoint location)
{
    double shortest = getDistanceForPoint(points[0], location);
    for (QPoint q : points)
    {
        double distance = getDistanceForPoint(q, location);
        if(distance < shortest)
            shortest = distance;
    }

    return shortest;
}

/**
 * @brief Path::getDistanceForPoint
 * Helper function for getting how far any point on the path is from a location in the world.
 * @param pointA
 * @param pointB
 * @return
 */
double Path::getDistanceForPoint(QPoint pointA, QPoint pointB)
{
    double xDist = pointB.x() - pointA.x();
    double yDist = pointB.y() - pointA.y();
    double totalDist = sqrt(xDist * xDist + yDist * yDist);
    return totalDist;
}
