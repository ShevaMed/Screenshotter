#ifndef SCREENSHOTWORKER_H
#define SCREENSHOTWORKER_H

#include <QObject>
#include <QPixmap>

class GridWidget;

class ScreenshotWorker : public QObject
{
    Q_OBJECT

public:
    ScreenshotWorker(GridWidget *gridWidget);

public slots:
    void doWork();

signals:
    void workFinished();

private:
    QPixmap takeScreenshot() const;
    qint16 compareScreenshots(const QPixmap &previousScreen, const QPixmap &currentScreen) const;

    QByteArray pixmapToByteArray(const QPixmap& pixmap) const;

private:
    GridWidget *gridWidget_;
};

#endif // SCREENSHOTWORKER_H
