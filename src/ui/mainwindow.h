#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GridWidget;
class ScreenshotThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initWindow();
    void timerTimeout();
    void updateTimerLabel();

private:
    Ui::MainWindow *ui;
    QPushButton *startStopButton_;
    QLabel *timerLabel_;
    GridWidget *gridWidget_;
    ScreenshotThread *screenshotThread_;
    QTimer *timer_;
    const qint16 INTERVAL;
    qint16 secondsLeft_;
};
#endif // MAINWINDOW_H
