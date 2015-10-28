#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "qcustomplot.h" 


enum shape_enum {None,MaxflatHalfband, EllipticHalfband, 
				 Butterworth, Chebyshev, Elliptic,  
				 MaxflatFIR, GaussianFIR, RemezFIR, 
				 RaisedCosine, VariableAllpass, VariableShelf, Notch50,
				 NotchIIR, CutBoost, Shelf, Cic, Comb, 
				 CombAllpass, RootRaisedCosine};

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
  void BChanged();
  void CChanged(); 
  void EChanged(); 
  void FChanged(); 
  void FHChanged(); 
  void RCChanged(); 
  void RRCChanged(); 
  void EHChanged(); 
  void RChanged(); 
  void NChanged(); 
  void CBChanged(); 
  void graphPressEvent(QMouseEvent *event);
  void graphMoveEvent(QMouseEvent *event);

private:
  int pts;
  double pass_edge;
  double trans;
  double stop_dBs;
  double alpha;
  int taps;
  int order;
  int bits;
  std::string shape;
  double* w;

  QCPGraph*  Butterworth_on;
  QCPGraph*  Chebyshev_on;
  QCPGraph*  Elliptic_on;
  QCPGraph*  MaxflatFIR_on;
  QCPGraph*  MaxflatHalfband_on;
  QCPGraph*  RaisedCosine_on;
  QCPGraph*  RootRaisedCosine_on;
  QCPGraph*  EllipticHalfband_on;
  QCPGraph*  Remez_on;
  QCPGraph*  NotchIIR_on;
  QCPGraph*  CutBoost_on;
  int graph_counter;

  QPoint dragStartPosition;
  QCPGraph* GetPtr();

};

#endif // MAINWINDOW_H
