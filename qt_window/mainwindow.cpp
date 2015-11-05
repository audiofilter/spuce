// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <cstdlib>
#include <QDebug>
#include <QDesktopWidget>
#include <QMessageBox>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  order = 13;
  alpha = 0.25;
  stop_dBs = 40;
  pts = 250;
  w = new double[pts];
  for (int i=0;i<pts;i++) {
		w[i] = (double)i*i;
  }
  LPF.init(pts);

  Hanning_on = NULL;
  Hamming_on = NULL;
  Blackman_on = NULL;
  Bartlett_on = NULL;
  Chebyshev_on = NULL;
  Kaiser_on = NULL;

  graph_counter = 0;

  ui->setupUi(this);
  //  setGeometry(400, 250, 542, 390);
  setup(ui->customPlot); 

  setWindowTitle("QCustomPlot: "+demoName);
  statusBar()->clearMessage();

  connect(ui->Hanning, SIGNAL(released()), this, SLOT(BChanged()));
  connect(ui->Hamming, SIGNAL(released()), this, SLOT(CChanged()));
  connect(ui->Blackman, SIGNAL(released()), this, SLOT(EChanged()));
  connect(ui->Bartlett, SIGNAL(released()), this, SLOT(FHChanged()));
  connect(ui->Chebyshev, SIGNAL(released()), this, SLOT(GChanged()));
  connect(ui->Kaiser, SIGNAL(released()), this, SLOT(CBChanged()));

  connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), 
					this, SLOT(graphPressEvent(QMouseEvent*)));
  connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), 
					this, SLOT(graphMoveEvent(QMouseEvent*)));


  ui->customPlot->replot();
}
void MainWindow::BChanged() {
  if (Hanning_on==NULL) {
	shape = "Hanning";
	LPF.change_filter(spuce::Hamming);
	Hanning_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(Hanning_on);
	Hanning_on = NULL;
	ui->customPlot->replot();
  }
}
void MainWindow::CChanged() {
  if (Hamming_on==NULL) {
	shape = "Hamming";
	LPF.change_filter(spuce::Hamming);
	Hamming_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(Hamming_on);
	Hamming_on = NULL;
	ui->customPlot->replot();
  }
}
void MainWindow::EChanged() {
  if (Blackman_on==NULL) {
	shape = "Blackman";
	LPF.change_filter(spuce::Blackman);
	Blackman_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(Blackman_on);
	Blackman_on = NULL;
	ui->customPlot->replot();
  }
}
void MainWindow::FHChanged() {
  if (Bartlett_on==NULL) {
	shape = "Bartlett";
	LPF.change_filter(spuce::Bartlett);
	Bartlett_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(Bartlett_on);
	Bartlett_on = NULL;
	ui->customPlot->replot();
  }
}
void MainWindow::GChanged() {
  if (Chebyshev_on==NULL) {
	shape = "Chebyshev";
	LPF.change_filter(spuce::Chebyshev);
	Chebyshev_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(Chebyshev_on);
	Chebyshev_on = NULL;
	ui->customPlot->replot();
  }
}
void MainWindow::CBChanged() {
  if (Kaiser_on==NULL) {
	shape = "Kaiser";
	LPF.change_filter(spuce::Kaiser);
	Kaiser_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(Kaiser_on);
	Kaiser_on = NULL;
	ui->customPlot->replot();
  }
}
/////////////////////////////
QCPGraph* MainWindow::GetPtr() {
  if (shape == "Hamming") return(Hamming_on);
  else if (shape=="Bartlett") return(Bartlett_on);
  else if (shape=="Hanning")	return(Hanning_on);
  else if (shape=="Blackman") return(Blackman_on);
  else if (shape=="Chebyshev") return(Chebyshev_on);
  else if (shape=="Kaiser") return(Kaiser_on);
  else std::cout << "Invalid filter selection " << shape << "\n";
  return(Hanning_on);
}
////////////////////////////////////
void MainWindow::setup(QCustomPlot *customPlot)
{
  demoName = "spuce : Windowing Demo";
  customPlot->legend->setVisible(false);
  customPlot->legend->setFont(QFont("Helvetica",9));
  // set locale to english, so we get english decimal separator:
  customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));

  customPlot->xAxis->setTickLabelRotation(10);
  customPlot->xAxis->setAutoTickCount(4);
  customPlot->xAxis->setNumberFormat("f");
  customPlot->xAxis->setNumberPrecision(2);

  customPlot->xAxis->setRange(0,0.5);
  customPlot->yAxis->setRange(-90,10);
  customPlot->axisRect()->setupFullAxesBox();
}

void MainWindow::plot2(QCustomPlot *customPlot)
{
  QVector<double> x0(pts), y0(pts);

  LPF.update(w);
  double y_inc = 1.0; 
  for (int i=0; i<pts; ++i)   {
    x0[i] = (double)0.5*i/pts;
    y0[i] = y_inc*(w[i]);
  }
  customPlot->graph()->setData(x0, y0);
  customPlot->graph()->setLineStyle(QCPGraph::lsLine); //(QCPGraph::LineStyle)(rand()%5+1));
  customPlot->graph()->setScatterStyle(QCPScatterStyle::ssNone); // (QCP::ScatterStyle)(rand()%9+1));
  QPen graphPen;

  graph_counter++;
  graph_counter = graph_counter%9;
  graphPen.setColor(QColor(Qt::GlobalColor(5+graph_counter)));
  graphPen.setWidthF(2);
  customPlot->graph()->setPen(graphPen);
  customPlot->xAxis->setRange(0,0.5);
  customPlot->yAxis->setRange(-90,10);
  customPlot->legend->setVisible(true);
  //  customPlot->setInteraction(QCustomPlot::iSelectPlottables);
  customPlot->graph()->setName(QString(shape.c_str()));
  customPlot->replot();
}

void MainWindow::plot3(QCustomPlot *customPlot)
{
  QVector<double> x0(pts), y0(pts);

  LPF.update(w);
  double y_inc = 1.0; 
  for (int i=0; i<pts; ++i)   {
    x0[i] = (double)0.5*i/pts;
    y0[i] = y_inc*(w[i]);
  }

  customPlot->graph()->setData(x0, y0);
  customPlot->graph()->setLineStyle(QCPGraph::lsLine); 
  customPlot->graph()->setScatterStyle(QCPScatterStyle::ssNone); // (QCP::ScatterStyle)(rand()%9+1));
  QPen graphPen;
  graphPen.setColor(QColor(Qt::GlobalColor(5+graph_counter)));
  graphPen.setWidthF(2);
  customPlot->graph()->setPen(graphPen);
  customPlot->xAxis->setRange(0,0.5);
  customPlot->yAxis->setRange(-90,10);
  customPlot->legend->setVisible(true);
  //  customPlot->setInteraction(QCustomPlot::iSelectPlottables);
  customPlot->graph()->setName(QString(shape.c_str()));
  customPlot->replot();
}

MainWindow::~MainWindow()
{
  delete [] w;
  delete ui;
}

void MainWindow::graphPressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) dragStartPosition = event->pos();
}

void MainWindow::graphMoveEvent(QMouseEvent *event)
{
  if (!(event->buttons() & Qt::LeftButton))  return;

  if (((event->pos() - dragStartPosition).manhattanLength()) 
	  < QApplication::startDragDistance()) return;

  QPoint dis = (event->pos() - dragStartPosition);
  double xdis = dis.x();
  double ydis = dis.y();
  
  if (fabs(xdis) > fabs(ydis)) {
	LPF.horiz_swipe(xdis);
  } else {
	LPF.vertical_swipe(ydis);
  }
  QCPGraph* ptr = GetPtr();
  dragStartPosition = event->pos();
  if (ptr != NULL) {
	ui->customPlot->graph()->clearData();
	plot3(ui->customPlot);
  }
}
