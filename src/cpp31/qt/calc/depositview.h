#ifndef CPP3_SMARTCALC_SRC_CPP31_QT_CALC_DEPOSITVIEW_H_
#define CPP3_SMARTCALC_SRC_CPP31_QT_CALC_DEPOSITVIEW_H_

#include <QDateEdit>
#include <QStandardItemModel>
#include <QWidget>

#include "depositcontroller.h"
#include "ui_depositview.h"

namespace Ui {
class DepositView;
}

namespace s21 {
class DepositView : public QWidget {
  Q_OBJECT

 public:
  explicit DepositView(QWidget *parent = nullptr);
  DepositView(const DepositView &other) = delete;
  DepositView(DepositView &&other) = delete;
  DepositView &operator=(const DepositView &other) = delete;
  DepositView &operator=(DepositView &&other) = delete;
  ~DepositView();

 signals:
  void DepositWindow();

 private slots:
  void ButtonBackClicked();
  void ButtonCountClicked();
  void ButtonExtraVisibilityClicked();
  void PackageExtraDataSend();
  void ButtonExtraCalcClicked();

 private:
  Ui::DepositView *ui;
  s21::DepositController *controller;
  QStandardItemModel *model;
};
};  //  namespace s21

#endif  //  CPP3_SMARTCALC_SRC_CPP31_QT_CALC_DEPOSITVIEW_H_
