/*!
\file
\brief Файл главного окна

Данный файл содержит в себе реализацию "Ui" и все манипуляции с ним
*/
#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setlocale(LC_ALL, "C");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_dot_clicked() { add_text("."); }

void MainWindow::on_pushButton_0_clicked() { add_text("0"); }

void MainWindow::on_pushButton_1_clicked() { add_text("1"); }

void MainWindow::on_pushButton_2_clicked() { add_text("2"); }

void MainWindow::on_pushButton_3_clicked() { add_text("3"); }

void MainWindow::on_pushButton_4_clicked() { add_text("4"); }

void MainWindow::on_pushButton_5_clicked() { add_text("5"); }

void MainWindow::on_pushButton_6_clicked() { add_text("6"); }
void MainWindow::on_pushButton_7_clicked() { add_text("7"); }

void MainWindow::on_pushButton_8_clicked() { add_text("8"); }

void MainWindow::on_pushButton_9_clicked() { add_text("9"); }

void MainWindow::on_pushButton_sqrt_clicked() { add_text("sqrt("); }

void MainWindow::on_pushButton_sin_clicked() { add_text("sin("); }

void MainWindow::on_pushButton_tan_clicked() { add_text("tan("); }

void MainWindow::on_pushButton_plus_clicked() { add_text("+"); }

void MainWindow::on_pushButton_minus_clicked() { add_text("-"); }

void MainWindow::on_pushButton_multiplay_clicked() { add_text("*"); }

void MainWindow::on_pushButton_divide_clicked() { add_text("/"); }

void MainWindow::on_pushButton_ln_clicked() { add_text("ln("); }

void MainWindow::on_pushButton_acos_clicked() { add_text("acos("); }

void MainWindow::on_pushButton_log_clicked() { add_text("log("); }

void MainWindow::on_pushButton_cos_clicked() { add_text("cos("); }

void MainWindow::on_pushButton_atan_clicked() { add_text("atan("); }

void MainWindow::on_pushButton_asin_clicked() { add_text("asin("); }

void MainWindow::on_pushButton_mod_clicked() { add_text("mod("); }

void MainWindow::on_pushButton_right_bkt_clicked() { add_text(")"); }

void MainWindow::on_pushButton_left_bkt_clicked() { add_text("("); }

void MainWindow::on_pushButton_X_clicked() { add_text("X"); }

void MainWindow::on_pushButton_stage_clicked() { add_text("^("); }

void MainWindow::keyPressEvent(QKeyEvent *event) {
  switch (event->text().toStdString()[0]) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '/':
    case '-':
    case '^':
    case '+':
    case '*':
    case '(':
    case ')':
      add_text(event->text());
      break;
    case '.':
    case ',':
      add_text(".");
      break;
    case '=':
    case '\r':
    case '\n':
      on_pushButton_peer_clicked();
      break;
    case 'X':
    case 'x':
      add_text("X");
      break;
    case '\b':
    case 127:  // Delete
      on_pushButton_CE_clicked();
      break;
    case 's':
      add_text("sin(");
      break;
    case 'c':
      add_text("cos(");
      break;
    case 't':
      add_text("tan(");
      break;
    case 'm':
      add_text("mod(");
      break;
    case 'l':
      add_text("log(");
      break;
  }
}

void MainWindow::on_pushButton_CE_clicked() {
  set_color_black();
  if (ui->pushButton_CE->text() == "AC") {
    ui->result_show->setText("0");
    ui->pushButton_CE->setText("CE");
  } else {
    QString mini_str = ui->result_show->text();
    mini_str.chop(1);
    if (!mini_str.isEmpty() && mini_str.back() == '^') mini_str.chop(1);
    while (!mini_str.isEmpty() && mini_str.back() >= 'a' &&
           mini_str.back() <= 'z') {
      mini_str.chop(1);
    }
    if (mini_str.isEmpty()) {
      mini_str = "0";
    }
    ui->result_show->setText(mini_str);
    correct_expression(mini_str);
  }
}

void MainWindow::add_text(const QString str) {
  set_color_black();
  if (ui->pushButton_CE->text() == "AC") {
    ui->pushButton_CE->setText("CE");
  }

  QString value_now = ui->result_show->text();
  QString set_value;

  if (value_now == "0" && str != "." && str != "mod") {
    set_value = str;
  } else if (сheck_for_minus(str)) {
    set_value = value_now + str;
  } else {
    set_value = value_now;
  }
  ui->result_show->setText(set_value);
  correct_expression(std::move(set_value));
}

bool MainWindow::сheck_for_minus(QString value_add) {
  QString value_now = ui->result_show->text();
  if (value_now.size() > 2 && value_now.back() == '-' &&
      (value_now[value_now.size() - 2] == '-' ||
       value_now[value_now.size() - 2] == '*' ||
       value_now[value_now.size() - 2] == '/' ||
       value_now[value_now.size() - 2] == '(') &&
      value_add == "-") {
    return false;
  }
  return true;
}

void MainWindow::set_color_red() {
  ui->result_show->setStyleSheet(
      "color: red;background-color: white; border-style: none;");
}

void MainWindow::set_color_black() {
  ui->result_show->setStyleSheet(
      "color: black;background-color: white; border-style: none;");
}

void MainWindow::correct_expression(QString expression) {
  s21::Controller controller(expression.toStdString(), ui->value_x->value());
  ui->help_show->setText(QString::fromStdString(controller.express_answer()));
  answer = QString::fromStdString(controller.get_result_exp());
}

void MainWindow::on_pushButton_peer_clicked() {
  if (answer != "") {
    ui->pushButton_CE->setText("AC");
    ui->result_show->setText(answer);
  } else {
    set_color_red();
  }
}

void MainWindow::on_value_x_valueChanged(double arg1) {
  correct_expression(ui->result_show->text());
}

void MainWindow::on_pushButton_graph_clicked() {
  s21::Controller check_valid =
      s21::Controller(ui->result_show->text().toStdString());
  if (check_valid.is_valid_for_graph()) {
    graph.set_exp(ui->result_show->text());
    if (!graph.isVisible()) {
      graph.show();
    }
  } else {
    set_color_red();
  }
}
