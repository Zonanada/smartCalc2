/*!
\file
\brief Заголовочный файл с реализацией контроллера

Данный файл содержит в себе реализацию контроллера
*/

#ifndef SRC_ONTROLLER_CONTROLLER_H
#define SRC_ONTROLLER_CONTROLLER_H
#include "../model/model.h"

namespace s21 {
/*
    \brief Класс котрый выполняет функцию контроллера
    \author Zonanada
    Данный класс создает модель и в которой вызывает нужные методы
*/
class Controller {
 public:
  /*!
  Параметизированный конструктор
  \param строка с выражением и значение "X" типа double
  */
  Controller(const std::string str, double value_x);
  /*!
  Параметизированный конструктор
  \param строка с выражением
  */
  Controller(const std::string str);
  /*!
  Конструктор копирования
  \param Объект другого конструктора
  */
  Controller(const Controller &other);
  /*!
  Конструктор перемещения
  \param Объект другого конструктора
  */
  Controller(Controller &&other);
  /*!
  Деструктор
  */
  ~Controller();
  /*!
  Метод, который вызывает метод модели, которая вычисляет ответ
  \return В случае некоректного ввода возващает "error"
  \return В случае не законченного выражения возвращает пустую строку
  \return В остальных случаях возвращает входную строку с рузультатом выражения
  */
  std::string express_answer() noexcept;

  /*!
  Вызывает метод модели, которая
  \return Возвращает строку с результатом выражения
  */
  std::string get_result_exp() noexcept;
  /*!
   Вызывает метод модели который вычисляет ответ без проверки на валидность
   \return Возвращает результат выражения типа "double"
   */
  double solution_without_checks() noexcept;

  /*!
  Оператор копирования
  \param Другой объект такого же класса
  \return Объект класса с заполнеными входными данными.
  */
  Controller operator=(const Controller &other) noexcept;
  /*!
  Оператор перемещения
  \param Другой объект такого же класса
  \return Объект класса с заполнеными входными данными.
  */
  Controller operator=(Controller &&other) noexcept;

  /*!
  Вызывает Сеттер значения "X"
  \param Значение "X" типа double
  */
  void set_x(double num) noexcept;

  bool is_valid_for_graph();

 private:
  s21::Model *model_;
};

}  // namespace s21

#endif
