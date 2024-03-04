.PHONY: all install uninstall dvi dist test style_check format_style valgrind clean fclean
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
	@open ../../README.md

dist:
ifeq ("", "$(wildcard ../release-build)")
	@mkdir ../release-build
	@cmake -B ../release-build -S . && make -C ../release-build
endif
	@mkdir -p ../dist
	@cd ../dist && tar cvzf $(TARGET)_v2.0.tgz ../release-build/bin/$(TARGET)*
	@echo "The build was successfully archived"

test:
ifeq ("", "$(wildcard ../release-build)")
	@mkdir ../release-build
	@cmake -B ../release-build -S . && make -C ../release-build
endif
	@echo "» Unit test results:"
	@ctest --output-on-failure --test-dir ../release-build

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

valgrind: ../release-build/bin/3DViewer
	@CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=valgrind.txt ./../release-build/bin/3DViewer
	@echo "┏=========================================┓"
	@echo "┃        Valgrind check is over           ┃"
	@echo "┃       logs have been generated          ┃"
	@echo "┗=========================================┛"

clean:
	@rm -rf tests/logs/*.log tests/$(TEST_MODUlES) *.dSYM **/*.dSYM report test_coverage.info
	@cmake --build ../build/ --target clean

fclean: clean
	@rm -rf ../build ../dist ~/Desktop/$(TARGET).app unit_tests_vg.log 
