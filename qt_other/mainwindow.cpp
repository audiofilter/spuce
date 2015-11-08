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

  MaxflatSubband_on = NULL;
  EllipticSubband_on = NULL;
  CutBoost_on = NULL;
  NotchIIR_on = NULL;

  graph_counter = 0;

  ui->setupUi(this);
  //  setGeometry(400, 250, 542, 390);
  setup(ui->customPlot); 

  setWindowTitle("QCustomPlot: "+demoName);
  statusBar()->clearMessage();

  connect(ui->MaxflatSubband, SIGNAL(released()), this, SLOT(MChanged()));
  connect(ui->EllipticSubband, SIGNAL(released()), this, SLOT(EChanged()));
  connect(ui->CutBoost, SIGNAL(released()), this, SLOT(CChanged()));
  connect(ui->NotchIIR, SIGNAL(released()), this, SLOT(NChanged()));

  connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), 
					this, SLOT(graphPressEvent(QMouseEvent*)));
  connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), 
					this, SLOT(graphMoveEvent(QMouseEvent*)));


  ui->customPlot->replot();
}
void MainWindow::MChanged() {
  if (MaxflatSubband_on==NULL) {
	shape = "MaxflatSubband";
	LPF.change_filter(spuce::MaxflatSubband);
	MaxflatSubband_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(MaxflatSubband_on);
	MaxflatSubband_on = NULL;
	ui->customPlot->replot();
  }
}
void MainWindow::EChanged() {
  if (EllipticSubband_on==NULL) {
	shape = "EllipticSubband";
	LPF.change_filter(spuce::EllipticSubband);
	EllipticSubband_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(EllipticSubband_on);
	EllipticSubband_on = NULL;
	ui->customPlot->replot();
  }
}
void MainWindow::CChanged() {
  if (CutBoost_on==NULL) {
	shape = "CutBoost";
	LPF.change_filter(spuce::CutBoost);
	CutBoost_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(CutBoost_on);
	CutBoost_on = NULL;
	ui->customPlot->replot();
  }
}
void MainWindow::NChanged() {
  if (NotchIIR_on==NULL) {
	shape = "NotchIIR";
	LPF.change_filter(spuce::NotchIIR);
	NotchIIR_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(NotchIIR_on);
	NotchIIR_on = NULL;
	ui->customPlot->replot();
  }
}
/////////////////////////////
QCPGraph* MainWindow::GetPtr() {
  if (shape == "EllipticSubband") return(EllipticSubband_on);
  else if (shape=="NotchIIR") return(NotchIIR_on);
  else if (shape=="MaxflatSubband")	return(MaxflatSubband_on);
  else if (shape=="CutBoost") return(CutBoost_on);
  else std::cout << "Invalid filter selection " << shape << "\n";
  return(MaxflatSubband_on);
}
////////////////////////////////////
void MainWindow::setup(QCustomPlot *customPlot)
{
  demoName = "spuce : Other Filters Demo";
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
