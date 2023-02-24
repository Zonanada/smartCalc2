/*!
\file
\brief Заголовочный файл с реализацией модели

Данный файл содержит в себе реализацию всех методов и структур класса
*/
#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H
#include <stdlib.h>

#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <string>

namespace s21 {

/*
    \brief Класс который поизводит все вычисления
    \author Zonanada
*/
class Model {
 private:
  struct leksem;
  struct type_count;

 public:
  /*!
  Параметризованный конструктор
  \param input вычисляемое выражение в виде строки, value_x значение "X" типа
  double \return Объект класса с заполнеными входными данными.
  */
  Model(std::string input, double value_x);
  /*!
  Параметризованный конструктор
  \param input вычисляемое выражение в виде строки
  \return Объект класса с заполненной строкой и value_x по умолчанию.
  */
  Model(std::string input);
  /*!
  Конструктор копирования
  \param Другой объект такого же класса
  \return Объект класса с заполнеными входными данными.
  */
  Model(const Model &other);
  /*!
  Конструктор перемещения
  \param Другой объект такого же класса
  \return Объект класса с заполнеными входными данными.
  */
  Model(Model &&other);

  /*!
  Оператор копирования
  \param Другой объект такого же класса
  \return Объект класса с заполнеными входными данными.
  */
  Model operator=(const Model &other);
  /*!
  Оператор перемещения
  \param Другой объект такого же класса
  \return Объект класса с заполнеными входными данными.
  */
  Model operator=(Model &&other);

  /*!
  Метод который вычисляет ответ
  \return В случае некоректного ввода возващает "error"
  \return В случае не законченного выражения возвращает пустую строку
  \return В остальных случаях возвращает входную строку с рузультатом выражения
  */
  std::string express_answer() noexcept;

  bool is_valid_for_graph();

  /*!
  Метод который вычисляет ответ без проверки на валидность
  \return Возвращает результат выражения типа "double"
  */
  double solution_without_checks() noexcept;

  /*!
  \return Возвращает строку с результатом выражения
  */
  std::string get_result_exp() const noexcept;

  /*!
  Сеттер значения "X"
  \param Значение "X" типа double
  */
  void set_x(double num) noexcept;

  /*!
  Геттер входной строки
  \return Возвращает входную строку
  */
  std::string get_input() const noexcept;

  /*!
  Геттер значения "X"
  \return Возвращает значение "X"
  */
  double get_x() const noexcept;

 private:
  /*!
  Метод который обрабатывает входную строку для дальнейшего вычисления
  */
  void input_processing();

  /*!
  Высчитывает результат из обратной польской нотации
  \return Возвращает строку с результатом выражения
  */
  std::string get_result() noexcept;

  /*!
  Метод который парсит входную строку и разбивает на лексемы
  */
  void parse() noexcept;

  /*!
  Метод который переводит из ификсной записи в обратную польскую нотацию
  */
  void translate_polish_notation() noexcept;

  /*!
  Метод который вычисляет результат выражения
  */
  void calculation() noexcept;

  /*!
  Посчёт всех типов лексем
  \return Возвращает структуру с количеством лексем каждого типа
  */
  bool is_ready_expression() noexcept;

  /*!
  Метод который добавляет закрывающие скобочки если необходимо
  */
  void add_backets() noexcept;
  /*!
  Метод котрый проверяет корректное количество скобочек
  \return Возвращает '1' в случе если некорректно расставленны скобочки или '0'
  */
  int check_backets() noexcept;

  /*!
  Метод который считает количество точек
  \return если больше 1 точки возвращает "false" иначе "true"*/
  bool count_dot(std::string str) noexcept;

  /*!
  Метод который вставляет лексему умножения между двумя лексемами с числами
  */
  void insert_multiplay() noexcept;

  /*!
  Метод который заменяет значение "X" на число
  */
  void chage_x_to_double() noexcept;

  /*!
  Метод который вcтавляет "-1*" вместо унарного минуса
  */
  void change_unary_minus() noexcept;

  /*!
  Метод который удаляет "-1*" из строки
  */
  std::string remove_unary_minus_in_exp() const noexcept;

  /*
  Метод который контролирует запись в стек. В случеае если пришла лексема с
  приоритетом
  <= верхней лексемы стек выталкивает значения в выходную строку до тех пор пока
  приоритет не станет меньше или не встретится открывающая скобка*/
  void stack_control_push(std::list<leksem>::iterator it_leks) noexcept;

  /*!
  Метод котрый возвращает результат бинарных операций
  \return число типа "double"
  */
  double binary_operations(leksem first, leksem second, leksem oper);

  /*!
  Метод котрый возвращает результат вычислений функций
  \return число типа "double"
  */
  double unary_operations(leksem first, leksem oper);

  /*!
  Метод который возвращает тип символа
  \return число из "enum"
  */
  int type_symbol(char symbol) noexcept;

  /*!
  Метод который проверяет на валидность
  \return Возвращает результат проверки на валидность
  */
  bool is_valid() noexcept;

  /*!
  Метод котрый проверяет является ли символ частью числа
  \return true/false
  */
  bool is_num(char symbol) noexcept;
  /*!
  Метод котрый проверяет является ли символ частью функции
  \return true/false
  */
  bool is_func(char symbol) noexcept;

  /*!
  Метод котрый проверяет является ли символ вычислительным знаком
  \return true/false
  */
  bool is_sign(char symbol) noexcept;

  /*!
  Очистка контейнеров для нового вычисления
  */
  void clear_data() noexcept;

  /*!
  Метод котрый переводит число double в строку и удаляет нули с конца
  \param число которое надо перевести в строку
  \return Возвращает строку с числом
  */
  std::string double_to_string(double num) noexcept;

  std::string input_;
  double value_x_;
  std::list<leksem> leksems_;
  std::list<leksem> output_str_;
  std::list<leksem> stack_;
  std::string result_exp_;

  struct leksem {
    std::string value;
    int priority;
    double num;
    bool visibility;

    leksem(double num);
    leksem(std::string value, int priority);
    leksem(std::string value, int priority, bool visibility);
    leksem(const leksem &other);
    leksem(leksem &&other) noexcept;
    leksem operator=(leksem const &other);
    void translate_double_in_value() noexcept;
    int operator*() noexcept;
  };

  std::map<std::string, int> priority{
      {"X", -2},   {"num", -1}, {"+", 1},    {"-", 1},  {"*", 2},
      {"/", 2},    {"(", 5},    {")", 6},    {"^", 3},  {"mod", 2},
      {"cos", 4},  {"sin", 4},  {"tan", 4},  {"ln", 4}, {"acos", 4},
      {"asin", 4}, {"atan", 4}, {"sqrt", 4}, {"log", 4}};

  enum {
    NUM = 0,
    FUNC = 1,
    SIGN = 2,
    X = 3,
    ANOTHER = 4,
  };
};

}  // namespace s21

#endif
