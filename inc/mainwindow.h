#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "plotter.h"
#include "serial_core.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updatePlot();
    void actionBtnCallback();
    void connectBtnCallback();

private:
    void setupPlotter();
    void setupUI();
    void listPortInfo();
    void fillPortParam();

    Ui::MainWindow *ui;

    QVBoxLayout *plotLayout;
    RealTimePlot *plot;
    QTimer *plot_timer;

    uint64_t n = 0;
    const int interval = 5; // interval in ms
    double y3 = 0;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> rand_uniform;

    bool _plot_paused = true;
    SerialCore *m_serial;
    SerialCore::Settings m_serialSetting;
};

#endif // MAINWINDOW_H
