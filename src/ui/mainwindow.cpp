#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScrollArea>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      startStopButton_(nullptr),
      timerLabel_(nullptr),
      screensGrid_(nullptr),
      timer_(new QTimer(this)),
      INTERVAL(60),
      secondsLeft_(INTERVAL)
{
    ui->setupUi(this);

    startStopButton_ = new QPushButton("Start", this);
    timerLabel_ = new QLabel(this);
    screensGrid_ = new QGridLayout;

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(startStopButton_);
    hLayout->addWidget(timerLabel_);
    //hLayout->addStretch();

    QGridLayout *wrapperGrid = new QGridLayout;
    wrapperGrid->addLayout(screensGrid_, 0, 0);
    QSpacerItem *spacerRight = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacerBottom = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    wrapperGrid->addItem(spacerRight, 0, 1);
    wrapperGrid->addItem(spacerBottom, 1, 0);

    QWidget *scrollWidget = new QWidget(this);
    scrollWidget->setLayout(wrapperGrid);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(scrollArea);

    ui->centralwidget->setLayout(vLayout);
    setMinimumSize(700, 350);

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

    connect(timer_, &QTimer::timeout, this, [this]()
    {
        if (--secondsLeft_ <= 0) {
            MainWindow::timerTimeout();
        }
        MainWindow::updateTimerLabel();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerTimeout()
{
    secondsLeft_ = INTERVAL;
}

void MainWindow::updateTimerLabel()
{
    timerLabel_->setText(QString("%1:%2").arg(secondsLeft_ / 60, 1, 10, QLatin1Char('0'))
                                   .arg(secondsLeft_ % 60, 2, 10, QLatin1Char('0')));
}

