#include "screenshotthread.h"
#include "src/database/dbmanager.h"
#include "src/ui/gridwidget.h"

#include <QGuiApplication>
#include <QScreen>
#include <QBuffer>

ScreenshotThread::ScreenshotThread(GridWidget *gridWidget)
    : gridWidget_(gridWidget)
{
    QVector<ScreenshotInfo> screens = DBManager::instance().selectAllScreenshots();

    for (int i = screens.count() - 1; i >= 0; --i) {
        gridWidget_->pushScreenToGrid(this->byteArrayToPixmap(screens[i].data),
                                      screens[i].similarity, false);
    }

    if (!screens.isEmpty()) {
        previousScreen_ = this->byteArrayToPixmap(screens.last().data);
    }
}

QPixmap ScreenshotThread::takeScreenshot() const
{
    return QGuiApplication::primaryScreen()->grabWindow(0);
}

qint16 ScreenshotThread::compareWithPrevious(const QPixmap &currentScreen) const
{
    QImage previousImage = previousScreen_.toImage();
    QImage currentImage = currentScreen.toImage();

    qint32 width = previousImage.width();
    qint32 height = previousImage.height();
    qint64 differentPixels = 0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QRgb previousPixel = previousImage.pixel(x, y);
            QRgb currentPixel = currentImage.pixel(x, y);
            if (previousPixel != currentPixel) {
                ++differentPixels;
            }
        }
    }
    int totalPixels = width * height;
    double similarity = (1.0 - (static_cast<double>(differentPixels) / totalPixels)) * 100.0;
    return static_cast<qint16>(similarity);
}

QByteArray ScreenshotThread::pixmapToByteArray(const QPixmap &pixmap) const
{
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");
    return data;
}

QPixmap ScreenshotThread::byteArrayToPixmap(const QByteArray &byteArray) const
{
    QPixmap pixmap;
    pixmap.loadFromData(byteArray, "PNG");
    return pixmap;
}

void ScreenshotThread::run()
{
    QPixmap currentScreen = this->takeScreenshot();
    qint16 similarity = this->compareWithPrevious(currentScreen);

    gridWidget_->pushScreenToGrid(currentScreen, similarity, true);
    DBManager::instance().insertScreenshot(ScreenshotInfo(currentScreen.cacheKey(), similarity,
                                                          this->pixmapToByteArray(currentScreen)));
    previousScreen_ = currentScreen;
}
