#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridwidget.h"
#include "src/screenlogic/screenshotworker.h"
#include "src/config/constants.h"

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
      secondsLeft_(Constants::INTERVAL_IN_SEC),
      screenshotWorker_(nullptr),
      screenshotThread_(nullptr)
{
    ui->setupUi(this);
    this->initWidget();

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

void MainWindow::initWidget()
{
    startStopButton_->setFixedSize(300, 40);
    startStopButton_->setStyleSheet("QPushButton { "
                                    "background-color: #254b70;"
                                    "color: #ffffff; font-size: 20px; font-weight: bold;"
                                    "border-radius: 10px; }"
                                    "QPushButton:hover { border: 2px solid black; }"
                                    "QPushButton:pressed { background-color: #9c0000; }");

    timerLabel_->setAlignment(Qt::AlignmentFlag::AlignCenter);
    timerLabel_->setStyleSheet("color: #cc0000; font-size: 25px; font-weight: bold;");

    QHBoxLayout *hLayout = new QHBoxLayout;
    QSpacerItem *spacerLeft= new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacerCenter = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacerRight = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hLayout->addSpacerItem(spacerLeft);
    hLayout->addWidget(startStopButton_);
    hLayout->addSpacerItem(spacerCenter);
    hLayout->addWidget(timerLabel_);
    hLayout->addSpacerItem(spacerRight);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(gridWidget_);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(scrollArea);
    vLayout->addLayout(hLayout);

    ui->centralwidget->setLayout(vLayout);
    this->setFixedSize(Constants::MAINWINDOW_WIDTH, Constants::MAINWINDOW_HEIGHT);
    this->setWindowTitle("Screenshotter");
}

void MainWindow::updateTimerLabel()
{
    timerLabel_->setText(QString("%1:%2").arg(secondsLeft_ / 60, 1, 10, QLatin1Char('0'))
                         .arg(secondsLeft_ % 60, 2, 10, QLatin1Char('0')));
}

void MainWindow::onTimerTimeout()
{
    if (--secondsLeft_ <= 0) {
        secondsLeft_ = Constants::INTERVAL_IN_SEC;

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

