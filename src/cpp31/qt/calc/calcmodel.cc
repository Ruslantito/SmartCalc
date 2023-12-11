#include "calcmodel.h"

void s21::CalcModel::SetInput(const std::string &input, double x) {
  input_ = input;
  x_ = x;
}

void s21::CalcModel::SetInput(const std::string &input) { input_ = input; }

void s21::CalcModel::SetInput(double x) { x_ = x; }

std::string s21::CalcModel::GetInput() const { return input_; }

double s21::CalcModel::GetX() const { return x_; }

void s21::CalcModel::SetResult(const std::string &result) { result_ = result; }

std::string s21::CalcModel::GetResult() const { return result_; }

void s21::CalcModel::SetEqualPressStatus(int equal_operation_pressed) {
  equal_operation_pressed_ = equal_operation_pressed;
}

int s21::CalcModel::GetEqualPressStatus() const {
  return equal_operation_pressed_;
}

void s21::CalcModel::SetFullOperation(const std::string &full_operation) {
  full_operation_ = full_operation;
}

std::string s21::CalcModel::GetFullOperation() const { return full_operation_; }

void s21::CalcModel::CalcTotal() {
  if (!Validate()) {
    CalcResult();
  } else {
    std::string result_final = "Error";
    SetResult(result_final);
  }
}

/**
 * @brief where these calculations actually take place
 *
 */
void s21::CalcModel::CalcResult() {
  std::string result_final = "Error";
  int err = 0;
  std::stack<NInput> stk;
  err = InputToInfixExpression(GetInput(), stk);
  if (!err) {
    std::stack<NInput> stk2;
    err = InfixExprToPostfix(stk, stk2);
    if (!err) {
      double res = 0;
      res = CalcRPN(stk2);
      std::stringstream ss;
      ss << res;
      result_final = ss.str();
      if (result_final == "inf") {
        result_final = "Error";
      }
    }
  }
  SetResult(result_final);
}

/**
 * @brief calculates an array of graphical data
 *
 * @param min_x
 * @param max_x
 * @param min_y
 * @param max_y
 * @param step
 * @param x
 * @param y
 */
void s21::CalcModel::CalcVector(const InputGraphLimits &limits,
                                std::vector<double> &x,
                                std::vector<double> &y) {
  double num_tmp = limits.min_x;
  while (num_tmp < limits.max_x) {
    SetInput(num_tmp);
    CalcResult();
    std::string res_str_tmp = GetResult();
    double res_db_tmp = std::stod(res_str_tmp);

    if (res_db_tmp >= limits.min_y && res_db_tmp <= limits.max_y) {
      x.push_back(num_tmp);
      y.push_back(res_db_tmp);
    } else {
      x.push_back(num_tmp);
      y.push_back(std::nan(""));
    }
    num_tmp += limits.step;
  }
}

/**
 * @brief checks for correct input
 *
 * @return int
 */
int s21::CalcModel::Validate() {
  std::string input_str = GetInput();
  State val_state = {0, 0, 0, 0, '0', 0};
  bool for_count = false;
  for (size_t i = 0; i < input_str.size(); i++) {
    if (std::isdigit(input_str[i]) || input_str[i] == 'x') {
      for_count = true;
      break;
    }
  }

  if (for_count && !input_str.empty()) {
    RemoveSpaces(input_str);
    RemoveUnary(input_str);
    CheckLastSign(input_str);
    ShrinkFuncNames(input_str);
    SetInput(input_str);
    val_state.prev = 0;
    std::vector<char> input(input_str.begin(), input_str.end());
    std::string list_func_names = "CSTcstqng";
    std::string list_arithmetic_expressions = "+-/*^m";
    for (size_t i = 0; i < input.size(); i++) {
      if ((input[i] >= '0') && (input[i] <= '9')) {
        if (val_state.printing_x) {
          val_state.error = 7;
          break;
        } else {
          val_state.printing_number = 1;
        }
      } else if (input[i] == '.') {
        if (val_state.dot_placed || val_state.printing_x) {
          val_state.error = 1;
          break;
        } else {
          val_state.dot_placed = 1;
        }
      } else if (input[i] == '(') {
        if (val_state.printing_x) {
          val_state.error = 7;
          break;
        } else {
          val_state.par_opened += 1;
          val_state.printing_number = 0;
        }
      } else if (input[i] == ')') {
        if (val_state.par_opened <= 0 || val_state.prev == '(') {
          val_state.error = 2;
          break;
        } else {
          val_state.par_opened -= 1;
        }
        val_state.printing_number = 0;
      } else if (list_arithmetic_expressions.find(input[i]) !=
                 std::string::npos) {
        if (!val_state.printing_number && (val_state.prev != ')') &&
            (val_state.prev != 'x')) {
          val_state.error = 3;
          break;
        } else {
          val_state.printing_number = 0;
          val_state.printing_x = 0;
        }
      } else if (list_func_names.find(input[i]) != std::string::npos) {
        std::string list_for_check = "(+-/*^m";
        if ((input[i + 1] != '(') ||
            (list_for_check.find(val_state.prev) == std::string::npos &&
             (val_state.prev != 0))) {
          val_state.error = 6;
          break;
        } else {
          val_state.printing_number = 0;
        }
      } else if (input[i] == 'x') {
        if (val_state.printing_number || (val_state.prev == ')') ||
            val_state.prev == 'x') {
          val_state.error = 7;
          break;
        } else {
          val_state.printing_x = 1;
          val_state.printing_number = 0;
        }
      } else if (input[i] == '=') {
        break;
      } else {
        val_state.error = 4;
        break;
      }
      if (!val_state.printing_number) {
        val_state.dot_placed = 0;
      }
      val_state.prev = input[i];
    }
    if (!val_state.error && (val_state.par_opened != 0)) {
      val_state.error = 5;
    }
  } else {
    val_state.error = 8;
  }
  return val_state.error;
}

/**
 * @brief used to remove extra spaces
 *
 * @param input_str
 */
void s21::CalcModel::RemoveSpaces(std::string &input_str) {
  input_str.erase(std::remove_if(input_str.begin(), input_str.end(), ::isspace),
                  input_str.end());
}

/**
 * @brief used to remove unary minuses
 *
 * @param input_str
 */
void s21::CalcModel::RemoveUnary(std::string &input_str) {
  if (!input_str.empty()) {
    char prev = *input_str.begin();
    if ((prev == '+') || (prev == '-')) {
      input_str.insert(0, "0");
    }
    for (size_t i = 1; i < input_str.size(); i++) {
      if ((((input_str)[i] == '+') || ((input_str)[i] == '-')) &&
          (prev == '(')) {
        input_str.insert(i, "0");
      }
      prev = (input_str)[i];
    }
  }
}

/**
 * @brief used to check the last character
 *
 * @param input_str
 */
void s21::CalcModel::CheckLastSign(std::string &input_str) {
  if (!input_str.empty()) {
    char prev = *(input_str.end() - 1);
    if ((prev == '+') || (prev == '-') || (prev == '*') || (prev == '/')) {
      input_str.resize(input_str.size() - 1);
    }
  }
}

void s21::CalcModel::ShrinkFuncNames(std::string &input_str) {
  const std::map<std::string, std::string> funcs{
      {"acos", "C"}, {"asin", "S"}, {"atan", "T"}, {"cos", "c"}, {"sin", "s"},
      {"tan", "t"},  {"mod", "m"},  {"sqrt", "q"}, {"log", "g"}, {"ln", "n"}};
  for (const auto &[toreplace, replacement] : funcs) {
    size_t pos;
    while ((pos = input_str.find(toreplace)) != std::string::npos) {
      input_str.replace(pos, toreplace.size(), replacement);
    }
  }
}

/**
 * @brief used to perform two actions with one function
 *
 * @param in_expectation
 * @param postfix
 */
void s21::CalcModel::PopPush(std::stack<NInput> &in_expectation,
                             std::stack<NInput> &postfix) {
  postfix.push(in_expectation.top());
  in_expectation.pop();
}

/**
 * @brief used to perform two actions with one function
 *
 * @param A
 * @param B
 * @return int
 */
int s21::CalcModel::PopStack(std::stack<NInput> &A, NInput &B) {
  if (A.empty()) {
    B.value = 0;
    B.type = kIncorrectT;
    return 1;
  }
  B = A.top();
  A.pop();
  return 0;
}

/**
 * @brief used to populate an array of structures with the desired data
 *
 * @param input_str
 * @param ch
 * @param input_tmp
 * @param str_len
 * @param i
 */
void s21::CalcModel::SplitData(const std::string &input_str, char ch,
                               NInput &input_tmp, int str_len, int &i) {
  if (std::isdigit(ch)) {
    int j = 0;
    std::string value_str;
    for (; j < str_len - i; j++) {
      char ch_tmp = (input_str)[i + j];
      if (std::isdigit(ch_tmp) || ch_tmp == '.') {
        value_str.push_back(ch_tmp);
      } else {
        break;
      }
    }
    i += j - 1;

    input_tmp.value = std::stod(value_str);
    input_tmp.type = kNumberT;
    input_tmp.priority = kNumberP;
  } else if (ch == 'x') {
    input_tmp.type = kXT;
    input_tmp.priority = kXP;
  } else if (ch == '+') {
    input_tmp.type = kPlusT;
    input_tmp.priority = kPlusP;
  } else if (ch == '-') {
    input_tmp.type = kMinusT;
    input_tmp.priority = kMinusP;
  } else if (ch == '*') {
    input_tmp.type = kMulT;
    input_tmp.priority = kMulP;
  } else if (ch == '/') {
    input_tmp.type = kDivT;
    input_tmp.priority = kDivP;
  } else if (ch == 'm') {
    input_tmp.type = kModT;
    input_tmp.priority = kModP;
  } else if (ch == '^') {
    input_tmp.type = kPowT;
    input_tmp.priority = kPowP;
  } else if (ch == 'c') {
    input_tmp.type = kCosT;
    input_tmp.priority = kCosP;
  } else if (ch == 's') {
    input_tmp.type = kSinT;
    input_tmp.priority = kSinP;
  } else if (ch == 't') {
    input_tmp.type = kTanT;
    input_tmp.priority = kTanP;
  } else if (ch == 'C') {
    input_tmp.type = kAcosT;
    input_tmp.priority = kAcosP;
  } else if (ch == 'S') {
    input_tmp.type = kAsinT;
    input_tmp.priority = kAsinP;
  } else if (ch == 'T') {
    input_tmp.type = kAtanT;
    input_tmp.priority = kAtanP;
  } else if (ch == 'q') {
    input_tmp.type = kSqrtT;
    input_tmp.priority = kSqrtP;
  } else if (ch == 'n') {
    input_tmp.type = kLnT;
    input_tmp.priority = kLnP;
  } else if (ch == 'g') {
    input_tmp.type = kLog10T;
    input_tmp.priority = kLog10P;
  } else if (ch == '(') {
    input_tmp.type = kParLeftT;
    input_tmp.priority = kParLeftP;
  } else if (ch == ')') {
    input_tmp.type = kParRightT;
    input_tmp.priority = kParRightP;
  }
}

/**
 * @brief used to convert input to infix notation
 *
 * @param input_str
 * @param stk
 * @return int
 */
int s21::CalcModel::InputToInfixExpression(const std::string &input_str,
                                           std::stack<NInput> &stk) {
  if (input_str.empty()) {
    return 1;
  }
  int str_len = input_str.size();
  for (int i = 0; i < str_len; i++) {
    char tmp;
    NInput input_tmp = {0.0, 0, kNumberT};
    tmp = (input_str)[i];
    if (i == (str_len - 1) && tmp == '=') {
      continue;
    }
    SplitData(input_str, tmp, input_tmp, str_len, i);
    stk.push(input_tmp);
  }
  return 0;
}

int s21::CalcModel::FindTypePriorErr(const std::stack<NInput> &in_expectation,
                                     const NInput &inf_tmp) {
  int err = 1;
  if (!in_expectation.empty()) {
    NInput q_top;
    q_top = in_expectation.top();
    err = q_top.type != kIncorrectT && q_top.type != kParLeftT ? 0 : 1;
    if (!err) {
      err = (q_top.priority > inf_tmp.priority) ||
                    ((q_top.priority == inf_tmp.priority) &&
                     (inf_tmp.type != kPowT))
                ? 0
                : 1;
    }
  }
  return err;
}

int s21::CalcModel::InfixExprToPostfix(std::stack<NInput> &infix,
                                       std::stack<NInput> &stk) {
  if (infix.empty()) {
    return 1;
  }
  std::stack<NInput> infix_tmp;
  while (!infix.empty()) {
    infix_tmp.push(infix.top());
    infix.pop();
  }
  std::stack<NInput> in_expectation;
  while (!infix_tmp.empty()) {
    NInput inf_tmp_top = infix_tmp.top();
    int inf_tmp_type = inf_tmp_top.type;
    if (inf_tmp_type >= kNumberT && inf_tmp_type <= kXT) {
      stk.push(inf_tmp_top);
    } else if (inf_tmp_type >= kCosT && inf_tmp_type <= kLog10T) {
      in_expectation.push(inf_tmp_top);
    } else if (inf_tmp_type >= kPlusT && inf_tmp_type <= kPowT) {
      while (!FindTypePriorErr(in_expectation, inf_tmp_top)) {
        PopPush(in_expectation, stk);
      }
      in_expectation.push(inf_tmp_top);
    } else if (inf_tmp_type == kParLeftT) {
      in_expectation.push(inf_tmp_top);
    } else if (inf_tmp_type == kParRightT) {
      NInput q_top = in_expectation.top();
      while (q_top.type != kParLeftT) {
        PopPush(in_expectation, stk);
        q_top = in_expectation.top();
      }
      in_expectation.pop();
      if (!in_expectation.empty()) {
        NInput tmp_n = in_expectation.top();
        if (tmp_n.type >= kCosT && tmp_n.type <= kLog10T) {
          PopPush(in_expectation, stk);
        }
      }
    }
    infix_tmp.pop();
  }
  while (!in_expectation.empty()) {
    PopPush(in_expectation, stk);
  }
  return 0;
}

/**
 * @brief perform arithmetic operations with elements
 * and return the result
 * @param postf_type
 * @param par_1
 * @param par_2
 * @return double
 */
double s21::CalcModel::CalcArithmetic(int postf_type, double par_1,
                                      double par_2) {
  double res = 0;
  if (postf_type == kPlusT) {
    res = par_1 + par_2;
  } else if (postf_type == kMinusT) {
    res = par_1 - par_2;
  } else if (postf_type == kMulT) {
    res = par_1 * par_2;
  } else if (postf_type == kDivT) {
    res = par_1 / par_2;
  } else if (postf_type == kModT) {
    res = fmod(par_1, par_2);
  } else if (postf_type == kPowT) {
    res = pow(par_1, par_2);
  } else if (postf_type == kCosT) {
    res = cos(par_2);
  } else if (postf_type == kSinT) {
    res = sin(par_2);
  } else if (postf_type == kTanT) {
    res = tan(par_2);
  } else if (postf_type == kAcosT) {
    res = acos(par_2);
  } else if (postf_type == kAsinT) {
    res = asin(par_2);
  } else if (postf_type == kAtanT) {
    res = atan(par_2);
  } else if (postf_type == kSqrtT) {
    res = sqrt(par_2);
  } else if (postf_type == kLnT) {
    res = log(par_2);
  } else if (postf_type == kLog10T) {
    res = log10(par_2);
  }
  return res;
}

double s21::CalcModel::CalcRPN(std::stack<NInput> &postfix) {
  std::stack<NInput> main_stack;
  std::stack<NInput> postfix_tmp;
  while (!postfix.empty()) {
    postfix_tmp.push(postfix.top());
    postfix.pop();
  }

  while (!postfix_tmp.empty()) {
    NInput res = {0.0, 0, kNumberT}, postf_arr = postfix_tmp.top();
    int postf_type = postf_arr.type;
    if (postf_type >= kNumberT && postf_type <= kXT) {
      if (postf_type) {
        res.value = GetX();
      } else {
        res.value = postf_arr.value;
      }
    } else {
      NInput tmp = {0.0, 0, kNumberT};
      PopStack(main_stack, tmp);
      double par_1 = tmp.value;
      double par_2 = 0.0;
      if (postf_type >= kPlusT && postf_type <= kPowT) {
        PopStack(main_stack, tmp);
        par_2 = tmp.value;
      }
      res.value = CalcArithmetic(postf_type, par_2, par_1);
    }
    main_stack.push(res);
    postfix_tmp.pop();
  }
  double result = 0.0;
  if (!main_stack.empty()) {
    result = main_stack.top().value;
  }
  return result;
}

int s21::CalcModel::InputInSize(const std::string &input) {
  if (input.size() < 256) {
    return 1;
  }
  return 0;
}

std::string s21::CalcModel::OnButtonDelClicked() {
  std::string last_str_1 = GetFullOperation();
  if (last_str_1.empty()) {
    return "";
  }

  std::string show_part_new;
  last_str_1.resize(last_str_1.size() - 1);
  char last_str_1_tmp = last_str_1.back();
  if (last_str_1_tmp != '-' && last_str_1_tmp != '+' && last_str_1_tmp != '/' &&
      last_str_1_tmp != '*') {
    for (int i = last_str_1.size(); i > 0; i--) {
      last_str_1_tmp = last_str_1.back();
      if (!std::isdigit(last_str_1_tmp) && last_str_1_tmp != '.') {
        break;
      }
      show_part_new.insert(0, 1, last_str_1_tmp);
      last_str_1.resize(last_str_1.size() - 1);
    }
  }

  std::string last_str_2 = GetFullOperation();
  std::string list_of_func_names_symb = "sndgtacolimqr";
  bool repeat = false;
  for (int i = last_str_2.size(); i > 0; i--) {
    if (list_of_func_names_symb.find(last_str_2.back()) != std::string::npos) {
      last_str_2.resize(last_str_2.size() - 1);
      repeat = true;
    } else if (!repeat) {
      last_str_2.resize(last_str_2.size() - 1);
      break;
    }
  }
  SetFullOperation(last_str_2);
  return show_part_new;
}

void s21::CalcModel::Operations(std::string &show_part,
                                const std::string &button) {
  std::string result_show = TakeLastDigits();
  if (button == "+/-" && !result_show.empty()) {
    double all_numbers;

    all_numbers = std::stod(result_show);
    if (all_numbers != 0.0) {
      double num_len_before = result_show.size();
      std::string show_part_new, show_part_tmp;
      int symb_after_comma = 0;
      std::string::size_type comma_position = result_show.find_first_of('.', 0);
      if (comma_position != std::string::npos) {
        symb_after_comma = num_len_before - comma_position - 1;
      }
      if (all_numbers < 0.0) {
        show_part_new = '(' + show_part_new + ')';
        num_len_before += 2;
      }

      all_numbers = all_numbers * -1;
      std::stringstream stream;
      stream << std::fixed << std::setprecision(symb_after_comma)
             << all_numbers;

      show_part_new = stream.str();
      show_part_tmp = show_part_new;
      std::string fullOperation_tmp = GetFullOperation();

      fullOperation_tmp.resize(fullOperation_tmp.size() - num_len_before);
      SetFullOperation(fullOperation_tmp);

      if (all_numbers < 0.0) {
        show_part_tmp = '(' + show_part_tmp + ')';
      }
      fullOperation_tmp += show_part_tmp;
      if (InputInSize(fullOperation_tmp)) {
        SetFullOperation(fullOperation_tmp);
        show_part = show_part_new;
      }
    }
  }
}

std::string s21::CalcModel::TakeLastDigits() {
  std::string result_show;
  std::string last_str_1 = GetFullOperation();
  if (!last_str_1.empty()) {
    char last_str_1_tmp = last_str_1.back();
    bool check_char_1 = false;
    bool check_char_0 = false;

    if (last_str_1_tmp == ')') {
      last_str_1.resize(last_str_1.size() - 1);
      last_str_1_tmp = last_str_1.back();
      check_char_1 = true;
      check_char_0 = true;
    }

    if (std::isdigit(last_str_1_tmp) || last_str_1_tmp == '.') {
      char last_char_1_tmp = '-';
      char last_char_0_tmp = '(';
      bool correct = true;
      for (int i = last_str_1.size(); i > 0; i--) {
        last_str_1_tmp = last_str_1.back();
        if (!std::isdigit(last_str_1_tmp) && last_str_1_tmp != '.') {
          if (check_char_1) {
            if (last_str_1_tmp == last_char_1_tmp) {
              check_char_1 = false;
            } else {
              correct = false;
              break;
            }
          } else if (check_char_0) {
            if (last_str_1_tmp != last_char_0_tmp) {
              correct = false;
            }
            break;
          } else {
            break;
          }
        }

        result_show.insert(0, 1, last_str_1_tmp);
        last_str_1.resize(last_str_1.size() - 1);
      }
      if (!correct) {
        result_show.clear();
      }
    }
  }
  return result_show;
}

void s21::CalcModel::MathOperationsTotal(int plus_bracket, int print_simb,
                                         std::string &show_part,
                                         const std::string &button) {
  if (print_simb) {
    std::string bracket = "";
    if (plus_bracket) {
      bracket = "(";
    }

    std::string fullOperation_tmp = GetFullOperation();
    fullOperation_tmp.append(button);
    fullOperation_tmp.append(bracket);

    if (InputInSize(fullOperation_tmp)) {
      SetFullOperation(fullOperation_tmp);
      show_part = "";
    }
  }
}

int s21::CalcModel::RecalcPrintSimbol0(const std::string &button) {
  int print_simb = 1;
  std::string tmp_str = GetFullOperation();
  std::string list_of_ariphmetics_sign_x = "+-*/x";
  if (list_of_ariphmetics_sign_x.find(tmp_str.back()) == std::string::npos) {
    if (std::isdigit(tmp_str.back()) && button.find(')') == std::string::npos &&
        button != "mod") {
      print_simb = 0;
    } else if (tmp_str.back() == ')' && button.find(')') == std::string::npos) {
      print_simb = 0;
    }
  }
  return print_simb;
}

int s21::CalcModel::RecalcPrintSimbol1() {
  int print_simb = 1;
  std::string tmp_str = GetFullOperation();
  std::string list_of_ariphmetics_sign = "+-*/";
  if (list_of_ariphmetics_sign.find(tmp_str.back()) == std::string::npos) {
    if (std::isdigit(tmp_str.back())) {
      print_simb = 0;
    } else if (tmp_str.back() == ')') {
      print_simb = 0;
    } else if (tmp_str.back() == 'x') {
      print_simb = 0;
    }
  }
  return print_simb;
}

int s21::CalcModel::RecalcPrintSimbol2(const std::string &show_part,
                                       const std::string &button,
                                       int &delete_simb) {
  int print_simb = 1;
  if (show_part.empty()) {
    std::string tmp_str = GetFullOperation();
    std::string list_of_func_names_symb_xb = "()sndgtacolimqrx";
    if (list_of_func_names_symb_xb.find(tmp_str.back()) == std::string::npos) {
      delete_simb = 1;
    }
    if (tmp_str.back() == '(') {
      print_simb = 0;
      if (button.find('-') != std::string::npos) {
        print_simb = 1;
      }
    } else if (tmp_str.size() > 1 && tmp_str.back() == '-' &&
               tmp_str.at(tmp_str.size() - 2) == '(') {
      print_simb = 0;
    }
  }
  return print_simb;
}

int s21::CalcModel::RecalcPrintSimbol3(std::string &show_part,
                                       const std::string &button) {
  if (GetEqualPressStatus()) {
    show_part = "";
    SetEqualPressStatus(0);
  }
  int print_simb = 1;
  std::string tmp_str = GetFullOperation();
  std::string list_of_ariphmetics_sign = "+-*/";
  if (list_of_ariphmetics_sign.find(tmp_str.back()) == std::string::npos) {
    std::string list_end_of_func_names_symb = "gnts";
    if (tmp_str.back() == ')') {
      print_simb = 0;
    } else if (list_end_of_func_names_symb.find(tmp_str.back()) !=
               std::string::npos) {
      print_simb = 0;
    } else if (tmp_str.back() == 'x') {
      print_simb = 0;
    } else if (button == "x" && std::isdigit(tmp_str.back())) {
      print_simb = 0;
    }
  }
  if (print_simb) {
    show_part.append(button);
  }
  return print_simb;
}

void s21::CalcModel::ButtonDotClicked(std::string &show_part) {
  if (GetEqualPressStatus()) {
    show_part = "";
    SetEqualPressStatus(0);
  }

  if (show_part.find('.') == std::string::npos) {
    if (std::isdigit(GetFullOperation().back())) {
      std::string fullOperation_tmp = GetFullOperation() + '.';
      if (InputInSize(fullOperation_tmp)) {
        show_part.append(".");
        SetFullOperation(fullOperation_tmp);
      }
    }
  }
}
