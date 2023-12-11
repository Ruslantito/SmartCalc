#ifndef CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CREDITVIEW_H_
#define CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CREDITVIEW_H_

#include <QStatusBar>
#include <QWidget>
#include <iostream>

#include "creditcontroller.h"
#include "ui_creditview.h"

namespace Ui {
class CreditView;
}

namespace s21 {
class CreditView : public QWidget {
  Q_OBJECT

 public:
  explicit CreditView(QWidget *parent = nullptr);
  CreditView(const CreditView &other) = delete;
  CreditView(CreditView &&other) = delete;
  CreditView &operator=(const CreditView &other) = delete;
  CreditView &operator=(CreditView &&other) = delete;
  ~CreditView();

 signals:
  void CreditWindow();

 private slots:
  void ButtonBackClicked();
  void ButtonCountClicked();

 private:
  Ui::CreditView *ui;
  s21::CreditController *controller;
};
};  //  namespace s21

#endif  //  CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CREDITVIEW_H_
