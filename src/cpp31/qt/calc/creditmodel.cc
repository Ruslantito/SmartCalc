#include "creditmodel.h"

void s21::CreditModel::SetInput(const InputCreditData &input_data) {
  input_ = input_data;
  if (input_data.duration_type_str == "месяцев") {
    input_.duration_type_int = 2;
  } else {
    input_.duration_type_int = 1;
  }

  if (input_data.credit_type_bool) {
    input_.credit_type_int = 2;
  } else {
    input_.credit_type_int = 1;
  }
}

double s21::CreditModel::GetTotalValue() const { return input_.total_value; }

int s21::CreditModel::GetDurationType() const {
  return input_.duration_type_int;
}

double s21::CreditModel::GetDurationValue() const {
  return input_.duration_value;
}

double s21::CreditModel::GetPercentValue() const {
  return input_.percent_value;
}

int s21::CreditModel::GetCreditType() const { return input_.credit_type_int; }

void s21::CreditModel::SetResult(double result_month_1, double result_month_2,
                                 double result_percent, double result_total) {
  result_month_1_ = result_month_1;
  result_month_2_ = result_month_2;
  result_percent_ = result_percent;
  result_total_ = result_total;
}

double s21::CreditModel::GetResultMonth1() const { return result_month_1_; }

double s21::CreditModel::GetResultMonth2() const { return result_month_2_; }

double s21::CreditModel::GetResultPercent() const { return result_percent_; }

double s21::CreditModel::GetResultTotal() const { return result_total_; }

void s21::CreditModel::Calculate(std::string &monthly, std::string &percent,
                                 std::string &total) {
  if (GetTotalValue() != 0 && GetDurationValue() != 0 &&
      GetPercentValue() != 0) {
    CreditCalc();
    if (GetCreditType() == 1) {
      std::stringstream stream;
      stream << std::fixed << std::setprecision(2) << GetResultMonth1();
      monthly = stream.str();
    } else {
      std::stringstream stream;
      stream << std::fixed << std::setprecision(2) << GetResultMonth1();
      std::string monthly_1 = stream.str();

      std::stringstream stream1;
      stream1 << std::fixed << std::setprecision(2) << GetResultMonth2();
      monthly = stream1.str() + " ... " + monthly_1;
    }
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << GetResultPercent();
    percent = stream.str();

    std::stringstream stream1;
    stream1 << std::fixed << std::setprecision(2) << GetResultTotal();
    total = stream1.str();
  }
}

void s21::CreditModel::CreditCalc() {
  double res_month_1 = 0.0, res_month_2 = 0.0;
  double res_total = 0.0, res_total_percent = 0.0;

  int credit_type = GetCreditType();
  int credit_duration_type = GetDurationType();
  double credit_duration_value = GetDurationValue();
  double credit_percent = GetPercentValue();
  double credit_sum = GetTotalValue();

  if (credit_duration_type == 1) {
    credit_duration_value *= 12.0;
  }
  credit_percent /= 100.0;
  if (credit_type == 1) {
    credit_percent /= 12.0;
    res_month_1 = credit_sum *
                  (credit_percent / (1.0 - pow((1.0 + credit_percent),
                                               credit_duration_value * -1.0)));

    res_month_1 = std::round(res_month_1 * 100) / 100;
    res_total = res_month_1 * credit_duration_value;
    res_total_percent = res_total - credit_sum;
  } else if (credit_type == 2) {
    double res_tmp = credit_sum / credit_duration_value;
    res_month_1 = res_tmp + credit_sum * credit_percent / 12.0;
    res_month_2 = res_month_1;
    double credit_sum_tmp = credit_sum - res_tmp;
    res_total = 0.0;
    res_total += res_month_1;
    for (int i = 1; i < credit_duration_value; i++) {
      res_tmp = credit_sum_tmp / (credit_duration_value - i);
      res_month_1 = credit_sum / credit_duration_value +
                    credit_sum_tmp * credit_percent / 12.0;
      credit_sum_tmp = credit_sum_tmp - res_tmp;
      res_total += res_month_1;
    }
    res_total_percent = res_total - credit_sum;
  }
  SetResult(res_month_1, res_month_2, res_total_percent, res_total);
}
