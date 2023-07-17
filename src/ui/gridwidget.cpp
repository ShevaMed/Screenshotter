#include "gridwidget.h"
#include "src/screenlogic/screenshotinfo.h"
#include "src/database/dbmanager.h"
#include "src/config/constants.h"

#include <QLabel>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>

GridWidget::GridWidget(QWidget *parent)
    : QWidget{parent},
      screensGrid_(new QGridLayout)
{
    this->initWidget();

    QVector<ScreenshotInfo> screens = DBManager::instance().selectAllScreenshots();

    for (qint32 i = screens.count() - 1; i >= 0; --i) {
        this->pushScreenToGrid(this->byteArrayToPixmap(screens[i].data),
                                      screens[i].similarity, false);
    }

    if (!screens.isEmpty()) {
        previousScreen_ = this->byteArrayToPixmap(screens.last().data);
    }
}

QPixmap GridWidget::getPreviousScreen() const
{
    return previousScreen_;
}

void GridWidget::setPreviousScreen(QPixmap screen)
{
    previousScreen_ = screen;
}

void GridWidget::pushScreenToGrid(const QPixmap &screen, qint16 similarity, bool pushFront)
{
    QLabel *screenLabel = new QLabel(this->parentWidget());
    QLabel *textLabel = new QLabel(QString::number(similarity) + '%', screenLabel);

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setColor(Qt::black); // border color
    shadowEffect->setBlurRadius(5);    // border blur radius
    shadowEffect->setOffset(1, 1);     // border offset

    textLabel->setGraphicsEffect(shadowEffect);
    textLabel->setStyleSheet("font-size: 30px; color: white;");

    QPixmap scaledScreen = screen.scaled(Constants::SCALED_SCREEN_WIDTH, Constants::SCALED_SCREEN_HEIGHT,
                                         Qt::KeepAspectRatio, Qt::SmoothTransformation);
    screenLabel->setPixmap(scaledScreen);

    if (pushFront) {
        this->pushFrontWidgetToGrid(screenLabel);
    } else {
        this->pushBackWidgetToGrid(screenLabel);
    }
}

void GridWidget::pushFrontWidgetToGrid(QWidget *widget)
{
    qint32 count = screensGrid_->count();

    for (qint32 i = count - 1; i >= 0; --i) {
        qint32 row = i / Constants::COUNT_ELEMENT_IN_ROW;
        qint32 column = i % Constants::COUNT_ELEMENT_IN_ROW;
        QLayoutItem *currentItem = screensGrid_->itemAtPosition(row, column);

        row = (i + 1) / Constants::COUNT_ELEMENT_IN_ROW;
        column = (i + 1) % Constants::COUNT_ELEMENT_IN_ROW;
        screensGrid_->addWidget(currentItem->widget(), row, column);
    }
    screensGrid_->addWidget(widget, 0, 0);
}

void GridWidget::pushBackWidgetToGrid(QWidget *widget)
{
    qint32 count = screensGrid_->count();
    qint32 row = count / Constants::COUNT_ELEMENT_IN_ROW;
    qint32 column = count % Constants::COUNT_ELEMENT_IN_ROW;
    screensGrid_->addWidget(widget, row, column);
}

QPixmap GridWidget::byteArrayToPixmap(const QByteArray &byteArray) const
{
    QPixmap pixmap;
    pixmap.loadFromData(byteArray, "PNG");
    return pixmap;
}

void GridWidget::initWidget()
{
    QGridLayout *wrapperGrid = new QGridLayout;
    wrapperGrid->addLayout(screensGrid_, 0, 0);
    QSpacerItem *spacerRight = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacerBottom = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    wrapperGrid->addItem(spacerRight, 0, 1);
    wrapperGrid->addItem(spacerBottom, 1, 0);
    this->setLayout(wrapperGrid);
}
