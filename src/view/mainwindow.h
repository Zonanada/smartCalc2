/*!
\file
\brief Заголовочный файл главного окна
*/
#ifndef SRC_VIEW_MAINWINDOW_H
#define SRC_VIEW_MAINWINDOW_H

#include <locale.h>

#include <QKeyEvent>
#include <QMainWindow>
#include <string>

#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /*!
  Конструктор
   */
  MainWindow(QWidget *parent = nullptr);
  /*!
  Деструктор
   */
  ~MainWindow();

 private slots:
  void on_pushButton_dot_clicked();
  void on_pushButton_0_clicked();
  void on_pushButton_1_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();
  void on_pushButton_CE_clicked();
  void on_pushButton_sqrt_clicked();
  void on_pushButton_sin_clicked();
  void on_pushButton_tan_clicked();
  void on_pushButton_plus_clicked();
  void on_pushButton_minus_clicked();
  void on_pushButton_multiplay_clicked();
  void on_pushButton_divide_clicked();
  void on_pushButton_ln_clicked();
  void on_pushButton_acos_clicked();
  void on_pushButton_log_clicked();
  void on_pushButton_cos_clicked();
  void on_pushButton_atan_clicked();
  void on_pushButton_asin_clicked();
  void on_pushButton_mod_clicked();
  void on_pushButton_right_bkt_clicked();
  void on_pushButton_left_bkt_clicked();
  void on_pushButton_X_clicked();
  void on_pushButton_stage_clicked();
  void on_pushButton_peer_clicked();
  void on_value_x_valueChanged(double arg1);
  void on_pushButton_graph_clicked();

 protected:
  void keyPressEvent(QKeyEvent *event) override;

 private:
  Ui::MainWindow *ui;
  void add_text(QString str);
  void correct_expression(const QString expression);
  bool сheck_for_minus(QString value_add);
  void set_color_red();
  void set_color_black();
  QString is_valid(QString str);
  Graph graph;
  QString answer = "";
};
#endif  // MAINWINDOW_H
