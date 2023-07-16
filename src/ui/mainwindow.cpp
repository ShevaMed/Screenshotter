#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridwidget.h"
#include "src/screenlogic/screenshotworker.h"

#include <QThread>
#include <QScrollArea>
#include <QString>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      startStopButton_(new QPushButton("Start", this)),
      timerLabel_(new QLabel(this)),
      gridWidget_(new GridWidget(this)),
      timer_(new QTimer(this)),
      INTERVAL(5),
      secondsLeft_(INTERVAL)
{
    ui->setupUi(this);
    this->initWindow();

    timer_->setInterval(1000);
    this->updateTimerLabel();

    connect(startStopButton_, &QPushButton::clicked, this, [this]()
    {
        if (timer_->isActive()) {
            timer_->stop();
            startStopButton_->setText("Start");
        } else {
            timer_->start();
            startStopButton_->setText("Stop");
        }
    });

    connect(timer_, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(startStopButton_);
    hLayout->addWidget(timerLabel_);
    //hLayout->addStretch();

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(gridWidget_);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(scrollArea);

    ui->centralwidget->setLayout(vLayout);
    this->setMinimumSize(700, 350);
}

void MainWindow::updateTimerLabel()
{
    timerLabel_->setText(QString("%1:%2").arg(secondsLeft_ / 60, 1, 10, QLatin1Char('0'))
                         .arg(secondsLeft_ % 60, 2, 10, QLatin1Char('0')));
}

void MainWindow::onTimerTimeout()
{
    if (--secondsLeft_ <= 0) {
        secondsLeft_ = INTERVAL;

        screenshotThread_ = new QThread(this);
        screenshotWorker_ = new ScreenshotWorker(gridWidget_);

        connect(screenshotThread_, &QThread::started, screenshotWorker_, &ScreenshotWorker::doWork);
        connect(screenshotWorker_, &ScreenshotWorker::workFinished, screenshotThread_, &QThread::quit);
        connect(screenshotThread_, &QThread::finished, screenshotWorker_, &ScreenshotWorker::deleteLater);

        screenshotThread_->start();
    }
    MainWindow::updateTimerLabel();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (screenshotThread_ && screenshotThread_->isRunning()) {
        screenshotThread_->quit();
        screenshotThread_->wait();
    }
    event->accept();
}

