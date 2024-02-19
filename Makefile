CC = gcc
TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
FLAGS = -Wall -Werror -Wextra -std=c11
SOURCES = matrix_arithmetic.c  matrix_core.c  matrix_support.c
DOCKER_VERSION = 1.0.0

all: clean test

test: clean custom_matrix.a
	$(CC) $(CFLAGS) tests/*.c custom_matrix.a $(TEST_LIBS) -o test
	./test
	rm -rf *.o tests/*.o

custom_matrix.a:
	for source in $(SOURCES); do \
		$(CC) -c $(CFLAGS) functions/$$source -o functions/$${source%.c}.o; \
	done
	ar rcs custom_matrix.a functions/*.o

gcov_flag:
	$(eval CFLAGS += -fprofile-arcs -ftest-coverage)

gcov_report: clean gcov_flag test
	gcov $(SOURCES)
	rm -rf html_report
	gcov -b *.c 
	lcov -d . -c -o coverage.info
	genhtml -o html_report coverage.info

clang:
	cp ../materials/linters/.clang-format ../src
	clang-format -i *.h *.c
	rm -rf .clang-format

style : 
	clang-format --style=google -i *.c *.h
	clang-format --style=google -i tests/*.c

test_leaks: test
	leaks --atExit -- ./test

docker:
	docker build -t ubuntu_test_matrix:$(DOCKER_VERSION) .
	docker run --rm -it ubuntu_test_matrix:$(DOCKER_VERSION)

clean : 
	rm -f *.out functions/*.o functions/*.gcda functions/*.gcno custom_matrix.a test *.gcda *.gcno *.info
	rm -rf html_report
