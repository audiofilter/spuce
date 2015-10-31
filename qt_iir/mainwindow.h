#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "qcustomplot.h" 

enum shape_enum {None, Butterworth, Chebyshev, Chebyshev2, Elliptic};

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
  void BoxChecked(bool);
  void BChanged();
  void CChanged(); 
  void C2Changed(); 
  void EChanged(); 
  void graphPressEvent(QMouseEvent *event);
  void graphMoveEvent(QMouseEvent *event);
  void updatePlot();

private:
  int pts;
  double pass_edge;
  double trans;
  double stop_dBs;
  int order;
  std::string shape;
  double* w;

  QCPGraph*  Butterworth_on;
  QCPGraph*  Chebyshev2_on;
  QCPGraph*  Chebyshev_on;
  QCPGraph*  Elliptic_on;
  int graph_counter;

  QPoint dragStartPosition;
  QCPGraph* GetPtr();

};

#endif // MAINWINDOW_H
