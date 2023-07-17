#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QObject>

class Constants
{
public:
    Constants();

    static const qint32 INTERVAL_IN_SEC;
    static const qint16 COUNT_ELEMENT_IN_ROW;

    static const qint32 SCALED_SCREEN_WIDTH;
    static const qint32 SCALED_SCREEN_HEIGHT;

    static const qint32 MAINWINDOW_WIDTH;
    static const qint32 MAINWINDOW_HEIGHT;
};

#endif // CONSTANTS_H
