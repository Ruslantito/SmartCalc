#ifndef CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CALCMODEL_H_
#define CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CALCMODEL_H_

#include <ctype.h>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace s21 {
class CalcModel {
 public:
  typedef enum {
    kNumberT = 0,
    kXT = 1,
    kPlusT = 2,
    kMinusT = 3,
    kMulT = 4,
    kDivT = 5,
    kModT = 6,
    kPowT = 7,
    kCosT = 8,
    kSinT = 9,
    kTanT = 10,
    kAcosT = 11,
    kAsinT = 12,
    kAtanT = 13,
    kSqrtT = 14,
    kLnT = 15,
    kLog10T = 16,
    kParLeftT = 17,
    kParRightT = 18,
    kIncorrectT = 19,
  } TypeTT;

  struct NInput {
    double value = 0.0;
    int priority = 0;
    TypeTT type = {};
  };

  typedef enum {
    kNumberP = 0,
    kXP = 0,
    kPlusP = 1,
    kMinusP = 1,
    kMulP = 2,
    kDivP = 2,
    kModP = 2,
    kPowP = 3,
    kCosP = 4,
    kSinP = 4,
    kTanP = 4,
    kAcosP = 4,
    kAsinP = 4,
    kAtanP = 4,
    kSqrtP = 4,
    kLnP = 4,
    kLog10P = 4,
    kParLeftP = 5,
    kParRightP = 5,
  } PriorityP;

  struct State {
    int par_opened = 0;
    int dot_placed = 0;
    int printing_number = 0;
    int printing_x = 0;
    char prev = {};
    int error = 0;
  };

  struct InputGraphLimits {
    int min_x = 0;
    int max_x = 0;
    int min_y = 0;
    int max_y = 0;
    double step = 0.0;
  };

  void SetInput(const std::string &input, double x);
  std::string GetResult() const;
  void CalcVector(const InputGraphLimits &limits, std::vector<double> &x,
                  std::vector<double> &y);
  int Validate();

  void SetEqualPressStatus(int equal_operation_pressed);
  int GetEqualPressStatus() const;

  void SetFullOperation(const std::string &full_operation);
  std::string GetFullOperation() const;

  void CalcTotal();
  std::string OnButtonDelClicked();

  void Operations(std::string &show_part, const std::string &button);
  void MathOperationsTotal(int plus_bracket, int print_simb,
                           std::string &show_part, const std::string &button);
  int RecalcPrintSimbol0(const std::string &button);
  int RecalcPrintSimbol1();
  int RecalcPrintSimbol2(const std::string &show_part,
                         const std::string &button, int &delete_simb);
  int RecalcPrintSimbol3(std::string &show_part, const std::string &button);
  void ButtonDotClicked(std::string &show_part);

 private:
  std::string input_;
  std::string result_;
  std::string full_operation_;
  double x_ = 0.0;
  int equal_operation_pressed_ = 0;

  void SetInput(const std::string &input);
  void SetInput(double x);
  void SetResult(const std::string &result);
  std::string GetInput() const;
  double GetX() const;

  void CalcResult();
  void RemoveSpaces(std::string &input_str);
  void RemoveUnary(std::string &input_str);
  void CheckLastSign(std::string &input_str);

  void ShrinkFuncNames(std::string &input_str);
  void PopPush(std::stack<NInput> &in_expectation, std::stack<NInput> &postfix);
  int PopStack(std::stack<NInput> &A, NInput &B);
  void SplitData(const std::string &input_str, char ch, NInput &input_tmp,
                 int str_len, int &i);
  int InputToInfixExpression(const std::string &input_str,
                             std::stack<NInput> &stk);
  int FindTypePriorErr(const std::stack<NInput> &in_expectation,
                       const NInput &inf_tmp);
  int InfixExprToPostfix(std::stack<NInput> &infix, std::stack<NInput> &stk);
  double CalcArithmetic(int postf_type, double par_1, double par_2);
  double CalcRPN(std::stack<NInput> &postfix);
  int InputInSize(const std::string &input);
  std::string TakeLastDigits();
};
}  //  namespace s21

#endif  //  CPP3_SMARTCALC_SRC_CPP31_QT_CALC_CALCMODEL_H_
