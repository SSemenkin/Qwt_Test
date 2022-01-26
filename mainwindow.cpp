#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_plot(new QwtPlot(this)),
      m_symbol(new QwtSymbol(QwtSymbol::Style::Ellipse, Qt::blue, Qt::NoPen, QSize(8,8))),
      m_pointGenerator(new PointGenerator)
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(m_plot);

    m_plot->setAxisScale(QwtPlot::xBottom, 0, 100);
    m_plot->setAxisScale(QwtPlot::yLeft, 0, 100);

    m_curve.setPen(QPen(Qt::NoPen));
    m_curve.setRenderHint(QwtPlotItem::RenderAntialiased);
    m_curve.setSymbol(m_symbol);

    m_curve.attach(m_plot);


    QObject::connect(ui->start, &QPushButton::clicked, this, &MainWindow::start);
    QObject::connect(ui->stop,  &QPushButton::clicked, this, &MainWindow::stop);
    QObject::connect(ui->pause, &QPushButton::clicked, this, &MainWindow::pause);
    QObject::connect(m_pointGenerator.data(), &PointGenerator::newPoint, this, &MainWindow::appendNewPoint);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_symbol;
}

void MainWindow::start()
{
    m_pointGenerator->start();
}

void MainWindow::stop()
{
    m_pointGenerator->stop();
    m_points.clear();
    m_curve.setSamples(m_points);
    m_plot->replot();
}

void MainWindow::pause()
{
    m_pointGenerator->stop();
}

void MainWindow::appendNewPoint(float x, float y)
{
    qDebug() << "Point " << x << y;
    m_points << QPointF(x, y);
    m_curve.setSamples(m_points);
    m_plot->replot();
}

