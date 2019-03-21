#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <iostream>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setting up ui
    ui->receiveText->setReadOnly(true);
    ui->hSplitter->setSizes(QList<int>({210, 0})); // set config box horizontal size, the rest for plotter

    connect(ui->actionBtn, SIGNAL(clicked()), this, SLOT(actionBtnCallback()));

    // just a test
    ui->receiveText->setPlainText("10, 10\n10\n");
    ui->receiveText->moveCursor(QTextCursor::End);
    ui->receiveText->insertPlainText("a\na\na\na\n\n\na\na\na\n\na\na\na");

    // setting up plot
    setupPlotter();
    gen = std::mt19937(rd());
    rand_uniform = std::uniform_int_distribution<>(-1000, 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPlotter()
{
    plotLayout = new QVBoxLayout(ui->plotWidget);
    plotLayout->setContentsMargins(0,0,0,0);
    plot = new RealTimePlot(3);
    plotLayout->addWidget(plot);

    plot_timer = new QTimer();
    plot_timer->setInterval(interval);
    connect(plot_timer, SIGNAL(timeout()), this, SLOT(updatePlot()));
}

void MainWindow::actionBtnCallback()
{
    if(_plot_paused){
        plot_timer->start(interval);
    }
    else{
        plot_timer->stop();
    }
    ui->actionBtn->setText(_plot_paused ? "Stop":"Start");
    _plot_paused ^= true;
}

void MainWindow::updatePlot()
{
    const int16_t freq = 2;
    double t = plot->elapsed();
    double y1 = sin(2*M_PI*freq*t);
    double y2 = 0;
    for(int i = 1; i < 57; i += 2) y2 += sin(i*M_PI*t)/i;
    y3 += rand_uniform(gen)/10000.0;
    
    plot->updateData(QVector<double>({y1, y2, y3}));
}