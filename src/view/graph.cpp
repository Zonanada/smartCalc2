/*!
\file
\brief файл с отрисовкой графика

Данный файл вычисляет и отрисовывает график функций
*/
#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QMainWindow(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

void Graph::build_graph(QString exp) {
  QChart *chart = new QChart();
  QLineSeries *line = new QLineSeries();
  QLineSeries *axis_x = new QLineSeries();
  QLineSeries *axis_y = new QLineSeries();
  QScatterSeries *dot = new QScatterSeries();

  dot->setColor(QColor::fromRgb(101, 153, 228));
  line->setColor(QColorConstants::Blue);
  axis_y->setColor(QColorConstants::Red);
  axis_x->setColor(QColorConstants::Red);
  axis_x->setOpacity(50);
  chart->addSeries(axis_x);
  chart->addSeries(axis_y);

  s21::Controller solution(exp.toStdString());
  double value_from_x = ui->from_x->value() - 0.1;
  double value_up_to_x = ui->up_to_x->value();
  double step = (value_up_to_x - value_from_x) / 290;
  for (double value_x = value_from_x; value_x < value_up_to_x + 0.1;
       value_x += step) {
    solution.set_x(value_x);
    double value_y = solution.solution_without_checks();
    if (!std::isinf(value_y) && !std::isnan(value_y)) {
      *line << QPointF(value_x, value_y);
      *dot << QPointF(value_x, value_y);
    }
  }

  chart->legend()->hide();
  if (ui->draw_line->isChecked()) {
    line->setMarkerSize(7);
    chart->addSeries(line);
  } else {
    chart->addSeries(dot);
  }

  *axis_x << QPointF(0, ui->from_y->value())
          << QPointF(0, ui->up_to_y->value());
  *axis_y << QPointF(value_from_x, 0) << QPointF(value_up_to_x, 0);

  chart->createDefaultAxes();
  chart->setTitle(exp);

  chart->axes(Qt::Horizontal)
      .first()
      ->setRange(ui->from_x->value(), ui->up_to_x->value());
  chart->axes(Qt::Vertical)
      .first()
      ->setRange(ui->from_y->value(), ui->up_to_y->value());

  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  ui->widget->layout()->addWidget(chartView);
}

void Graph::set_exp(QString exp) {
  general_exp = exp;
  if (chartView != nullptr) {
    delete chartView;
  }
  build_graph(exp);
}

void Graph::on_from_x_valueChanged(double arg1) {
  if (arg1 >= ui->up_to_x->value()) {
    ui->from_x->setValue(arg1 - 1);
  }
  set_exp(general_exp);
}

void Graph::on_from_y_valueChanged(double arg1) {
  if (arg1 >= ui->up_to_y->value()) {
    ui->from_y->setValue(arg1 - 1);
  }
  set_exp(general_exp);
}

void Graph::on_up_to_x_valueChanged(double arg1) {
  if (arg1 <= ui->from_x->value()) {
    ui->up_to_x->setValue(arg1 + 1);
  }
  set_exp(general_exp);
}

void Graph::on_up_to_y_valueChanged(double arg1) {
  if (arg1 <= ui->from_y->value()) {
    ui->up_to_y->setValue(arg1 + 1);
  }
  set_exp(general_exp);
}

void Graph::on_draw_line_toggled(bool checked) { set_exp(general_exp); }
