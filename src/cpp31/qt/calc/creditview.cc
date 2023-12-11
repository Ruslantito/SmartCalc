#include "creditview.h"

/**
 * @brief Construct a new s21::Credit View::Credit View object
 *
 * @param parent
 */
s21::CreditView::CreditView(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditView) {
  ui->setupUi(this);
  controller = new s21::CreditController;

  connect(ui->button_back, &QPushButton::clicked, this,
          &CreditView::ButtonBackClicked);
  connect(ui->button_count, &QPushButton::clicked, this,
          &CreditView::ButtonCountClicked);
}

/**
 * @brief Destroy the s21::Credit View::Credit View object
 *
 */
s21::CreditView::~CreditView() {
  delete controller;
  delete ui;
}

void s21::CreditView::ButtonBackClicked() {
  this->close();
  emit CreditWindow();
}

void s21::CreditView::ButtonCountClicked() {
  std::string monthly, percent, total;

  CreditModel::InputCreditData input_data{
      ui->credit_total_value->value(),
      ui->credit_duration_value->value(),
      ui->credit_percent_value->value(),
      ui->credit_duration->currentText().toStdString(),
      ui->credit_type_diff->isChecked(),
      0,
      0};

  controller->SetInput(input_data);
  controller->Calculate(monthly, percent, total);

  ui->result_month->setText(QString::fromStdString(monthly));
  ui->result_percent->setText(QString::fromStdString(percent));
  ui->result_total->setText(QString::fromStdString(total));
}
