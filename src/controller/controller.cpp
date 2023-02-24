#include "controller.h"

namespace s21 {

Controller::Controller(const std::string str, double value_x)
    : model_(new s21::Model(str, value_x)){};

Controller::Controller(const std::string str) : model_(new s21::Model(str)){};

Controller::Controller(const Controller &other) : model_(other.model_){};

Controller::Controller(Controller &&other) : model_(std::move(other.model_)){};

Controller::~Controller() { delete model_; }

std::string Controller::express_answer() noexcept {
  return model_->express_answer();
}

std::string Controller::get_result_exp() noexcept {
  return model_->get_result_exp();
}

double Controller::solution_without_checks() noexcept {
  return model_->solution_without_checks();
}

Controller Controller::operator=(const Controller &other) noexcept {
  delete model_;
  model_ = other.model_;
  return *this;
}

Controller Controller::operator=(Controller &&other) noexcept {
  delete model_;
  model_ = std::move(other.model_);
  return *this;
}

void Controller::set_x(double num) noexcept { model_->set_x(num); }

bool Controller::is_valid_for_graph() { return model_->is_valid_for_graph(); }

}  // namespace s21
