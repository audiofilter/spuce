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
  pts = 250;
  w = new double[pts];
  for (int i=0;i<pts;i++) {
		w[i] = (double)i*i;
  }
  lpf_init(pts);

  MaxflatFIR_on = NULL;
  RaisedCosine_on = NULL;
  RootRaisedCosine_on = NULL;
  Remez_on = NULL;
  Gaussian_on = NULL;
  Sinc_on = NULL;

  shape = "Maxflat FIR";
  lpf_sel(shape.c_str());
  band_sel("LOW_PASS");
  graph_counter = 0;

  ui->setupUi(this);
  setup(ui->customPlot); 

  setWindowTitle("QCustomPlot: "+demoName);
  statusBar()->clearMessage();

  connect(ui->MaxflatFIR, SIGNAL(released()), this, SLOT(FChanged()));
  connect(ui->RaisedCosine, SIGNAL(released()), this, SLOT(RCChanged()));
  connect(ui->RootRaisedCosine, SIGNAL(released()), this, SLOT(RRCChanged()));
  connect(ui->Remez, SIGNAL(released()), this, SLOT(RChanged()));
  connect(ui->Gaussian, SIGNAL(released()), this, SLOT(GChanged()));
  connect(ui->Sinc, SIGNAL(released()), this, SLOT(SChanged()));

  connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), 
					this, SLOT(graphPressEvent(QMouseEvent*)));
  connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), 
					this, SLOT(graphMoveEvent(QMouseEvent*)));


  ui->customPlot->replot();
}
void MainWindow::BoxChecked(bool t) {
	if (ui->LowPass->isChecked()) {
		band_sel("LOW_PASS");
	} else if (ui->HighPass->isChecked()) {
		band_sel("HIGH_PASS");
	}	else if (ui->BandPass->isChecked()) {
		band_sel("BAND_PASS");
	}	else if (ui->BandStop->isChecked()) {
		band_sel("BAND_STOP");
	}
	updatePlot();
}
void MainWindow::updatePlot()
{
  horiz_swipe(0,true);
  /*
  order = get_order();
  ui->order->setText(QApplication::translate("MainWindow", std::to_string(order).c_str(), 0));
  ui->ripple->setText(QApplication::translate("MainWindow", std::to_string(ripple()).c_str(), 0));
  ui->fc->setText(QApplication::translate("MainWindow", std::to_string(fc()).c_str(), 0));
  */
    if (MaxflatFIR_on || RaisedCosine_on || RootRaisedCosine_on
        || Remez_on || Gaussian_on || Sinc_on) {
        ui->customPlot->graph()->clearData();
        plot3(ui->customPlot);
    }
}

void MainWindow::CBChanged() {}
void MainWindow::BChanged() {}
void MainWindow::CChanged() {}
void MainWindow::EChanged() {}
void MainWindow::FHChanged() {}
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
void MainWindow::SChanged() {
  if (Sinc_on==NULL) {
		shape = "Sinc FIR";
		lpf_sel(shape.c_str());
		Sinc_on = ui->customPlot->addGraph();
		plot2(ui->customPlot);
  } else {
		ui->customPlot->removeGraph(Sinc_on);
		Sinc_on = NULL;
		ui->customPlot->replot();
  }
}
/////////////////////////////
QCPGraph* MainWindow::GetPtr() {
  //  std::cout << " shape was = " << shape << "\n";
  if (shape=="Maxflat FIR") return(MaxflatFIR_on);
  else if (shape=="Gaussian FIR") return(Gaussian_on);
  else if (shape=="Remez FIR") return(Remez_on);
  else if (shape=="Sinc FIR") return(Sinc_on);
  else if (shape=="Raised Cosine") return(RaisedCosine_on);
  else if (shape=="Root Raised Cosine") return(RootRaisedCosine_on);
  else std::cout << "Invalid filter selection\n";
  return(Gaussian_on);
}
////////////////////////////////////
void MainWindow::setup(QCustomPlot *customPlot)
{
  demoName = "spuce : FIR Filter Demo";
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

  QObject::connect(ui->LowPass,SIGNAL(clicked(bool)),this,SLOT(BoxChecked(bool)));
  QObject::connect(ui->HighPass,SIGNAL(clicked(bool)),this,SLOT(BoxChecked(bool)));
  QObject::connect(ui->BandPass,SIGNAL(clicked(bool)),this,SLOT(BoxChecked(bool)));
  QObject::connect(ui->BandStop,SIGNAL(clicked(bool)),this,SLOT(BoxChecked(bool)));
  
  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(ui->LowPass);
  vbox->addWidget(ui->HighPass);
  vbox->addWidget(ui->BandPass);
  vbox->addWidget(ui->BandStop);
  ui->groupBox->setLayout(vbox);
  
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
	bool in_passband = (m>-10);
  
	double y_db = -100.0*y + 10;
	bool above_stop = (-y_db < m);

  if (fabs(xdis) > fabs(ydis)) {
    if (get_filter_type()) {
      set_center(xdis);
    } else {
      horiz_swipe(xdis,in_passband);
    }
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
