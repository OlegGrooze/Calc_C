#include "smartcalc_v1.h"

#include <clocale>

#include "ui_smartcalc_v1.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../smartcalc.h"
#ifdef __cplusplus
}
#endif

SmartCalc_v1::SmartCalc_v1(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SmartCalc_v1) {
  ui->setupUi(this);
  setlocale(LC_NUMERIC, "C");
  connect(ui->_0, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->_1, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->_2, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->_3, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->_4, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->_5, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->_6, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->_7, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->_8, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->_9, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->Addition, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->Subtraction, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->Multiplication, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->Division, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->pow, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->bracket_1, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->bracket_2, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->_x, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(print2()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(print2()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(print2()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(print2()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(print2()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(print2()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(print2()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(print2()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(print2()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(print()));
  connect(ui->AC, SIGNAL(clicked()), this, SLOT(clearWindow()));
  connect(ui->equal, SIGNAL(clicked()), this, SLOT(calc_result()));
}

SmartCalc_v1::~SmartCalc_v1() { delete ui; }

void SmartCalc_v1::keyPressEvent(QKeyEvent *calc_key) {
  if (calc_key->key() == Qt::Key_Return) {
    calc_result();
    on_credit_res_clicked();
    on_deposit_res_clicked();
  }
}

void SmartCalc_v1::calc_result() {
  char string[1024] = {0};
  char output[1024] = {0};
  bool RESULT_CODE = 0;
  QByteArray input = ui->lineEdit->text().toLocal8Bit();
  double x = ui->XXX->text().toDouble(&RESULT_CODE);
  memcpy(string, input, ui->lineEdit->text().length() + 1);
  smart_calculator(string, x, output);
  ui->lineEdit->setText(QString::fromLocal8Bit(output));
}

void SmartCalc_v1::clearWindow() { ui->lineEdit->setText(" 0"); }

void SmartCalc_v1::print() {
  if (ui->lineEdit->text() == " 0") {
    ui->lineEdit->setText("");
  }
  QPushButton *button = (QPushButton *)sender();
  QString symbol = button->text();
  ui->lineEdit->setText(ui->lineEdit->text() += symbol);
}

void SmartCalc_v1::print2() {
  if (ui->lineEdit->text() == " 0") {
    ui->lineEdit->setText("");
  }
  QPushButton *button = (QPushButton *)sender();
  QString symbol = button->text();
  ui->lineEdit->setText(ui->lineEdit->text() += symbol + "(");
}

void SmartCalc_v1::on_Plot_clicked() {
  int maxX = ui->max_X->text().toInt();
  int maxY = ui->max_Y->text().toInt();
  int minX = ui->min_X->text().toInt();
  int minY = ui->min_Y->text().toInt();
  int step = maxX - minX;
  char string[1024] = {0};
  char *result = (char *)calloc(1024, sizeof(char));
  QByteArray input = ui->lineEdit->text().toLocal8Bit();
  QVector<double> x(1024), y(1024);
  QPen redPen;
  memcpy(string, input, ui->lineEdit->text().length() + 1);
  for (int i = 0; i < 1024; ++i) {
    memset(result, '\0', 1024);
    x[i] = minX + step * (i / 1024.0);
    smart_calculator(string, x[i], result);
    if (!strcmp(result, "INF"))
      y[i] = INFINITY;
    else if (!strcmp(result, "NAN"))
      y[i] = NAN;
    else if (strcmp(result, "ERROR"))
      y[i] = strtod(result, NULL);
  }
  ui->Grafics->addGraph();
  redPen.setColor(QColor(255, 0, 0, 255));
  redPen.setStyle(Qt::SolidLine);
  redPen.setWidthF(2);
  ui->Grafics->graph(0)->setPen(redPen);
  ui->Grafics->graph(0)->setData(x, y);
  ui->Grafics->xAxis->setLabel("x");
  ui->Grafics->yAxis->setLabel("y");
  ui->Grafics->xAxis->setRange(minX, maxX);
  ui->Grafics->yAxis->setRange(minY, maxY);
  ui->Grafics->setInteraction(QCP::iRangeZoom, true);
  ui->Grafics->setInteraction(QCP::iRangeDrag, true);
  ui->Grafics->replot();
  free(result);
}

void SmartCalc_v1::on_credit_res_clicked() {
  long double creditAmount = ui->creditAmount->value();
  int period = 0;
  long double percent = 0;
  int type = 0;
  long double monthlyPayment = 0;
  long double overpayment = 0;
  long double totalPayment = 0;
  long double min = 0;
  long double max = 0;
  period = ui->period->value();
  percent = ui->percent->value();
  if (ui->typeAnn->isChecked()) {
    type = ANNUITY;
  } else if (ui->typeDiff->isChecked()) {
    type = DIFFERENTIATED;
  }
  if (percent >= 0.01 && percent <= 999) {
    credit_calculator(creditAmount, period, percent, type, &monthlyPayment,
                      &overpayment, &totalPayment, &max, &min);
    if (type == DIFFERENTIATED) {
      ui->monthlyPayment->setText(QString::number(max, 'f', 2));
      ui->monthlyPayment->setText(ui->monthlyPayment->text() += " - ");
      ui->monthlyPayment->setText(ui->monthlyPayment->text() +=
                                  QString::number(min, 'f', 2));
    } else {
      ui->monthlyPayment->setText(QString::number(monthlyPayment, 'f', 2));
    }
    ui->overpayment->setText(QString::number(overpayment, 'f', 2));
    ui->totalPayment->setText(QString::number(totalPayment, 'f', 2));
  }
}

void SmartCalc_v1::on_deposit_res_clicked() {
  long double depositAmount = 0;
  int period_dep = 0;
  long double percent_dep = 0;
  long double tax_dep = 0;
  int frequency = 0;
  int capitalization = 0;
  long double payment = 0;
  long double invoiceSum = 0;
  long double taxSum = 0;
  depositAmount = ui->depositAmount->value();
  period_dep = ui->period_dep->value();
  percent_dep = ui->percent_dep->value();
  tax_dep = ui->tax_dep->value();
  frequency = ui->frequency->value();
  if (ui->capitalization->isChecked()) {
    capitalization = 1;
  }
  if (ui->capitalization_no->isChecked()) {
    capitalization = 0;
  }
  deposit_calculator(depositAmount, period_dep, percent_dep, tax_dep, frequency,
                     capitalization, &payment, &invoiceSum, &taxSum);
  ui->payment->setText(QString::number(payment, 'f', 2));
  ui->invoiceSum->setText(QString::number(invoiceSum, 'f', 2));
  ui->tax->setText(QString::number(taxSum, 'f', 2));
}
