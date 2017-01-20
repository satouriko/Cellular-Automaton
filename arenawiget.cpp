#include "arenawiget.h"
#include "ui_arenawiget.h"

ArenaWiget::ArenaWiget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArenaWiget)
{
    ui->setupUi(this);
}

ArenaWiget::~ArenaWiget()
{
    delete ui;
}
