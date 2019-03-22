#include "plotter.h"

// RealTimePlot::RealTimePlot(int n_plot, int interval, QGraphicsItem *parent, Qt::WindowFlags wFlags):
//     QChart(QChart::ChartTypeCartesian, parent, wFlags),
//     _n_plot(n_plot), 
//     _interval(interval)
// {
//     m_series = QVector<QLineSeries*>(_n_plot);
//     m_axisX = new QValueAxis;
//     m_axisX = new QValueAxis;
//     addAxis(m_axisX, Qt::AlignBottom);
//     // addAxis(m_axisY, Qt::AlignLeft);
//     m_axisX->setTickCount(20);
//     m_axisX->setRange(0, 10);
//     m_axisY->setRange(-1, 1);

//     for(int i = 0; i < _n_plot; i++){
//         m_series[i]->setPen(QPen(QColor::fromHsv(int(0.618033988749895*360*i/(2*_n_plot)), 254, 254, 255)));
//         m_series[i]->append(0, 0);
//         addSeries(m_series[i]);
//         m_series[i]->attachAxis(m_axisX);
//         m_series[i]->attachAxis(m_axisY);
//     }
//     legend()->hide();
//     setAnimationOptions(QChart::AllAnimations);
// }

// RealTimePlot::~RealTimePlot()
// {

// }

// void RealTimePlot::updateData(QVector<double> ys)
// {
//     double t = elapsed();
//     for(int i = 0; i < _n_plot; i++){
//         m_series[i]->append(t, ys[i]);
//     }
    
//     _n++;
// }

// void RealTimePlot::updateData(double y)
// {
//     updateData(QVector<double>({y}));
// }

// double RealTimePlot::elapsed()
// {
//     return (double)(_n*_interval)/1000.0;
// }

RealTimePlot::RealTimePlot(int n_plot, int interval, QWidget *parent)
    : QCustomPlot(parent), _n_plot(n_plot), _interval(interval)
{
    for(int i = 0; i < _n_plot; i++){
        addGraph();
        graph(i)->setPen(QPen(QColor::fromHsv(int(0.618033988749895*360*i/(2*_n_plot)), 254, 254, 255)));
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
