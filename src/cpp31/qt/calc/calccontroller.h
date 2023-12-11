#ifndef CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CALCCONTROLLER_H_
#define CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CALCCONTROLLER_H_

#include <iostream>

#include "calcmodel.h"

namespace s21 {
class CalcController {
 public:
  CalcController();
  CalcController(const CalcController &other) = delete;
  CalcController(CalcController &&other) = delete;
  CalcController &operator=(const CalcController &other) = delete;
  CalcController &operator=(CalcController &&other) = delete;
  ~CalcController();

  void SetInputValue(const std::string &data, double x);
  std::string GetResultValue() const;

  void CalcVector(const CalcModel::InputGraphLimits &limits,
                  std::vector<double> &x, std::vector<double> &y);
  int Validate();

  void SetEqualPressStatus(int equal_operation_pressed);
  int GetEqualPressStatus() const;

  void SetFullOperation(const std::string &full_operation);
  std::string GetFullOperation() const;

  void DoCalcTotal();
  std::string ButtonDelClicked();

  void DoOperations(std::string &show_part, const std::string &button);
  int DoRecalcPrintSimbol0(const std::string &button);
  int DoRecalcPrintSimbol1();
  int DoRecalcPrintSimbol2(const std::string &show_part,
                           const std::string &button, int &delete_simb);
  int DoRecalcPrintSimbol3(std::string &show_part, const std::string &button);
  void DoButtonDotClicked(std::string &show_part);
  void DoMathOperationsTotal(int plus_bracket, int print_simb,
                             std::string &show_part, const std::string &button);

 private:
  s21::CalcModel *model;
};
}  //  namespace s21

#endif  //  CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CALCCONTROLLER_H_
