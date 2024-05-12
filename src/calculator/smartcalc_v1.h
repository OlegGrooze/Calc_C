#ifndef SMARTCALC_V1_H
#define SMARTCALC_V1_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE namespace Ui { class SmartCalc_v1; }
QT_END_NAMESPACE

class SmartCalc_v1 : public QMainWindow {
  Q_OBJECT

 public:
  SmartCalc_v1(QWidget *parent = nullptr);
  ~SmartCalc_v1();

 private:
  Ui::SmartCalc_v1 *ui;
  QVector<double> x, y;

  // credit *creditWindow;
  // deposit *depositWindow;

 protected:
  void keyPressEvent(QKeyEvent *calc_key) override;

 private slots:
  void print();
  void print2();
  void clearWindow();
  void calc_result();
  void on_Plot_clicked();
  void on_credit_res_clicked();
  void on_deposit_res_clicked();
};
#endif  // SMARTCALC_V1_H
