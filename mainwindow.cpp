#include "mainwindow.h"
#include <QLayout>
#include "panel.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new Panel(this));
    mainLayout->addWidget(new Panel(this));
    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{

}
