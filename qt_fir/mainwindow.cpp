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
  order = 3;
  taps = 25;
  alpha = 0.25;
  trans = 0.1;
  stop_dBs = 40;
  bits = 0;
  pts = 250;
  w = new double[pts];
  for (int i=0;i<pts;i++) {
	w[i] = (double)i*i;
  }
  lpf_init(pts);

  Butterworth_on = NULL;
  Chebyshev_on = NULL;
  Elliptic_on = NULL;
  MaxflatFIR_on = NULL;
  MaxflatHalfband_on = NULL;
  RaisedCosine_on = NULL;
  RootRaisedCosine_on = NULL;
  EllipticHalfband_on = NULL;
  Remez_on = NULL;
  NotchIIR_on = NULL;
  CutBoost_on = NULL;

  graph_counter = 0;

  ui->setupUi(this);
  //  setGeometry(400, 250, 542, 390);
  setup(ui->customPlot); 

  setWindowTitle("QCustomPlot: "+demoName);
  statusBar()->clearMessage();

  connect(ui->Butterworth, SIGNAL(released()), this, SLOT(BChanged()));
  connect(ui->Chebyshev, SIGNAL(released()), this, SLOT(CChanged()));
  connect(ui->Elliptic, SIGNAL(released()), this, SLOT(EChanged()));
  connect(ui->MaxflatFIR, SIGNAL(released()), this, SLOT(FChanged()));
  connect(ui->MaxflatHalfband, SIGNAL(released()), this, SLOT(FHChanged()));
  connect(ui->RaisedCosine, SIGNAL(released()), this, SLOT(RCChanged()));
  connect(ui->RootRaisedCosine, SIGNAL(released()), this, SLOT(RRCChanged()));
  connect(ui->EllipticHalfband, SIGNAL(released()), this, SLOT(EHChanged()));
  connect(ui->Remez, SIGNAL(released()), this, SLOT(RChanged()));
  connect(ui->NotchIIR, SIGNAL(released()), this, SLOT(NChanged()));
  connect(ui->CutBoost, SIGNAL(released()), this, SLOT(CBChanged()));

  connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), 
		  this, SLOT(graphPressEvent(QMouseEvent*)));
  connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), 
		  this, SLOT(graphMoveEvent(QMouseEvent*)));


  ui->customPlot->replot();
}
void MainWindow::BChanged() {
  if (Butterworth_on==NULL) {
	shape = "Butterworth";
	lpf_sel(shape.c_str());
	Butterworth_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(Butterworth_on);
	Butterworth_on = NULL;
	ui->customPlot->replot();
  }
}
void MainWindow::CChanged() {
  if (Chebyshev_on==NULL) {
	shape = "Chebyshev";
	lpf_sel(shape.c_str());
	Chebyshev_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(Chebyshev_on);
	Chebyshev_on = NULL;
	ui->customPlot->replot();
  }
}
void MainWindow::EChanged() {
  if (Elliptic_on==NULL) {
	shape = "Elliptic";
	lpf_sel(shape.c_str());
	Elliptic_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(Elliptic_on);
	Elliptic_on = NULL;
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
  if (MaxflatHalfband_on==NULL) {
	shape = "Maxflat Subband";
	lpf_sel(shape.c_str());
	MaxflatHalfband_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(MaxflatHalfband_on);
	MaxflatHalfband_on = NULL;
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
void MainWindow::EHChanged() {
  if (EllipticHalfband_on==NULL) {
	shape = "Elliptic Subband";
	lpf_sel(shape.c_str());
	EllipticHalfband_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(EllipticHalfband_on);
	EllipticHalfband_on = NULL;
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
void MainWindow::NChanged() {
  if (NotchIIR_on==NULL) {
	shape = "Notch";
	lpf_sel(shape.c_str());
	NotchIIR_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(NotchIIR_on);
	NotchIIR_on = NULL;
	ui->customPlot->replot();
  }
}
void MainWindow::CBChanged() {
  if (CutBoost_on==NULL) {
	shape = "Cut/Boost";
	lpf_sel(shape.c_str());
	CutBoost_on = ui->customPlot->addGraph();
	plot2(ui->customPlot);
  } else {
	ui->customPlot->removeGraph(CutBoost_on);
	CutBoost_on = NULL;
	ui->customPlot->replot();
  }
}
/////////////////////////////
QCPGraph* MainWindow::GetPtr() {
  //  std::cout << " shape was = " << shape << "\n";
	if (shape == "Chebyshev") return(Chebyshev_on);
	else if (shape=="Maxflat Subband") return(MaxflatHalfband_on);
	else if (shape=="Elliptic Subband") return(EllipticHalfband_on);
	else if (shape=="Butterworth")	return(Butterworth_on);
	else if (shape=="Elliptic") return(Elliptic_on);
	else if (shape=="Maxflat FIR") return(MaxflatFIR_on);
	else if (shape=="Remez FIR") return(Remez_on);
	else if (shape=="Raised Cosine") return(RaisedCosine_on);
	else if (shape=="Notch") return(NotchIIR_on);
	else if (shape=="Cut/Boost") return(CutBoost_on);
	else if (shape=="Root Raised Cosine") return(RootRaisedCosine_on);
	else std::cout << "Invalid filter selection\n";
	return(Butterworth_on);
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

  update_w(w,1.0);
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

  update_w(w,1.0);
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

  if (fabs(xdis) > fabs(ydis)) {
		horiz_swipe(xdis,true);
  } else {
		vertical_swipe(-ydis,true,true);
  }
  QCPGraph* ptr = GetPtr();
  dragStartPosition = event->pos();
  if (ptr != NULL) {
	ui->customPlot->graph()->clearData();
	plot3(ui->customPlot);
  }
}
