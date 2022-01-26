#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_symbol.h"

#include "pointgenerator.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private: // methods
    void start();
    void stop();
    void pause();
    void appendNewPoint(float x, float y);

private: // members
    Ui::MainWindow *ui;
    QwtPlot *m_plot;
    QwtPlotCurve m_curve;
    QwtSymbol *m_symbol;
    QPolygonF m_points;

    QScopedPointer<PointGenerator> m_pointGenerator;
};
#endif // MAINWINDOW_H
