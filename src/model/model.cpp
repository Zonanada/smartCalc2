/*!
\file
\brief Файл с реализацией модели

*/
#include "model.h"

namespace s21 {

Model::Model(std::string input, double value_x)
    : input_(input), value_x_(value_x) {
  input_processing();
}

Model::Model(std::string input) : input_(input), value_x_(1) {
  input_processing();
}

Model::Model(const Model &other)
    : input_(other.input_), value_x_(other.value_x_) {}

Model::Model(Model &&other)
    : input_(std::move(other.input_)), value_x_(std::move(other.value_x_)) {}

Model Model::operator=(const Model &other) {
  input_ = other.input_;
  result_exp_ = other.result_exp_;
  value_x_ = other.value_x_;
  leksems_ = other.leksems_;
  output_str_ = other.output_str_;
  stack_ = other.stack_;
  return *this;
}

Model Model::operator=(Model &&other) {
  input_ = std::move(other.input_);
  result_exp_ = std::move(other.result_exp_);
  value_x_ = std::move(other.value_x_);
  leksems_ = std::move(other.leksems_);
  output_str_ = std::move(other.output_str_);
  stack_ = std::move(other.stack_);
  return *this;
}

std::string Model::express_answer() noexcept {
  if (!is_valid()) {
    result_exp_ = "error";
    return result_exp_;
  }

  if (is_ready_expression()) {
    add_backets();
    result_exp_ = get_result();
    if (result_exp_ == "nan" || result_exp_ == "-nan" || result_exp_ == "inf" ||
        result_exp_ == "-inf") {
      result_exp_ = "error";
      return result_exp_;
    } else {
      return remove_unary_minus_in_exp() + "=" + result_exp_;
    }
  }
  return "";
}

bool Model::is_valid_for_graph() {
  return is_valid() && (*leksems_.back() == -1 || *leksems_.back() == 6);
}

double Model::solution_without_checks() noexcept {
  clear_data();
  parse();
  change_unary_minus();
  change_x_to_double();
  insert_multiplay();
  add_backets();
  translate_polish_notation();
  calculation();
  double result = stack_.back().num;
  return result;
}

std::string Model::get_result_exp() const noexcept { return result_exp_; }

void Model::set_x(double num) noexcept { value_x_ = num; }

std::string Model::get_input() const noexcept { return input_; }

double Model::get_x() const noexcept { return value_x_; }

void Model::input_processing() {
  parse();
  change_unary_minus();
  change_x_to_double();
  insert_multiplay();
}

std::string Model::get_result() noexcept {
  translate_polish_notation();
  calculation();
  return double_to_string(stack_.back().num);
}

void Model::parse() noexcept {
  std::string local_str;
  for (auto it = input_.begin(); it != input_.end(); it++) {
    if (*it != ' ') {
      local_str.push_back(*it);

      if (*it == '.' && (!is_num(*(it + 1)) || *(it + 1) == '.')) {
        local_str.push_back('0');
      }

      if (type_symbol(*it) != type_symbol(*(it + 1)) || is_sign(*it) ||
          *it == 'X') {
        leksem local(local_str,
                     is_num(*it) ? priority["num"] : priority[local_str]);
        leksems_.push_back(std::move(local));
        local_str.clear();
      }
    }
  }
}

void Model::translate_polish_notation() noexcept {
  for (auto it = leksems_.begin(); it != leksems_.end(); it++) {
    if (it->priority == -1) {
      output_str_.push_back((*it));
    } else if (it->priority < 6) {
      stack_control_push(it);
    }
    if (it->priority == 6) {
      while (!stack_.empty() && stack_.back().value != "(") {
        output_str_.push_back(stack_.back());
        stack_.pop_back();
      }
      stack_.pop_back();
    }
  }
  while (!stack_.empty()) {
    output_str_.push_back((stack_.back()));
    stack_.pop_back();
  }
}

void Model::calculation() noexcept {
  while (!output_str_.empty()) {
    if (output_str_.front().priority == -1) {
      output_str_.front().translate_double_in_value();
      stack_.push_back(output_str_.front());
      output_str_.pop_front();
    } else if (output_str_.front().priority < 4) {
      leksem second_num = std::move(stack_.back());
      stack_.pop_back();
      leksem first_num = std::move(stack_.back());
      stack_.pop_back();
      leksem result(
          binary_operations((first_num), (second_num), (output_str_.front())));
      stack_.push_back((result));
      output_str_.pop_front();
    } else {
      leksem value = (stack_.back());
      stack_.pop_back();
      leksem result(unary_operations((value), (output_str_.front())));
      stack_.push_back((result));
      output_str_.pop_front();
    }
  }
}

bool Model::is_ready_expression() noexcept {
  int nums = 0;
  int sign = 0;
  int func = 0;
  for (auto it = leksems_.begin(); it != leksems_.end(); it++) {
    switch (**it) {
      case -1:
        nums++;
        break;
      case 1:
      case 2:
      case 3:
        sign++;
        break;
      case 4:
        func++;
        break;
    }
  }

  bool result = ((nums >= 2 && sign >= 1) || (nums >= 1 && func >= 1)) &&
                (*leksems_.back() == -1 || *leksems_.back() == 6);
  return result;
}

void Model::add_backets() noexcept {
  int brackets_left = 0;
  int brackets_right = 0;
  for (auto it = leksems_.begin(); it != leksems_.end(); it++) {
    if (**it == 5) {
      brackets_left++;
    } else if (**it == 6) {
      brackets_right++;
    }
  }

  for (int i = 0; i < brackets_left - brackets_right; i++) {
    leksem tmp(")", 6);
    leksems_.push_back(tmp);
  }
}

bool Model::is_brackets_correct() noexcept {
  int brackets_left = 0;
  int brackets_right = 0;
  for (auto it = leksems_.begin(); it != leksems_.end(); it++) {
    if (**it == 5) {
      brackets_left++;
    } else if (**it == 6) {
      brackets_right++;
    }
  }

  if (brackets_right > brackets_left) return 1;
  return 0;
}

bool Model::count_dot(std::string str) noexcept {
  int count_dot = 0;
  for (auto it = str.begin(); it != str.end(); it++) {
    if (*it == '.') count_dot++;
  }
  return count_dot < 2;
}

void Model::insert_multiplay() noexcept {
  for (auto it_first = leksems_.begin(); it_first != leksems_.end();
       it_first++) {
    auto it_second = it_first;
    it_second++;
    if ((**it_first == -1 &&
         (**it_second == 5 || **it_second == 4 || **it_second == -1)) ||
        (**it_first == 6 && (**it_second == 5 || **it_second == -1))) {
      leksem tmp("*", 2, false);
      leksems_.insert(it_second, std::move(tmp));
    }
  }
}

void Model::change_x_to_double() noexcept {
  for (auto it = leksems_.begin(); it != leksems_.end(); it++) {
    if (**it == -2) {
      it->value = double_to_string(value_x_);
      it->priority = -1;
    }
  }
}

void Model::change_unary_minus() noexcept {
  if (leksems_.size() > 2) {
    leksem leksem_for_insert("-1", priority["num"]);
    auto finish_change = leksems_.end();
    finish_change--;
    for (auto it_first = leksems_.begin(); it_first != finish_change;
         it_first++) {
      auto it_averege = it_first;
      it_averege++;
      auto it_last = it_averege;
      it_last++;
      if (it_first->value == "-" && it_first == leksems_.begin() &&
          (**it_averege == -1 || **it_averege == -2 || **it_averege == 4 ||
           it_averege->value == "(")) {
        it_first = leksems_.erase(it_first);
        it_first = leksems_.insert(it_first, leksem_for_insert);
      } else if (it_averege->value == "-" &&
                 ((**it_first >= 1 && **it_first <= 4) ||
                  it_first->value == "(") &&
                 it_last != leksems_.end() &&
                 (**it_last == -1 || **it_last == 4 || it_last->value == "X" ||
                  it_last->value == "(")) {
        it_averege = leksems_.erase(it_averege);
        leksems_.insert(it_averege, leksem_for_insert);
      }
    }
  }
}

std::string Model::remove_unary_minus_in_exp() const noexcept {
  std::string exp;
  for (auto it = leksems_.begin(); it != leksems_.end(); it++) {
    auto next = it;
    next++;
    if (it->value == "-1" && next->value == "*") {
      exp += "-";
      it++;
      continue;
    }
    exp += it->value;
  }
  return exp;
}

void Model::stack_control_push(std::list<leksem>::iterator it_leks) noexcept {
  if (!stack_.empty() && *stack_.back() >= **it_leks) {
    while (!stack_.empty() && *(stack_.back()) >= **it_leks &&
           *(stack_.back()) != 5) {
      output_str_.push_back(stack_.back());
      stack_.pop_back();
    }
  }
  stack_.push_back(*it_leks);
}

double Model::binary_operations(leksem first_num, leksem second_num,
                                leksem oper) {
  std::string find = (oper.value);
  if (find == "+") return first_num.num + second_num.num;
  if (find == "-") return first_num.num - second_num.num;
  if (find == "*") return first_num.num * second_num.num;
  if (find == "/") return first_num.num / second_num.num;
  if (find == "^") return pow(first_num.num, second_num.num);
  if (find == "/") return first_num.num / second_num.num;
  if (find == "mod") return fmod(first_num.num, second_num.num);
  throw std::out_of_range("error, binary_operations");
}

double Model::unary_operations(leksem value, leksem oper) {
  std::string find = (oper.value);
  if (find == "cos") return cos(value.num);
  if (find == "sin") return sin(value.num);
  if (find == "tan") return tan(value.num);
  if (find == "log") return log10(value.num);
  if (find == "ln") return log(value.num);
  if (find == "acos") return acos(value.num);
  if (find == "asin") return asin(value.num);
  if (find == "atan") return atan(value.num);
  if (find == "sqrt") return sqrt(value.num);
  throw std::out_of_range("error, unary_operations");
}

int Model::type_symbol(char symbol) noexcept {
  if (is_num(symbol)) {
    return NUM;
  } else if (is_func(symbol)) {
    return FUNC;
  } else if (is_sign(symbol)) {
    return SIGN;
  } else if (symbol == 'X') {
    return X;
  } else {
    return ANOTHER;
  }
}

bool Model::is_valid() noexcept {
  if (leksems_.size() < 2) return true;
  auto it_first = leksems_.begin();
  auto it_second = leksems_.begin();
  it_second++;
  if (*leksems_.front() != -1 && *leksems_.front() != 5 &&
      *leksems_.front() != 4 && leksems_.front().value != "-")
    return false;
  if (it_first->value == "-" && it_second->value == "-") {
    return false;
  }

  for (std::size_t i = 1; i < leksems_.size(); i++, it_first++, it_second++) {
    if (**it_first == 1 && (it_second->value == "+" || **it_second == 2 ||
                            **it_second == 3 || **it_second == 6)) {
      return false;
    } else if (**it_first == 2 &&
               (it_second->value == "+" || **it_second == 2 ||
                **it_second == 3 || **it_second == 6)) {
      return false;
    } else if (**it_first == 3 &&
               (it_second->value == "+" || **it_second == 2 ||
                **it_second == 3 || **it_second == 6)) {
      return false;
    } else if (**it_first == 5 &&
               (it_second->value == "+" || **it_second == 2 ||
                **it_second == 3 || **it_second == 6 ||
                it_second->value == ".")) {
      return false;
    } else if (!count_dot(it_first->value) || !count_dot(it_second->value)) {
      return false;
    }
  }
  if (is_brackets_correct()) return false;
  return true;
}

bool Model::is_num(char symbol) noexcept {
  return symbol == '.' || (symbol >= '0' && symbol <= '9');
}

bool Model::is_func(char symbol) noexcept {
  int result = symbol >= 'a' && symbol <= 'z';
  return result;
}

bool Model::is_sign(char symbol) noexcept {
  return (symbol >= '(' && symbol <= '+') || symbol == '-' || symbol == '/' ||
         symbol == '^';
}

void Model::clear_data() noexcept {
  leksems_.clear();
  output_str_.clear();
  stack_.clear();
}

std::string Model::double_to_string(double num) noexcept {
  char *tmp = (char *)calloc(50, sizeof(char));
  sprintf(tmp, "%.8lf", num);
  for (char *ptr = (tmp + 48); ptr - tmp > 0; ptr--) {
    if (*ptr == '\0' || *ptr == '0') {
      *ptr = '\0';
    } else if (*ptr == '.' || *ptr == ',') {
      *ptr = '\0';
      ptr = tmp;
    } else {
      ptr = tmp;
    }
  }

  std::string result = std::string(tmp);
  free(tmp);
  return result;
}

Model::leksem::leksem(double num)
    : value("num"), priority(-1), num(num), visibility(true) {}
Model::leksem::leksem(std::string value, int priority)
    : value(value), priority(priority), visibility(true) {}
Model::leksem::leksem(std::string value, int priority, bool visibility)
    : value(value), priority(priority), visibility(visibility) {}
Model::leksem::leksem(const leksem &other)
    : value(other.value),
      priority(other.priority),
      num(other.num),
      visibility(other.visibility) {}

Model::leksem::leksem(leksem &&other) noexcept {
  value = std::move(other.value);
  priority = other.priority;
  num = other.num;
  visibility = other.visibility;
}
Model::leksem Model::leksem::operator=(leksem const &other) {
  value = other.value;
  priority = other.priority;
  num = other.num;
  visibility = other.visibility;
  return *this;
}

void Model::leksem::translate_double_in_value() noexcept { num = stod(value); }

int Model::leksem::operator*() noexcept { return priority; }
}  // namespace s21
