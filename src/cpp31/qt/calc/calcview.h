#ifndef CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CALCVIEW_H_
#define CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CALCVIEW_H_

#include <QMainWindow>
#include <QString>
#include <QVector4D>
#include <QtGui>
#include <cstring>
#include <iostream>

#include "./qcustomplot_lib/qcustomplot.h"
#include "./ui_calcview.h"
#include "calccontroller.h"
#include "creditview.h"
#include "depositview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcView;
}
QT_END_NAMESPACE

namespace s21 {
class CalcView : public QMainWindow {
  Q_OBJECT

 public:
  CalcView(QWidget *parent = nullptr);
  CalcView(const CalcView &other) = delete;
  CalcView(CalcView &&other) = delete;
  CalcView &operator=(const CalcView &other) = delete;
  CalcView &operator=(CalcView &&other) = delete;
  ~CalcView();

  void SetLineColor(const QColor &line_color);
  QColor GetLineColor() const;

 private slots:
  void DigitsNumbers();
  void Operations();
  void MathOperations();
  void MathOperations2();
  void MathOperations3();
  void MathOperationsTotal(int plus_bracket, int print_simb);

  void ButtonDotClicked();
  void ButtonDelClicked();
  void ButtonDelTotalClicked();
  void ButtonEqClicked();

  void GraphCustomPlot();
  void GraphRecalcLine(int index, QPen &blue_dot_pen, int width);
  void SetLineColorButton();

  void ButtonLineColorClicked();
  void ButtonDrawClicked();
  void ButtonClearClicked();
  void ButtonShowGraphClicked();
  void ButtonHideGraphClicked();

  void GoToCreditCalc();
  void GoToDepositCalc();

 private:
  Ui::CalcView *ui;
  s21::CalcController *controller;
  CreditView *credit_calc;
  DepositView *deposit_calc;

  QColor line_color_{};
};
};  //  namespace s21

#endif  //  CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CALCVIEW_H_
