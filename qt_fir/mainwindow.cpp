// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <cstdlib>
#include <QDebug>
#include <QDesktopWidget>
#include <QMessageBox>

#include <iostream>
#include "des_filter.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  pass_edge = 0;
  order = 13;
  taps = 25;
  alpha = 0.25;
  trans = 0.1;
  stop_dBs = 40;
  pts = 250;
  w = new double[pts];
  for (int i=0;i<pts;i++) {
		w[i] = (double)i*i;
  }
  lpf_init(pts);

  Hanning_on = NULL;
  Hamming_on = NULL;
  Blackman_on = NULL;
  MaxflatFIR_on = NULL;
  Bartlett_on = NULL;
  RaisedCosine_on = NULL;
  RootRaisedCosine_on = NULL;
  Remez_on = NULL;
  Gaussian_on = NULL;
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
  connect(ui->MaxflatFIR, SIGNAL(released()), this, SLOT(FChanged()));
  connect(ui->Bartlett, SIGNAL(released()), this, SLOT(FHChanged()));
  connect(ui->RaisedCosine, SIGNAL(released()), this, SLOT(RCChanged()));
  connect(ui->RootRaisedCosine, SIGNAL(released()), this, SLOT(RRCChanged()));
  connect(ui->Remez, SIGNAL(released()), this, SLOT(RChanged()));
  connect(ui->Gaussian, SIGNAL(released()), this, SLOT(GChanged()));
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
		lpf_sel(shape.c_str());
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
		lpf_sel(shape.c_str());
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
		lpf_sel(shape.c_str());
		Blackman_on = ui->customPlot->addGraph();
		plot2(ui->customPlot);
  } else {
		ui->customPlot->removeGraph(Blackman_on);
		Blackman_on = NULL;
		ui->customPlot->replot();
  }
}
void MainWindow::FChanged() {
  if (MaxflatFIR_on==NULL) {
		shape = "Maxflat FIR";
		lpf_sel(shape.c_str());
		MaxflatFIR_on = ui->customPlot->addGraph();
		plot2(ui->customPlot);
  } else {
		ui->customPlot->removeGraph(MaxflatFIR_on);
		MaxflatFIR_on = NULL;
		ui->customPlot->replot();
  }
}
void MainWindow::FHChanged() {
  if (Bartlett_on==NULL) {
		shape = "Bartlett";
		lpf_sel(shape.c_str());
		Bartlett_on = ui->customPlot->addGraph();
		plot2(ui->customPlot);
  } else {
		ui->customPlot->removeGraph(Bartlett_on);
		Bartlett_on = NULL;
		ui->customPlot->replot();
  }
}
void MainWindow::RCChanged() {
  if (RaisedCosine_on==NULL) {
		shape = "Raised Cosine";
		lpf_sel(shape.c_str());
		RaisedCosine_on = ui->customPlot->addGraph();
		plot2(ui->customPlot);
  } else {
		ui->customPlot->removeGraph(RaisedCosine_on);
		RaisedCosine_on = NULL;
		ui->customPlot->replot();
  }
}
void MainWindow::RRCChanged() {
  if (RootRaisedCosine_on==NULL) {
		shape = "Root Raised Cosine";
		lpf_sel(shape.c_str());
		RootRaisedCosine_on = ui->customPlot->addGraph();
		plot2(ui->customPlot);
  } else {
		ui->customPlot->removeGraph(RootRaisedCosine_on);
		RootRaisedCosine_on = NULL;
		ui->customPlot->replot();
  }
}
void MainWindow::RChanged() {
  if (Remez_on==NULL) {
		shape = "Remez FIR";
		lpf_sel(shape.c_str());
		Remez_on = ui->customPlot->addGraph();
		plot2(ui->customPlot);
  } else {
		ui->customPlot->removeGraph(Remez_on);
		Remez_on = NULL;
		ui->customPlot->replot();
  }
}
void MainWindow::GChanged() {
  if (Gaussian_on==NULL) {
		shape = "Gaussian FIR";
		lpf_sel(shape.c_str());
		Gaussian_on = ui->customPlot->addGraph();
		plot2(ui->customPlot);
  } else {
		ui->customPlot->removeGraph(Gaussian_on);
		Gaussian_on = NULL;
		ui->customPlot->replot();
  }
}
void MainWindow::CBChanged() {
  if (Kaiser_on==NULL) {
		shape = "Kaiser";
		lpf_sel(shape.c_str());
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
  //  std::cout << " shape was = " << shape << "\n";
	if (shape == "Hamming") return(Hamming_on);
	else if (shape=="Bartlett") return(Bartlett_on);
	else if (shape=="Hanning")	return(Hanning_on);
	else if (shape=="Blackman") return(Blackman_on);
	else if (shape=="Maxflat FIR") return(MaxflatFIR_on);
	else if (shape=="Gaussian FIR") return(Gaussian_on);
	else if (shape=="Remez FIR") return(Remez_on);
	else if (shape=="Raised Cosine") return(RaisedCosine_on);
	else if (shape=="Kaiser") return(Kaiser_on);
	else if (shape=="Root Raised Cosine") return(RootRaisedCosine_on);
	else std::cout << "Invalid filter selection\n";
	return(Hanning_on);
}
////////////////////////////////////
void MainWindow::setup(QCustomPlot *customPlot)
{
  demoName = "spuce : Low Pass Filter Demo";
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

  update_w(w);
  double y_inc = 1.0; 
  for (int i=0; i<pts; ++i)   {
    x0[i] = (double)0.5*i/pts;
    y0[i] = y_inc*(w[i]);
  }
  customPlot->graph()->setData(x0, y0);
  customPlot->graph()->setLineStyle(QCPGraph::lsLine); //(QCPGraph::LineStyle)(rand()%5+1));
  customPlot->graph()->setScatterStyle(QCPScatterStyle::ssNone); // (QCP::ScatterStyle)(rand()%9+1));
  QPen graphPen;
  //  graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
  //graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);

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

  update_w(w);
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
  /*
  std::cout << "Drag from (" << dragStartPosition.x()
			<< "," << dragStartPosition.y()
			<< ")\n";
  */
}

void MainWindow::graphMoveEvent(QMouseEvent *event)
{
  if (!(event->buttons() & Qt::LeftButton))  return;

  if (((event->pos() - dragStartPosition).manhattanLength()) 
	  < QApplication::startDragDistance()) return;

  QPoint dis = (event->pos() - dragStartPosition);
  double xdis = dis.x();
  double ydis = dis.y();

	double y = event->pos().y()/400.0;
	double x = M_PI*event->pos().x()/600.0;
	
	double m = get_mag(x);
	bool in_passband = (m>-3);
	
	double y_db = -100.0*y + 10;
	bool above_stop = (-y_db < m);

  if (fabs(xdis) > fabs(ydis)) {
		horiz_swipe(xdis,in_passband);
  } else {
		vertical_swipe(-ydis,in_passband,above_stop);
  }
  QCPGraph* ptr = GetPtr();
  dragStartPosition = event->pos();
  if (ptr != NULL) {
	ui->customPlot->graph()->clearData();
	plot3(ui->customPlot);
  }
}
