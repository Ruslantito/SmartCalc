#include "creditcontroller.h"

/**
 * @brief Construct a new s21::Credit Controller::Credit Controller object
 *
 */
s21::CreditController::CreditController() : model(new s21::CreditModel) {}

/**
 * @brief Destroy the s21::Credit Controller::Credit Controller object
 *
 */
s21::CreditController::~CreditController() { delete model; }

void s21::CreditController::SetInput(
    const CreditModel::InputCreditData &input_data) {
  model->SetInput(input_data);
}

void s21::CreditController::Calculate(std::string &monthly,
                                      std::string &percent,
                                      std::string &total) {
  return model->Calculate(monthly, percent, total);
}
