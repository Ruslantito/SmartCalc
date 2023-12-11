#include "calcview.h"

/*! \mainpage CPP3_SmartCalc_v.2.0.
 *
 * \section intro_sec Introdation.
 *
 * The all programs developed in C++ language of C++17 standard.
 * The code is follow the Google style.
 * The program code located in the src folder.
 * The all classes implemented within the s21 namespace.
 * Prepared full coverage of expression calculation modules with unit-tests
 * using the GTest library. The program built with Makefile which contains
 * standard set of targets for GNU-programs: all, install, uninstall, clean,
 * dvi, dist, tests. The all programs implementation based on QT library with
 * API for C++17.
 *
 * The all programs implemented using the MVC pattern.
 *
 *
 *
 * \subsection part1_sec Part 1: Smart calculator.
 *
 * The calculator enables the users to perform mathematical operations.
 * It can also display a graph of functions with the necessary information.
 *
 *
 *
 * \subsection part2_sec Part 2: Credit calculator.
 *
 * The credit calculator will help you determine the monthly payments on a
 * credit. Simply enter the credit amount, term and interest rate in the fields
 * below and click calculate.
 *
 *
 *
 * \subsection part3_sec Part 3: Deposit calculator.
 *
 * The Deposit calculator gives an indication to the user about the interest
 * which will be earned and total value of deposit at maturity. It calculates
 * the total amount of the deposit at the end of maturity. The User can compare
 * different settings to choose which suits best to them for opening a deposit.
 *
 *
 */

/**
 * @brief Construct a new s21::Calc View::Calc View object
 *
 * @param parent
 */
s21::CalcView::CalcView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalcView) {
  ui->setupUi(this);

  controller = new s21::CalcController;
  controller->SetFullOperation("");
  controller->SetEqualPressStatus(0);
  SetLineColor({30, 40, 255, 150});
  SetLineColorButton();
  credit_calc = new CreditView();
  connect(credit_calc, &CreditView::CreditWindow, this, &CalcView::show);
  deposit_calc = new DepositView();
  connect(deposit_calc, &DepositView::DepositWindow, this, &CalcView::show);

  connect(ui->button_0, &QPushButton::clicked, this, &CalcView::DigitsNumbers);
  connect(ui->button_1, &QPushButton::clicked, this, &CalcView::DigitsNumbers);
  connect(ui->button_2, &QPushButton::clicked, this, &CalcView::DigitsNumbers);
  connect(ui->button_3, &QPushButton::clicked, this, &CalcView::DigitsNumbers);
  connect(ui->button_4, &QPushButton::clicked, this, &CalcView::DigitsNumbers);
  connect(ui->button_5, &QPushButton::clicked, this, &CalcView::DigitsNumbers);
  connect(ui->button_6, &QPushButton::clicked, this, &CalcView::DigitsNumbers);
  connect(ui->button_7, &QPushButton::clicked, this, &CalcView::DigitsNumbers);
  connect(ui->button_8, &QPushButton::clicked, this, &CalcView::DigitsNumbers);
  connect(ui->button_9, &QPushButton::clicked, this, &CalcView::DigitsNumbers);
  connect(ui->button_x, &QPushButton::clicked, this, &CalcView::DigitsNumbers);
  connect(ui->button_plus, &QPushButton::clicked, this,
          &CalcView::MathOperations3);
  connect(ui->button_minus, &QPushButton::clicked, this,
          &CalcView::MathOperations3);
  connect(ui->button_mul, &QPushButton::clicked, this,
          &CalcView::MathOperations3);
  connect(ui->button_div, &QPushButton::clicked, this,
          &CalcView::MathOperations3);
  connect(ui->button_exp, &QPushButton::clicked, this,
          &CalcView::MathOperations3);
  connect(ui->button_mod, &QPushButton::clicked, this,
          &CalcView::MathOperations2);
  connect(ui->button_br_left, &QPushButton::clicked, this,
          &CalcView::MathOperations2);
  connect(ui->button__br_right, &QPushButton::clicked, this,
          &CalcView::MathOperations2);
  connect(ui->button_minus_un, &QPushButton::clicked, this,
          &CalcView::Operations);
  connect(ui->button_sqrt, &QPushButton::clicked, this,
          &CalcView::MathOperations);
  connect(ui->button_ln, &QPushButton::clicked, this,
          &CalcView::MathOperations);
  connect(ui->button_log, &QPushButton::clicked, this,
          &CalcView::MathOperations);
  connect(ui->button_sin, &QPushButton::clicked, this,
          &CalcView::MathOperations);
  connect(ui->button_cos, &QPushButton::clicked, this,
          &CalcView::MathOperations);
  connect(ui->button_tan, &QPushButton::clicked, this,
          &CalcView::MathOperations);
  connect(ui->button_asin, &QPushButton::clicked, this,
          &CalcView::MathOperations);
  connect(ui->button_acos, &QPushButton::clicked, this,
          &CalcView::MathOperations);
  connect(ui->button_atan, &QPushButton::clicked, this,
          &CalcView::MathOperations);
  connect(ui->button_dot, &QPushButton::clicked, this,
          &CalcView::ButtonDotClicked);
  connect(ui->button_del, &QPushButton::clicked, this,
          &CalcView::ButtonDelClicked);
  connect(ui->button_del_total, &QPushButton::clicked, this,
          &CalcView::ButtonDelTotalClicked);
  connect(ui->button_eq, &QPushButton::clicked, this,
          &CalcView::ButtonEqClicked);
  connect(ui->lineColor, &QPushButton::clicked, this,
          &CalcView::ButtonLineColorClicked);
  connect(ui->draw, &QPushButton::clicked, this, &CalcView::ButtonDrawClicked);
  connect(ui->clear, &QPushButton::clicked, this,
          &CalcView::ButtonClearClicked);
  connect(ui->button_show_graph, &QPushButton::clicked, this,
          &CalcView::ButtonShowGraphClicked);
  connect(ui->button_hide_graph, &QPushButton::clicked, this,
          &CalcView::ButtonHideGraphClicked);
  connect(ui->actionGo_to_Credit_calc, &QAction::triggered, this,
          &CalcView::GoToCreditCalc);
  connect(ui->actionGo_to_Deposit_Calc, &QAction::triggered, this,
          &CalcView::GoToDepositCalc);
}

/**
 * @brief Destroy the s21::Calc View::Calc View object
 *
 */
s21::CalcView::~CalcView() {
  delete controller;
  delete credit_calc;
  delete deposit_calc;
  delete ui;
}

/**
 * @brief Setter for line color
 *
 * @param line_color
 */
void s21::CalcView::SetLineColor(const QColor &line_color) {
  line_color_ = line_color;
}

/**
 * @brief getter for line color
 *
 * @return QColor
 */
QColor s21::CalcView::GetLineColor() const { return line_color_; }

/**
 * @brief used to enter numbers
 *
 */
void s21::CalcView::DigitsNumbers() {
  QPushButton *button = (QPushButton *)sender();
  std::string show_part = ui->result_show->text().toStdString();
  int with_braket = 0;
  int print_simb =
      controller->DoRecalcPrintSimbol3(show_part, button->text().toStdString());
  MathOperationsTotal(with_braket, print_simb);
  ui->result_show->setText(QString::fromStdString(show_part));
}

/**
 * @brief used to enter unary minus
 *
 */
void s21::CalcView::Operations() {
  QPushButton *button = (QPushButton *)sender();
  std::string show_part = ui->result_show->text().toStdString();
  controller->DoOperations(show_part, button->text().toStdString());
  ui->result_show->setText(QString::fromStdString(show_part));
  ui->result_show_full->setText(
      QString::fromStdString(controller->GetFullOperation()));
}

/**
 * @brief used to enter the functions of sin, cos and etc.
 *
 */
void s21::CalcView::MathOperations() {
  int with_braket = 1;
  int print_simb = controller->DoRecalcPrintSimbol1();
  MathOperationsTotal(with_braket, print_simb);
}

/**
 * @brief used to enter function of mod and brackets
 *
 */
void s21::CalcView::MathOperations2() {
  int with_braket = 0;
  QPushButton *button = (QPushButton *)sender();
  int print_simb =
      controller->DoRecalcPrintSimbol0(button->text().toStdString());
  MathOperationsTotal(with_braket, print_simb);
}

/**
 * @brief used to enter arithmetic characters (+, -, etc)
 *
 */
void s21::CalcView::MathOperations3() {
  int with_braket = 0, delete_simb = 0;
  QPushButton *button = (QPushButton *)sender();
  std::string show_part = ui->result_show->text().toStdString();

  int print_simb = controller->DoRecalcPrintSimbol2(
      show_part, button->text().toStdString(), delete_simb);
  if (delete_simb) {
    ButtonDelClicked();
  }
  MathOperationsTotal(with_braket, print_simb);
}

/**
 * @brief used to enter a character with or without a bracket
 *
 * @param plus_bracket
 * @param print_simb
 */
void s21::CalcView::MathOperationsTotal(int plus_bracket, int print_simb) {
  QPushButton *button = (QPushButton *)sender();
  std::string show_part = ui->result_show->text().toStdString();

  controller->DoMathOperationsTotal(plus_bracket, print_simb, show_part,
                                    button->text().toStdString());
  ui->result_show->setText(QString::fromStdString(show_part));
  ui->result_show_full->setText(
      QString::fromStdString(controller->GetFullOperation()));
}

/**
 * @brief used to handle button click
 *
 */
void s21::CalcView::ButtonDotClicked() {
  std::string show_part = ui->result_show->text().toStdString();

  controller->DoButtonDotClicked(show_part);
  ui->result_show->setText(QString::fromStdString(show_part));
  ui->result_show_full->setText(
      QString::fromStdString(controller->GetFullOperation()));
}

/**
 * @brief used to handle button click
 *
 */
void s21::CalcView::ButtonDelClicked() {
  std::string tmp = controller->ButtonDelClicked();

  ui->result_show->setText(QString::fromStdString(tmp));
  ui->result_show_full->setText(
      QString::fromStdString(controller->GetFullOperation()));
}

/**
 * @brief used to handle button click
 *
 */
void s21::CalcView::ButtonDelTotalClicked() {
  ui->result_show->setText("");
  ui->result_show_full->setText("");
  ui->result_show_eq->setText("0");
  controller->SetFullOperation("");
}

/**
 * @brief used to handle button click
 *
 */
void s21::CalcView::ButtonEqClicked() {
  std::string result_tt, show_full = ui->result_show_full->text().toStdString();
  double x = ui->value_x->text().toDouble();
  controller->SetInputValue(show_full, x);
  controller->DoCalcTotal();
  result_tt = controller->GetResultValue();
  ui->result_show_eq->setText(QString::fromStdString(result_tt));
  controller->SetEqualPressStatus(1);
}

/**
 * @brief used to draw a graph
 *
 */
void s21::CalcView::GraphCustomPlot() {
  std::string show_full = ui->result_show_full->text().toStdString();
  if (show_full.size()) {
    double xx = 0.0;
    controller->SetInputValue(show_full, xx);
    QCustomPlot *graph_new = ui->widget;
    if (!controller->Validate()) {
      std::vector<double> x, y;
      CalcModel::InputGraphLimits graph_input_limits{
          ui->inputMinX->value(), ui->inputMaxX->value(),
          ui->inputMinY->value(), ui->inputMaxY->value(), ui->step->value()};
      controller->CalcVector(graph_input_limits, x, y);
      QVector<double> q_x = QVector<double>(x.begin(), x.end());
      QVector<double> q_y = QVector<double>(y.begin(), y.end());
      graph_new->addGraph();
      graph_new->graph(0)->setData(q_x, q_y);
      graph_new->xAxis->setLabel("x");
      graph_new->yAxis->setLabel("y");
      graph_new->xAxis->setRange(ui->inputMinX->value(),
                                 ui->inputMaxX->value());
      graph_new->yAxis->setRange(ui->inputMinY->value(),
                                 ui->inputMaxY->value());

      QPen blue_dot_pen;
      GraphRecalcLine(ui->lineStyle->currentIndex(), blue_dot_pen,
                      ui->lineWidth->value());
      graph_new->graph(0)->setPen(blue_dot_pen);
      graph_new->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    } else {
      if (graph_new->graph(0)) {
        graph_new->graph(0)->data().data()->clear();
      }
    }
    graph_new->replot();
  }
}

void s21::CalcView::GraphRecalcLine(int index, QPen &blue_dot_pen, int width) {
  blue_dot_pen.setColor(GetLineColor());
  switch (index) {
    case 0:
      blue_dot_pen.setStyle(Qt::SolidLine);
      break;
    case 1:
      blue_dot_pen.setStyle(Qt::DotLine);
      break;
    case 2:
      blue_dot_pen.setStyle(Qt::DashLine);
      break;
    case 3:
      blue_dot_pen.setStyle(Qt::DashDotLine);
      break;
    case 4:
      blue_dot_pen.setStyle(Qt::DashDotDotLine);
      break;
    default:
      blue_dot_pen.setStyle(Qt::SolidLine);
      break;
  }
  blue_dot_pen.setWidthF(width);
}

/**
 * @brief used to handle button click
 *
 */
void s21::CalcView::SetLineColorButton() {
  QString tmp = "background-color:rgba(";
  tmp.append(QString::number(GetLineColor().red()));
  tmp.append(", ");
  tmp.append(QString::number(GetLineColor().green()));
  tmp.append(", ");
  tmp.append(QString::number(GetLineColor().blue()));
  tmp.append(", 1);");

  ui->labelColor->setStyleSheet(tmp);
}

/**
 * @brief used to handle button click
 *
 */
void s21::CalcView::ButtonLineColorClicked() {
  QColor tmp_color = QColorDialog::getColor(GetLineColor());
  if (tmp_color.isValid()) {
    SetLineColor(tmp_color);
    SetLineColorButton();
  }
}

/**
 * @brief used to handle button click
 *
 */
void s21::CalcView::ButtonDrawClicked() { GraphCustomPlot(); }

/**
 * @brief used to handle button click
 *
 */
void s21::CalcView::ButtonClearClicked() {
  if (ui->widget->graph(0)) {
    ui->widget->graph(0)->data().data()->clear();
    ui->widget->replot();
  }
}

/**
 * @brief used to handle button click
 *
 */
void s21::CalcView::ButtonShowGraphClicked() {
  ui->button_show_graph->hide();
  this->setGeometry(this->geometry().x(), this->geometry().y(),
                    this->maximumWidth(), this->maximumHeight());
}

/**
 * @brief used to handle button click
 *
 */
void s21::CalcView::ButtonHideGraphClicked() {
  ui->button_show_graph->show();
  this->setGeometry(this->geometry().x(), this->geometry().y(),
                    this->maximumWidth(), this->minimumHeight());
}

/**
 * @brief used to move to another window
 *
 */
void s21::CalcView::GoToCreditCalc() {
  credit_calc->show();
  this->close();
}

/**
 * @brief used to move to another window
 *
 */
void s21::CalcView::GoToDepositCalc() {
  deposit_calc->show();
  this->close();
}
