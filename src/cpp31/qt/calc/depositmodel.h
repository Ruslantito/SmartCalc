#ifndef CPP3_SMARTCALC_SRC_CPP31_QT_CALC_DEPOSITMODEL_H_
#define CPP3_SMARTCALC_SRC_CPP31_QT_CALC_DEPOSITMODEL_H_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace s21 {
class DepositModel {
 public:
  typedef enum {
    kDaily = 1,
    kMonthly = 2,
    kQuarterly = 3,
    kHalfYearly = 4,
    kYearly = 5,
    kAtTheEnd = 6,
    kCountInYears = 7,
    kCountInMonths = 8,
  } PeriodSelectionTypes;

  struct InputDepositData {
    int total_value = 0;
    int duration_value = 0;
    double percent_value = 0;
    int refill_value = 0;
    int withdrawal_value = 0;
    double tax_value = 0;
    std::string duration_type_str = "";
    std::string payment_frequency_type_str = "";
    std::string refill_frequency_type_str = "";
    std::string withdrawal_frequency_type_str = "";
    int interest_capitalization_check = 0;
    int refill_check = 0;
    int withdrawal_check = 0;
    std::tm deposit_date_start = {};

    int duration_type_int = 0;
    int payment_frequency_type_int = 0;
    int refill_frequency_type_int = 0;
    int withdrawal_frequency_type_in = 0;
  };

  void SetInput(const InputDepositData &input_data);
  void SetExtraInput(int sum_for_count, double key_rate_of_bank);
  void Calculate(std::string &percent, std::string &tax, std::string &total,
                 std::string &incom_minus_tax);
  void CalculateExtra(double &extra_result_income_free_tax);

 private:
  InputDepositData input_{};
  double extra_sum_for_count_ = 0.0;
  double extra_key_rate_of_bank_ = 0.0;
  double extra_result_income_free_tax_ = 0.0;
  double result_percent_ = 0.0;
  double result_tax_ = 0.0;
  double result_total_ = 0.0;
  double result_incom_minus_tax_ = 0.0;

  //  void InitFields();
  void SetExtraResultIncomeFree(const double &extra_result_income_free_tax);
  double GetTotalValue() const;

  void SetResult(double result_percent, double result_tax, double result_total,
                 double result_incom_minus_tax);

  double GetDurationValue() const;
  double GetPercentValue() const;
  double GetRefillValue() const;
  double GetTaxValue() const;
  double GetWithdrawalValue() const;
  double GetExtraSumForCount() const;
  double GetExtraKeyRateOfBank() const;
  double GetExtraResultIncomeFree() const;
  double GetResultPercent() const;
  double GetResultTax() const;
  double GetResultTotal() const;
  double GetResultIncomMinusTax() const;

  int GetRefillCheck() const;
  int GetInterestCapitalizationCheck() const;
  int GetWithdrawalCheck() const;

  int GetDurationType() const;
  int GetPaymentFrequencyType() const;
  int GetRefillFrequencyType() const;
  int GetWithdrawalFrequencyType() const;

  std::tm GetDepositDateStart() const;

  void DepositCalc();
  double TaxFreeIncome();
  int CalcPeriodForCount(int check_status, int frequency_type, int for_count);

  int CalcPercentByPeriod(
      std::tm &date_year_start, std::tm &date_year_end,
      std::vector<double> &total_percent_total_percent_day,
      const std::vector<int> &period_total_refill_withdrawal_count);

  void CalcRepeatAndDays(const std::tm &date_deposit_start, int &repeat,
                         int &days_for_count, int period_for_count,
                         int count_total);
  int CalcCountStatus(int period_for_count);
  double CalcDateDifferent(const std::tm &date_start, const std::tm &date_end);
  int CountLeapYears(const std::tm &date);
  void CalcDateAddMonth(std::tm &date, int months);
  int InitializePeriodicity(const std::string &selected);
};
}  //  namespace s21

#endif  //  CPP3_SMARTCALC_SRC_CPP31_QT_CALC_DEPOSITMODEL_H_
