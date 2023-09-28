CFLAGS=-std=c++17 -Wall -Werror -Wshadow -Wextra

OS = $(shell uname)

ifeq ($(OS), Darwin)
	CHKFLAGS = -lm -lgtest -lgtest_main -lpthread
	LK = leaks --atExit -- ./test.out
	PRINT = open
else
	CHKFLAGS = -lgtest -lgtest_main -pthread
	LK = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test.out
	PRINT = xdg-open
endif


all: clean run

install:
	# mkdir -p build
	qmake6 front/Calculator.pro -o build/
	cd build; make
	cd ../
	mkdir -p app
	cp -r build/Calculator.app app/

run: install
	ifeq ($(OS), Darwin)
		./app/Calculator.app/Contents/MacOS/Calculator
	else

	endif

uninstall:
	@rm -rf app

tests:
	g++ $(CFLAGS) tests.cc model/model.cc $(CHKFLAGS) -o tests.out
	./tests.out

dvi: 
	open documentation.html

gcov_report:
	g++ $(CFLAGS) --coverage model/model.cc -c -o model_coverage.o
	g++ $(CFLAGS) --coverage tests.cc -c -o tests_coverage.o
	g++ $(CFLAGS) model_coverage.o  tests_coverage.o -o $@ $(CHKFLAGS)  -lgcov
	./$@
	@mkdir -p report
	@gcovr --html --html-details -o ./report/report.html
	@$(PRINT) ./report/report.html

dist:
	mkdir -p SmartCalcV2
	cp -r front SmartCalcV2
	cp -r model SmartCalcV2
	cp Makefile SmartCalcV2
	cp calc_test.c SmartCalcV2
	cp documentation.html SmartCalcV2
	tar -czf SmartCalcV2.tar SmartCalcV2
	rm -rf SmartCalcV2

clean:
	@rm -rf *.a *.o *.out tests gcov_report *.gcda *.gcno *.tar
	@rm -rf build
	@rm -rf report

style:
	@cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config model/*.* controller/*.*
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -style=google -i model/*.cc
	@clang-format -style=google -i model/*.h
	@clang-format -style=google -i front/*.cc
	@clang-format -style=google -i front/*.h
	@clang-format -style=google -i tests.cc
	clang-format -style=google -n model/*.h
	clang-format -style=google -n front/*.cc
	clang-format -style=google -n front/*.h
	clang-format -style=google -n tests.cc

	@rm -rf .clang-format

leaks:
	g++ $(CFLAGS) tests.cc model/model.cc $(CHKFLAGS) -o tests.out
	$(LK)