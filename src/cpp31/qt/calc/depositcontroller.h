#ifndef CPP3_SMARTCALC_SRC_CPP31_QT_CALC_DEPOSITCONTROLLER_H_
#define CPP3_SMARTCALC_SRC_CPP31_QT_CALC_DEPOSITCONTROLLER_H_

#include "depositmodel.h"

namespace s21 {
class DepositController {
 public:
  DepositController();
  DepositController(const DepositController &other) = delete;
  DepositController(DepositController &&other) = delete;
  DepositController &operator=(const DepositController &other) = delete;
  DepositController &operator=(DepositController &&other) = delete;
  ~DepositController();

  void SetInput(const DepositModel::InputDepositData &input_data);
  void SetExtraInput(int sum_for_count, double key_rate_of_bank);
  void Calculate(std::string &percent, std::string &tax, std::string &total,
                 std::string &incom_minus_tax);
  void CalculateExtra(double &extra_result_income_free_tax);

 private:
  s21::DepositModel *model;
};
}  //  namespace s21

#endif  //  CPP3_SMARTCALC_SRC_CPP31_QT_CALC_DEPOSITCONTROLLER_H_
