#ifndef SCREENSHOTINFO_H
#define SCREENSHOTINFO_H

#include <QByteArray>

struct ScreenshotInfo
{
    qint64 hash = 0;
    qint16 similarity = 0;
    QByteArray data;

    ScreenshotInfo() = default;
    ScreenshotInfo(qint64 hash, qint16 similarity, QByteArray data) :
        hash(hash), similarity(similarity), data(data)
    {}
};

#endif // SCREENSHOTINFO_H
