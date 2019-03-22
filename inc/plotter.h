#ifndef PLOTTER_H
#define PLOTTER_H

// #include <QtCharts/QChart>
// #include <QtCharts/QLineSeries>
// #include <QtCharts/QValueAxis>
// #include <QTimer>

// QT_CHARTS_USE_NAMESPACE

// class RealTimePlot : public QChart
// {
//     Q_OBJECT

// public:
//     RealTimePlot(int n_plot=1, int interval=5, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = 0);
//     virtual ~RealTimePlot();
//     void updateData(double y);
//     void updateData(QVector<double> ys);
//     double elapsed();

// private:
//     uint64_t _n = 0;
//     uint16_t _n_plot;
//     uint16_t _interval;

//     QVector<QLineSeries*> m_series;
//     QValueAxis* m_axisX;
//     QValueAxis* m_axisY;
// };

#include "qcustomplot.h"

class RealTimePlot : public QCustomPlot
{
public:
    RealTimePlot(int n_plot=1, int interval=5, QWidget *parent = nullptr);
    void updateData(double y);
    void updateData(QVector<double> ys);
    double elapsed();

private:
    uint64_t _n = 0;
    uint16_t _n_plot;
    uint16_t _interval;
};

#endif // PLOTTER_H