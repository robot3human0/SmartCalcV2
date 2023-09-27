CFLAGS=-std=c11 -Wall -Werror -Wshadow -Wextra

ifeq ($(shell uname), Linux)
	CHKFLAGS=-pthread -lcheck_pic -pthread -lrt -lm -lsubunit
else
	CHKFLAGS=-lcheck
endif

all: clean run

install:
	mkdir -p build
	qmake front/Calculator.pro -o build/
	cd build; make
	cd ../
	mkdir -p app
	cp -r build/Calculator.app app/

run: install
	./app/Calculator.app/Contents/MacOS/Calculator

uninstall:
	@rm -rf app

test:
	gcc $(CFLAGS) --coverage calc_test.c back/polka.c back/stack.c $(CHKFLAGS) 
	./a.out

dvi: 
	open documentation.html

gcov_report:
	gcc $(CFLAGS) --coverage back/polka.c -c -o polka_coverage.o
	gcc $(CFLAGS) --coverage back/stack.c -c -o stack_coverage.o
	gcc $(CFLAGS) --coverage calc_test.c -c -o test_coverage.o
	gcc $(CFLAGS) polka_coverage.o stack_coverage.o test_coverage.o -o $@ $(CHKFLAGS)  -lgcov
	./$@
	gcovr --html --html-details -o report.html
	open report.html

dist:
	mkdir -p SmartCalcV2
	cp -r front SmartCalcV2
	cp -r model SmartCalcV2
	cp -r controller SmartCalcV2
	cp Makefile SmartCalcV2
	cp calc_test.c SmartCalcV2
	cp documentation.html SmartCalcV2
	tar -czf SmartCalcV2.tar SmartCalcV2
	rm -rf SmartCalcV2

clean:
	@rm -rf *.a *.o *.out tests gcov_report *.gcda *.gcno *.tar Smartcalc
	@rm -rf report.css report.calc_test.* report.functions.html report.html report.polka.c.* report.stack.c.*
	@rm -rf build

style:
	@cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config model/*.* controller/*.*
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -style=google -n model/*.cc
	clang-format -style=google -n model/*.h
	clang-format -style=google -n controller/*.cc
	clang-format -style=google -n controller/*.h
	clang-format -style=google -n front/*.cpp
	clang-format -style=google -n front/*.h
	@rm -rf .clang-format
