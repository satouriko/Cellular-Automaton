#ifndef ARENAWIDGET_H
#define ARENAWIDGET_H

#include <QWidget>

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
private:
    Ui::ArenaWidget *ui;
signals:
    void onDraw(QPainter *painter);
};

#endif // ARENAWIDGET_H
