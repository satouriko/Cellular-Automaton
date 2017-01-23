#ifndef ARENAWIDGET_H
#define ARENAWIDGET_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class ArenaWidget;
}

class ArenaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArenaWidget(QWidget *parent = 0);
    ~ArenaWidget();
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
private:
    Ui::ArenaWidget *ui;
signals:
    void onDraw(QPainter *painter);
    void onPaintCell(int x, int y, bool);
};

#endif // ARENAWIDGET_H
