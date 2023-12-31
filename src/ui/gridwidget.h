#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QLayout>

class GridWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GridWidget(QWidget *parent = nullptr);

    QPixmap getPreviousScreen() const;
    void setPreviousScreen(QPixmap screen);

    void pushScreenToGrid(const QPixmap& screen, qint16 similarity, bool pushFront);
    void pushFrontWidgetToGrid(QWidget *widget);
    void pushBackWidgetToGrid(QWidget *widget);

    QPixmap byteArrayToPixmap(const QByteArray& byteArray) const;

private:
    void initWidget();

private:
    QGridLayout *screensGrid_;
    QPixmap previousScreen_;
};

#endif // GRIDWIDGET_H
