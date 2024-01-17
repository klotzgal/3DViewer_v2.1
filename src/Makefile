.PHONY: all install uninstall dvi dist test gcov_report valgrind_check style_check format_style fonts clean fclean
TARGET = 3DViewer

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
OS = $(shell uname)
MODULES = $(wildcard modules/*.c)
OBJECTS = $(patsubst %.cc, %.o, $(MODULES))
TEST_MODUlES = test_modules

ifeq ($(OS), Linux)
	LDLIBS = -lcheck_pic -pthread -lrt -lm -lsubunit
else
	LDLIBS = -lcheck -lm
endif

all: clean #install

%.o: %.c
	mkdir -p obj
	$(CC) -c $(CFLAGS) $< $(LDLIBS) -o $(patsubst modules%, obj%, $@)

install:
	@echo "Start installation"
	@mkdir -p ../release-build
	@cmake -B ../release-build -S . && make -C ../release-build
	@cp -R ../release-build/bin/$(TARGET)* ~/Desktop
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃     The project is located in the       ┃"
	@echo "┃    build folder and on the desktop.     ┃"
	@echo "┗=========================================┛"

uninstall:
	@rm -rf ~/Desktop/$(TARGET)* ../release-build
	@echo "Uninstall completed successfully"

dvi:
	@open ../README_RUS.md

dist:
	@mkdir -p ../dist
	@cp -R ../release-build/bin/$(TARGET)* ../dist
# @cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET)_v2.0.tgz *
	@cd ../dist && rm -rf $(TARGET)* README.md README_RUS.md
	@echo "The build was successfully archived"

test:
ifeq ("", "$(wildcard ../release-build)")
	@mkdir ../release-build
	@cmake -B ../release-build -S . && make -C ../release-build
endif
	@echo "» Unit test results:"
	@ctest --output-on-failure --test-dir ../release-build

gcov_report: $(OBJECTS)
	@echo "┏=========================================┓"
	@echo "┃     Generating your html report ...     ┃"
	@echo "┗=========================================┛"
	@$(CC) --coverage $(CFLAGS) ./tests/unit_tests.c $(LDLIBS) ./modules/*.c -o ./tests/$(TEST_MODUlES)
	@./tests/$(TEST_MODUlES)
	@mkdir -p tests/modules_gcov
	@mv *.gcno ./tests/modules_gcov/ && mv *.gcda ./tests/modules_gcov/
	@lcov -t "test_coverage" -o test_coverage.info -c -d .
	@genhtml -o report test_coverage.info
	@open report/index.html
	@rm -rf *.gcda *.gcno report/test_coverage.info tests/modules_gcov

style_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -n **/*.cc **/*.h 
	@rm ./.clang-format

format_style:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -i **/*.cc **/*.h
	@rm ./.clang-format

valgrind_check: test
	@CK_FORK=no valgrind --vgdb=no --leak-check=full \
	--show-leak-kinds=all --track-origins=yes --log-file="unit_tests_vg.log" -v --verbose -q --quiet -s tests/$(TEST_MODUlES)
	@echo "┏=========================================┓"
	@echo "┃        Valgrind check is over           ┃"
	@echo "┃       logs have been generated          ┃"
	@echo "┗=========================================┛"

clean:
	@rm -rf tests/logs/*.log tests/$(TEST_MODUlES) *.dSYM **/*.dSYM report test_coverage.info
	@cmake --build ../build/ --target clean

fclean: clean
	@rm -rf ../build ../dist ~/Desktop/$(TARGET).app unit_tests_vg.log 

cmake:
	@mkdir -p ../build
	@cmake -B ../build -S ..  && make -C ../build && ./../build/bin/main

valgrind:
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=valgrind.txt ./../build/bin/main
