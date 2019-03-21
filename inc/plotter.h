#ifndef PLOTTER_H
#define PLOTTER_H

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