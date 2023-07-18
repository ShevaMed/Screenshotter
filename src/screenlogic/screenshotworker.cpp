#include "screenshotworker.h"
#include "src/screenlogic/screenshotinfo.h"
#include "src/database/dbmanager.h"
#include "src/ui/gridwidget.h"
#include "src/ui/mainwindow.h"

#include <QGuiApplication>
#include <QScreen>
#include <QBuffer>

ScreenshotWorker::ScreenshotWorker(GridWidget *gridWidget)
    : gridWidget_(gridWidget)
{
}

void ScreenshotWorker::doWork()
{
    QPixmap currentScreen = this->takeScreenshot();
    QPixmap previousScreen = gridWidget_->getPreviousScreen();
    qint16 similarity = (previousScreen.isNull()) ? 0 : this->compareScreenshots(previousScreen, currentScreen);

    gridWidget_->pushScreenToGrid(currentScreen, similarity, true);
    DBManager::instance().insertScreenshot(ScreenshotInfo(currentScreen.cacheKey(), similarity,
                                                          this->pixmapToByteArray(currentScreen)));
    gridWidget_->setPreviousScreen(currentScreen);

    emit workFinished();
}

QPixmap ScreenshotWorker::takeScreenshot() const
{
    return QGuiApplication::primaryScreen()->grabWindow(0);
}

qint16 ScreenshotWorker::compareScreenshots(const QPixmap &previousScreen, const QPixmap &currentScreen) const
{
    QImage previousImage = previousScreen.toImage();
    QImage currentImage = currentScreen.toImage();

    qint32 minWidth = std::min(previousImage.width(), currentScreen.width());
    qint32 minHeight = std::min(previousImage.height(), currentScreen.height());
    qint64 differentPixels = 0;

    for (qint32 y = 0; y < minHeight; ++y) {
        for (qint32 x = 0; x < minWidth; ++x) {
            QRgb previousPixel = previousImage.pixel(x, y);
            QRgb currentPixel = currentImage.pixel(x, y);
            if (previousPixel != currentPixel) {
                ++differentPixels;
            }
        }
    }
    qint32 maxWidth = std::max(previousImage.width(), currentScreen.width());
    qint32 maxHeight = std::max(previousImage.height(), currentScreen.height());
    qint64 totalPixels = maxWidth * maxHeight;
    double similarity = (1.0 - (static_cast<double>(differentPixels) / totalPixels)) * 100.0;
    return static_cast<qint16>(similarity);
}

QByteArray ScreenshotWorker::pixmapToByteArray(const QPixmap &pixmap) const
{
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");
    return data;
}
