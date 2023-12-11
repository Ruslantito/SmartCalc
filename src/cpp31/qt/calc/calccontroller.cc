#include "calccontroller.h"

s21::CalcController::CalcController() : model(new s21::CalcModel){};
s21::CalcController::~CalcController() { delete model; }

void s21::CalcController::SetInputValue(const std::string &data, double x) {
  model->SetInput(data, x);
}

std::string s21::CalcController::GetResultValue() const {
  return model->GetResult();
}

void s21::CalcController::CalcVector(const CalcModel::InputGraphLimits &limits,
                                     std::vector<double> &x,
                                     std::vector<double> &y) {
  return model->CalcVector(limits, x, y);
}

int s21::CalcController::Validate() { return model->Validate(); }

void s21::CalcController::SetEqualPressStatus(int equal_operation_pressed) {
  model->SetEqualPressStatus(equal_operation_pressed);
}

int s21::CalcController::GetEqualPressStatus() const {
  return model->GetEqualPressStatus();
}

void s21::CalcController::SetFullOperation(const std::string &full_operation) {
  model->SetFullOperation(full_operation);
}

std::string s21::CalcController::GetFullOperation() const {
  return model->GetFullOperation();
}

void s21::CalcController::DoCalcTotal() { model->CalcTotal(); }

std::string s21::CalcController::ButtonDelClicked() {
  return model->OnButtonDelClicked();
}

void s21::CalcController::DoOperations(std::string &show_part,
                                       const std::string &button) {
  return model->Operations(show_part, button);
}

int s21::CalcController::DoRecalcPrintSimbol0(const std::string &button) {
  return model->RecalcPrintSimbol0(button);
}

int s21::CalcController::DoRecalcPrintSimbol1() {
  return model->RecalcPrintSimbol1();
}

int s21::CalcController::DoRecalcPrintSimbol2(const std::string &show_part,
                                              const std::string &button,
                                              int &delete_simb) {
  return model->RecalcPrintSimbol2(show_part, button, delete_simb);
}

int s21::CalcController::DoRecalcPrintSimbol3(std::string &show_part,
                                              const std::string &button) {
  return model->RecalcPrintSimbol3(show_part, button);
}

void s21::CalcController::DoButtonDotClicked(std::string &show_part) {
  return model->ButtonDotClicked(show_part);
}

void s21::CalcController::DoMathOperationsTotal(int plus_bracket,
                                                int print_simb,
                                                std::string &show_part,
                                                const std::string &button) {
  return model->MathOperationsTotal(plus_bracket, print_simb, show_part,
                                    button);
}
