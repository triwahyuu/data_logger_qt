#include "plotter.h"
#include <QDebug>
#include <iostream>

RealTimePlot::RealTimePlot(int n_plot, int interval, QWidget *parent)
    : QCustomPlot(parent), _n_plot(n_plot), _interval(interval)
{
    for(int i = 0; i < _n_plot; i++){
        addGraph();
        graph(i)->setPen(QPen(QColor::fromHsv(int(0.618033988749895*360*i/_n_plot), 255, 255, 255)));
    }

    xAxis->setRange(0, 5);
    yAxis->setRange(-1.1, 1.1);
    connect(xAxis, SIGNAL(rangeChanged(QCPRange)), xAxis2, SLOT(setRange(QCPRange)));
    connect(yAxis, SIGNAL(rangeChanged(QCPRange)), yAxis2, SLOT(setRange(QCPRange)));
    axisRect()->setupFullAxesBox();
}

void RealTimePlot::updateData(QVector<double> ys)
{
    double t = elapsed();
    for(int i = 0; i < _n_plot; i++){
        graph(i)->addData(t, ys[i]);
    }

    graph()->rescaleValueAxis(true);
    replot();
    xAxis->setRange(t, 5, Qt::AlignRight);
    _n++;
}

void RealTimePlot::updateData(double y)
{
    updateData(QVector<double>({y}));
}

double RealTimePlot::elapsed()
{
    return (double)(_n*_interval)/1000.0;
}
