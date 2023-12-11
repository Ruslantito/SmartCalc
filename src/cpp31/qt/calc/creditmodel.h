#ifndef CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CREDITMODEL_H_
#define CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CREDITMODEL_H_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace s21 {
class CreditModel {
 public:
  struct InputCreditData {
    int total_value = 0;
    int duration_value = 0;
    double percent_value = 0;
    std::string duration_type_str = "";
    bool credit_type_bool = false;
    int duration_type_int = 0;
    int credit_type_int = 0;
  };

  void SetInput(const InputCreditData &input_data);
  void Calculate(std::string &monthly, std::string &percent,
                 std::string &total);

 private:
  InputCreditData input_{};
  double result_month_1_ = 0.0;
  double result_month_2_ = 0.0;
  double result_percent_ = 0.0;
  double result_total_ = 0.0;

  double GetTotalValue() const;
  int GetDurationType() const;
  double GetDurationValue() const;
  double GetPercentValue() const;
  int GetCreditType() const;

  void SetResult(double result_month_1, double result_month_2,
                 double result_percent, double result_total);

  double GetResultMonth1() const;
  double GetResultMonth2() const;
  double GetResultPercent() const;
  double GetResultTotal() const;
  void CreditCalc();
};
}  //  namespace s21

#endif  //  CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CREDITMODEL_H_
