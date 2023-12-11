#include <gtest/gtest.h>
#include "../cpp31/qt/calc/depositmodel.h"
#include "../cpp31/qt/calc/creditmodel.h"
#include "../cpp31/qt/calc/calcmodel.h"


s21::DepositModel model_deposit;
s21::CreditModel model_credit;
s21::CalcModel model_calc;


TEST(Deposit, Test_1) { 
    int deposit_total_value = 100000.0;
    int deposit_duration_value = 12.0;
    double deposit_percent_value = 5.0;
    int deposit_refill_value = 0.0;
    int deposit_withdrawal_value = 0.0;

    int deposit_refill_check = 0;
    int deposit_interest_capitalization_check = 0;
    int deposit_withdrawal_check = 0;

    std::string deposit_duration_type = "лет";
    std::string deposit_refill_frequency_type = "Раз в месяц";
    std::string deposit_payment_frequency_type = "Раз в месяц";
    std::string deposit_withdrawal_frequency_type = "Раз в месяц";

    std::tm deposit_date_start;
    deposit_date_start.tm_mday = 1;
    deposit_date_start.tm_mon = 2;
    deposit_date_start.tm_year = 2023;

    double extra_sum_for_count = 1000000.0;
    double extra_key_rate_of_bank = 7.5; 
    double deposit_tax_value = 13.0;

    std::string percent, tax, total, incom_minus_tax;
    std::string res_percent = "60000.00";
    std::string res_tax = "0.00";
    std::string res_total = "160000.00";
    std::string res_incom_minus_tax = "60000.00";


    s21::DepositModel::InputDepositData input_data {
        deposit_total_value,
        deposit_duration_value,
        deposit_percent_value,
        deposit_refill_value,
        deposit_withdrawal_value,
        deposit_tax_value,
        deposit_duration_type,
        deposit_payment_frequency_type,
        deposit_refill_frequency_type,
        deposit_withdrawal_frequency_type,
        deposit_interest_capitalization_check,
        deposit_refill_check,
        deposit_withdrawal_check,
        deposit_date_start,
        0, 0, 0, 0};

    model_deposit.SetInput(input_data);
    model_deposit.SetExtraInput(extra_sum_for_count, extra_key_rate_of_bank);
    model_deposit.Calculate(percent, tax, total, incom_minus_tax);

    EXPECT_EQ(percent, res_percent);
    EXPECT_EQ(tax, res_tax);
    EXPECT_EQ(total, res_total);
    EXPECT_EQ(incom_minus_tax, res_incom_minus_tax);
}

TEST(Deposit, Test_2) { 
    int deposit_total_value = 100000.0;
    int deposit_duration_value = 12.0;
    double deposit_percent_value = 5.0;
    int deposit_refill_value = 0.0;
    int deposit_withdrawal_value = 0.0;

    int deposit_refill_check = 0;
    int deposit_interest_capitalization_check = 2;
    int deposit_withdrawal_check = 0;

    std::string deposit_duration_type = "лет";
    std::string deposit_refill_frequency_type = "Раз в месяц";
    std::string deposit_payment_frequency_type = "Раз в месяц";
    std::string deposit_withdrawal_frequency_type = "Раз в месяц";

    std::tm deposit_date_start;
    deposit_date_start.tm_mday = 1;
    deposit_date_start.tm_mon = 2;
    deposit_date_start.tm_year = 2023;

    double extra_sum_for_count = 1000000.0;
    double extra_key_rate_of_bank = 7.5; 
    double deposit_tax_value = 13.0;

    std::string percent, tax, total, incom_minus_tax;
    std::string res_percent = "81984.73";
    std::string res_tax = "908.01";
    std::string res_total = "181984.73";
    std::string res_incom_minus_tax = "81076.71";

    s21::DepositModel::InputDepositData input_data {
        deposit_total_value,
        deposit_duration_value,
        deposit_percent_value,
        deposit_refill_value,
        deposit_withdrawal_value,
        deposit_tax_value,
        deposit_duration_type,
        deposit_payment_frequency_type,
        deposit_refill_frequency_type,
        deposit_withdrawal_frequency_type,
        deposit_interest_capitalization_check,
        deposit_refill_check,
        deposit_withdrawal_check,
        deposit_date_start,
        0, 0, 0, 0};

    model_deposit.SetInput(input_data);
    model_deposit.SetExtraInput(extra_sum_for_count, extra_key_rate_of_bank);
    model_deposit.Calculate(percent, tax, total, incom_minus_tax);

    EXPECT_EQ(percent, res_percent);
    EXPECT_EQ(tax, res_tax);
    EXPECT_EQ(total, res_total);
    EXPECT_EQ(incom_minus_tax, res_incom_minus_tax);
}

TEST(Deposit, Test_3) { 
    int deposit_total_value = 10000000.0;
    int deposit_duration_value = 12.0;
    double deposit_percent_value = 5.0;
    int deposit_refill_value = 0.0;
    int deposit_withdrawal_value = 0.0;

    int deposit_refill_check = 0;
    int deposit_interest_capitalization_check = 2;
    int deposit_withdrawal_check = 0;

    std::string deposit_duration_type = "лет";
    std::string deposit_refill_frequency_type = "Раз в месяц";
    std::string deposit_payment_frequency_type = "Раз в месяц";
    std::string deposit_withdrawal_frequency_type = "Раз в месяц";

    std::tm deposit_date_start;
    deposit_date_start.tm_mday = 1;
    deposit_date_start.tm_mon = 2;
    deposit_date_start.tm_year = 2023;

    double extra_sum_for_count = 1000000.0;
    double extra_key_rate_of_bank = 7.5; 
    double deposit_tax_value = 13.0;

    std::string percent, tax, total, incom_minus_tax;
    std::string res_percent = "8198472.62";
    std::string res_tax = "1056051.44";
    std::string res_total = "18198472.62";
    std::string res_incom_minus_tax = "7142421.18";

    s21::DepositModel::InputDepositData input_data {
        deposit_total_value,
        deposit_duration_value,
        deposit_percent_value,
        deposit_refill_value,
        deposit_withdrawal_value,
        deposit_tax_value,
        deposit_duration_type,
        deposit_payment_frequency_type,
        deposit_refill_frequency_type,
        deposit_withdrawal_frequency_type,
        deposit_interest_capitalization_check,
        deposit_refill_check,
        deposit_withdrawal_check,
        deposit_date_start,
        0, 0, 0, 0};

    model_deposit.SetInput(input_data);
    model_deposit.SetExtraInput(extra_sum_for_count, extra_key_rate_of_bank);
    model_deposit.Calculate(percent, tax, total, incom_minus_tax);

    EXPECT_EQ(percent, res_percent);
    EXPECT_EQ(tax, res_tax);
    EXPECT_EQ(total, res_total);
    EXPECT_EQ(incom_minus_tax, res_incom_minus_tax);
}

TEST(Deposit, Test_4) { 
    int deposit_total_value = 10000000.0;
    int deposit_duration_value = 12.0;
    double deposit_percent_value = 5.0;
    int deposit_refill_value = 1000.0;
    int deposit_withdrawal_value = 0.0;

    int deposit_refill_check = 2;
    int deposit_interest_capitalization_check = 2;
    int deposit_withdrawal_check = 0;

    std::string deposit_duration_type = "лет";
    std::string deposit_payment_frequency_type = "Ежедневно";
    std::string deposit_refill_frequency_type = "Раз в месяц";
    std::string deposit_withdrawal_frequency_type = "Раз в месяц";

    std::tm deposit_date_start;
    deposit_date_start.tm_mday = 1;
    deposit_date_start.tm_mon = 2;
    deposit_date_start.tm_year = 2023;

    double extra_sum_for_count = 1000000.0;
    double extra_key_rate_of_bank = 7.5; 
    double deposit_tax_value = 13.0;

    std::string percent, tax, total, incom_minus_tax;
    std::string res_percent = "8273367.23";
    std::string res_tax = "1065787.74";
    std::string res_total = "18417367.23";
    std::string res_incom_minus_tax = "7207579.49";

    s21::DepositModel::InputDepositData input_data {
        deposit_total_value,
        deposit_duration_value,
        deposit_percent_value,
        deposit_refill_value,
        deposit_withdrawal_value,
        deposit_tax_value,
        deposit_duration_type,
        deposit_payment_frequency_type,
        deposit_refill_frequency_type,
        deposit_withdrawal_frequency_type,
        deposit_interest_capitalization_check,
        deposit_refill_check,
        deposit_withdrawal_check,
        deposit_date_start,
        0, 0, 0, 0};

    model_deposit.SetInput(input_data);
    model_deposit.SetExtraInput(extra_sum_for_count, extra_key_rate_of_bank);
    model_deposit.Calculate(percent, tax, total, incom_minus_tax);

    EXPECT_EQ(percent, res_percent);
    EXPECT_EQ(tax, res_tax);
    EXPECT_EQ(total, res_total);
    EXPECT_EQ(incom_minus_tax, res_incom_minus_tax);
}

TEST(Deposit, Test_5) { 
    int deposit_total_value = 10000000.0;
    int deposit_duration_value = 12.0;
    double deposit_percent_value = 5.0;
    int deposit_refill_value = 1000.0;
    int deposit_withdrawal_value = 0.0;

    int deposit_refill_check = 2;
    int deposit_interest_capitalization_check = 2;
    int deposit_withdrawal_check = 0;

    std::string deposit_duration_type = "лет";
    std::string deposit_payment_frequency_type = "Раз в квартал";
    std::string deposit_refill_frequency_type = "Раз в месяц";
    std::string deposit_withdrawal_frequency_type = "Раз в месяц";

    std::tm deposit_date_start;
    deposit_date_start.tm_mday = 1;
    deposit_date_start.tm_mon = 2;
    deposit_date_start.tm_year = 2023;

    double extra_sum_for_count = 1000000.0;
    double extra_key_rate_of_bank = 7.5; 
    double deposit_tax_value = 13.0;

    std::string percent, tax, total, incom_minus_tax;
    std::string res_percent = "8206880.27";
    std::string res_tax = "1057144.44";
    std::string res_total = "18350880.27";
    std::string res_incom_minus_tax = "7149735.84";

    s21::DepositModel::InputDepositData input_data {
        deposit_total_value,
        deposit_duration_value,
        deposit_percent_value,
        deposit_refill_value,
        deposit_withdrawal_value,
        deposit_tax_value,
        deposit_duration_type,
        deposit_payment_frequency_type,
        deposit_refill_frequency_type,
        deposit_withdrawal_frequency_type,
        deposit_interest_capitalization_check,
        deposit_refill_check,
        deposit_withdrawal_check,
        deposit_date_start,
        0, 0, 0, 0};

    model_deposit.SetInput(input_data);
    model_deposit.SetExtraInput(extra_sum_for_count, extra_key_rate_of_bank);
    model_deposit.Calculate(percent, tax, total, incom_minus_tax);

    EXPECT_EQ(percent, res_percent);
    EXPECT_EQ(tax, res_tax);
    EXPECT_EQ(total, res_total);
    EXPECT_EQ(incom_minus_tax, res_incom_minus_tax);
}

TEST(Deposit, Test_6) { 
    int deposit_total_value = 10000000.0;
    int deposit_duration_value = 12.0;
    double deposit_percent_value = 5.0;
    int deposit_refill_value = 1000.0;
    int deposit_withdrawal_value = 500.0;

    int deposit_refill_check = 2;
    int deposit_interest_capitalization_check = 2;
    int deposit_withdrawal_check = 2;

    std::string deposit_duration_type = "лет";
    std::string deposit_payment_frequency_type = "Раз в полгода";
    std::string deposit_refill_frequency_type = "Раз в год";
    std::string deposit_withdrawal_frequency_type = "Раз в месяц";

    std::tm deposit_date_start;
    deposit_date_start.tm_mday = 1;
    deposit_date_start.tm_mon = 2;
    deposit_date_start.tm_year = 2023;

    double extra_sum_for_count = 1000000.0;
    double extra_key_rate_of_bank = 7.5; 
    double deposit_tax_value = 13.0;

    std::string percent, tax, total, incom_minus_tax;
    std::string res_percent = "8064148.91";
    std::string res_tax = "1038589.36";
    std::string res_total = "18004148.91";
    std::string res_incom_minus_tax = "7025559.55";

    s21::DepositModel::InputDepositData input_data {
        deposit_total_value,
        deposit_duration_value,
        deposit_percent_value,
        deposit_refill_value,
        deposit_withdrawal_value,
        deposit_tax_value,
        deposit_duration_type,
        deposit_payment_frequency_type,
        deposit_refill_frequency_type,
        deposit_withdrawal_frequency_type,
        deposit_interest_capitalization_check,
        deposit_refill_check,
        deposit_withdrawal_check,
        deposit_date_start,
        0, 0, 0, 0};

    model_deposit.SetInput(input_data);
    model_deposit.SetExtraInput(extra_sum_for_count, extra_key_rate_of_bank);
    model_deposit.Calculate(percent, tax, total, incom_minus_tax);

    EXPECT_EQ(percent, res_percent);
    EXPECT_EQ(tax, res_tax);
    EXPECT_EQ(total, res_total);
    EXPECT_EQ(incom_minus_tax, res_incom_minus_tax);
}

TEST(Deposit, Test_7) { 
    double extra_sum_for_count = 1000000.0;
    double extra_key_rate_of_bank = 7.5;

    double extra_res_income_free_tax;
    double res_extra_res_income_free_tax = 75000.0;

    model_deposit.SetExtraInput(extra_sum_for_count, extra_key_rate_of_bank);
    model_deposit.CalculateExtra(extra_res_income_free_tax);

    EXPECT_EQ(extra_res_income_free_tax, res_extra_res_income_free_tax);
}


TEST(Credit, Test_1) { 
    int credit_sum = 150500;
    std::string dur_type = "лет";
    int dur_value = 2;
    double credit_percent = 5.0;
    bool credit_type = false;

    std::string month, percent, total;
    std::string res_month = "6602.64";
    std::string res_percent = "7963.36";
    std::string res_total = "158463.36";
    s21::CreditModel::InputCreditData input_data {
                            credit_sum,
                            dur_value,
                            credit_percent,
                            dur_type,
                            credit_type,
                            0, 0};

    model_credit.SetInput(input_data);
    model_credit.Calculate(month, percent, total);

    EXPECT_EQ(month, res_month);
    EXPECT_EQ(percent, res_percent);
    EXPECT_EQ(total, res_total);
}

TEST(Credit, Test_2) { 
    int credit_sum = 150500.0;
    std::string dur_type = "лет";
    int dur_value = 2.0;
    double credit_percent = 5.0;
    bool credit_type = true;

    std::string month, percent, total;
    std::string res_month = "6897.92 ... 6296.96";
    std::string res_percent = "7838.54";
    std::string res_total = "158338.54";
    s21::CreditModel::InputCreditData input_data {
                            credit_sum,
                            dur_value,
                            credit_percent,
                            dur_type,
                            credit_type,
                            0, 0};

    model_credit.SetInput(input_data);
    model_credit.Calculate(month, percent, total);

    EXPECT_EQ(month, res_month);
    EXPECT_EQ(percent, res_percent);
    EXPECT_EQ(total, res_total);
}


TEST(Calc, Test_1) {     
    std::string data = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
    double x = 0.0;
    std::string result;
    std::string res_ff = "3.00012";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_2) { 
    std::string data = "3 + 5 mod (6 - 5.4)";
    double x = 0.0;

    std::string result;
    std::string res_ff = "3.2";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_3) { 
    std::string data = "sin(2)";
    double x = 0.0;

    std::string result;
    std::string res_ff = "0.909297";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_4) { 
    std::string data = "3 + sin(cos(tan(0.8))) - acos(asin(atan(0.8))) * sqrt(1.1) / ln(5) ^ log(100)";
    double x = 0.0;

    std::string result;
    std::string res_ff = "3.19431";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_5) { 
    std::string data = "sqrt(-2)";
    double x = 0.0;

    std::string result;
    std::string res_ff = "nan";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_6) { 

    std::string data = "sin(x)";
    double xx = 0.0;

    std::vector<double> x, y;
    int inputMinX = 1;
    int inputMaxX = 5;
    int inputMinY = -5;
    int inputMaxY = 5;
    double step = 1;
    s21::CalcModel::InputGraphLimits GraphInputLimits{
        inputMinX, 
        inputMaxX, 
        inputMinY, 
        inputMaxY, 
        step};

    std::vector<double> res_x{ 1, 2, 3, 4 };
    std::vector<double> res_y{ 0, 0.638961, 0.890577, 0.983028 } ; 
    
    model_calc.SetInput(data, xx);
    model_calc.CalcVector(GraphInputLimits, x, y);
    
    EXPECT_EQ(x, res_x);
    EXPECT_EQ(y, res_y);
}

TEST(Calc, Test_7) { 
    std::string data = "sin(x)";
    double x = 1.0;

    std::string result;
    std::string res_ff = "0.841471";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_8) { 
    std::string data = "3 + sin(cos(tan(0.8))) - acos(asin(atan(0.8)))";
    std::string data_back;
    std::string res_data = "3 + sin(cos(tan(0.8))) - acos(asin(atan(0.8)))";
 
    model_calc.SetFullOperation(data);
    data_back = model_calc.GetFullOperation();
    
    EXPECT_EQ(data_back, res_data);
}

TEST(Calc, Test_9) { 
    std::string data = "3 + sin(cos(tan(0.8))) - acos(asin(atan(0.8)))";
    std::string data_back, res_data = "3 + sin(cos(tan(0.8))) - acos(asin(atan(0.8)))";
    std::string show_part_back, res_show_part = "3 + sin(cos(tan(0.8))) - acos(asin(atan(0.8";
 
    model_calc.SetFullOperation(data);
    data_back = model_calc.GetFullOperation();
    
    EXPECT_EQ(data_back, res_data);
}

TEST(Calc, Test_10) { 
    std::string data = "3 + sin(cos(tan(0.8))) - acos(asin(atan(0.128)))";
    std::string back_number, res_back_number;
 
    model_calc.SetFullOperation(data);

    model_calc.OnButtonDelClicked();
    model_calc.OnButtonDelClicked();
    model_calc.OnButtonDelClicked();
    back_number = model_calc.OnButtonDelClicked();
    res_back_number = "0.12";
    EXPECT_EQ(back_number, res_back_number);

    back_number = model_calc.OnButtonDelClicked();
    res_back_number = "0.1";
    EXPECT_EQ(back_number, res_back_number);
}

TEST(Calc, Test_11) { 
    std::string data = "3.128";
    std::string res_data = "3.128";
 
    model_calc.SetFullOperation(data);
    model_calc.ButtonDotClicked(data);
    EXPECT_EQ(data, res_data);

    res_data = model_calc.GetFullOperation();
    EXPECT_EQ(data, res_data);
}

TEST(Calc, Test_12) { 
    std::string data = "3128";
    std::string res_data = "3128.";
 
    model_calc.SetFullOperation(data);
    model_calc.ButtonDotClicked(data);
    EXPECT_EQ(data, res_data);

    res_data = model_calc.GetFullOperation();
    EXPECT_EQ(data, res_data);
}

TEST(Calc, Test_13) { 
    std::string data = "3.13";
    std::string res_data = "-3.13";
    std::string data_2 = "(-3.13)";
    std::string button = "+/-";
 
    model_calc.SetFullOperation(data);
    model_calc.Operations(data, button);

    EXPECT_EQ(data, res_data);

    res_data = model_calc.GetFullOperation();
    EXPECT_EQ(data_2, res_data);
}

TEST(Calc, Test_14) { 
    std::string data = "3128";
    std::string res_data = "3128";
 
    model_calc.SetFullOperation(data);
    EXPECT_EQ(data, res_data);

    std::string button = "+";
    int print_simb, res_print_simb = 0;
    print_simb = model_calc.RecalcPrintSimbol0(button);

    EXPECT_EQ(print_simb, res_print_simb);
}

TEST(Calc, Test_15) { 
    std::string data = "3128+";
    std::string res_data = "3128+";
 
    model_calc.SetFullOperation(data);
    EXPECT_EQ(data, res_data);

    std::string button = "+";
    int print_simb, res_print_simb = 1;
    print_simb = model_calc.RecalcPrintSimbol0(button);

    EXPECT_EQ(print_simb, res_print_simb);
}

TEST(Calc, Test_16) { 
    std::string data = "3128";
    std::string res_data = "3128";
 
    model_calc.SetFullOperation(data);
    EXPECT_EQ(data, res_data);

    int print_simb, res_print_simb = 0;
    print_simb = model_calc.RecalcPrintSimbol1();

    EXPECT_EQ(print_simb, res_print_simb);
}

TEST(Calc, Test_17) { 
    std::string data = "3128+";
    std::string res_data = "3128+";
 
    model_calc.SetFullOperation(data);
    EXPECT_EQ(data, res_data);

    int print_simb, res_print_simb = 1;
    print_simb = model_calc.RecalcPrintSimbol1();

    EXPECT_EQ(print_simb, res_print_simb);
}

TEST(Calc, Test_18) { 
    std::string data = "3128+";
    std::string show_part = "", res_show_part;
    std::string res_data = "3128+";
    int delete_simb = 0, res_delete_simb = 1;
 
    model_calc.SetFullOperation(data);
    EXPECT_EQ(data, res_data);

    std::string button = "-";
    int print_simb, res_print_simb = 1;
    print_simb = model_calc.RecalcPrintSimbol2(show_part, button, delete_simb);

    EXPECT_EQ(print_simb, res_print_simb);
    EXPECT_EQ(delete_simb, res_delete_simb);
}

TEST(Calc, Test_19) { 
    std::string data = "3128";
    std::string show_part = "", res_show_part;
    std::string res_data = "3128";
    int delete_simb = 0, res_delete_simb = 1;
 
    model_calc.SetFullOperation(data);
    EXPECT_EQ(data, res_data);

    std::string button = "+";
    int print_simb, res_print_simb = 1;
    print_simb = model_calc.RecalcPrintSimbol2(show_part, button, delete_simb);

    EXPECT_EQ(print_simb, res_print_simb);
    EXPECT_EQ(delete_simb, res_delete_simb);
}

TEST(Calc, Test_20) { 
    std::string data = "3128+";
    std::string res_data = "3128+";
    std::string show_part = "1";
    std::string res_show_part = "13";

    model_calc.SetFullOperation(data);
    EXPECT_EQ(data, res_data);

    std::string button = "3";
    int print_simb, res_print_simb = 1;
    print_simb = model_calc.RecalcPrintSimbol3(show_part, button);

    EXPECT_EQ(print_simb, res_print_simb);
    EXPECT_EQ(show_part, res_show_part);
}

TEST(Calc, Test_21) { 
    std::string data = "(3128+4)";
    std::string res_data = "(3128+4)";
    std::string show_part = "1";
    std::string res_show_part = "1";

    model_calc.SetFullOperation(data);
    EXPECT_EQ(data, res_data);

    std::string button = "3";
    int print_simb, res_print_simb = 0;
    print_simb = model_calc.RecalcPrintSimbol3(show_part, button);

    EXPECT_EQ(print_simb, res_print_simb);
    EXPECT_EQ(show_part, res_show_part);
}

TEST(Calc, Test_22) { 
    std::string data = "3128+";
    std::string res_data = "3128+";
    std::string res_data_2 = "3128+3";

    std::string show_part = "3";
    std::string res_show_part = "";

    int plus_bracket = 0;
    int print_simb = 1;
    
    model_calc.SetFullOperation(data);
    EXPECT_EQ(data, res_data);

    std::string button = "3";
    model_calc.MathOperationsTotal(plus_bracket, print_simb, show_part, button);
    EXPECT_EQ(show_part, res_show_part);
    
    res_data = model_calc.GetFullOperation();
    EXPECT_EQ(res_data_2, res_data);
}

TEST(Calc, Test_23) {     
    std::string data = "sin(1)-(-sin(1))";
    double x = 0.0;
    std::string result;
    std::string res_ff = "1.68294";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_24) {     
    std::string data = "7modsin(1)";
    double x = 0.0;
    std::string result;
    std::string res_ff = "0.268232";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_25) {     
    std::string data = "2^2^9";
    double x = 0.0;
    std::string result;
    std::string res_ff = "1.34078e+154";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_26) {     
    std::string data = "xxx";
    double x = 0.0;
    std::string result;
    std::string res_ff = "Error";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_27) {     
    std::string data = "x1";
    double x = 0.0;
    std::string result;
    std::string res_ff = "Error";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_28) {     
    std::string data = "11x";
    double x = 0.0;
    std::string result;
    std::string res_ff = "Error";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_29) {     
    std::string data = ")logx";
    double x = 0.0;
    std::string result;
    std::string res_ff = "Error";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_30) {     
    std::string data = "loglogx";
    double x = 0.0;
    std::string result;
    std::string res_ff = "Error";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}

TEST(Calc, Test_31) {     
    std::string data = "log(x11";
    double x = 0.0;
    std::string result;
    std::string res_ff = "Error";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}


TEST(Calc, Test_32) {     
    std::string data = "3/0";
    double x = 0.0;
    std::string result;
    std::string res_ff = "Error";

    model_calc.SetInput(data, x);
    model_calc.CalcTotal();
    result = model_calc.GetResult();

    EXPECT_EQ(result, res_ff);
}
