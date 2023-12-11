# PROJECT
# CPP SMARTCALC v2.0-0

# SOURCE, OBJECT AND TEST FILES / FOLDERS
TEST_FOLDER    = tests
TEST_OUTPUT    = test
TEST_PRE_H     = 
SOURCE_FOLDER  = cpp31
TARGET 		   = build/calc
CLANG_FOLDER   = ../materials/linters/.clang-format
DOXYGEN_FOLDER = $(SOURCE_FOLDER)/doxygen
TAR 		   = calc.tar.gz

# Gcpp SETTINGS
COMPILATOR     = g++ -g
FLAGS_BASIC    = -Wall -Wextra -Werror --std=c++17 -pedantic
FLAGS_EXTRA    = $(FLAGS_BASIC) -fsanitize=address,undefined,leak
FLAGS_COV      = -lgtest -lgtest_main -coverage
BUILD_CALC_FOLDER = $(SOURCE_FOLDER)/qt/build-calc-Desktop_x86_darwin_generic_mach_o_64bit-Debug

# FILETYPES FOR CLEAN AND FCLEAN TARGETS
GCOV_INFO      = gcov_report.info
GCOV_FOLDER    = report
VALGRIND_LOG   = _valgrind-out.txt
TMP_FILES      = $(GCOV_INFO) *.gcda *.gcno *.gcda $(TEST_FOLDER)/*.gcno $(TEST_FOLDER)/*.gch *.gcov *.out $(TEST_OUTPUT).dSYM ./$(TEST_OUTPUT) $(DOXYGEN_FOLDER)/html
REST_FILES     = $(GCOV_FOLDER) $(VALGRIND_LOG) $(BUILD_CALC_FOLDER) $(TAR)

QT_TMP         = ./build
QT_SOURCE      = $(SOURCE_FOLDER)/qt/calc

.PHONY: all
all: install ## install and run program
	$(TARGET)

.PHONY: install
install: ## generate Makefile from cmake and run it to create executable
	cmake -S $(QT_SOURCE) -B ./build && cd ./build && make

.PHONY: uninstall
uninstall: ## remove files: cmake generated
	rm -rf $(QT_TMP)

.PHONY: clean
clean:
	rm -rf $(TMP_FILES) $(QT_TMP)

.PHONY: fclean
fclean: clean
	rm -rf $(REST_FILES)

.PHONY: dvi
dvi: ## generate and open doc
	cd $(DOXYGEN_FOLDER) && ./doxygen Doxyfile && open html/index.html

.PHONY: gcov
gcov: tests
	lcov -t "gcov_report" -o $(GCOV_INFO) -c -d . --no-external && \
	genhtml -o $(GCOV_FOLDER) $(GCOV_INFO);
	$(MAKE) clean
	open $(GCOV_FOLDER)/index.html

.PHONY: dist
dist:
	rm -rf $(BUILD_CALC_FOLDER)
	tar -zcf $(TAR) ./$(SOURCE_FOLDER) Makefile

.PHONY: tests
tests:
	$(MAKE) clean
	$(COMPILATOR) $(TEST_FOLDER)/test_all_calc.cc $(QT_SOURCE)/calcmodel.cc $(QT_SOURCE)/depositmodel.cc $(QT_SOURCE)/creditmodel.cc -o $(TEST_OUTPUT) $(FLAGS_EXTRA) $(FLAGS_COV)
	./$(TEST_OUTPUT) 


.PHONY: lint
lint:
	cp $(CLANG_FOLDER) $(QT_SOURCE)/
	clang-format -n $(QT_SOURCE)/*.h
	clang-format -n $(QT_SOURCE)/*.cc
	rm -rf $(QT_SOURCE)/.clang-format
	cppcheck --enable=all --language=c++ --std=c++17 --suppress=missingIncludeSystem --suppress=unusedFunction $(QT_SOURCE)/*.h $(QT_SOURCE)/*.cc

.PHONY: format
format:
	cp $(CLANG_FOLDER) $(QT_SOURCE)/
	clang-format -i $(QT_SOURCE)/*.h
	clang-format -i $(QT_SOURCE)/*.cc
	rm -rf $(QT_SOURCE)/.clang-format

.PHONY: grind
grind: FLAGS_EXTRA = $(FLAGS_BASIC)
grind: fclean tests
	leaks -atExit -- $(TEST_OUTPUT)
	$(MAKE) clean
