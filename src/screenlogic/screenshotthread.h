#ifndef SCREENSHOTTHREAD_H
#define SCREENSHOTTHREAD_H

#include <QThread>
#include <QPixmap>

class GridWidget;

class ScreenshotThread : public QThread
{
    Q_OBJECT

public:
    ScreenshotThread(GridWidget *gridWidget);

private:
    QPixmap takeScreenshot() const;
    qint16 compareWithPrevious(const QPixmap& currentScreen) const;

    QByteArray pixmapToByteArray(const QPixmap& pixmap) const;
    QPixmap byteArrayToPixmap(const QByteArray& byteArray) const;

protected:
    void run() override;

private:
    QPixmap previousScreen_;
    GridWidget *gridWidget_;
};

#endif // SCREENSHOTTHREAD_H
