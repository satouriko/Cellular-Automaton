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
    connect(this->gc, SIGNAL(onIncreaseCC()), this, SLOT(increaseCC()));
    connect(this->gc, SIGNAL(onRedraw()), this, SLOT(redraw()));
    connect(ui->widget, SIGNAL(onPaintCell(int,int,bool)), this, SLOT(addCell(int,int,bool)));

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

void MainWindow::addCell(int x, int y, bool add)
{
    if(ui->CarFactoryRadioButton->isChecked()) {
        this->gc->cfFactory(x, y, ui->gf_spinBox->value(), ui->minSpeed_spinBox->value(), ui->maxSpeed_spinBox->value());
    }
    else if(ui->CarCollectorRadioButton->isChecked()) {
        this->gc->ccFactory(x, y);
    }
    else {
        if(!add)
            this->gc->blockDistroyer(x, y);
        else {
            char t = (ui->LBrushRadioButton->isChecked()) ? 'L' : (
                     (ui->RBrushRadioButton->isChecked()) ? 'R' : (
                     (ui->lBrushRadioButton->isChecked()) ? 'l' : (
                     (ui->rBrushRadioButton->isChecked()) ? 'r' : '1' )));
            this->gc->blockFactory(x, y, t);
        }
    }
    ui->widget->repaint();
}

void MainWindow::on_LBrushRadioButton_clicked()
{
    ui->RBrushRadioButton->setChecked(false);
    ui->CarFactoryRadioButton->setChecked(false);
    ui->CarCollectorRadioButton->setChecked(false);
    ui->_1BrushRadioButton->setChecked(false);
    ui->lBrushRadioButton->setChecked(false);
    ui->rBrushRadioButton->setChecked(false);
}

void MainWindow::on_RBrushRadioButton_clicked()
{
    ui->LBrushRadioButton->setChecked(false);
    ui->CarFactoryRadioButton->setChecked(false);
    ui->CarCollectorRadioButton->setChecked(false);
    ui->_1BrushRadioButton->setChecked(false);
    ui->lBrushRadioButton->setChecked(false);
    ui->rBrushRadioButton->setChecked(false);
}

void MainWindow::on_CarFactoryRadioButton_clicked()
{
    ui->RBrushRadioButton->setChecked(false);
    ui->LBrushRadioButton->setChecked(false);
    ui->CarCollectorRadioButton->setChecked(false);
    ui->_1BrushRadioButton->setChecked(false);
    ui->lBrushRadioButton->setChecked(false);
    ui->rBrushRadioButton->setChecked(false);
}

void MainWindow::on_CarCollectorRadioButton_clicked()
{
    ui->LBrushRadioButton->setChecked(false);
    ui->RBrushRadioButton->setChecked(false);
    ui->CarFactoryRadioButton->setChecked(false);
    ui->_1BrushRadioButton->setChecked(false);
    ui->lBrushRadioButton->setChecked(false);
    ui->rBrushRadioButton->setChecked(false);
}

void MainWindow::on__1BrushRadioButton_clicked()
{
    ui->LBrushRadioButton->setChecked(false);
    ui->RBrushRadioButton->setChecked(false);
    ui->CarFactoryRadioButton->setChecked(false);
    ui->CarCollectorRadioButton->setChecked(false);
    ui->lBrushRadioButton->setChecked(false);
    ui->rBrushRadioButton->setChecked(false);
}

void MainWindow::on_lBrushRadioButton_clicked()
{
    ui->LBrushRadioButton->setChecked(false);
    ui->RBrushRadioButton->setChecked(false);
    ui->CarFactoryRadioButton->setChecked(false);
    ui->CarCollectorRadioButton->setChecked(false);
    ui->_1BrushRadioButton->setChecked(false);
    ui->rBrushRadioButton->setChecked(false);
}

void MainWindow::on_rBrushRadioButton_clicked()
{
    ui->LBrushRadioButton->setChecked(false);
    ui->RBrushRadioButton->setChecked(false);
    ui->CarFactoryRadioButton->setChecked(false);
    ui->CarCollectorRadioButton->setChecked(false);
    ui->_1BrushRadioButton->setChecked(false);
    ui->lBrushRadioButton->setChecked(false);
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->pushButton_4->text() == "Pause")
        emit on_pushButton_4_clicked();
    this->gc->clearBlock();
    ui->widget->repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->pushButton_4->text() == "Pause")
        emit on_pushButton_4_clicked();
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

void MainWindow::on_pushButton_5_clicked()
{
    if(ui->pushButton_4->text() == "Pause")
        emit on_pushButton_4_clicked();
    this->gc->clearCarFactories();
    ui->widget->repaint();
}

void MainWindow::increaseCC() {
    ui->spinBox->setValue(ui->spinBox->value() + 1);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->spinBox->setValue(0);
}
