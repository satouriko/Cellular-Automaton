#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamecontroller.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->settings.updateSettings(ui->safeGapSpinBox->value(), ui->speedLimitSpinBox->value(),
                                  ui->accDoubleSpinBox->value(), ui->fpsSpinBox->value());
    this->gc = new GameController(this->settings);

    connect(ui->widget, SIGNAL(onDraw(QPainter*)), this->gc, SLOT(draw(QPainter*)));
    connect(this->gc, SIGNAL(onRedraw()), this, SLOT(redraw()));
    connect(ui->widget, SIGNAL(onPaintCell(int,int)), this, SLOT(addCell(int,int)));

    this->gc->startLooping();
}

MainWindow::~MainWindow()
{
    delete gc;
    delete ui;
}

void MainWindow::redraw()
{
    ui->widget->repaint();
}

void MainWindow::addCell(int x, int y)
{
    if(ui->CarFactoryRadioButton->isChecked()) {
        this->gc->cfFactory(x, y, ui->gf_spinBox->value(), ui->minSpeed_spinBox->value(), ui->maxSpeed_spinBox->value());
    }
    else {
        char t = (ui->LBrushRadioButton->isChecked()) ? 'L' : 'R';
        this->gc->blockFactory(x, y, t);
    }
    ui->widget->repaint();
}

void MainWindow::on_LBrushRadioButton_clicked()
{
    ui->RBrushRadioButton->setChecked(false);
    ui->CarFactoryRadioButton->setChecked(false);
}

void MainWindow::on_RBrushRadioButton_clicked()
{
    ui->LBrushRadioButton->setChecked(false);
    ui->CarFactoryRadioButton->setChecked(false);
}

void MainWindow::on_pushButton_clicked()
{
    this->gc->clearBlock();
    ui->widget->repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->gc->clearCar();
    ui->widget->repaint();
}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->pushButton_4->text() == "Pause")
    {
        this->gc->stopLooping();
        ui->pushButton_4->setText("Resume");
    }
    else
    {
        this->gc->startLooping();
        ui->pushButton_4->setText("Pause");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    this->settings.updateSettings(ui->safeGapSpinBox->value(), ui->speedLimitSpinBox->value(),
                                  ui->accDoubleSpinBox->value(), ui->fpsSpinBox->value());
    this->gc->updateParams();
}

void MainWindow::on_CarFactoryRadioButton_clicked()
{
    ui->RBrushRadioButton->setChecked(false);
    ui->LBrushRadioButton->setChecked(false);
}

void MainWindow::on_pushButton_5_clicked()
{
    this->gc->clearCarFactories();
    ui->widget->repaint();
}
