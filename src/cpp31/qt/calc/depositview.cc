#include "depositview.h"

/**
 * @brief Construct a new s21::Deposit View::Deposit View object
 *
 * @param parent
 */
s21::DepositView::DepositView(QWidget *parent)
    : QWidget(parent), ui(new Ui::DepositView) {
  ui->setupUi(this);
  controller = new s21::DepositController;

  ui->extra_hide_show->setCurrentIndex(0);

  connect(ui->button_back, &QPushButton::clicked, this,
          &DepositView::ButtonBackClicked);
  connect(ui->button_count, &QPushButton::clicked, this,
          &DepositView::ButtonCountClicked);
  connect(ui->button_extra_visibility, &QPushButton::clicked, this,
          &DepositView::ButtonExtraVisibilityClicked);
  connect(ui->button_extra_calc, &QPushButton::clicked, this,
          &DepositView::ButtonExtraCalcClicked);
}

s21::DepositView::~DepositView() {
  delete controller;
  delete ui;
}

void s21::DepositView::ButtonBackClicked() {
  this->close();
  emit DepositWindow();
}

void s21::DepositView::ButtonCountClicked() {
  std::string tax, percent, total, incom_minus_tax;
  std::tm deposit_date_start;
  ui->deposit_date_start->date().getDate(&deposit_date_start.tm_year,
                                         &deposit_date_start.tm_mon,
                                         &deposit_date_start.tm_mday);
  DepositModel::InputDepositData input_data{
      ui->deposit_total_value->value(),
      ui->deposit_duration_value->value(),
      ui->deposit_percent_value->value(),
      ui->deposit_refill_value->value(),
      ui->deposit_withdrawal_value->value(),
      ui->deposit_tax_value->value(),
      ui->deposit_duration_type->currentText().toStdString(),
      ui->deposit_payment_frequency_type->currentText().toStdString(),
      ui->deposit_refill_frequency_type->currentText().toStdString(),
      ui->deposit_withdrawal_frequency_type->currentText().toStdString(),
      ui->deposit_interest_capitalization_check->checkState(),
      ui->deposit_refill_check->checkState(),
      ui->deposit_withdrawal_check->checkState(),
      deposit_date_start,
      0,
      0,
      0,
      0};
  controller->SetInput(input_data);
  PackageExtraDataSend();
  controller->Calculate(percent, tax, total, incom_minus_tax);

  ui->result_percent->setText(QString::fromStdString(percent));
  ui->result_tax->setText(QString::fromStdString(tax));
  ui->result_total->setText(QString::fromStdString(total));
  ui->result_incom_minus_tax->setText(QString::fromStdString(incom_minus_tax));
}

void s21::DepositView::ButtonExtraVisibilityClicked() {
  ui->extra_hide_show->setCurrentIndex(
      abs(ui->extra_hide_show->currentIndex() - 1));
}

void s21::DepositView::PackageExtraDataSend() {
  controller->SetExtraInput(ui->extra_sum_for_count->value(),
                            ui->extra_key_rate_of_bank->value());
}

void s21::DepositView::ButtonExtraCalcClicked() {
  double extra_result_income_free_tax;
  PackageExtraDataSend();
  controller->CalculateExtra(extra_result_income_free_tax);
  ui->extra_res_income_free_tax->setValue(extra_result_income_free_tax);
}
