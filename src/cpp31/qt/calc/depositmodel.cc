#include "depositmodel.h"

/**
 * @brief s21::DepositModel::SetInput
 * @param input_data
 */
void s21::DepositModel::SetInput(const InputDepositData &input_data) {
  input_ = input_data;
  input_.duration_type_int = InitializePeriodicity(input_.duration_type_str);
  input_.payment_frequency_type_int =
      InitializePeriodicity(input_.payment_frequency_type_str);
  input_.refill_frequency_type_int =
      InitializePeriodicity(input_.refill_frequency_type_str);
  input_.withdrawal_frequency_type_in =
      InitializePeriodicity(input_.withdrawal_frequency_type_str);
}

void s21::DepositModel::SetExtraInput(int sum_for_count,
                                      double key_rate_of_bank) {
  extra_sum_for_count_ = sum_for_count;
  extra_key_rate_of_bank_ = key_rate_of_bank;
}

void s21::DepositModel::SetExtraResultIncomeFree(
    const double &extra_result_income_free_tax) {
  extra_result_income_free_tax_ = extra_result_income_free_tax;
}

double s21::DepositModel::GetTotalValue() const { return input_.total_value; }

void s21::DepositModel::SetResult(double result_percent, double result_tax,
                                  double result_total,
                                  double result_incom_minus_tax) {
  result_tax_ = result_tax;
  result_percent_ = result_percent;
  result_total_ = result_total;
  result_incom_minus_tax_ = result_incom_minus_tax;
}

double s21::DepositModel::GetDurationValue() const {
  return input_.duration_value;
}

double s21::DepositModel::GetPercentValue() const {
  return input_.percent_value;
}

double s21::DepositModel::GetRefillValue() const { return input_.refill_value; }

double s21::DepositModel::GetTaxValue() const { return input_.tax_value; }

double s21::DepositModel::GetWithdrawalValue() const {
  return input_.withdrawal_value;
}

double s21::DepositModel::GetExtraSumForCount() const {
  return extra_sum_for_count_;
}

double s21::DepositModel::GetExtraKeyRateOfBank() const {
  return extra_key_rate_of_bank_;
}

double s21::DepositModel::GetExtraResultIncomeFree() const {
  return extra_result_income_free_tax_;
}

double s21::DepositModel::GetResultPercent() const { return result_percent_; }

double s21::DepositModel::GetResultTax() const { return result_tax_; }

double s21::DepositModel::GetResultTotal() const { return result_total_; }

double s21::DepositModel::GetResultIncomMinusTax() const {
  return result_incom_minus_tax_;
}

int s21::DepositModel::GetRefillCheck() const { return input_.refill_check; }

int s21::DepositModel::GetInterestCapitalizationCheck() const {
  return input_.interest_capitalization_check;
}

int s21::DepositModel::GetWithdrawalCheck() const {
  return input_.withdrawal_check;
}

int s21::DepositModel::GetDurationType() const {
  return input_.duration_type_int;
}

int s21::DepositModel::GetPaymentFrequencyType() const {
  return input_.payment_frequency_type_int;
}

int s21::DepositModel::GetRefillFrequencyType() const {
  return input_.refill_frequency_type_int;
}

int s21::DepositModel::GetWithdrawalFrequencyType() const {
  return input_.withdrawal_frequency_type_in;
}

std::tm s21::DepositModel::GetDepositDateStart() const {
  return input_.deposit_date_start;
}

void s21::DepositModel::Calculate(std::string &percent, std::string &tax,
                                  std::string &total,
                                  std::string &incom_minus_tax) {
  if (GetTotalValue() != 0 && GetDurationValue() != 0) {
    DepositCalc();
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << GetResultPercent();
    percent = stream.str();

    std::stringstream stream0;
    stream0 << std::fixed << std::setprecision(2) << GetResultTax();
    tax = stream0.str();

    std::stringstream stream1;
    stream1 << std::fixed << std::setprecision(2) << GetResultTotal();
    total = stream1.str();

    std::stringstream stream2;
    stream2 << std::fixed << std::setprecision(2) << GetResultIncomMinusTax();
    incom_minus_tax = stream2.str();
  }
}

void s21::DepositModel::CalculateExtra(double &extra_result_income_free_tax) {
  TaxFreeIncome();
  extra_result_income_free_tax = GetExtraResultIncomeFree();
}

void s21::DepositModel::DepositCalc() {
  double res_total_percent = 0;
  double res_total = GetTotalValue();
  double res_tax = 0.0, res_incom_minus_tax = 0.0;

  std::tm date_deposit_start = GetDepositDateStart();
  std::tm date_deposit_end = date_deposit_start;
  std::tm date_year_start = date_deposit_start;
  std::tm date_year_end = date_year_start;
  CalcDateAddMonth(date_year_end, 12);

  int duration_value = GetDurationValue();
  if (GetDurationType() == kCountInYears) {
    duration_value *= 12;
  }

  int refill_check = GetRefillCheck();
  int refill_period_for_count =
      CalcPeriodForCount(refill_check, GetRefillFrequencyType(), 0);
  int withdrawal_check = GetWithdrawalCheck();
  int withdrawal_period_for_count =
      CalcPeriodForCount(withdrawal_check, GetWithdrawalFrequencyType(), 0);

  int repeat_count_year = std::ceil(duration_value / 12.0);
  int duration_value_tmp = duration_value;

  for (int i = 0; i < repeat_count_year; ++i) {
    int repeat_count_months = std::min(12, duration_value_tmp);
    duration_value_tmp -= 12;

    int days_in_year = CalcDateDifferent(date_year_start, date_year_end);
    date_year_start = date_year_end;
    CalcDateAddMonth(date_year_end, 12);

    double percent_value = GetPercentValue() / 100;
    double percent_per_day = percent_value / days_in_year;

    int period_for_count = CalcPeriodForCount(GetInterestCapitalizationCheck(),
                                              GetPaymentFrequencyType(), 1);
    int count_refill = CalcCountStatus(refill_period_for_count);
    int count_withdrawal = CalcCountStatus(withdrawal_period_for_count);
    period_for_count = std::min(period_for_count, repeat_count_months);
    int count_total = CalcCountStatus(period_for_count);

    for (int j = 0; j < repeat_count_months; ++j) {
      std::vector<double> total_percent_total_percent_day{
          res_total, res_total_percent, percent_per_day};
      std::vector<int> period_total_refill_withdrawal_count{
          period_for_count, count_total, count_refill, count_withdrawal};
      CalcPercentByPeriod(date_deposit_start, date_deposit_end,
                          total_percent_total_percent_day,
                          period_total_refill_withdrawal_count);
      res_total = total_percent_total_percent_day.at(0);
      res_total_percent = total_percent_total_percent_day.at(1);

      if (count_total == 1) {
        period_for_count =
            std::min(period_for_count, repeat_count_months - j);  // - 1);
        count_total = CalcCountStatus(period_for_count);
      } else {
        count_total++;
      }
      if (count_refill == 1) {
        count_refill = CalcCountStatus(refill_period_for_count);
      } else {
        count_refill++;
      }
      if (count_withdrawal == 1) {
        count_withdrawal = CalcCountStatus(withdrawal_period_for_count);
      } else {
        count_withdrawal++;
      }
    }
  }

  if (!GetInterestCapitalizationCheck() ||
      GetPaymentFrequencyType() == kAtTheEnd) {
    res_total += res_total_percent;
  }

  if (res_total_percent > TaxFreeIncome()) {
    res_tax = (res_total_percent - TaxFreeIncome()) * GetTaxValue() / 100;
  }
  res_incom_minus_tax = res_total_percent - res_tax;
  SetResult(res_total_percent, res_tax, res_total, res_incom_minus_tax);
}

double s21::DepositModel::TaxFreeIncome() {
  double res = GetExtraSumForCount() * GetExtraKeyRateOfBank() / 100;
  SetExtraResultIncomeFree(res);
  return res;
}

int s21::DepositModel::CalcPeriodForCount(int check_status, int frequency_type,
                                          int for_count) {
  int period_for_count = 0;
  if (check_status > 0 && frequency_type != kAtTheEnd) {
    if (frequency_type == kDaily) {
      period_for_count = 1;
    } else if (frequency_type == kMonthly) {
      period_for_count = 1;
    } else if (frequency_type == kQuarterly) {
      period_for_count = 3;
    } else if (frequency_type == kHalfYearly) {
      period_for_count = 6;
    } else if (frequency_type == kYearly) {
      period_for_count = 12;
    }
  } else {
    period_for_count = 1;
    if (!for_count) {
      period_for_count = 15;
    }
  }
  return period_for_count;
}

int s21::DepositModel::CalcPercentByPeriod(
    std::tm &date_deposit_start, std::tm &date_deposit_end,
    std::vector<double> &total_percent_total_percent_day,
    const std::vector<int> &period_total_refill_withdrawal_count) {
  double res_total = total_percent_total_percent_day.at(0);
  double res_total_percent = total_percent_total_percent_day.at(1);
  double percent_per_day = total_percent_total_percent_day.at(2);

  int period_for_count = period_total_refill_withdrawal_count.at(0);
  int count_total = period_total_refill_withdrawal_count.at(1);
  int count_refill = period_total_refill_withdrawal_count.at(2);
  int count_withdrawal = period_total_refill_withdrawal_count.at(3);

  int res_total_negativ = 0;
  int repeat = 0;
  int days_in_deposit_for_count = 0;

  CalcRepeatAndDays(date_deposit_start, repeat, days_in_deposit_for_count,
                    period_for_count, count_total);
  date_deposit_end = date_deposit_start;
  CalcDateAddMonth(date_deposit_end, 1);
  date_deposit_start = date_deposit_end;

  for (int j = 0; j < repeat; ++j) {
    if (count_total > 0) {
      double percent_per_period =
          percent_per_day * res_total * days_in_deposit_for_count;
      res_total_percent += percent_per_period;
      if (!GetInterestCapitalizationCheck() ||
          GetPaymentFrequencyType() == kAtTheEnd) {
        continue;
      }
      res_total += percent_per_period;
    }
  }

  double res_total_tmp = res_total;
  if (count_refill > 0) {
    res_total_tmp += GetRefillValue();
  }
  if (count_withdrawal > 0) {
    res_total_tmp -= GetWithdrawalValue();
  }
  if (res_total_tmp < 0) {
    res_total_negativ = 1;
  } else {
    res_total = res_total_tmp;
  }

  auto it = total_percent_total_percent_day.begin();
  it = total_percent_total_percent_day.insert(it, res_total);
  it = total_percent_total_percent_day.begin();
  it++;
  total_percent_total_percent_day.insert(it, res_total_percent);

  return res_total_negativ;
}

void s21::DepositModel::CalcRepeatAndDays(const std::tm &date_deposit_start,
                                          int &repeat, int &days_for_count,
                                          int period_for_count,
                                          int count_total) {
  if (GetPaymentFrequencyType() == kDaily &&
      GetInterestCapitalizationCheck() > 0) {
    std::tm deposit_start_tmp = date_deposit_start;
    std::tm date_deposit_end_tmp = date_deposit_start;
    CalcDateAddMonth(date_deposit_end_tmp, period_for_count);
    int days_for_count_tmp =
        CalcDateDifferent(deposit_start_tmp, date_deposit_end_tmp);

    repeat = days_for_count_tmp;
    days_for_count = 1;
  } else if (GetPaymentFrequencyType() != kMonthly &&
             GetPaymentFrequencyType() != kAtTheEnd &&
             GetInterestCapitalizationCheck() > 0 && count_total > 0) {
    std::tm deposit_start_tmp = date_deposit_start;
    CalcDateAddMonth(deposit_start_tmp, ((period_for_count - 1) * -1));
    std::tm date_deposit_end_tmp = date_deposit_start;
    CalcDateAddMonth(date_deposit_end_tmp, 1);
    int days_for_count_tmp =
        CalcDateDifferent(deposit_start_tmp, date_deposit_end_tmp);

    repeat = 1;
    days_for_count = days_for_count_tmp;
  } else {
    std::tm deposit_start_tmp = date_deposit_start;
    std::tm date_deposit_end_tmp = date_deposit_start;
    CalcDateAddMonth(date_deposit_end_tmp, period_for_count);
    int days_for_count_tmp =
        CalcDateDifferent(deposit_start_tmp, date_deposit_end_tmp);

    repeat = 1;
    days_for_count = days_for_count_tmp;
  }
}

int s21::DepositModel::CalcCountStatus(int period_for_count) {
  return (period_for_count * -1) + 2;
}

double s21::DepositModel::CalcDateDifferent(const std::tm &date_start,
                                            const std::tm &date_end) {
  const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  long int n1 = date_start.tm_year * 365 + date_start.tm_mday;
  for (int i = 0; i < date_start.tm_mon - 1; i++) {
    n1 += monthDays[i];
  }
  n1 += CountLeapYears(date_start);

  long int n2 = date_end.tm_year * 365 + date_end.tm_mday;
  for (int i = 0; i < date_end.tm_mon - 1; i++) {
    n2 += monthDays[i];
  }
  n2 += CountLeapYears(date_end);

  return (n2 - n1);
}

int s21::DepositModel::CountLeapYears(const std::tm &date) {
  int years = date.tm_year;
  if (date.tm_mon <= 2) {
    years--;
  }
  return years / 4 - years / 100 + years / 400;
}

void s21::DepositModel::CalcDateAddMonth(std::tm &date, int months) {
  int years = 0;
  int month_tmp = 0;
  int calc_tmp = date.tm_mon + months;

  if (calc_tmp < 0) {
    calc_tmp = 12 + calc_tmp;
    years = std::ceil((calc_tmp / 12.0)) * -1;
  } else {
    years = calc_tmp / 12;
  }

  month_tmp = calc_tmp % 12;
  if (calc_tmp == 12) {
    month_tmp = 12;
    years -= 1;
  }
  date.tm_year += years;
  date.tm_mon = month_tmp;
}

int s21::DepositModel::InitializePeriodicity(const std::string &selected) {
  int assign = 0;
  if (selected == "Ежедневно") {
    assign = kDaily;
  } else if (selected == "Раз в месяц") {
    assign = kMonthly;
  } else if (selected == "Раз в квартал") {
    assign = kQuarterly;
  } else if (selected == "Раз в полгода") {
    assign = kHalfYearly;
  } else if (selected == "Раз в год") {
    assign = kYearly;
  } else if (selected == "В конце срока") {
    assign = kAtTheEnd;
  } else if (selected == "лет") {
    assign = kCountInYears;
  } else if (selected == "месяцев") {
    assign = kCountInMonths;
  }

  return assign;
}
