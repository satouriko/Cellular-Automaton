#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cellcar.h"
#include "gamecontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void redraw();
private:
    Ui::MainWindow *ui;
    GameController *gc;
};

#endif // MAINWINDOW_H
