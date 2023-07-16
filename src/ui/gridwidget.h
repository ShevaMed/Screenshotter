#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QLayout>

class GridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridWidget(QWidget *parent = nullptr);

signals:

private:
    QGridLayout *screensGrid_;
};

#endif // GRIDWIDGET_H
