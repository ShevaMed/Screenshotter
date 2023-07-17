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
class ScreenshotWorker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initWidget();
    void updateTimerLabel();

private slots:
    void onTimerTimeout();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::MainWindow *ui;

    QPushButton *startStopButton_;
    QLabel *timerLabel_;
    GridWidget *gridWidget_;

    QTimer *timer_;
    qint32 secondsLeft_;

    ScreenshotWorker *screenshotWorker_;
    QThread *screenshotThread_;
};
#endif // MAINWINDOW_H
