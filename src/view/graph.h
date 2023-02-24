/*!
\file
\brief Заголовочный файл окна отрисовки
*/
#ifndef SRC_VIEW_SRC_GRAPH_H
#define SRC_VIEW_SRC_GRAPH_H

#include <QChartView>
#include <QLineSeries>
#include <QScatterSeries>
#include <QtCharts>
#include <cmath>

#include "../controller/controller.h"

namespace Ui {
class Graph;
}
/*
    \brief Класс который отрисовые график функций
    Данный класс создает объект "QChart" и вставляет в виджет
*/
class Graph : public QMainWindow {
  Q_OBJECT

 public:
  /*!
  Конструктор
   */
  explicit Graph(QWidget *parent = nullptr);
  /*!
  Десруктор
  */
  ~Graph();

  /*!
  Создание нового окна если его нет и запуск отрисовки графика
  \param Строка с выражением
  */
  void set_exp(QString exp);
  /*!
  Отрисовка графика
  \param Строка с выражением
  */
  void build_graph(QString exp);

 private slots:

  void on_from_x_valueChanged(double arg1);

  void on_from_y_valueChanged(double arg1);

  void on_up_to_x_valueChanged(double arg1);

  void on_up_to_y_valueChanged(double arg1);

  void on_draw_line_toggled(bool checked);

 private:
  Ui::Graph *ui;
  QChartView *chartView = nullptr;
  QString general_exp;
};

#endif  // GRAPH_H
