#include "depositcontroller.h"

/**
 * @brief Construct a new s21::Deposit Controller::Deposit Controller object
 *
 */
s21::DepositController::DepositController() : model(new s21::DepositModel) {}

/**
 * @brief Destroy the s21::Deposit Controller::Deposit Controller object
 *
 */
s21::DepositController::~DepositController() { delete model; }

void s21::DepositController::SetInput(
    const DepositModel::InputDepositData &input_data) {
  model->SetInput(input_data);
}

void s21::DepositController::SetExtraInput(int sum_for_count,
                                           double key_rate_of_bank) {
  model->SetExtraInput(sum_for_count, key_rate_of_bank);
}

void s21::DepositController::Calculate(std::string &percent, std::string &tax,
                                       std::string &total,
                                       std::string &incom_minus_tax) {
  return model->Calculate(percent, tax, total, incom_minus_tax);
}

void s21::DepositController::CalculateExtra(
    double &extra_result_income_free_tax) {
  return model->CalculateExtra(extra_result_income_free_tax);
};
