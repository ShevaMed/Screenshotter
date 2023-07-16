#include "gridwidget.h"
#include "src/database/dbmanager.h"

#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPen>

GridWidget::GridWidget(QWidget *parent)
    : QWidget{parent},
      screensGrid_(new QGridLayout),
      COUNT_ELEMENT_IN_ROW(3)
{
    QGridLayout *wrapperGrid = new QGridLayout;
    wrapperGrid->addLayout(screensGrid_, 0, 0);
    QSpacerItem *spacerRight = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacerBottom = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    wrapperGrid->addItem(spacerRight, 0, 1);
    wrapperGrid->addItem(spacerBottom, 1, 0);
    this->setLayout(wrapperGrid);

    QVector<ScreenshotInfo> screens = DBManager::instance().selectAllScreenshots();

    for (int i = screens.count() - 1; i >= 0; --i) {
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

}

void GridWidget::pushFrontWidgetToGrid(QWidget *widget)
{

}

void GridWidget::pushBackWidgetToGrid(QWidget *widget)
{

}

QPixmap GridWidget::byteArrayToPixmap(const QByteArray &byteArray) const
{
    QPixmap pixmap;
    pixmap.loadFromData(byteArray, "PNG");
    return pixmap;
}

