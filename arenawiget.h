#ifndef ARENAWIGET_H
#define ARENAWIGET_H

#include <QWidget>

namespace Ui {
class ArenaWiget;
}

class ArenaWiget : public QWidget
{
    Q_OBJECT

public:
    explicit ArenaWiget(QWidget *parent = 0);
    ~ArenaWiget();

private:
    Ui::ArenaWiget *ui;
};

#endif // ARENAWIGET_H
