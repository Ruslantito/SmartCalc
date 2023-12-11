#ifndef CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CREDITCONTROLLER_H_
#define CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CREDITCONTROLLER_H_

#include <iostream>

#include "creditmodel.h"

namespace s21 {
class CreditController {
 public:
  CreditController();
  CreditController(const CreditController &other) = delete;
  CreditController(CreditController &&other) = delete;
  CreditController &operator=(const CreditController &other) = delete;
  CreditController &operator=(CreditController &&other) = delete;
  ~CreditController();

  void SetInput(const CreditModel::InputCreditData &input_data);

  void Calculate(std::string &monthly, std::string &percent,
                 std::string &total);

 private:
  s21::CreditModel *model;
};
}  //  namespace s21

#endif  //  CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CREDITCONTROLLER_H_
