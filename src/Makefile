TARGET = SmartCalc_v1
CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11 
TEST = test.c
LIBRARY = SmartCalc_v1.a
SMART=-L. SmartCalc_v1.a
SRC = $(wildcard  *.c) 
OBJ = $(patsubst %.c, %.o, $(SRC))
CHECK:=$(shell pkg-config --cflags --libs check)

OS:=$(shell uname -s)
ifeq ($(OS), Darwin)
      TEST_FLAGS = -lcheck -lm
else
      TEST_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
endif


all: $(LIBRARY)

$(LIBRARY): $(SRC)
	$(CC) $(FLAGS) -c $(SRC)
	ar rc $(LIBRARY) $(OBJ)
	ranlib $(LIBRARY) 
	rm -f $(OBJ)

$(TARGET) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(TARGET)


%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

	
test : $(LIBRARY)
	$(CC) $(FLAGS) --coverage $(TEST) $(TEST_FLAGS) $(LIBRARY) -o test
	./test

install:
	cd calculator && qmake && make && make clean
	mkdir ../build
	cp -r calculator/calculator ../build/
	cp -r calculator/calculator.app ~/Desktop

uninstall:
	rm -rf calculator/calculator.app
	rm -rf ~/Desktop/calculator.app
	rm -rf calculator/calculator
	rm -rf ../build
	
dvi:
	open dvi.html

dist:
	mkdir archiv
	cp -r *.c *.h Makefile calculator/ archiv
	tar -cvzf calculator.tar.gz archiv
	rm -rf archiv

gcov_report: clean $(LIBRARY)
	$(CC) $(FLAGS) --coverage $(TEST) $(TEST_FLAGS) parser.c stack.c smartcalc.c -o test $(SMART)
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf *.o *.gcno *.gcda test test.info *.out report *.a
	rm -rf calculator.tar.gz
	
style:
	clang-format -style=google -i *.c calculator/*.cpp
	clang-format -style=google -i *.h calculator/*.h
	clang-format -style=google -n *.c calculator/*.cpp
	clang-format -style=google -n *.h calculator/*.h
