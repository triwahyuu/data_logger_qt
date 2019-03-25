#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPortInfo>
#include <algorithm>
#include <QDebug>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupUI();
    setupPlotter();
    fillPortParam();
    listPortInfo();

    m_serial = new SerialCore();

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
    plot = new RealTimePlot(3, interval);
    plotLayout->addWidget(plot);

    plot_timer = new QTimer();
    plot_timer->setInterval(interval);
    connect(plot_timer, SIGNAL(timeout()), this, SLOT(updatePlot()));
}

void MainWindow::setupUI()
{
    ui->receiveText->setReadOnly(true);
    ui->hSplitter->setSizes(QList<int>({210, 0})); // set config box horizontal size, the rest for plotter

    // just a test
    ui->receiveText->setPlainText("10, 10\n10\n");
    ui->receiveText->moveCursor(QTextCursor::End);
    ui->receiveText->insertPlainText("a\na\na\na\n\n\na\na\na\n\na\na\na");

    connect(ui->actionBtn, SIGNAL(clicked()), this, SLOT(actionBtnCallback()));
    connect(ui->deviceCombo, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this](int idx){
        m_serialSetting.portName = ui->deviceCombo->itemData(idx).toString();
    });
    connect(ui->baudComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this](int idx){
        m_serialSetting.baudRate = static_cast<QSerialPort::BaudRate>(ui->baudComboBox->itemData(idx).toInt());
    });
    connect(ui->parityComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this](int idx){
        m_serialSetting.parity = static_cast<QSerialPort::Parity>(ui->parityComboBox->itemData(idx).toInt());
    });
    connect(ui->bitComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this](int idx){
        m_serialSetting.dataBits = static_cast<QSerialPort::DataBits>(ui->bitComboBox->itemData(idx).toInt());
    });
    connect(ui->stopComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this](int idx){
        m_serialSetting.stopBits = static_cast<QSerialPort::StopBits>(ui->stopComboBox->itemData(idx).toInt());
    });
}

void MainWindow::listPortInfo()
{
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos){
        ui->deviceCombo->addItem(info.portName());
    }
}

void MainWindow::fillPortParam()
{
    ui->baudComboBox->addItem(QStringLiteral("4800"), QSerialPort::Baud4800);
    ui->baudComboBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudComboBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudComboBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudComboBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudComboBox->setCurrentIndex(1);

    ui->bitComboBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->bitComboBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->bitComboBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->bitComboBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->bitComboBox->setCurrentIndex(3);

    ui->parityComboBox->addItem(tr("None"), QSerialPort::NoParity);
    ui->parityComboBox->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->parityComboBox->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->parityComboBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->parityComboBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->stopComboBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    ui->stopComboBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    m_serialSetting.baudRate = QSerialPort::Baud9600;
    m_serialSetting.dataBits = QSerialPort::Data8;
    m_serialSetting.parity = QSerialPort::NoParity;
    m_serialSetting.stopBits = QSerialPort::OneStop;

    // ui->flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    // ui->flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    // ui->flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
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

void MainWindow::connectBtnCallback()
{
    if(m_serial->isOpened()){
        m_serial->close();
        ui->connectBtn->setText("Connect");
    }
    else{
        m_serial->open();
        ui->connectBtn->setText("Disconnect");
    }
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