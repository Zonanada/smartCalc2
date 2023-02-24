#include "../model/model.h"

#include <gtest/gtest.h>

TEST(constructor_first, constructor_first_true) {
  s21::Model model("15.4+16.7*4.532mod5");
  ASSERT_EQ(model.express_answer(), "15.4+16.7*4.532mod5=16.0844");
  ASSERT_EQ(model.get_result_exp(), "16.0844");
}

TEST(constructor_second, constructor_second_true) {
  s21::Model model("sin(cos(X25", 0.5);
  ASSERT_EQ(model.express_answer(), "sin(cos(0.5*25))=0.84027935");
  ASSERT_EQ(model.get_result_exp(), "0.84027935");
}

TEST(constructor_copy, constructor_copy_true) {
  s21::Model model("cos(sin(X", 1.23);
  s21::Model copy(model);
  ASSERT_EQ(model.get_input(), copy.get_input());
  ASSERT_EQ(model.get_x(), copy.get_x());
}

TEST(constructor_moving, constructor_movin_true) {
  s21::Model model("cos(sin(X", 1.23);
  s21::Model copy = std::move(model);
  ASSERT_EQ(model.get_input(), "");
  ASSERT_EQ(copy.get_input(), "cos(sin(X");
}

TEST(operator_copy, operator_copy_true) {
  s21::Model model("cos(sin(X");
  s21::Model copy("1+1");
  model.set_x(15.5);
  copy = model;
  ASSERT_EQ(model.get_input(), copy.get_input());
  ASSERT_EQ(model.get_x(), copy.get_x());
}

TEST(operator_moving, operator_moving_true) {
  s21::Model model("cos(sin(X", 1.23);
  s21::Model copy("1+1");
  copy = std::move(model);
  ASSERT_EQ(model.get_input(), "");
  ASSERT_EQ(copy.get_input(), "cos(sin(X");
}

TEST(validity, validity_false) {
  s21::Model model("1+2-4*+", 1.23);
  ASSERT_EQ(model.express_answer(), "error");
}

TEST(validity_2, validity_false) {
  s21::Model model("asin(2)", 1.23);
  ASSERT_EQ(model.express_answer(), "error");
}

TEST(validity_3, validity_false) {
  s21::Model model("sin(-2-3", 1.23);
  ASSERT_EQ(model.express_answer(), "sin(-2-3)=0.95892427");
}

TEST(validity_4, validity_false) {
  s21::Model model("atan(-", 1.23);
  ASSERT_EQ(model.express_answer(), "");
}

TEST(validity_5, validity_false) {
  s21::Model model("sqrt(-+", 1.23);
  ASSERT_EQ(model.express_answer(), "error");
}

TEST(validity_6, validity_false) {
  s21::Model model("4*/", 1.23);
  ASSERT_EQ(model.express_answer(), "error");
}

TEST(validity_7, validity_false) {
  s21::Model model("tan(1))", 1.23);
  ASSERT_EQ(model.express_answer(), "error");
}

TEST(validity_8, validity_false) {
  s21::Model model("4^+", 1.23);
  ASSERT_EQ(model.express_answer(), "error");
}

TEST(validity_9, validity_false) {
  s21::Model model("67/(*4)", 1.23);
  ASSERT_EQ(model.express_answer(), "error");
}

TEST(validity_10, validity_false) {
  s21::Model model("2.4.+3", 1.23);
  ASSERT_EQ(model.express_answer(), "error");
}

TEST(parse, parse_true) {
  s21::Model model(".+3");
  ASSERT_EQ(model.express_answer(), ".0+3=3");
}

TEST(correct_answer, correct_answer_true) {
  s21::Model model("atan(0.5");
  ASSERT_NEAR(model.solution_without_checks(), 0.463647609, 1e-7);
}

TEST(correct_answer_2, correct_answer_true) {
  s21::Model model("sqrt(16");
  ASSERT_NEAR(model.solution_without_checks(), 4, 1e-7);
}

TEST(correct_answer_3, correct_answer_true) {
  s21::Model model("^)");
  ASSERT_EQ(model.express_answer(), "error");
}

TEST(correct_answer_4, correct_answer_true) {
  s21::Model model("-X+3", -2);
  ASSERT_EQ(model.express_answer(), "--2+3=5");
}

TEST(correct_answer_5, correct_answer_true) {
  s21::Model model("-2+-2");
  ASSERT_EQ(model.express_answer(), "-2+-2=-4");
}

TEST(correct_answer_6, correct_answer_true) {
  s21::Model model("-sqrt(-X)", -2);
  ASSERT_EQ(model.express_answer(), "-sqrt(--2)=-1.41421356");
}

TEST(correct_answer_7, correct_answer_true) {
  s21::Model model("3..+2", -2);
  ASSERT_EQ(model.express_answer(), "error");
}

TEST(correct_answer_8, correct_answer_true) {
  s21::Model model("sin(.");
  ASSERT_EQ(model.express_answer(), "sin(.0)=0");
}

TEST(correct_answer_9, correct_answer_true) {
  s21::Model model("-");
  ASSERT_EQ(model.express_answer(), "");
}


TEST(solution_without_checks, solution_without_checks_true) {
  s21::Model model("cos(sin(X", 1.23);
  ASSERT_NEAR(model.solution_without_checks(), 0.58777634833, 1e-7);
}

TEST(valid_graph, valid_graph_false) {
  s21::Model model("cos(sin-))");
  ASSERT_FALSE(model.is_valid_for_graph());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
