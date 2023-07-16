#include "gridwidget.h"

GridWidget::GridWidget(QWidget *parent)
    : QWidget{parent},
      screensGrid_(new QGridLayout)
{
    QGridLayout *wrapperGrid = new QGridLayout;
    wrapperGrid->addLayout(screensGrid_, 0, 0);
    QSpacerItem *spacerRight = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacerBottom = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    wrapperGrid->addItem(spacerRight, 0, 1);
    wrapperGrid->addItem(spacerBottom, 1, 0);
    this->setLayout(wrapperGrid);
}
