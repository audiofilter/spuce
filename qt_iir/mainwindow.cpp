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
  trans = 0.1;
  stop_dBs = 40;
  pts = 250;
  w = new double[pts];
  for (int i=0;i<pts;i++) {
		w[i] = (double)i*i;
  }
  lpf_init(pts);

  Butterworth_on = NULL;
  Chebyshev_on = NULL;
	Chebyshev2_on = NULL;
  Elliptic_on = NULL;

  graph_counter = 0;

  ui->setupUi(this);
  //  setGeometry(400, 250, 542, 390);
  setup(ui->customPlot); 

  setWindowTitle("QCustomPlot: "+demoName);
  statusBar()->clearMessage();

  connect(ui->Butterworth, SIGNAL(released()), this, SLOT(BChanged()));
  connect(ui->Chebyshev, SIGNAL(released()), this, SLOT(CChanged()));
	connect(ui->Chebyshev2, SIGNAL(released()), this, SLOT(C2Changed()));
  connect(ui->Elliptic, SIGNAL(released()), this, SLOT(EChanged()));

  connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),		  this, SLOT(graphPressEvent(QMouseEvent*)));
  connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), 		  this, SLOT(graphMoveEvent(QMouseEvent*)));

  ui->customPlot->replot();
}
void MainWindow::BoxChecked() {
	if (ui->LowPass->isChecked()) {
		set_filter_type(0);
	} else if (ui->HighPass->isChecked()) {
		set_filter_type(1);
	}	else if (ui->BandPass->isChecked()) {
		set_filter_type(2);
	}	else if (ui->BandStop->isChecked()) {
		set_filter_type(3);
	}
}

void MainWindow::BChanged() {
  if (Butterworth_on==NULL) {
		shape = "Butterworth";
		lpf_sel(shape.c_str());
		order = get_order();
		ui->order->setText(QApplication::translate("MainWindow", std::to_string(order).c_str(), 0));
		ui->ripple->setText(QApplication::translate("MainWindow", std::to_string(ripple()).c_str(), 0));
		ui->fc->setText(QApplication::translate("MainWindow", std::to_string(fc()).c_str(), 0));
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
		order = get_order();
		ui->order->setText(QApplication::translate("MainWindow", std::to_string(order).c_str(), 0));
		ui->ripple->setText(QApplication::translate("MainWindow", std::to_string(ripple()).c_str(), 0));
		ui->fc->setText(QApplication::translate("MainWindow", std::to_string(fc()).c_str(), 0));
		Chebyshev_on = ui->customPlot->addGraph();
		plot2(ui->customPlot);
  } else {
		ui->customPlot->removeGraph(Chebyshev_on);
		Chebyshev_on = NULL;
		ui->customPlot->replot();
  }
}
void MainWindow::C2Changed() {
  if (Chebyshev2_on==NULL) {
		shape = "Chebyshev2";
		lpf_sel(shape.c_str());
		order = get_order();
		ui->order->setText(QApplication::translate("MainWindow", std::to_string(order).c_str(), 0));
		ui->ripple->setText(QApplication::translate("MainWindow", std::to_string(ripple()).c_str(), 0));
		ui->fc->setText(QApplication::translate("MainWindow", std::to_string(fc()).c_str(), 0));
		Chebyshev2_on = ui->customPlot->addGraph();
		plot2(ui->customPlot);
  } else {
		ui->customPlot->removeGraph(Chebyshev2_on);
		Chebyshev2_on = NULL;
		ui->customPlot->replot();
  }
}
void MainWindow::EChanged() {
  if (Elliptic_on==NULL) {
		shape = "Elliptic";
		lpf_sel(shape.c_str());
		order = get_order();
		ui->order->setText(QApplication::translate("MainWindow", std::to_string(order).c_str(), 0));
		ui->ripple->setText(QApplication::translate("MainWindow", std::to_string(ripple()).c_str(), 0));
		ui->fc->setText(QApplication::translate("MainWindow", std::to_string(fc()).c_str(), 0));
		Elliptic_on = ui->customPlot->addGraph();
		plot2(ui->customPlot);
  } else {
		ui->customPlot->removeGraph(Elliptic_on);
		Elliptic_on = NULL;
		ui->customPlot->replot();
  }
}
/////////////////////////////
QCPGraph* MainWindow::GetPtr() {
  //  std::cout << " shape was = " << shape << "\n";
	if (shape == "Chebyshev") return(Chebyshev_on);
	else if (shape=="Chebyshev2")	return(Chebyshev2_on);
	else if (shape=="Butterworth")	return(Butterworth_on);
	else if (shape=="Elliptic") return(Elliptic_on);
	else std::cout << "Invalid filter selection\n";
	return(Butterworth_on);
}
////////////////////////////////////
void MainWindow::setup(QCustomPlot *customPlot)
{
  demoName = "spuce : Low Pass Filter Demo";

	ui->order->setText(QApplication::translate("MainWindow", "3", 0));

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(ui->LowPass);
	vbox->addWidget(ui->HighPass);
	vbox->addWidget(ui->BandPass);
	vbox->addWidget(ui->BandStop);
	ui->groupBox->setLayout(vbox);
	
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
	order = get_order();
	ui->order->setText(QApplication::translate("MainWindow", std::to_string(order).c_str(), 0));
	ui->ripple->setText(QApplication::translate("MainWindow", std::to_string(ripple()).c_str(), 0));
	ui->fc->setText(QApplication::translate("MainWindow", std::to_string(fc()).c_str(), 0));
	
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
	order = get_order();
	ui->order->setText(QApplication::translate("MainWindow", std::to_string(order).c_str(), 0));
	ui->ripple->setText(QApplication::translate("MainWindow", std::to_string(ripple()).c_str(), 0));
	ui->fc->setText(QApplication::translate("MainWindow", std::to_string(fc()).c_str(), 0));

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

  if (((event->pos() - dragStartPosition).manhattanLength()) < QApplication::startDragDistance()) return;

	BoxChecked();
	
  QPoint dis = (event->pos() - dragStartPosition);
  double xdis = dis.x();
  double ydis = dis.y();

	double x = M_PI*event->pos().x()/600.0;
	double y = event->pos().y()/400.0;

	double m = get_mag(x);
	bool in_passband = (m>-3);
	
	double y_db = -100.0*y + 10;
	bool above_stop = (-y_db < m);
	
  if (fabs(xdis) > fabs(ydis)) {
		// Bandpass or Bandstop
		if (get_filter_type() > 1) {
			set_center(xdis);
		} else {
			horiz_swipe(xdis,in_passband);
		}
  } else {
		vertical_swipe(-ydis,in_passband,above_stop);
  }

	order = get_order();
	ui->order->setText(QApplication::translate("MainWindow", std::to_string(order).c_str(), 0));
	ui->ripple->setText(QApplication::translate("MainWindow", std::to_string(ripple()).c_str(), 0));
	ui->fc->setText(QApplication::translate("MainWindow", std::to_string(fc()).c_str(), 0));
	
  QCPGraph* ptr = GetPtr();
  dragStartPosition = event->pos();
  if (ptr != NULL) {
		ui->customPlot->graph()->clearData();
		plot3(ui->customPlot);
  }
}
