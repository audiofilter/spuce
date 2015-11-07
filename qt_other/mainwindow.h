#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)

#include <QtWidgets/QMainWindow>
#include "qcustomplot.h" 
#include "make_filter.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void setup(QCustomPlot *customPlot);
  void plot2(QCustomPlot *customPlot);
  void plot3(QCustomPlot *customPlot);
  
private:
  Ui::MainWindow *ui;
  QString demoName;
  QCPItemTracer *itemDemoPhaseTracer;

public slots:
  void MChanged();
  void EChanged(); 
  void NChanged(); 
  void CChanged(); 
  void graphPressEvent(QMouseEvent *event);
  void graphMoveEvent(QMouseEvent *event);

private:
  int pts;
  double stop_dBs;
  double alpha;
  int order;
  std::string shape;
  double* w;
  spuce::make_filter LPF;

  QCPGraph*  MaxflatSubband_on;
  QCPGraph*  EllipticSubband_on;
  QCPGraph*  NotchIIR_on;
  QCPGraph*  CutBoost_on;
  int graph_counter;

  QPoint dragStartPosition;
  QCPGraph* GetPtr();

};

#endif // MAINWINDOW_H
