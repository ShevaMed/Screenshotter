#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void timerTimeout();
    void updateTimerLabel();

private:
    Ui::MainWindow *ui;
    QPushButton *startStopButton_;
    QLabel *timerLabel_;
    QGridLayout *screensGrid_;
    QTimer *timer_;
    const qint16 INTERVAL;
    qint16 secondsLeft_;
};
#endif // MAINWINDOW_H
