CC = g++ #-g
FLAGS = -Wall -Werror -Wextra --std=c++17 #-pedantic -fsanitize=address
FLAGS_COV = -lgtest -pthread -lgcov -fprofile-arcs -ftest-coverage
OPEN_FILE = open ../build/calculator.app

.PHONY: all
all: install

.PHONY: install
install:
	cd ../build && cmake ../src/. && make
	./../build/calculator

.PHONY: uninstall
uninstall:
	rm -fr ../build/* ../build/.qt .cmake .qtc_clangd

.PHONY: dist
dist:
	zip -r ../../smartcalc2.zip ../../CPP3_SmartCalc_v2.0-2

.PHONY: dvi
dvi:
	doxygen Doxyfile && open ./html/index.html

.PHONY: lint
lint:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./model/* ./controller/* ./view/*
	rm .clang-format

.PHONY: gcov_report
gcov_report: tests
	lcov --no-external -o ./coverage.info -c -d .
	genhtml -o ./report ./coverage.info
	open ./report/index.html

.PHONY: tests
tests:
	$(CC) $(FLAGS) ./model/model.cpp ./tests/s21_model_test.cpp -o test $(FLAGS_COV)
	./test

.PHONY: clean
clean: uninstall
	rm -fr report test *.info *.gcda *.gcno smartcalc.tar.gz html latex app
